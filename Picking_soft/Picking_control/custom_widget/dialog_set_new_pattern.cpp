#include "dialog_set_new_pattern.h"
#include "ui_dialog_set_new_pattern.h"
#include "ui_form_pattern_crop_image.h"
#include "ui_form_pattern_set_picking_pos.h"

DialogSetNewPattern::DialogSetNewPattern(
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSetNewPattern),
    form_crop_image(new Ui::FormPatternCropImage),
    form_picking_pos(new Ui::FormPatternSetPickingPos),
    m_current_step(0),
    m_has_image(false) {
  ui->setupUi(this);

  m_wg_crop_image = new QWidget(this);
  form_crop_image->setupUi(m_wg_crop_image);

  m_wg_set_picking_pos = new QWidget(this);
  form_picking_pos->setupUi(m_wg_set_picking_pos);

  m_wg_map[0] = m_wg_crop_image;
  m_wg_map[1] = m_wg_set_picking_pos;

  m_wg_title_map[0] = tr("Set Pattern Image");
  m_wg_title_map[1] = tr("Set picking position");

  ui->main_stack_wg->addWidget(m_wg_crop_image);
  ui->main_stack_wg->addWidget(m_wg_set_picking_pos);

  ui->main_stack_wg->setCurrentWidget(m_wg_map.value(0));
  ui->lb_step_name->setText(m_wg_title_map.value(0));

  ui->btn_back->setEnabled(false);
  ui->btn_next->setEnabled(false);
  connect(ui->btn_back, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_back_clicked);
  connect(ui->btn_next, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_next_clicked);
  connect(ui->btn_cancel, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_cancel_clicked);

  // form step 1
  form_crop_image->btn_set_roi->setEnabled(false);
  form_crop_image->btn_clear_roi->setEnabled(false);
  connect(form_crop_image->btn_choose_image, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_form_choose_image_clicked);
  connect(form_crop_image->btn_trigger, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_form_trigger_clicked);
  connect(form_crop_image->btn_set_roi, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_form_set_roi_clicked);
  connect(form_crop_image->btn_clear_roi, &QPushButton::clicked,
          this, &DialogSetNewPattern::btn_form_clear_roi_clicked);
  connect(form_crop_image->graphics_view, &ImageWidget::signal_draw_roi_finished,
          this, &DialogSetNewPattern::form_draw_crop_roi_finished);

  this->setModal(false);
}

DialogSetNewPattern::~DialogSetNewPattern() {
  delete ui;
}

void DialogSetNewPattern::btn_back_clicked() {
  m_current_step -= 1;
  if ((m_current_step < 0)) {
    m_current_step = 0;
    return;
  }
  ui->btn_back->setDisabled((m_current_step <= 0));
  ui->btn_next->setDisabled(false);
  set_current_step_wg();
}

void DialogSetNewPattern::btn_next_clicked() {
  m_current_step += 1;
  if ((m_current_step > 3)) {
    m_current_step = 3;
    return;
  }
  ui->btn_back->setDisabled(false);
  ui->btn_next->setDisabled((m_current_step >= 3));
  set_current_step_wg();
}

void DialogSetNewPattern::btn_cancel_clicked() {
  this->reject();
}

void DialogSetNewPattern::btn_form_choose_image_clicked() {
  form_crop_image->graphics_view->showChooseImageDialog();

  // if (m_item_crop_roi != nullptr) {
  //   form_crop_image->graphics_view->scene()->removeItem(m_item_crop_roi);
  //   m_item_crop_roi == nullptr;
  // }

  form_crop_image->btn_set_roi->setEnabled(
      (form_crop_image->graphics_view->hadImage()) &&
      (m_item_crop_roi == nullptr));

}

void DialogSetNewPattern::btn_form_trigger_clicked() {
  // trigger from camera
}

void DialogSetNewPattern::btn_form_set_roi_clicked() {
  form_crop_image->graphics_view->startDrawROI();
}

void DialogSetNewPattern::btn_form_clear_roi_clicked() {
  if (m_item_crop_roi == nullptr) {
    return;
  }
  form_crop_image->graphics_view->scene()->removeItem(m_item_crop_roi);
  form_crop_image->btn_set_roi->setEnabled(true);
  form_crop_image->btn_clear_roi->setEnabled(false);
  m_item_crop_roi = nullptr;
}

void DialogSetNewPattern::form_draw_crop_roi_finished(ItemRoi *roi) {
  if (roi == nullptr) {
    return;
  }

  ui->btn_next->setEnabled(true);
  form_crop_image->btn_set_roi->setEnabled(false);
  form_crop_image->btn_clear_roi->setEnabled(true);
  m_item_crop_roi = roi;
}

void DialogSetNewPattern::set_current_step_wg() {
  if (m_wg_map.contains(m_current_step)) {
    ui->main_stack_wg->setCurrentWidget(m_wg_map.value(m_current_step));
    ui->lb_step_name->setText(m_wg_title_map.value(m_current_step));
  }

  switch (m_current_step) {
    case 1:
      m_item_cropped_pixmap = form_crop_image->graphics_view->getCroppedFromRoi
                              (m_item_crop_roi);
      form_picking_pos->graphics_view->loadImage(m_item_cropped_pixmap);
      break;
  }
}
