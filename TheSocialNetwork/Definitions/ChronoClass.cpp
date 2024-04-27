#include "E:/Programming/TheSocialNetwork/TheSocialNetwork/Headers/ChronoClass.hpp"

Date::Date() : day(0), month(0), year(0) {}
Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}
bool operator == (Date& d1, Date& d2) {
    return( (d1.day == d2.day) && (d1.month == d2.month) && (d1.year == d2.year) );
}
void Date::operator = (const Date& d2) {
    day = d2.day;
    month = d2.month;
    year = d2.year;
}
void Date::print() const {
    if (day == 0 || day > 31 || month == 0 || month > 12 || year <= 0) {
        cout << "Date is invalid or unspecified" << endl;
    }
    else {
        cout << day << "/" << month << "/" << year << endl;
    }
}
