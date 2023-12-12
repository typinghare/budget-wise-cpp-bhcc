QT += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/main.cpp \
    src/repository/CategoryRepository.cpp \
    src/repository/RecordRepository.cpp \
    src/repository/SubcategoryRepository.cpp \
    src/repository/UserInfoRepository.cpp \
    src/service/RecordService.cpp \
    src/util/TimerUtil.cpp \
    src/window/CreateRecordWindow.cpp \
    src/window/MainWindow.cpp \
    src/window/LoginWindow.cpp \
    src/window/SignUpWindow.cpp \
    src/window/ForgotPasswordWindow.cpp \
    src/window/CategoryWindow.cpp \
    src/window/SubcategoryWindow.cpp \
    src/window/UpdateCategoryWindow.cpp \
    src/entity/User.cpp \
    src/entity/UserInfo.cpp \
    src/entity/Category.cpp \
    src/entity/Subcategory.cpp \
    src/entity/Record.cpp \
    src/repository/UserRepository.cpp \
    src/util/FileUtil.cpp \
    src/util/PasswordUtil.cpp \
    src/util/WindowUtil.cpp \
    src/common/Date.cpp \
    src/Database.cpp \
    src/LocalUser.cpp \
    src/window/UpdateSubcategoryWindow.cpp

HEADERS += \
    src/repository/CategoryRepository.h \
    src/repository/RecordRepository.h \
    src/repository/SubcategoryRepository.h \
    src/repository/UserInfoRepository.h \
    src/service/RecordService.h \
    src/services.h \
    src/util/TimerUtil.h \
    src/window/CreateRecordWindow.h \
    src/window/MainWindow.h \
    src/window/LoginWindow.h \
    src/window/SignUpWindow.h \
    src/window/ForgotPasswordWindow.h \
    src/window/CategoryWindow.h \
    src/window/SubcategoryWindow.h \
    src/entity/User.h \
    src/entity/UserInfo.h \
    src/entity/Category.h \
    src/entity/Subcategory.h \
    src/entity/Record.h \
    src/repository/UserRepository.h \
    src/util/FileUtil.h \
    src/util/PasswordUtil.h \
    src/util/WindowUtil.h \
    src/common/Date.h \
    src/Database.h \
    src/LocalUser.h \
    src/utils.h \
    src/test.h \
    src/window/UpdateCategoryWindow.h \
    src/window/UpdateSubcategoryWindow.h \
    src/windows.h

FORMS += \
    src/window/CategoryWindow.ui \
    src/window/CreateRecordWindow.ui \
    src/window/ForgotPasswordWindow.ui \
    src/window/LoginWindow.ui \
    src/window/MainWindow.ui \
    src/window/SignUpWindow.ui \
    src/window/SubcategoryWindow.ui \
    src/window/UpdateCategoryWindow.ui \
    src/window/UpdateSubcategoryWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
