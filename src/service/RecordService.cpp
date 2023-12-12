#include "RecordService.h"

#include "src/Database.h"

RecordService::RecordService() {
}

QList<Record*> RecordService::getAllRecords(unsigned int userId) {
    auto recordRepository = Database::getInstance()->getRecordRepository();
    return recordRepository.getAll(userId);
}
