/********************************************************************************
** Form generated from reading UI file 'form_project_navigate.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_PROJECT_NAVIGATE_H
#define UI_FORM_PROJECT_NAVIGATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_new_job;
    QPushButton *btn_load_job;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(400, 300);
        horizontalLayout = new QHBoxLayout(Dialog);
        horizontalLayout->setObjectName("horizontalLayout");
        btn_new_job = new QPushButton(Dialog);
        btn_new_job->setObjectName("btn_new_job");

        horizontalLayout->addWidget(btn_new_job);

        btn_load_job = new QPushButton(Dialog);
        btn_load_job->setObjectName("btn_load_job");

        horizontalLayout->addWidget(btn_load_job);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        btn_new_job->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
        btn_load_job->setText(QCoreApplication::translate("Dialog", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_PROJECT_NAVIGATE_H
