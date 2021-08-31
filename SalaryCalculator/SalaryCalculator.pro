

QT       += core gui
RC_ICONS = IcoFile.ico
TARGET = Calculator

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    globalfunc.cpp \
    head.cpp \
    main.cpp \
    mainwindow.cpp \
    setting.cpp

HEADERS += \
    globalfunc.h \
    head.h \
    mainwindow.h \
    setting.h

FORMS += \
    head.ui \
    mainwindow.ui \
    setting.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ResourceFile.qrc