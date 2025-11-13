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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <custom_widget/divider_bar.h>
#include <custom_widget/image_widget.h>
#include <custom_widget/robot/commandeditorpanel.h>
#include <custom_widget/robot/commandtreeview.h>
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
    QWidget *page_dashboard;
    QLabel *label;
    QWidget *page_vision;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    ImageWidget *graphicsView_main;
    DividerBar *widget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btn_set_roi;
    QPushButton *btn_set_polygon;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_robot;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_add;
    QPushButton *btn_delete;
    QPushButton *btn_move_up;
    QPushButton *btn_move_down;
    rp::CommandTreeView *treeView;
    rp::CommandEditorPanel *stackedWidget_cmd_editor;
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
        MainWindow->resize(1014, 639);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionChange_language = new QAction(MainWindow);
        actionChange_language->setObjectName("actionChange_language");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
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
        page_dashboard = new QWidget();
        page_dashboard->setObjectName("page_dashboard");
        label = new QLabel(page_dashboard);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 40, 131, 21));
        stackedWidget->addWidget(page_dashboard);
        page_vision = new QWidget();
        page_vision->setObjectName("page_vision");
        horizontalLayout_4 = new QHBoxLayout(page_vision);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        graphicsView_main = new ImageWidget(page_vision);
        graphicsView_main->setObjectName("graphicsView_main");

        verticalLayout_4->addWidget(graphicsView_main);

        widget = new DividerBar(page_vision);
        widget->setObjectName("widget");

        verticalLayout_4->addWidget(widget);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        btn_set_roi = new QPushButton(page_vision);
        btn_set_roi->setObjectName("btn_set_roi");

        verticalLayout_3->addWidget(btn_set_roi);

        btn_set_polygon = new QPushButton(page_vision);
        btn_set_polygon->setObjectName("btn_set_polygon");

        verticalLayout_3->addWidget(btn_set_polygon);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_4->addLayout(verticalLayout_3);

        stackedWidget->addWidget(page_vision);
        page_robot = new QWidget();
        page_robot->setObjectName("page_robot");
        horizontalLayout_3 = new QHBoxLayout(page_robot);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btn_add = new QPushButton(page_robot);
        btn_add->setObjectName("btn_add");

        horizontalLayout_2->addWidget(btn_add);

        btn_delete = new QPushButton(page_robot);
        btn_delete->setObjectName("btn_delete");

        horizontalLayout_2->addWidget(btn_delete);

        btn_move_up = new QPushButton(page_robot);
        btn_move_up->setObjectName("btn_move_up");

        horizontalLayout_2->addWidget(btn_move_up);

        btn_move_down = new QPushButton(page_robot);
        btn_move_down->setObjectName("btn_move_down");

        horizontalLayout_2->addWidget(btn_move_down);


        verticalLayout_2->addLayout(horizontalLayout_2);

        treeView = new rp::CommandTreeView(page_robot);
        treeView->setObjectName("treeView");
        treeView->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
        treeView->setDefaultDropAction(Qt::DropAction::MoveAction);

        verticalLayout_2->addWidget(treeView);


        horizontalLayout_3->addLayout(verticalLayout_2);

        stackedWidget_cmd_editor = new rp::CommandEditorPanel(page_robot);
        stackedWidget_cmd_editor->setObjectName("stackedWidget_cmd_editor");
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget_cmd_editor->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget_cmd_editor->addWidget(page_2);

        horizontalLayout_3->addWidget(stackedWidget_cmd_editor);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 1);
        stackedWidget->addWidget(page_robot);

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

        stackedWidget->setCurrentIndex(1);


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
        btn_set_roi->setText(QCoreApplication::translate("MainWindow", "Set ROI", nullptr));
        btn_set_polygon->setText(QCoreApplication::translate("MainWindow", "Set Polygon", nullptr));
        btn_add->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        btn_delete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        btn_move_up->setText(QCoreApplication::translate("MainWindow", "Move up", nullptr));
        btn_move_down->setText(QCoreApplication::translate("MainWindow", "Move down", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
