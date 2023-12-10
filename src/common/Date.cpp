#include "Date.h"

Date::Date(const short year, const short month, const short day):
    year(year),
    month(month),
    day(day) {
}

short Date::getYear() const {
    return year;
}

short Date::getMonth() const {
    return month;
}

short Date::getDay() const {
    return day;
}
