#include "imagewidget.h"

#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

ImageWidget::ImageWidget(QWidget *parent)
    : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(nullptr),
    m_setting(nullptr),
    m_using_user_setting(false),
    m_mode(WgMode::Normal) {

  setScene(m_scene);

  // off smooth pixmap transform to disable blur when zoom in
  setRenderHint(QPainter::SmoothPixmapTransform, false);
}

/**
 * @brief ImageWidget::setSettings
 * @param setting
 */
void ImageWidget::setSettings(QSettings *setting) {
  if (setting == nullptr) {
    return;
  }

  if ((!m_using_user_setting) && (this->m_setting != nullptr)){
    delete this->m_setting;
  }

  this->m_setting = setting;
  m_using_user_setting = true;
}

void ImageWidget::removeSettings() {
  if ((m_using_user_setting) && (this->m_setting != nullptr)){
    this->m_setting = nullptr;
    m_using_user_setting = false;
  }
}

void ImageWidget::loadImage(const QString &filePath) {
  QImage image(filePath);
  if (image.isNull()) {
    qDebug() << "Failed to load image:" << filePath;
    return;
  }
  QPixmap pixmap = QPixmap::fromImage(image);
  if (!m_pixmapItem) {
    m_pixmapItem = m_scene->addPixmap(pixmap);
    // using FastTransformation to avoid blur image
    m_pixmapItem->setTransformationMode(Qt::FastTransformation);
  } else {
    m_pixmapItem->setPixmap(pixmap);
  }
  m_scene->setSceneRect(pixmap.rect());
  // fit image with current window size
  this->fitInView(m_pixmapItem->boundingRect(), Qt::KeepAspectRatio);
}

void ImageWidget::goIntoDrawRoiMode() {
  this->changeWgMode(WgMode::DrawROI);
}

void ImageWidget::mousePressEvent(QMouseEvent *event) {
  // custom handle mouse press event
  switch (event->button()) {
    case Qt::RightButton:
      if (this->rightMouseButtonPressed(event)) {
        return;
      }
      break;
    case Qt::LeftButton:
      if (this->leftMouseButtonPressed(event)) {
        return;
      }
      break;
  }

  QGraphicsView::mousePressEvent(event);
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {

  switch (m_mode) {
    case WgMode::Normal:

      break;
    case WgMode::DrawROI:
      {
        QPointF currentPos = mapToScene(event->pos());
        QRectF newRect(roi_start_pos, currentPos);
        // Chuẩn hóa lại rectangle để đảm bảo chiều rộng và chiều cao luôn dương
        newRect = newRect.normalized();
        temp_roi->setRect(newRect);
        return;
      }
    case WgMode::Pan:
      {
        QPoint delta = event->pos() - m_last_pan_point;
        if (!delta.isNull()) {
          this->horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
          this->verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
          m_last_pan_point = event->pos();
        }
      }
      break;
  }

  QGraphicsView::mouseMoveEvent(event);
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event) {
  // custom handle mouse release event
  switch (event->button()) {
    case Qt::RightButton:
      if (this->rightMouseButtonReleased(event)) {
        return;
      }
      break;
    case Qt::LeftButton:
      if (this->leftMouseButtonReleased(event)) {
        return;
      }
      break;
  }

  QGraphicsView::mouseReleaseEvent(event);
}

void ImageWidget::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event->button() == Qt::MiddleButton) {
    this->fitInView(m_pixmapItem->boundingRect(), Qt::KeepAspectRatio);
  }

  QGraphicsView::mouseDoubleClickEvent(event);
}

void ImageWidget::wheelEvent(QWheelEvent *event) {

  if (event->modifiers() & Qt::ControlModifier) {
    // Xác định hệ số zoom; nếu cuộn lên: phóng to; nếu cuộn xuống: thu nhỏ
    double angle = event->angleDelta().y();
    double factor = (angle > 0) ? 1.15 : 0.85;
    this->scale(factor, factor);
    return;
  }

  QGraphicsView::wheelEvent(event);
}

bool ImageWidget::rightMouseButtonPressed(QMouseEvent *event) {
  switch (this->m_mode) {
    case WgMode::Normal:
      {

      }
      break;
    case WgMode::DrawROI:
      {

      }
      break;
  }

  return false;
}

bool ImageWidget::leftMouseButtonPressed(QMouseEvent *event) {
  switch (this->m_mode) {
    case WgMode::Normal:
    {
      // widget switch to pan mode
      this->changeWgMode(WgMode::Pan);
      m_last_pan_point = event->pos();
    }
    break;
    case WgMode::DrawROI:
    {
      roi_start_pos = mapToScene(event->pos());
      temp_roi = new QGraphicsRectItem();
      temp_roi->setPen(QPen(Qt::red, 2, Qt::DashLine));
      temp_roi->setBrush(QBrush(Qt::transparent));
      temp_roi->setRect(QRectF(roi_start_pos, QSizeF(0, 0)));
      if (scene()) {
        scene()->addItem(temp_roi);
      }
      return true;
    }
    break;
  }

  return false;
}

bool ImageWidget::rightMouseButtonReleased(QMouseEvent *event) {
  switch (this->m_mode) {
    case WgMode::Normal:
    {
      // show selection menu
      QMenu contextMenu;
      QAction *loadImageAction = contextMenu.addAction("Load Image");
      QAction *addROIAction = contextMenu.addAction("Add ROI");
      QAction *selectedAction = contextMenu.exec(event->globalPos());

      if (selectedAction == loadImageAction) {
        qDebug() << "ImageWidget: User choose load image from mouse event.";
        userChooseLoadImage();
      } else if (selectedAction == addROIAction) {
        qDebug() << "ImageWidget: User choose add ROI from mouse event.";
        goIntoDrawRoiMode();
      }
    }
    break;
    case WgMode::DrawROI:
    {

    }
    break;
  }

  return false;
}

bool ImageWidget::leftMouseButtonReleased(QMouseEvent *event) {
  switch (this->m_mode) {
    case WgMode::Normal:
    {

    }
    break;
    case WgMode::DrawROI:
    {
      changeWgMode(WgMode::Normal);
      qDebug() << "ROI created:" << temp_roi->rect();
      temp_roi = nullptr;
      return true;
    }
    case WgMode::Pan:
    {
      m_last_pan_point = QPoint();
      changeWgMode(WgMode::Normal);
    }
    break;
  }

  return false;
}

void ImageWidget::userChooseLoadImage() {
  QString path = showSelectImagePathDialog();
  if (path.isEmpty()) {
    return;
  }

  loadImage(path);
}

QString ImageWidget::showSelectImagePathDialog() {
  if (m_setting == nullptr) {
    m_setting = new QSettings("DGB", "Image widget");
  }

  QString lastDirectory = m_setting->value("lastDirectory", "").toString();

  QString filePath = QFileDialog::getOpenFileName(this,
                                                  "Choose image",
                                                  lastDirectory,
                                                  "Image Files (*.png *.jpg *.jpeg *.bmp)");

  if (!filePath.isEmpty()) {
    QString directory = QFileInfo(filePath).absolutePath();
    m_setting->setValue("lastDirectory", directory);
  }

  return filePath;
}

void ImageWidget::changeWgMode(WgMode mode) {
  if (this->m_mode == mode) {
    return;
  }

  this->m_previous_mode = this->m_mode;
  this->m_mode = mode;

  switch (mode) {
    case WgMode::Normal:
      this->setCursor(Qt::ArrowCursor);
      qDebug() << "Image widget change mode: NORMAL mode.";
      break;
    case WgMode::DrawROI:
      this->setCursor(Qt::CrossCursor);
      qDebug() << "Image widget change mode: DRAW ROI mode.";
      break;
    case WgMode::Pan:
      this->setCursor(Qt::ClosedHandCursor);
      qDebug() << "Image widget change mode: PAN mode.";
      break;
  }
}
