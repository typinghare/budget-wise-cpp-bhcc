#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#include "repository/UserRepository.h"
#include "repository/UserInfoRepository.h"
#include "repository/CategoryRepository.h"
#include "repository/SubcategoryRepository.h"
#include "repository/RecordRepository.h"

/**
 * @brief General manager. It holds all repositories.
 */
class Database {
private:
    static Database* INSTANCE;

    /**
     * @brief Set the only constructor to private to prevent this class to be instancialized.
     */
    Database();

    /**
     * @brief Initializes tables; creates tables if tables do not exist.
     */
    void createTables();

    /**
     * @brief Drops a table.
     * @param tableName The name of the table to drop.
     */
    void dropTable(const QString& tableName);

    /**
     * @brief Creates a table.
     * @param tableName The name of the table to create.
     * @param sql The essential part of the sql statement (in the parenthesis).
     */
    void createTable(const QString& tableName, const QString& sql);

public:
    /**
     * @brief Returns an database instance (singleton).
     */
    static Database* getInstance();

public:
    ~Database();

    /**
     * @brief Returns the user repository.
     */
    UserRepository getUserRepository();

    /**
     * @brief Returns the user info repository.
     */
    UserInfoRepository getUserInfoRepository();

    /**
     * @brief Returns the category repository.
     */
    CategoryRepository getCategoryRepository();

    /**
     * @brief Returns the subcategory repository.
     */
    SubcategoryRepository getSubcategoryRepository();

    /**
     * @brief Returns the record repository.
     * @return
     */
    RecordRepository getRecordRepository();

private:
    QSqlDatabase db;

    // Repositories
    UserRepository userRepository;
    UserInfoRepository userInfoRepository;
    CategoryRepository categoryRepository;
    SubcategoryRepository subcategoryRepository;
    RecordRepository recordRepository;
};

#endif // DATABASE_H
