#include "CreateRecordWindow.h"
#include "ui_CreateRecordWindow.h"

#include "src/Database.h"
#include "src/LocalUser.h"

CreateRecordWindow::CreateRecordWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CreateRecordWindow) {
    ui->setupUi(this);

    // Set window title
    setWindowTitle("Create Record");

    // Events
    connect(ui->okButton, &QPushButton::clicked, this, &CreateRecordWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CreateRecordWindow::onCancelButtonClicked);
    connect(ui->categoryCombo, QOverload<int>::of(&QComboBox::activated), this, &CreateRecordWindow::onComboBoxActivated);

    // Styles
    ui->amountStatusLabel->setStyleSheet("color: red");
}

CreateRecordWindow::~CreateRecordWindow() {
    delete ui;
}

void CreateRecordWindow::refreshCategories() {
    // Clear
    ui->categoryCombo->clear();
    categoryIdMap.clear();

    auto userId = LocalUser::get()->getId();
    auto categoryRepository = Database::getInstance()->getCategoryRepository();
    QList<Category*> categoryList = categoryRepository.getAll(userId);
    int index = 0;
    for (auto &category: categoryList) {
        int categoryId = category->getId();
        QString categoryName = category->getName();
        categoryIdMap[index++] = categoryId;
        ui->categoryCombo->addItem(categoryName);
    }

    loadSubcategories(categoryIdMap[0]);
}

void CreateRecordWindow::setAmount(double amount) {
    ui->amountInput->setText(QString::number(amount));
}

int CreateRecordWindow::getCategoryCount() {
    return ui->categoryCombo->count();
}

void CreateRecordWindow::onOkButtonClicked() {
    ui->amountStatusLabel->setText("");

    // Check whether the amount string is a number
    QString amountStr = ui->amountInput->text();
    bool isDouble = false;
    amountStr.toDouble(&isDouble);
    if (!isDouble) {
        ui->amountStatusLabel->setText("It is not a number!");
        return;
    }

    int categoryIndex = ui->categoryCombo->currentIndex();
    int subcategoryIndex = ui->subcategoryCombo->currentIndex();
    int categoryId = categoryIdMap[categoryIndex];
    int subcategoryId = subcategoryIdMap[subcategoryIndex];
    double amount = ui->amountInput->text().toDouble();
    qDebug() << categoryId;

    emit confirmed(categoryId, subcategoryId, amount);
}

void CreateRecordWindow::onCancelButtonClicked() {
    ui->amountStatusLabel->setText("");
    setAmount(0);
    emit canceled();
}

void CreateRecordWindow::onComboBoxActivated(int index) {
    int categoryId = categoryIdMap[index];
    loadSubcategories(categoryId);
}

void CreateRecordWindow::loadSubcategories(unsigned int categoryId) {
    // Clear
    ui->subcategoryCombo->clear();
    subcategoryIdMap.clear();

    // (empty) - No subcategory
    ui->subcategoryCombo->addItem("(not selected)");
    subcategoryIdMap[0] = 0;

    auto subcategoryRepository = Database::getInstance()->getSubcategoryRepository();
    QList<Subcategory*> subcategoryList = subcategoryRepository.getAllByCategoryId(categoryId);

    int _index = 1;
    for (auto &subcategory: subcategoryList) {
        int subcategoryId = subcategory->getId();
        QString subcategoryName = subcategory->getName();
        subcategoryIdMap[_index++] = subcategoryId;
        ui->subcategoryCombo->addItem(subcategoryName);
    }
}
