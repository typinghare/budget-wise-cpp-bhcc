#include <QApplication>

#include "windows.h"
#include "Database.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
