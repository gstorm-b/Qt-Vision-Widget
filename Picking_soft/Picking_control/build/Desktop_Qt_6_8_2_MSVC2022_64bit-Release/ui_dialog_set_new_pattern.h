/********************************************************************************
** Form generated from reading UI file 'dialog_set_new_pattern.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SET_NEW_PATTERN_H
#define UI_DIALOG_SET_NEW_PATTERN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSetNewPattern
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lb_step_name;
    QStackedWidget *main_stack_wg;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_cancel;
    QPushButton *btn_back;
    QPushButton *btn_next;

    void setupUi(QDialog *DialogSetNewPattern)
    {
        if (DialogSetNewPattern->objectName().isEmpty())
            DialogSetNewPattern->setObjectName("DialogSetNewPattern");
        DialogSetNewPattern->resize(649, 426);
        verticalLayout = new QVBoxLayout(DialogSetNewPattern);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 15, -1, -1);
        lb_step_name = new QLabel(DialogSetNewPattern);
        lb_step_name->setObjectName("lb_step_name");

        verticalLayout->addWidget(lb_step_name);

        main_stack_wg = new QStackedWidget(DialogSetNewPattern);
        main_stack_wg->setObjectName("main_stack_wg");

        verticalLayout->addWidget(main_stack_wg);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_cancel = new QPushButton(DialogSetNewPattern);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(btn_cancel);

        btn_back = new QPushButton(DialogSetNewPattern);
        btn_back->setObjectName("btn_back");
        btn_back->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(btn_back);

        btn_next = new QPushButton(DialogSetNewPattern);
        btn_next->setObjectName("btn_next");
        btn_next->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(btn_next);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DialogSetNewPattern);

        QMetaObject::connectSlotsByName(DialogSetNewPattern);
    } // setupUi

    void retranslateUi(QDialog *DialogSetNewPattern)
    {
        DialogSetNewPattern->setWindowTitle(QCoreApplication::translate("DialogSetNewPattern", "Dialog", nullptr));
        lb_step_name->setText(QCoreApplication::translate("DialogSetNewPattern", "TextLabel", nullptr));
        btn_cancel->setText(QCoreApplication::translate("DialogSetNewPattern", "Cancel", nullptr));
        btn_back->setText(QCoreApplication::translate("DialogSetNewPattern", "Back", nullptr));
        btn_next->setText(QCoreApplication::translate("DialogSetNewPattern", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSetNewPattern: public Ui_DialogSetNewPattern {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SET_NEW_PATTERN_H
