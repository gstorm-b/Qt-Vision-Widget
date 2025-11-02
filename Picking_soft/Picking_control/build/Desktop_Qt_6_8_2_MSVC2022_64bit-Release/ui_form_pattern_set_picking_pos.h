/********************************************************************************
** Form generated from reading UI file 'form_pattern_set_picking_pos.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PATTERN_SET_PICKING_POS_H
#define UI_FORM_PATTERN_SET_PICKING_POS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <custom_widget/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_FormPatternSetPickingPos
{
public:
    QHBoxLayout *horizontalLayout;
    ImageWidget *graphics_view;
    QFormLayout *formLayout;
    QLabel *lb_title_x;
    QLabel *lb_title_y;
    QDoubleSpinBox *dspb_X;
    QDoubleSpinBox *dspb_Y;
    QLabel *lb_title_angle;
    QDoubleSpinBox *dspb_angle;

    void setupUi(QWidget *FormPatternSetPickingPos)
    {
        if (FormPatternSetPickingPos->objectName().isEmpty())
            FormPatternSetPickingPos->setObjectName("FormPatternSetPickingPos");
        FormPatternSetPickingPos->resize(632, 460);
        horizontalLayout = new QHBoxLayout(FormPatternSetPickingPos);
        horizontalLayout->setObjectName("horizontalLayout");
        graphics_view = new ImageWidget(FormPatternSetPickingPos);
        graphics_view->setObjectName("graphics_view");

        horizontalLayout->addWidget(graphics_view);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(20);
        lb_title_x = new QLabel(FormPatternSetPickingPos);
        lb_title_x->setObjectName("lb_title_x");

        formLayout->setWidget(0, QFormLayout::LabelRole, lb_title_x);

        lb_title_y = new QLabel(FormPatternSetPickingPos);
        lb_title_y->setObjectName("lb_title_y");

        formLayout->setWidget(1, QFormLayout::LabelRole, lb_title_y);

        dspb_X = new QDoubleSpinBox(FormPatternSetPickingPos);
        dspb_X->setObjectName("dspb_X");
        dspb_X->setMinimumSize(QSize(100, 0));
        dspb_X->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);

        formLayout->setWidget(0, QFormLayout::FieldRole, dspb_X);

        dspb_Y = new QDoubleSpinBox(FormPatternSetPickingPos);
        dspb_Y->setObjectName("dspb_Y");
        dspb_Y->setMinimumSize(QSize(100, 0));
        dspb_Y->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);

        formLayout->setWidget(1, QFormLayout::FieldRole, dspb_Y);

        lb_title_angle = new QLabel(FormPatternSetPickingPos);
        lb_title_angle->setObjectName("lb_title_angle");

        formLayout->setWidget(2, QFormLayout::LabelRole, lb_title_angle);

        dspb_angle = new QDoubleSpinBox(FormPatternSetPickingPos);
        dspb_angle->setObjectName("dspb_angle");
        dspb_angle->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);

        formLayout->setWidget(2, QFormLayout::FieldRole, dspb_angle);


        horizontalLayout->addLayout(formLayout);


        retranslateUi(FormPatternSetPickingPos);

        QMetaObject::connectSlotsByName(FormPatternSetPickingPos);
    } // setupUi

    void retranslateUi(QWidget *FormPatternSetPickingPos)
    {
        FormPatternSetPickingPos->setWindowTitle(QCoreApplication::translate("FormPatternSetPickingPos", "Form", nullptr));
        lb_title_x->setText(QCoreApplication::translate("FormPatternSetPickingPos", "X", nullptr));
        lb_title_y->setText(QCoreApplication::translate("FormPatternSetPickingPos", "Y", nullptr));
        lb_title_angle->setText(QCoreApplication::translate("FormPatternSetPickingPos", "Angle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormPatternSetPickingPos: public Ui_FormPatternSetPickingPos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PATTERN_SET_PICKING_POS_H
