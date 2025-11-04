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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <custom_widget/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_FormPatternSetConditionalArea
{
public:
    QHBoxLayout *horizontalLayout;
    ImageWidget *graphics_view;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_set_roi;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FormPatternSetConditionalArea)
    {
        if (FormPatternSetConditionalArea->objectName().isEmpty())
            FormPatternSetConditionalArea->setObjectName("FormPatternSetConditionalArea");
        FormPatternSetConditionalArea->resize(831, 518);
        horizontalLayout = new QHBoxLayout(FormPatternSetConditionalArea);
        horizontalLayout->setObjectName("horizontalLayout");
        graphics_view = new ImageWidget(FormPatternSetConditionalArea);
        graphics_view->setObjectName("graphics_view");

        horizontalLayout->addWidget(graphics_view);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btn_set_roi = new QPushButton(FormPatternSetConditionalArea);
        btn_set_roi->setObjectName("btn_set_roi");

        verticalLayout->addWidget(btn_set_roi);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(FormPatternSetConditionalArea);

        QMetaObject::connectSlotsByName(FormPatternSetConditionalArea);
    } // setupUi

    void retranslateUi(QWidget *FormPatternSetConditionalArea)
    {
        FormPatternSetConditionalArea->setWindowTitle(QCoreApplication::translate("FormPatternSetConditionalArea", "Form", nullptr));
        btn_set_roi->setText(QCoreApplication::translate("FormPatternSetConditionalArea", "Add ROI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormPatternSetConditionalArea: public Ui_FormPatternSetConditionalArea {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PATTERN_SET_CONDITIONAL_AREA_H
