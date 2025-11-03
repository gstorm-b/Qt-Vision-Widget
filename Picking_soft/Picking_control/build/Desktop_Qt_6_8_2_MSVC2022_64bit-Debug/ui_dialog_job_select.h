/********************************************************************************
** Form generated from reading UI file 'dialog_job_select.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_JOB_SELECT_H
#define UI_DIALOG_JOB_SELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <custom_widget/icon_button.h>

QT_BEGIN_NAMESPACE

class Ui_DialogJobSelect
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    IconToolButton *tbtn_new_job;
    IconToolButton *tbtn_load_job;
    IconToolButton *tbtn_load_last_job;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogJobSelect)
    {
        if (DialogJobSelect->objectName().isEmpty())
            DialogJobSelect->setObjectName("DialogJobSelect");
        DialogJobSelect->resize(484, 461);
        verticalLayout_2 = new QVBoxLayout(DialogJobSelect);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        tbtn_new_job = new IconToolButton(DialogJobSelect);
        tbtn_new_job->setObjectName("tbtn_new_job");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbtn_new_job->sizePolicy().hasHeightForWidth());
        tbtn_new_job->setSizePolicy(sizePolicy);
        tbtn_new_job->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(tbtn_new_job, 0, 0, 1, 1);

        tbtn_load_job = new IconToolButton(DialogJobSelect);
        tbtn_load_job->setObjectName("tbtn_load_job");
        sizePolicy.setHeightForWidth(tbtn_load_job->sizePolicy().hasHeightForWidth());
        tbtn_load_job->setSizePolicy(sizePolicy);
        tbtn_load_job->setMinimumSize(QSize(100, 100));
        tbtn_load_job->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);

        gridLayout->addWidget(tbtn_load_job, 0, 1, 1, 1);

        tbtn_load_last_job = new IconToolButton(DialogJobSelect);
        tbtn_load_last_job->setObjectName("tbtn_load_last_job");
        sizePolicy.setHeightForWidth(tbtn_load_last_job->sizePolicy().hasHeightForWidth());
        tbtn_load_last_job->setSizePolicy(sizePolicy);
        tbtn_load_last_job->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(tbtn_load_last_job, 1, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);

        verticalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(50, 20, -1, -1);
        label_3 = new QLabel(DialogJobSelect);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_2 = new QLabel(DialogJobSelect);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label = new QLabel(DialogJobSelect);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_4 = new QLabel(DialogJobSelect);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(DialogJobSelect);
        pushButton->setObjectName("pushButton");

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(DialogJobSelect);

        QMetaObject::connectSlotsByName(DialogJobSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogJobSelect)
    {
        DialogJobSelect->setWindowTitle(QCoreApplication::translate("DialogJobSelect", "Dialog", nullptr));
        tbtn_new_job->setText(QCoreApplication::translate("DialogJobSelect", "...", nullptr));
        tbtn_load_job->setText(QCoreApplication::translate("DialogJobSelect", "...", nullptr));
        tbtn_load_last_job->setText(QCoreApplication::translate("DialogJobSelect", "...", nullptr));
        label_3->setText(QCoreApplication::translate("DialogJobSelect", "Camera", nullptr));
        label_2->setText(QCoreApplication::translate("DialogJobSelect", "Robot", nullptr));
        label->setText(QCoreApplication::translate("DialogJobSelect", "Name", nullptr));
        label_4->setText(QCoreApplication::translate("DialogJobSelect", "Number of registed sample", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogJobSelect", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogJobSelect: public Ui_DialogJobSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_JOB_SELECT_H
