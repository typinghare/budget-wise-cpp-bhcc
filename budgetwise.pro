QT += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    repository/CategoryRepository.cpp \
    repository/RecordRepository.cpp \
    repository/SubcategoryRepository.cpp \
    util/Timer.cpp \
    window/MainWindow.cpp \
    window/LoginWindow.cpp \
    window/SignUpWindow.cpp \
    window/ForgotPasswordWindow.cpp \
    window/CategoryWindow.cpp \
    window/SubcategoryWindow.cpp \
    entity/User.cpp \
    entity/UserInfo.cpp \
    entity/Category.cpp \
    entity/Subcategory.cpp \
    entity/Record.cpp \
    repository/UserRepository.cpp \
    util/FileUtil.cpp \
    util/PasswordUtil.cpp \
    util/WindowUtil.cpp \
    common/Date.cpp \
    Database.cpp \
    LocalUser.cpp \
    window/UpdateCategoryWindow.cpp

HEADERS += \
    repository/CategoryRepository.h \
    repository/RecordRepository.h \
    repository/SubcategoryRepository.h \
    util/Timer.h \
    window/MainWindow.h \
    window/LoginWindow.h \
    window/SignUpWindow.h \
    window/ForgotPasswordWindow.h \
    window/CategoryWindow.h \
    window/SubcategoryWindow.h \
    entity/User.h \
    entity/UserInfo.h \
    entity/Category.h \
    entity/Subcategory.h \
    entity/Record.h \
    repository/UserRepository.h \
    util/FileUtil.h \
    util/PasswordUtil.h \
    util/WindowUtil.h \
    common/Date.h \
    Database.h \
    LocalUser.h \
    utils.h \
    test.h \
    window/UpdateCategoryWindow.h \
    windows.h

FORMS += \
    CategoryWindow.ui \
    ForgotPasswordWindow.ui \
    LoginWindow.ui \
    MainWindow.ui \
    SignUpWindow.ui \
    SubcategoryWindow.ui \
    window/UpdateCategoryWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    README.md \
    img/uml_brief.png
