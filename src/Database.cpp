#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "Database.h"

Database* Database::INSTANCE = nullptr;

Database* Database::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new Database();
    }

    return INSTANCE;
}

void Database::dropTable(const QString& tableName) {
    QSqlQuery query;
    bool succesfullyDropped = query.exec("DROP TABLE IF EXISTS " + tableName + ";");

    if (succesfullyDropped) {
        qDebug() << "Dropped table successfully:" << tableName.toStdString().c_str();
    } else {
        qDebug() << "Fail to drop table:" <<  tableName.toStdString().c_str();
    }
}

void Database::createTable(const QString& tableName, const QString& sql) {
    QSqlQuery query;
    bool succesfullyCreated = query.exec("CREATE TABLE IF NOT EXISTS " + tableName + "(" + sql + ");");

    if (succesfullyCreated) {
        qDebug() << "Created table successfully:" << tableName.toStdString().c_str();
    } else {
        qDebug() << "Fail to create table:" <<  tableName.toStdString().c_str();
    }
}

Database::Database() {
    QString databaseType = "QSQLITE";
    QString databaseName = "budget_wise";
    db = QSqlDatabase::addDatabase(databaseType);
    db.setDatabaseName(databaseName);

    if (!db.open()) {
        qDebug() << "Unable to open the database!";
        qDebug() << db.lastError().text();
    } else {
        QString databaseLabel = "(" + databaseType + ") " + databaseName;
        qInfo() << "Database connected successfully: " << databaseLabel.toStdString().c_str();
    }

    createTables();
}

void Database::createTables() {
    createTable(
        "user",
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "auth_string TEXT NOT NULL,"
        "email TEXT NOT NULL");
    createTable(
        "category",
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "FOREIGN KEY (user_id) REFERENCES user(id)");
    // dropTable(query, "subcategory");
    createTable(
        "subcategory",
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "category_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "FOREIGN KEY (user_id) REFERENCES user(id),"
        "FOREIGN KEY (category_id) REFERENCES category(id)");
}

UserRepository Database::getUserRepository() {
    return userRepository;
}

CategoryRepository Database::getCategoryRepository() {
    return categoryRepository;
}

SubcategoryRepository Database::getSubcategoryRepository() {
    return subcategoryRepository;
}

RecordRepository Database::getRecordRepository() {
    return recordRepository;
}
