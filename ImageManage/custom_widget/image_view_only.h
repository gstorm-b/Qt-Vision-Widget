#ifndef IMAGE_VIEW_ONLY_H
#define IMAGE_VIEW_ONLY_H

#include <QMouseEvent>
#include <QWheelEvent>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSettings>
#include <QPointF>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QAction>


class ImageViewOnly : public QGraphicsView {
  Q_OBJECT

public:
  enum InteractMode {
    IModeNone,
    IModeZoom,
    IModePan
  };

  explicit ImageViewOnly(QWidget *parent = nullptr);
  ~ImageViewOnly();
  void setSettings(QSettings *setting);
  void removeSettings();
  QPixmap getImage();
  bool hadImage();
  QGraphicsPixmapItem* getPixmapItem();

public slots:
  void loadImage(const QString &filePath);
  void loadImage(QPixmap &pixmap);
  void removeImage();

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

private:
  void createPixmapItem(QPixmap &pixmap);

  void changeInteractMode(InteractMode mode);
  void backToPreviousMode();
  void changeCursor();
  QString interactMode2String(InteractMode mode);

  bool rightMouseButtonPressed(QMouseEvent *event);
  bool leftMouseButtonPressed(QMouseEvent *event);
  bool rightMouseButtonReleased(QMouseEvent *event);
  bool leftMouseButtonReleased(QMouseEvent *event);

private:
  QGraphicsScene *m_scene;
  QGraphicsPixmapItem  *m_pixmapItem;
  QRectF m_pixmap_bounding_rect;

  QSettings *m_setting;
  bool m_using_user_setting;

  InteractMode m_current_mode;
  InteractMode m_previous_mode;
  bool m_scene_interacting;

  bool m_has_panned;
  QPoint m_last_pan_point;

  bool m_roi_started;
  QGraphicsRectItem *m_temp_roi;
  QPointF m_roi_start_point;
};

#endif // IMAGE_VIEW_ONLY_H
