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
#include <QtWidgets/QLabel>
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
    TabWidgetButton *tbtn_state_camera;
    TabWidgetButton *tbtn_state_robot;
    TabWidgetButton *tbtn_state_plc;
    QSpacerItem *verticalSpacer_2;
    TabWidgetButton *tbtn_dashboard;
    TabWidgetButton *tbtn_vision;
    TabWidgetButton *tbtn_robot;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *page_2;
    QLabel *label_2;
    QWidget *page_3;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuView;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1014, 639);
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
        tbtn_state_camera = new TabWidgetButton(centralwidget);
        tbtn_state_camera->setObjectName("tbtn_state_camera");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbtn_state_camera->sizePolicy().hasHeightForWidth());
        tbtn_state_camera->setSizePolicy(sizePolicy);
        tbtn_state_camera->setMinimumSize(QSize(100, 50));

        verticalLayout->addWidget(tbtn_state_camera);

        tbtn_state_robot = new TabWidgetButton(centralwidget);
        tbtn_state_robot->setObjectName("tbtn_state_robot");
        sizePolicy.setHeightForWidth(tbtn_state_robot->sizePolicy().hasHeightForWidth());
        tbtn_state_robot->setSizePolicy(sizePolicy);
        tbtn_state_robot->setMinimumSize(QSize(100, 50));

        verticalLayout->addWidget(tbtn_state_robot);

        tbtn_state_plc = new TabWidgetButton(centralwidget);
        tbtn_state_plc->setObjectName("tbtn_state_plc");
        sizePolicy.setHeightForWidth(tbtn_state_plc->sizePolicy().hasHeightForWidth());
        tbtn_state_plc->setSizePolicy(sizePolicy);
        tbtn_state_plc->setMinimumSize(QSize(100, 50));

        verticalLayout->addWidget(tbtn_state_plc);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_2);

        tbtn_dashboard = new TabWidgetButton(centralwidget);
        tbtn_dashboard->setObjectName("tbtn_dashboard");
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
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 40, 131, 21));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_2 = new QLabel(page_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(70, 50, 111, 21));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(90, 60, 111, 21));
        stackedWidget->addWidget(page_3);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1014, 21));
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

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionChange_language->setText(QCoreApplication::translate("MainWindow", "Change language", nullptr));
        tbtn_state_camera->setText(QCoreApplication::translate("MainWindow", "Camera connect", nullptr));
        tbtn_state_robot->setText(QCoreApplication::translate("MainWindow", "Robot connect", nullptr));
        tbtn_state_plc->setText(QCoreApplication::translate("MainWindow", "PLC Connect", nullptr));
        tbtn_dashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        tbtn_vision->setText(QCoreApplication::translate("MainWindow", "Vision", nullptr));
        tbtn_robot->setText(QCoreApplication::translate("MainWindow", "Robot", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "This is dashboard", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "This is vision", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "This is robot", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
