#include "Dummy.h"

#include <QDateTime>

#include "src/Database.h"

QDateTime getDateTime(const QString dateString) {
    return QDateTime::fromString(dateString, "MM/dd/yyyy");
}

void Dummy::makeDummyRecords() {
    // Drop the record table
    auto db = Database::getInstance();
    db->dropTable("category");
    db->dropTable("subcategory");
    db->dropTable("record");
    db->createTables();

    auto categoryRepository = db->getCategoryRepository();
    auto subcategoryRepository = db->getSubcategoryRepository();
    auto recordRepository = db->getRecordRepository();

    // Categories
    categoryRepository.create(1, "Housing");        // 1
    categoryRepository.create(1, "Online");         // 2
    categoryRepository.create(1, "Pay");            // 3
    categoryRepository.create(1, "Income");         // 4

    // Subcategories
    subcategoryRepository.create(1, 1, "Rent");         // 1
    subcategoryRepository.create(1, 1, "Gas");          // 2
    subcategoryRepository.create(1, 1, "Electricity");  // 3
    subcategoryRepository.create(1, 2, "Rent");         // 4
    subcategoryRepository.create(1, 2, "Insurance");    // 5
    subcategoryRepository.create(1, 2, "Amazon");       // 6
    subcategoryRepository.create(1, 3, "Costco");       // 7
    subcategoryRepository.create(1, 3, "Grocery");      // 8
    subcategoryRepository.create(1, 4, "Salary");       // 9
    subcategoryRepository.create(1, 4, "Part-time");    // 10

    int _ = 10;

    // 05
    recordRepository.create(1, 4, _, getDateTime("05/01/2023"), 3514);
    recordRepository.create(1, 2, 4, getDateTime("05/10/2023"), -1500);
    recordRepository.create(1, 1, 3, getDateTime("05/17/2023"), -84.23);

    // 06
    recordRepository.create(1, 4, _, getDateTime("06/01/2023"), 3672);
    recordRepository.create(1, 2, 4, getDateTime("06/10/2023"), -1500);
    recordRepository.create(1, 1, 2, getDateTime("06/15/2023"), -92.33);
    recordRepository.create(1, 4, 0, getDateTime("06/25/2023"), 300);

    // 07
    recordRepository.create(1, 4, _, getDateTime("07/01/2023"), 3325);
    recordRepository.create(1, 2, 4, getDateTime("07/10/2023"), -1600);
    recordRepository.create(1, 2, 5, getDateTime("07/14/2023"), -399.99);
    recordRepository.create(1, 2, 6, getDateTime("07/29/2023"), -143.65);
}
