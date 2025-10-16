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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogJobSelect
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *tbtn_new_job;
    QToolButton *tbtn_load_job;

    void setupUi(QDialog *DialogJobSelect)
    {
        if (DialogJobSelect->objectName().isEmpty())
            DialogJobSelect->setObjectName("DialogJobSelect");
        DialogJobSelect->resize(657, 370);
        horizontalLayout = new QHBoxLayout(DialogJobSelect);
        horizontalLayout->setObjectName("horizontalLayout");
        tbtn_new_job = new QToolButton(DialogJobSelect);
        tbtn_new_job->setObjectName("tbtn_new_job");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbtn_new_job->sizePolicy().hasHeightForWidth());
        tbtn_new_job->setSizePolicy(sizePolicy);
        tbtn_new_job->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(tbtn_new_job);

        tbtn_load_job = new QToolButton(DialogJobSelect);
        tbtn_load_job->setObjectName("tbtn_load_job");
        sizePolicy.setHeightForWidth(tbtn_load_job->sizePolicy().hasHeightForWidth());
        tbtn_load_job->setSizePolicy(sizePolicy);
        tbtn_load_job->setMinimumSize(QSize(100, 100));

        horizontalLayout->addWidget(tbtn_load_job);


        retranslateUi(DialogJobSelect);

        QMetaObject::connectSlotsByName(DialogJobSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogJobSelect)
    {
        DialogJobSelect->setWindowTitle(QCoreApplication::translate("DialogJobSelect", "Dialog", nullptr));
        tbtn_new_job->setText(QCoreApplication::translate("DialogJobSelect", "...", nullptr));
        tbtn_load_job->setText(QCoreApplication::translate("DialogJobSelect", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogJobSelect: public Ui_DialogJobSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_JOB_SELECT_H
