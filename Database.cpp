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

/**
 * @brief Creates a table.
 * @param query Qt SQL query object.
 * @param tableName The name of the table.
 * @param sql The essential SQL of the table (inside the parentheses).
 */
void createTable(QSqlQuery& query, const QString& tableName, const QString& sql) {
    // query.exec("DROP TABLE IF EXISTS " + tableName + ";");
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
        qDebug() << "Database connected successfully: " << databaseLabel.toStdString().c_str();
    }

    // Create tables
    QSqlQuery query;
    createTable(
        query,
        "user",
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL,"
        "auth_string TEXT NOT NULL,"
        "email TEXT NOT NULL");
    createTable(
        query,
        "category",
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "user_id INTEGER NOT NULL,"
        "name TEXT NOT NULL,"
        "FOREIGN KEY (user_id) REFERENCES user(id)");

    // Initialize repositories
    userRepository = UserRepository();
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
