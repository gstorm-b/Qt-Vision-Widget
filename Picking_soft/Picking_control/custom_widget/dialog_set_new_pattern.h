#ifndef DIALOG_SET_NEW_PATTERN_H
#define DIALOG_SET_NEW_PATTERN_H

#include <QDialog>
#include <QWidget>
#include <QMap>

#include "custom_widget/image_widget.h"
#include "custom_widget/item_roi.h"
#include "custom_widget/item_picking_pos.h"
#include "custom_widget/item_gripper_box.h"

namespace Ui { class DialogSetNewPattern;
                class FormPatternCropImage;
                class FormPatternSetPickingPos;
                class FormPatternSetConditionalArea;
}

class DialogSetNewPattern : public QDialog {
  Q_OBJECT

public:
  explicit DialogSetNewPattern(QWidget *parent = nullptr);
  ~DialogSetNewPattern();

private:
  void btn_next_clicked();
  void btn_back_clicked();
  void btn_cancel_clicked();

  // Step 1
  void btn_form_choose_image_clicked();
  void btn_form_trigger_clicked();
  void btn_form_set_roi_clicked();
  void btn_form_clear_roi_clicked();
  void form_draw_crop_roi_finished(QGraphicsItem *roi, ImageWidget::ItemAddType typee);

  // Step 2
  void form_picking_pos_changed(QPointF point);
  void form_picking_angle_changed(qreal angle);
  void form_picking_pos_edited();
  void form_picking_angle_edited();

  // Step 3
  void form_condition_area_size_edited();
  void form_condition_area_angle_edited();
  void form_condition_area_distance_edited();

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  void set_current_step_wg();

private:
  Ui::DialogSetNewPattern *ui;
  Ui::FormPatternCropImage *form_crop_image;
  Ui::FormPatternSetPickingPos *form_picking_pos;
  Ui::FormPatternSetConditionalArea *form_conditional_area;

  QWidget *m_wg_crop_image;
  QWidget *m_wg_set_picking_pos;
  QWidget *m_wg_set_conditional_area;

  QMap<int, QWidget*> m_wg_map;
  QMap<int, QString> m_wg_title_map;
  int m_current_step;

  const int m_max_step = 3;
  // step 1 crop pattern
  bool m_has_image;
  ItemRoi *m_item_crop_roi{nullptr};
  QPixmap m_item_cropped_pixmap;
  // step 2 set picking position
  ItemPickingCenter *m_item_picking_center{nullptr};
  // sep 3 set conditional area
  ItemPickingCenter *m_item_picking_center_fixed{nullptr};
  ItemGripperBox *m_gripper_box{nullptr};
};

#endif // DIALOG_SET_NEW_PATTERN_H
