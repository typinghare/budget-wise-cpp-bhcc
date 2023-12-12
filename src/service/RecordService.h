#ifndef RECORDSERVICE_H
#define RECORDSERVICE_H

#include <QList>

#include "src/repository/RecordRepository.h"

class RecordService {
public:
    RecordService();

    QList<Record*> getAllRecords(unsigned int userId);
};

#endif // RECORDSERVICE_H
