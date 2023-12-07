#include "SubcategoryWindow.h"
#include "ui_SubcategoryWindow.h"

SubcategoryWindow::SubcategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubcategoryWindow) {
    ui->setupUi(this);
}

SubcategoryWindow::~SubcategoryWindow() {
    delete ui;
}
