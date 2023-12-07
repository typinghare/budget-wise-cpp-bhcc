#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#include "repository/UserRepository.h"
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
    CategoryRepository categoryRepository;
    SubcategoryRepository subcategoryRepository;
    RecordRepository recordRepository;
};

#endif // DATABASE_H
