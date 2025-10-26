#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>

class ImageWidget : public QGraphicsView {
  Q_OBJECT
public:
  enum InteractionMode { Navigate, DrawRect, DrawPolygon };
  Q_ENUM(InteractionMode)

  explicit ImageWidget(QWidget *parent = nullptr);
  ~ImageWidget() override = default;

  void setPixmap(const QPixmap &pix);
  void fitImage();
  void setInteractionMode(InteractionMode mode);
  InteractionMode interactionMode() const { return m_mode; }

public slots:
  void cancelDrawing();
  void undoPolygonVertex();

signals:
  void roiRectFinished(const QRectF &rect);       // scene coordinates
  void polygonFinished(const QPolygonF &poly);   // scene coordinates
  void drawingCanceled();

protected:
  // Events
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

private:
  // helpers
  QPointF mapToSceneF(const QPoint &viewPoint) const;
  void startRect(const QPointF &scenePos);
  void updateRect(const QPointF &scenePos);
  void finishRect();
  void startPolygon(const QPointF &scenePos);
  void addPolygonVertex(const QPointF &scenePos);
  void updatePolygonPreview();
  void finishPolygon();
  void cancelCurrentDrawing();

  // zoom/pan
  void scaleView(qreal factor);
  bool isSpacePanning() const { return m_spacePressed; }

private:
  QGraphicsScene *m_scene = nullptr;
  QGraphicsPixmapItem *m_pixItem = nullptr;

  // drawing rect
  QGraphicsRectItem *m_currentRect = nullptr;
  QPointF m_rectStartScene;

  // drawing polygon
  QGraphicsPolygonItem *m_polygonPreview = nullptr;
  QPolygonF m_polygonPoints;

  InteractionMode m_mode = Navigate;

  // state for panning
  bool m_panning = false;
  bool m_spacePressed = false;
  QPoint m_lastPanPoint;

  // zoom control
  qreal m_zoomFactor = 1.0;
  const qreal m_zoomStep = 1.15;
  const qreal m_maxZoom = 100;
  const qreal m_minZoom = 0.01;
};

#endif // IMAGE_WIDGET_H
