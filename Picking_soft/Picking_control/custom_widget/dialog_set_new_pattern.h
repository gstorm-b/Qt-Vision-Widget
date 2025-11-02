#ifndef DIALOG_SET_NEW_PATTERN_H
#define DIALOG_SET_NEW_PATTERN_H

#include <QDialog>
#include <QWidget>
#include <QMap>

#include "custom_widget/item_roi.h"

namespace Ui { class DialogSetNewPattern;
                class FormPatternCropImage;
                class FormPatternSetPickingPos;
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

  void btn_form_choose_image_clicked();
  void btn_form_trigger_clicked();
  void btn_form_set_roi_clicked();
  void btn_form_clear_roi_clicked();
  void form_draw_crop_roi_finished(ItemRoi *roi);

private:
  void set_current_step_wg();

private:
  Ui::DialogSetNewPattern *ui;
  Ui::FormPatternCropImage *form_crop_image;
  Ui::FormPatternSetPickingPos *form_picking_pos;

  QWidget *m_wg_crop_image;
  QWidget *m_wg_set_picking_pos;

  QMap<int, QWidget*> m_wg_map;
  QMap<int, QString> m_wg_title_map;
  int m_current_step;

  // step 1
  bool m_has_image;
  ItemRoi *m_item_crop_roi{nullptr};
  QPixmap m_item_cropped_pixmap;
};

#endif // DIALOG_SET_NEW_PATTERN_H
