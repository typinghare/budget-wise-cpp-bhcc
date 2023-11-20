QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LoginWindow.cpp \
    SignUpWindow.cpp \
    entity/Category.cpp \
    entity/Date.cpp \
    entity/Record.cpp \
    entity/Subcategory.cpp \
    main.cpp \
    MainWindow.cpp \
    util/FIleUtil.cpp \
    util/WindowUtil.cpp

HEADERS += \
    LoginWindow.h \
    MainWindow.h \
    SignUpWindow.h \
    entity/Category.h \
    entity/Date.h \
    entity/Record.h \
    entity/Subcategory.h \
    entity/entities.h \
    util/FIleUtil.h \
    util/WindowUtil.h

FORMS += \
    LoginWindow.ui \
    MainWindow.ui \
    SignUpWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    img/uml_brief.png
