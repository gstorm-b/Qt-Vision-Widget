/********************************************************************************
** Form generated from reading UI file 'set_workspace_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_WORKSPACE_DIALOG_H
#define UI_SET_WORKSPACE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <custom_widget/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_SetWorkspaceDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    ImageWidget *graphicsView;
    QVBoxLayout *verticalLayout;
    QPushButton *btn_set_roi;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_cancel;
    QPushButton *btn_apply;

    void setupUi(QDialog *SetWorkspaceDialog)
    {
        if (SetWorkspaceDialog->objectName().isEmpty())
            SetWorkspaceDialog->setObjectName("SetWorkspaceDialog");
        SetWorkspaceDialog->resize(751, 588);
        verticalLayout_2 = new QVBoxLayout(SetWorkspaceDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        graphicsView = new ImageWidget(SetWorkspaceDialog);
        graphicsView->setObjectName("graphicsView");

        horizontalLayout_2->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        btn_set_roi = new QPushButton(SetWorkspaceDialog);
        btn_set_roi->setObjectName("btn_set_roi");
        btn_set_roi->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        verticalLayout->addWidget(btn_set_roi);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_cancel = new QPushButton(SetWorkspaceDialog);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(btn_cancel);

        btn_apply = new QPushButton(SetWorkspaceDialog);
        btn_apply->setObjectName("btn_apply");
        btn_apply->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(btn_apply);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(SetWorkspaceDialog);

        QMetaObject::connectSlotsByName(SetWorkspaceDialog);
    } // setupUi

    void retranslateUi(QDialog *SetWorkspaceDialog)
    {
        SetWorkspaceDialog->setWindowTitle(QCoreApplication::translate("SetWorkspaceDialog", "Dialog", nullptr));
        btn_set_roi->setText(QCoreApplication::translate("SetWorkspaceDialog", "Set ROI", nullptr));
        btn_cancel->setText(QCoreApplication::translate("SetWorkspaceDialog", "Cancel", nullptr));
        btn_apply->setText(QCoreApplication::translate("SetWorkspaceDialog", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetWorkspaceDialog: public Ui_SetWorkspaceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_WORKSPACE_DIALOG_H
