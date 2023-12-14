#include "Dummy.h"

#include <QDateTime>

#include "src/Database.h"

QDateTime getDateTime(const QString dateString) {
    return QDateTime::fromString(dateString, "MM/dd/yyyy");
}

void Dummy::makeDummyRecords() {
    auto recordRepository = Database::getInstance()->getRecordRepository();

    recordRepository.create(1, 2, 4, getDateTime("05/01/2023"), 3514);
    recordRepository.create(1, 1, 1, getDateTime("05/10/2023"), -1500);
    recordRepository.create(1, 1, 2, getDateTime("05/17/2023"), -84.23);

    recordRepository.create(1, 2, 4, getDateTime("06/01/2023"), 3672);
    recordRepository.create(1, 1, 1, getDateTime("06/10/2023"), -1500);
    recordRepository.create(1, 1, 2, getDateTime("06/17/2023"), -92.33);
    recordRepository.create(1, 2, 0, getDateTime("06/17/2023"), 300);
}
