QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custom_widget/image_view_only.cpp \
    custom_widget/thumb_view/thumbnail_delegate.cpp \
    custom_widget/thumb_view/thumbnail_item_widget.cpp \
    custom_widget/thumb_view/thumbnail_list_view.cpp \
    custom_widget/thumb_view/thumbnail_model.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    custom_widget/image_view_only.h \
    custom_widget/thumb_view/thumbnail_delegate.h \
    custom_widget/thumb_view/thumbnail_item_widget.h \
    custom_widget/thumb_view/thumbnail_list_view.h \
    custom_widget/thumb_view/thumbnail_model.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
