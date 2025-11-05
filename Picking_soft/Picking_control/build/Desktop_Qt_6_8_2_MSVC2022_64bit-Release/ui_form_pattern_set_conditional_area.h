/********************************************************************************
** Form generated from reading UI file 'form_pattern_set_conditional_area.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PATTERN_SET_CONDITIONAL_AREA_H
#define UI_FORM_PATTERN_SET_CONDITIONAL_AREA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <custom_widget/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_FormPatternSetConditionalArea
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
    QLabel *label;
    QSpinBox *spb_distance;

    void setupUi(QWidget *FormPatternSetConditionalArea)
    {
        if (FormPatternSetConditionalArea->objectName().isEmpty())
            FormPatternSetConditionalArea->setObjectName("FormPatternSetConditionalArea");
        FormPatternSetConditionalArea->resize(833, 489);
        horizontalLayout = new QHBoxLayout(FormPatternSetConditionalArea);
        horizontalLayout->setObjectName("horizontalLayout");
        graphics_view = new ImageWidget(FormPatternSetConditionalArea);
        graphics_view->setObjectName("graphics_view");

        horizontalLayout->addWidget(graphics_view);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(20);
        lb_title_x = new QLabel(FormPatternSetConditionalArea);
        lb_title_x->setObjectName("lb_title_x");

        formLayout->setWidget(0, QFormLayout::LabelRole, lb_title_x);

        lb_title_y = new QLabel(FormPatternSetConditionalArea);
        lb_title_y->setObjectName("lb_title_y");

        formLayout->setWidget(1, QFormLayout::LabelRole, lb_title_y);

        dspb_X = new QDoubleSpinBox(FormPatternSetConditionalArea);
        dspb_X->setObjectName("dspb_X");
        dspb_X->setMinimumSize(QSize(100, 0));
        dspb_X->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        dspb_X->setMinimum(-5000.000000000000000);
        dspb_X->setMaximum(5000.000000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, dspb_X);

        dspb_Y = new QDoubleSpinBox(FormPatternSetConditionalArea);
        dspb_Y->setObjectName("dspb_Y");
        dspb_Y->setMinimumSize(QSize(100, 0));
        dspb_Y->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        dspb_Y->setMinimum(-5000.000000000000000);
        dspb_Y->setMaximum(5000.000000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, dspb_Y);

        lb_title_angle = new QLabel(FormPatternSetConditionalArea);
        lb_title_angle->setObjectName("lb_title_angle");

        formLayout->setWidget(2, QFormLayout::LabelRole, lb_title_angle);

        dspb_angle = new QDoubleSpinBox(FormPatternSetConditionalArea);
        dspb_angle->setObjectName("dspb_angle");
        dspb_angle->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        dspb_angle->setMinimum(-180.000000000000000);
        dspb_angle->setMaximum(180.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, dspb_angle);

        label = new QLabel(FormPatternSetConditionalArea);
        label->setObjectName("label");

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        spb_distance = new QSpinBox(FormPatternSetConditionalArea);
        spb_distance->setObjectName("spb_distance");
        spb_distance->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);

        formLayout->setWidget(3, QFormLayout::FieldRole, spb_distance);


        horizontalLayout->addLayout(formLayout);


        retranslateUi(FormPatternSetConditionalArea);

        QMetaObject::connectSlotsByName(FormPatternSetConditionalArea);
    } // setupUi

    void retranslateUi(QWidget *FormPatternSetConditionalArea)
    {
        FormPatternSetConditionalArea->setWindowTitle(QCoreApplication::translate("FormPatternSetConditionalArea", "Form", nullptr));
        lb_title_x->setText(QCoreApplication::translate("FormPatternSetConditionalArea", "X", nullptr));
        lb_title_y->setText(QCoreApplication::translate("FormPatternSetConditionalArea", "Y", nullptr));
        lb_title_angle->setText(QCoreApplication::translate("FormPatternSetConditionalArea", "Angle", nullptr));
        label->setText(QCoreApplication::translate("FormPatternSetConditionalArea", "Distance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormPatternSetConditionalArea: public Ui_FormPatternSetConditionalArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PATTERN_SET_CONDITIONAL_AREA_H
