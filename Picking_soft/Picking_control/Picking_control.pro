QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custom_widget/image_widget.cpp \
    custom_widget/robot/command.cpp \
    custom_widget/robot/commandeditor.cpp \
    custom_widget/robot/commandeditorpanel.cpp \
    custom_widget/robot/commandmodel.cpp \
    custom_widget/robot/commandtreeview.cpp \
    form/robot/moveleditor.cpp \
    form\job\dialog_job_select.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    custom_widget/icon_button.h \
    custom_widget/image_widget.h \
    custom_widget/robot/command.h \
    custom_widget/robot/commandeditor.h \
    custom_widget/robot/commandeditorpanel.h \
    custom_widget/robot/commandmodel.h \
    custom_widget/robot/commandnode.h \
    custom_widget/robot/commandrowwidget.h \
    custom_widget/robot/commandtreeview.h \
    custom_widget/robot/rowdelegate.h \
    custom_widget/tab_widget/tab_widget_button.h \
    form/robot/hyprgcommand.h \
    form/robot/moveleditor.h \
    form\job\dialog_job_select.h \
    mainwindow.h

FORMS += \
    form\job\dialog_job_select.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
