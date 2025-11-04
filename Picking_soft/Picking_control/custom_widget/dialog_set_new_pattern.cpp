#include "dialog_set_new_pattern.h"
#include "ui_dialog_set_new_pattern.h"
#include "ui_form_pattern_crop_image.h"
#include "ui_form_pattern_set_picking_pos.h"
#include "ui_form_pattern_set_conditional_area.h"

DialogSetNewPattern::DialogSetNewPattern(
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogSetNewPattern),
    form_crop_image(new Ui::FormPatternCropImage),
    form_picking_pos(new Ui::FormPatternSetPickingPos),
    form_conditional_area(new Ui::FormPatternSetConditionalArea),
    m_current_step(0),
    m_has_image(false) {
  ui->setupUi(this);

  m_wg_crop_image = new QWidget(this);
  form_crop_image->setupUi(m_wg_crop_image);

  m_wg_set_picking_pos = new QWidget(this);
  form_picking_pos->setupUi(m_wg_set_picking_pos);

  m_wg_set_conditional_area = new QWidget(this);
  form_conditional_area->setupUi(m_wg_set_conditional_area);

  m_wg_map[0] = m_wg_crop_image;
  m_wg_map[1] = m_wg_set_picking_pos;
  m_wg_map[2] = m_wg_set_conditional_area;

  m_wg_title_map[0] = tr("Set Pattern Image");
  m_wg_title_map[1] = tr("Set picking position");
  m_wg_title_map[2] = tr("Set condition area");

  ui->main_stack_wg->addWidget(m_wg_crop_image);
  ui->main_stack_wg->addWidget(m_wg_set_picking_pos);
  ui->main_stack_wg->addWidget(m_wg_set_conditional_area);

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

  connect(form_picking_pos->dspb_X, &QDoubleSpinBox::editingFinished,
          this, &DialogSetNewPattern::form_picking_pos_edited);
  connect(form_picking_pos->dspb_Y, &QDoubleSpinBox::editingFinished,
          this, &DialogSetNewPattern::form_picking_pos_edited);
  connect(form_picking_pos->dspb_angle, &QDoubleSpinBox::editingFinished,
          this, &DialogSetNewPattern::form_picking_angle_edited);

  connect(form_conditional_area->btn_set_roi, &QPushButton::clicked,
          this, &DialogSetNewPattern::form_condition_area_set_roi_clicked);

  ui->btn_cancel->setDefault(false);
  ui->btn_cancel->setAutoDefault(false);
  ui->btn_next->setDefault(false);
  ui->btn_next->setAutoDefault(false);
  ui->btn_back->setDefault(false);
  ui->btn_back->setAutoDefault(false);
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
  ui->btn_next->setText(tr("Next"));
}

void DialogSetNewPattern::btn_next_clicked() {
  if (m_current_step >= (m_max_step - 1)) {
    accept();
  }

  m_current_step += 1;
  if ((m_current_step > m_max_step)) {
    m_current_step = m_max_step - 1;
    return;
  }
  ui->btn_back->setDisabled(false);
  if ((m_current_step >= (m_max_step - 1))) {
    // ui->btn_next->setDisabled(true);
    ui->btn_next->setText(tr("Finsh"));
  } else {
    // ui->btn_next->setDisabled(false);
    ui->btn_next->setText(tr("Next"));
  }
  set_current_step_wg();
}

void DialogSetNewPattern::btn_cancel_clicked() {
  this->reject();
}

void DialogSetNewPattern::btn_form_choose_image_clicked() {
  form_crop_image->graphics_view->showChooseImageDialog();

  form_crop_image->btn_set_roi->setEnabled(
      (form_crop_image->graphics_view->hadImage()) &&
      (m_item_crop_roi == nullptr));
}

void DialogSetNewPattern::btn_form_trigger_clicked() {
  // trigger from camera
}

void DialogSetNewPattern::btn_form_set_roi_clicked() {
  form_crop_image->graphics_view->startDrawROI(ImageWidget::NormalROI);
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

void DialogSetNewPattern::form_draw_crop_roi_finished(QGraphicsItem *roi,
                                                      ImageWidget::ItemAddType type) {
  if (roi == nullptr) {
    return;
  }

  ui->btn_next->setEnabled(true);
  form_crop_image->btn_set_roi->setEnabled(false);
  form_crop_image->btn_clear_roi->setEnabled(true);
  m_item_crop_roi = dynamic_cast<ItemRoi*>(roi);
}

void DialogSetNewPattern::form_picking_pos_changed(QPointF point) {
  form_picking_pos->dspb_X->setValue(point.x());
  form_picking_pos->dspb_Y->setValue(point.y());
}

void DialogSetNewPattern::form_picking_angle_changed(qreal angle) {
  form_picking_pos->dspb_angle->setValue(angle);
}

void DialogSetNewPattern::form_picking_pos_edited() {
  QPointF point(form_picking_pos->dspb_X->value(), form_picking_pos->dspb_Y->value());
  m_item_picking_center->setPositionInParent(point);
}

void DialogSetNewPattern::form_picking_angle_edited() {
  if (m_item_crop_roi != nullptr) {
    m_item_picking_center->setAngleInParent(form_picking_pos->dspb_angle->value());
  }
}

void DialogSetNewPattern::form_condition_area_set_roi_clicked() {
  form_conditional_area->graphics_view->startDrawROI(ImageWidget::ItemAddType::RotatedROI);
}

void DialogSetNewPattern::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    event->accept();
    return;
  }
  QDialog::keyPressEvent(event);
}

void DialogSetNewPattern::set_current_step_wg() {
  if (m_wg_map.contains(m_current_step)) {
    ui->main_stack_wg->setCurrentWidget(m_wg_map.value(m_current_step));
    ui->lb_step_name->setText(m_wg_title_map.value(m_current_step));
  }

  // QPixmap temp_pixmap;

  switch (m_current_step) {
    case 1:
    {
      m_item_cropped_pixmap = form_crop_image->graphics_view->getCroppedFromRoi
                              (m_item_crop_roi);
      form_picking_pos->graphics_view->loadImage(m_item_cropped_pixmap);

      if (m_item_picking_center == nullptr) {
        m_item_picking_center = new ItemPickingCenter(form_picking_pos->graphics_view->getPixmapItem());
        // form_picking_pos->graphics_view->scene()->addItem(m_item_picking_center);
        connect(m_item_picking_center, &ItemPickingCenter::positionChanged,
                this, &DialogSetNewPattern::form_picking_pos_changed);
        connect(m_item_picking_center, &ItemPickingCenter::angleChanged,
                this, &DialogSetNewPattern::form_picking_angle_changed);
      }

      const QGraphicsPixmapItem *px_item = form_picking_pos->graphics_view->getPixmapItem();
      m_item_picking_center->setPos(px_item->boundingRect().center());
    }
      break;

    case 2:
    {
      QPixmap temp_pixmap = form_crop_image->graphics_view->getPixmapItem()->pixmap();
      form_conditional_area->graphics_view->loadImage(temp_pixmap);
    }
      break;

    default:
      break;
  }
}
