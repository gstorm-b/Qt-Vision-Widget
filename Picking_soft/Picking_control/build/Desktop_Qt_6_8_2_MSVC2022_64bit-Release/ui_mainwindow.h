/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <custom_widget/tab_widget/tab_widget_button.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionChange_language;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    TabWidgetButton *tbtn_dashboard;
    TabWidgetButton *tbtn_vision;
    TabWidgetButton *tbtn_robot;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(906, 489);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionChange_language = new QAction(MainWindow);
        actionChange_language->setObjectName("actionChange_language");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 10, 2, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        tbtn_dashboard = new TabWidgetButton(centralwidget);
        tbtn_dashboard->setObjectName("tbtn_dashboard");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbtn_dashboard->sizePolicy().hasHeightForWidth());
        tbtn_dashboard->setSizePolicy(sizePolicy);
        tbtn_dashboard->setMinimumSize(QSize(100, 100));

        verticalLayout->addWidget(tbtn_dashboard);

        tbtn_vision = new TabWidgetButton(centralwidget);
        tbtn_vision->setObjectName("tbtn_vision");
        sizePolicy.setHeightForWidth(tbtn_vision->sizePolicy().hasHeightForWidth());
        tbtn_vision->setSizePolicy(sizePolicy);
        tbtn_vision->setMinimumSize(QSize(100, 100));

        verticalLayout->addWidget(tbtn_vision);

        tbtn_robot = new TabWidgetButton(centralwidget);
        tbtn_robot->setObjectName("tbtn_robot");
        sizePolicy.setHeightForWidth(tbtn_robot->sizePolicy().hasHeightForWidth());
        tbtn_robot->setSizePolicy(sizePolicy);
        tbtn_robot->setMinimumSize(QSize(100, 100));

        verticalLayout->addWidget(tbtn_robot);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 906, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionExit);
        menuView->addAction(actionChange_language);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionChange_language->setText(QCoreApplication::translate("MainWindow", "Change language", nullptr));
        tbtn_dashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        tbtn_vision->setText(QCoreApplication::translate("MainWindow", "Vision", nullptr));
        tbtn_robot->setText(QCoreApplication::translate("MainWindow", "Robot", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
