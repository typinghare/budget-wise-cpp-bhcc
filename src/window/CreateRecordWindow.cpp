#include "CreateRecordWindow.h"
#include "ui_CreateRecordWindow.h"

CreateRecordWindow::CreateRecordWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateRecordWindow) {
    ui->setupUi(this);

    // Set window title
    setWindowTitle("Create Record");

    // Events
    connect(ui->okButton, &QPushButton::clicked, this, &CreateRecordWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CreateRecordWindow::onCancelButtonClicked);
}

CreateRecordWindow::~CreateRecordWindow() {
    delete ui;
}

void CreateRecordWindow::setSubcategories(QList<Subcategory *> subcategoryList) {
    int index = 0;
    for (auto &subcategory: subcategoryList) {
        unsigned int subcategoryId = subcategory->getId();
        QString subcategoryName = subcategory->getName();
        subcategoryIdMap[index++] = subcategoryId;
        ui->subcategoryCombo->addItem(subcategoryName);
    }
}

void CreateRecordWindow::setAmount(float amount) {
    ui->amountInput->setText(QString::number(amount));
}

int CreateRecordWindow::getSubcategoryCount() {
    return ui->subcategoryCombo->count();
}

void CreateRecordWindow::onOkButtonClicked() {
    int currentIndex = ui->subcategoryCombo->currentIndex();
    unsigned int subcategoryId = subcategoryIdMap[currentIndex];
    float amount = ui->amountInput->text().toFloat();

    emit confirmed(subcategoryId, amount);
}

void CreateRecordWindow::onCancelButtonClicked() {
    setAmount(0);
    emit canceled();
}
