/********************************************************************************
** Form generated from reading UI file 'form_pattern_crop_image.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PATTERN_CROP_IMAGE_H
#define UI_FORM_PATTERN_CROP_IMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <custom_widget/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_FormPatternCropImage
{
public:
    QHBoxLayout *horizontalLayout;
    ImageWidget *graphics_view;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_choose_image;
    QPushButton *btn_trigger;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btn_set_roi;
    QPushButton *btn_clear_roi;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FormPatternCropImage)
    {
        if (FormPatternCropImage->objectName().isEmpty())
            FormPatternCropImage->setObjectName("FormPatternCropImage");
        FormPatternCropImage->resize(557, 394);
        horizontalLayout = new QHBoxLayout(FormPatternCropImage);
        horizontalLayout->setObjectName("horizontalLayout");
        graphics_view = new ImageWidget(FormPatternCropImage);
        graphics_view->setObjectName("graphics_view");

        horizontalLayout->addWidget(graphics_view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btn_choose_image = new QPushButton(FormPatternCropImage);
        btn_choose_image->setObjectName("btn_choose_image");

        verticalLayout->addWidget(btn_choose_image);

        btn_trigger = new QPushButton(FormPatternCropImage);
        btn_trigger->setObjectName("btn_trigger");

        verticalLayout->addWidget(btn_trigger);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        btn_set_roi = new QPushButton(FormPatternCropImage);
        btn_set_roi->setObjectName("btn_set_roi");

        verticalLayout->addWidget(btn_set_roi);

        btn_clear_roi = new QPushButton(FormPatternCropImage);
        btn_clear_roi->setObjectName("btn_clear_roi");

        verticalLayout->addWidget(btn_clear_roi);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(FormPatternCropImage);

        QMetaObject::connectSlotsByName(FormPatternCropImage);
    } // setupUi

    void retranslateUi(QWidget *FormPatternCropImage)
    {
        FormPatternCropImage->setWindowTitle(QCoreApplication::translate("FormPatternCropImage", "Form", nullptr));
        btn_choose_image->setText(QCoreApplication::translate("FormPatternCropImage", "Choose Image", nullptr));
        btn_trigger->setText(QCoreApplication::translate("FormPatternCropImage", "Trigger", nullptr));
        btn_set_roi->setText(QCoreApplication::translate("FormPatternCropImage", "Set ROI", nullptr));
        btn_clear_roi->setText(QCoreApplication::translate("FormPatternCropImage", "Clear ROI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormPatternCropImage: public Ui_FormPatternCropImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PATTERN_CROP_IMAGE_H
