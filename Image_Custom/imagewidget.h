#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QMouseEvent>
#include <QWheelEvent>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSettings>

#include <QPointF>

class ImageWidget : public QGraphicsView {
  Q_OBJECT

  public:
    enum WgMode {
      Normal,
      DrawROI,
      Pan
    };

    explicit ImageWidget(QWidget *parent = nullptr);
    void setSettings(QSettings *setting);
    void removeSettings();

  public slots:
    void loadImage(const QString &filePath);
    void goIntoDrawRoiMode();

  protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

  private:
    bool rightMouseButtonPressed(QMouseEvent *event);
    bool leftMouseButtonPressed(QMouseEvent *event);
    bool rightMouseButtonReleased(QMouseEvent *event);
    bool leftMouseButtonReleased(QMouseEvent *event);

    void userChooseLoadImage();
    QString showSelectImagePathDialog();

    void changeWgMode(WgMode mode);

  private:
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_pixmapItem;

    QSettings *m_setting;
    bool m_using_user_setting;

    WgMode m_mode;
    WgMode m_previous_mode;
    // const bool m_show_debug;

    QPointF roi_start_pos;
    QGraphicsRectItem *temp_roi;
    QPoint m_last_pan_point;
};

#endif // IMAGEWIDGET_H
