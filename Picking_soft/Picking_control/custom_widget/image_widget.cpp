#include "image_widget.h"

#include <QScrollBar>
#include <QDebug>
#include <QApplication>

ImageWidget::ImageWidget(QWidget *parent)
    : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixItem(nullptr),
    m_currentRect(nullptr),
    m_polygonPreview(nullptr) {
  setScene(m_scene);
  setRenderHint(QPainter::Antialiasing, true);
  setRenderHint(QPainter::SmoothPixmapTransform, true);
  setDragMode(QGraphicsView::NoDrag);
  setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

  // Smooth interaction defaults
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void ImageWidget::setPixmap(const QPixmap &pix)
{
  m_scene->clear();
  m_pixItem = m_scene->addPixmap(pix);
  m_pixItem->setZValue(0);
  m_scene->setSceneRect(m_pixItem->boundingRect());
  fitImage();
}

void ImageWidget::fitImage()
{
  if (!m_pixItem) return;
  fitInView(m_pixItem, Qt::KeepAspectRatio);
  m_zoomFactor = transform().m11(); // approximate
}

void ImageWidget::setInteractionMode(InteractionMode mode)
{
  cancelCurrentDrawing();
  m_mode = mode;
  // change cursor for UX
  if (m_mode == Navigate) setCursor(Qt::ArrowCursor);
  else if (m_mode == DrawRect) setCursor(Qt::CrossCursor);
  else if (m_mode == DrawPolygon) setCursor(Qt::CrossCursor);
}

void ImageWidget::cancelDrawing()
{
  cancelCurrentDrawing();
  emit drawingCanceled();
}

void ImageWidget::undoPolygonVertex()
{
  if (m_mode != DrawPolygon) return;
  if (!m_polygonPoints.isEmpty()) {
    m_polygonPoints.removeLast();
    updatePolygonPreview();
  }
}

QPointF ImageWidget::mapToSceneF(const QPoint &viewPoint) const
{
  return mapToScene(viewPoint);
}

// ---------- Mouse / wheel / key events ----------

void ImageWidget::wheelEvent(QWheelEvent *event)
{
  // Zoom when Ctrl is pressed OR when no modifier and user wants wheel zoom default.
  // Adjust to your preference.
  const bool ctrl = event->modifiers() & Qt::ControlModifier;
  if (ctrl) {
    const qreal delta = event->angleDelta().y();
    if (delta > 0) scaleView(m_zoomStep);
    else if (delta < 0) scaleView(1.0 / m_zoomStep);
    event->accept();
    return;
  }

  // otherwise pass to base class for normal behavior (scroll)
  QGraphicsView::wheelEvent(event);
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
  // Middle button pan
  if (event->button() == Qt::MiddleButton) {
    m_panning = true;
    m_lastPanPoint = event->pos();
    setCursor(Qt::ClosedHandCursor);
    event->accept();
    return;
  }

  // space + left drag -> pan (very common UX)
  if (event->button() == Qt::LeftButton && isSpacePanning()) {
    m_panning = true;
    m_lastPanPoint = event->pos();
    setCursor(Qt::ClosedHandCursor);
    event->accept();
    return;
  }

  // Interaction modes with left click
  if (event->button() == Qt::LeftButton) {
    QPointF scenePos = mapToSceneF(event->pos());
    if (m_mode == DrawRect) {
      startRect(scenePos);
      event->accept();
      return;
    } else if (m_mode == DrawPolygon) {
      // left click adds vertex
      addPolygonVertex(scenePos);
      event->accept();
      return;
    }
  }

  QGraphicsView::mousePressEvent(event);
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
  if (m_panning) {
    QPoint delta = event->pos() - m_lastPanPoint;
    m_lastPanPoint = event->pos();
    // move scrollbars (faster than manipulating transform directly)
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    return;
  }

  if (m_mode == DrawRect && m_currentRect) {
    QPointF scenePos = mapToSceneF(event->pos());
    updateRect(scenePos);
    return;
  }

  QGraphicsView::mouseMoveEvent(event);
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::MiddleButton) {
    m_panning = false;
    setCursor(isSpacePanning() ? Qt::OpenHandCursor : Qt::ArrowCursor);
    event->accept();
    return;
  }
  if (event->button() == Qt::LeftButton && m_panning) {
    // was space+left panning
    m_panning = false;
    setCursor(isSpacePanning() ? Qt::OpenHandCursor : Qt::ArrowCursor);
    event->accept();
    return;
  }

  if (event->button() == Qt::LeftButton) {
    if (m_mode == DrawRect && m_currentRect) {
      finishRect();
      event->accept();
      return;
    }
  }

  // right click can finish polygon
  if (event->button() == Qt::RightButton && m_mode == DrawPolygon && !m_polygonPoints.isEmpty()) {
    finishPolygon();
    event->accept();
    return;
  }

  QGraphicsView::mouseReleaseEvent(event);
}

void ImageWidget::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space) {
    m_spacePressed = true;
    if (!m_panning) setCursor(Qt::OpenHandCursor);
    event->accept();
    return;
  }

  // Finish polygon with Enter
  if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && m_mode == DrawPolygon) {
    if (!m_polygonPoints.isEmpty()) {
      finishPolygon();
      return;
    }
  }

  // Undo vertex with Backspace
  if (event->key() == Qt::Key_Backspace && m_mode == DrawPolygon) {
    undoPolygonVertex();
    return;
  }

  // Zoom by keys
  if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
    scaleView(m_zoomStep);
    return;
  }
  if (event->key() == Qt::Key_Minus) {
    scaleView(1.0 / m_zoomStep);
    return;
  }

  QGraphicsView::keyPressEvent(event);
}

void ImageWidget::keyReleaseEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Space) {
    m_spacePressed = false;
    if (!m_panning) setCursor(Qt::ArrowCursor);
    event->accept();
    return;
  }
  QGraphicsView::keyReleaseEvent(event);
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
  QGraphicsView::resizeEvent(event);
  // optional: keep fit-to-window when resizing (uncomment if desired)
  // fitImage();
}

// ---------- drawing helpers ----------

void ImageWidget::startRect(const QPointF &scenePos)
{
  cancelCurrentDrawing();
  m_rectStartScene = scenePos;
  m_currentRect = m_scene->addRect(QRectF(m_rectStartScene, QSizeF(0,0)));
  m_currentRect->setPen(QPen(Qt::red, 1.5));
  m_currentRect->setBrush(QBrush(QColor(255,0,0,30)));
  m_currentRect->setZValue(10);
}

void ImageWidget::updateRect(const QPointF &scenePos)
{
  if (!m_currentRect) return;
  QRectF r(m_rectStartScene, scenePos);
  r = r.normalized();
  m_currentRect->setRect(r);
}

void ImageWidget::finishRect()
{
  if (!m_currentRect) return;
  QRectF r = m_currentRect->rect();
  // Emit and keep item (or remove it, depending on design)
  // Here we keep the item but make it selectable.
  m_currentRect->setFlag(QGraphicsItem::ItemIsSelectable, true);
  m_currentRect->setFlag(QGraphicsItem::ItemIsMovable, true);
  m_currentRect->setZValue(5);
  emit roiRectFinished(r);
  m_currentRect = nullptr; // allow next rect creation
}

void ImageWidget::startPolygon(const QPointF &scenePos)
{
  cancelCurrentDrawing(); // ensure clean
  m_polygonPoints.clear();
  m_polygonPreview = m_scene->addPolygon(QPolygonF(), QPen(Qt::green, 1.5), QBrush(QColor(0,255,0,40)));
  m_polygonPreview->setZValue(10);
  addPolygonVertex(scenePos);
}

void ImageWidget::addPolygonVertex(const QPointF &scenePos)
{
  if (!m_polygonPreview) {
    startPolygon(scenePos);
    return;
  }
  m_polygonPoints.append(scenePos);
  updatePolygonPreview();
}

void ImageWidget::updatePolygonPreview()
{
  if (!m_polygonPreview) return;
  m_polygonPreview->setPolygon(m_polygonPoints);
}

void ImageWidget::finishPolygon()
{
  if (!m_polygonPreview) return;
  // Optionally close polygon if more than 2 points
  if (m_polygonPoints.size() >= 3) {
    QGraphicsPolygonItem *finalItem = new QGraphicsPolygonItem(m_polygonPoints);
    finalItem->setPen(QPen(Qt::blue, 1.5));
    finalItem->setBrush(QBrush(QColor(0,0,255,40)));
    finalItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    finalItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    finalItem->setZValue(5);
    m_scene->addItem(finalItem);
    emit polygonFinished(m_polygonPoints);
  }
  // remove preview
  m_scene->removeItem(m_polygonPreview);
  delete m_polygonPreview;
  m_polygonPreview = nullptr;
  m_polygonPoints.clear();
}

void ImageWidget::cancelCurrentDrawing()
{
  if (m_currentRect) {
    m_scene->removeItem(m_currentRect);
    delete m_currentRect;
    m_currentRect = nullptr;
  }
  if (m_polygonPreview) {
    m_scene->removeItem(m_polygonPreview);
    delete m_polygonPreview;
    m_polygonPreview = nullptr;
    m_polygonPoints.clear();
  }
}

void ImageWidget::scaleView(qreal factor)
{
  // constrain zoom
  qreal newScale = m_zoomFactor * factor;
  if (newScale < m_minZoom || newScale > m_maxZoom) return;
  scale(factor, factor);
  m_zoomFactor = newScale;
}
