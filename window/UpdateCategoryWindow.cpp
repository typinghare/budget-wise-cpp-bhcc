#include "UpdateCategoryWindow.h"
#include "ui_UpdateCategoryWindow.h"

UpdateCategoryWindow::UpdateCategoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateCategoryWindow) {
    ui->setupUi(this);

    // Events
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
}

UpdateCategoryWindow::~UpdateCategoryWindow() {
    delete ui;
}

void UpdateCategoryWindow::onOkButtonClicked() {
    QString categoryName = ui->categoryNameInput->text();
    ui->categoryNameInput->setText("");
    emit categoryNameConfirmed(categoryName);
    close();
}

void UpdateCategoryWindow::onCancelButtonClicked() {
    ui->categoryNameInput->setText("");
    onOkButtonClicked();
}
