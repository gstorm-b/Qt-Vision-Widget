#include "image_view_only.h"

#include <QFileDialog>
#include <QMenu>

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QScrollBar>

#ifdef ENABLE_DEBUG_MODE
#define PRINT_DEBUG_INFO(msg)　qDebug() << msg
#else
#define PRINT_DEBUG_INFO(msg) //
#endif

ImageViewOnly::ImageViewOnly(QWidget *parent)
    : QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(nullptr),
    m_setting(nullptr),
    m_using_user_setting(false),
    m_current_mode(IModeNone),
    m_previous_mode(IModeNone),
    m_scene_interacting(false),
    m_has_panned(false),
    m_roi_started(false) {

  this->setScene(m_scene);

  QBrush brush(QColor(0x9c988f));
  this->setBackgroundBrush(brush);

  // set view port update mode to avoid ghosting
  this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  // off smooth pixmap transform to disable blur when zoom in
  this->setRenderHint(QPainter::SmoothPixmapTransform, false);
}

ImageViewOnly::~ImageViewOnly() {
  // delete m_pixmapItem;
}

void ImageViewOnly::setSettings(QSettings *setting) {
  if (setting == nullptr) {
    return;
  }

  if ((!m_using_user_setting) && (this->m_setting != nullptr)){
    delete this->m_setting;
  }

  this->m_setting = setting;
  m_using_user_setting = true;
}

void ImageViewOnly::removeSettings() {
  if ((m_using_user_setting) && (this->m_setting != nullptr)){
    this->m_setting = nullptr;
    m_using_user_setting = false;
  }
}

QPixmap ImageViewOnly::getImage() {
  return m_pixmapItem->pixmap();
}


void ImageViewOnly::loadImage(const QString &filePath) {
  QImage image(filePath);
  if (image.isNull()) {
    PRINT_DEBUG_INFO("Failed to load image:" << filePath);
    return;
  }

  QPixmap pixmap = QPixmap::fromImage(image);
  if (!m_pixmapItem) {
    createPixmapItem(pixmap);
    // using FastTransformation to avoid blur image
    m_pixmapItem->setTransformationMode(Qt::FastTransformation);
  } else {
    m_pixmapItem->setPixmap(pixmap);
  }

  m_scene->setSceneRect(pixmap.rect().adjusted(-15, -15, 10, 10));
  // fit image with current window size
  m_pixmap_bounding_rect = m_pixmapItem->boundingRect();
  this->fitInView(m_pixmap_bounding_rect, Qt::KeepAspectRatio);
}

void ImageViewOnly::loadImage(QPixmap &pixmap) {
  if (!m_pixmapItem) {
    createPixmapItem(pixmap);
    // using FastTransformation to avoid blur image
    m_pixmapItem->setTransformationMode(Qt::FastTransformation);
  } else {
    m_pixmapItem->setPixmap(pixmap);
  }

  m_scene->setSceneRect(pixmap.rect().adjusted(-10, -10, 10, 10));
  // fit image with current window size
  m_pixmap_bounding_rect = m_pixmapItem->boundingRect();
  this->fitInView(m_pixmap_bounding_rect, Qt::KeepAspectRatio);
}

void ImageViewOnly::removeImage() {
  if (!hadImage()) {
    PRINT_DEBUG_INFO("[IMG ROI Widget] Remove failed, image empty.");
    return;
  }

  m_scene->removeItem(m_pixmapItem);
  delete m_pixmapItem;
  m_pixmapItem = nullptr;
  this->fitInView(m_pixmap_bounding_rect, Qt::KeepAspectRatio);
}

void ImageViewOnly::mousePressEvent(QMouseEvent *event) {
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
    default:
      break;
  }

  QGraphicsView::mousePressEvent(event);
}

void ImageViewOnly::mouseMoveEvent(QMouseEvent *event) {
  switch (m_current_mode) {
    case IModeNone:

      break;
    case IModeZoom:

      break;
    case IModePan:
    {
      m_has_panned = true;
      QPoint delta = event->pos() - m_last_pan_point;
      if (!delta.isNull()) {
        this->horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() - delta.x());
        this->verticalScrollBar()->setValue(
            verticalScrollBar()->value() - delta.y());
        m_last_pan_point = event->pos();
      }
    }
    break;
  }

  QGraphicsView::mouseMoveEvent(event);
}

void ImageViewOnly::mouseReleaseEvent(QMouseEvent *event) {
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
    default:
      break;
  }

  QGraphicsView::mouseReleaseEvent(event);
}

void ImageViewOnly::mouseDoubleClickEvent(QMouseEvent *event) {
  switch (event->button()) {
    case Qt::MiddleButton:
      if (m_current_mode == IModeNone) {
        this->fitInView(m_pixmap_bounding_rect, Qt::KeepAspectRatio);
      }
      break;
    default:
      break;
  }

  QGraphicsView::mouseDoubleClickEvent(event);
}

void ImageViewOnly::wheelEvent(QWheelEvent *event) {
  if (event->modifiers() & Qt::ControlModifier) {
    changeInteractMode(IModeZoom);
    double angle = event->angleDelta().y();
    double factor = (angle > 0) ? 1.15 : 0.85;
    this->scale(factor, factor);
    backToPreviousMode();
    return;
  }

  QGraphicsView::wheelEvent(event);
}

void ImageViewOnly::keyPressEvent(QKeyEvent *event) {

  QGraphicsView::keyPressEvent(event);
}

void ImageViewOnly::keyReleaseEvent(QKeyEvent *event) {
  if ((event->key() == Qt::Key_Control) && (m_current_mode == IModePan)) {
    m_last_pan_point = QPoint();
    // this->setCursor(Qt::ArrowCursor);
    changeInteractMode(IModeNone);
    event->accept();
    // return;
  }

  QGraphicsView::keyReleaseEvent(event);
}

void ImageViewOnly::changeInteractMode(InteractMode mode) {
  if (mode != m_current_mode) {
    m_previous_mode = m_current_mode;
    m_current_mode = mode;
    changeCursor();
    m_scene_interacting = (m_current_mode != IModeNone) ? true : false;

    // PRINT_DEBUG_INFO("[IMG ROI Widget] Chang mode:"
    //          << interactMode2String(m_previous_mode)
    //          << ">>"
    //          << interactMode2String(m_current_mode));
  }
}

void ImageViewOnly::backToPreviousMode() {
  if (m_previous_mode == m_current_mode) {
    return;
  }

  InteractMode temp_mode = m_current_mode;
  m_current_mode = m_previous_mode;
  m_previous_mode = temp_mode;
  changeCursor();
  m_scene_interacting = (m_current_mode != IModeNone) ? true : false;

  // PRINT_DEBUG_INFO("[IMG ROI Widget] Chang mode (back):"
  //          << interactMode2String(m_previous_mode)
  //          << ">>"
  //          << interactMode2String(m_current_mode));
}

void ImageViewOnly::changeCursor() {
  switch (m_current_mode) {
    case IModeNone:
      this->setCursor(Qt::ArrowCursor);
      break;
    case IModeZoom:

      break;
    case IModePan:
      this->setCursor(Qt::ClosedHandCursor);
      break;
  }
}

void ImageViewOnly::createPixmapItem(QPixmap &pixmap) {
  // m_pixmapItem = new PixmapBoundingLine(pixmap);
  m_pixmapItem = new QGraphicsPixmapItem(pixmap);
  // m_pixmapItem->setBorderLineWidth(4);
  // m_pixmapItem->setBorderColor(QColor(Qt::green));
  m_scene->addItem(m_pixmapItem);
}

bool ImageViewOnly::hadImage() {
  return (m_pixmapItem != nullptr);
}

QGraphicsPixmapItem* ImageViewOnly::getPixmapItem() {
  return m_pixmapItem;
}

QString ImageViewOnly::interactMode2String(InteractMode mode) {
  switch (mode) {
    case IModeNone:
      return "None";
    case IModeZoom:
      return "Zoom";
    case IModePan:
      return "Pan";
  }
  return "Unknown";
}

bool ImageViewOnly::rightMouseButtonPressed(QMouseEvent *event) {
  return false;
}

bool ImageViewOnly::leftMouseButtonPressed(QMouseEvent *event) {
  if ((event->modifiers() & Qt::ControlModifier) && (!m_roi_started)) {
    m_has_panned = false;
    m_last_pan_point = event->pos();
    changeInteractMode(IModePan);
    return false;
  }

  return false;
}

bool ImageViewOnly::rightMouseButtonReleased(QMouseEvent *event) {
  return false;
}

bool ImageViewOnly::leftMouseButtonReleased(QMouseEvent *event) {
  switch (m_current_mode) {
    case IModeNone:
    {

    }
    break;
    case IModeZoom:

      break;
    case IModePan:
    {
      m_last_pan_point = QPoint();
      backToPreviousMode();
      if (m_has_panned) {
        return true;
      } else {
        return false;
      }
    }
    break;
  }

  return false;
}
