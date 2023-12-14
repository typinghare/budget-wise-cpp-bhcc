#include "RecordService.h"

#include <QDateTime>

#include "src/Database.h"

RecordService::RecordService() {
}

QList<Record*> RecordService::getAllRecords(unsigned int userId, bool desc) {
    auto recordRepository = Database::getInstance()->getRecordRepository();
    return recordRepository.getAll(userId, desc);
}

QSharedPointer<Record> RecordService::createRecord(
    unsigned int userId,
    unsigned int categoryId,
    unsigned int subcategoryId,
    float amount) {
    auto recordRepository = Database::getInstance()->getRecordRepository();
    auto createdAt = QDateTime::currentDateTime();
    QSharedPointer<Record> record(recordRepository.create(userId, categoryId, subcategoryId, createdAt, amount));
    if (record.isNull()) {
        return record;
    }

    return record;
}

bool RecordService::deleteLastRecord(unsigned int userId) {
    // // Get the user's last record
    // auto recordRepository = Database::getInstance()->getRecordRepository();
    // QSharedPointer<Record> record(recordRepository.getLast(userId));
    // if (record.isNull()) {
    //     return false;
    // }

    // // Get the user's current balance
    // auto userInfoRepository = Database::getInstance()->getUserInfoRepository();
    // QSharedPointer<UserInfo> userInfo(userInfoRepository.getByUserId(userId));
    // if (userInfo.isNull()) {
    //     return false;
    // }

    // // Delete the record
    // float amount = record->getAmount();
    // bool removeRecordResult = recordRepository.remove(record->getId());
    // if (!removeRecordResult) {
    //     return false;
    // }

    // // Add the amount back to the balance; update the user info
    // float newBalance = userInfo->getBalance() + amount;
    // userInfoRepository.updateBalance(userId, newBalance);

    return true;
}
