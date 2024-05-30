#include "Date.h"

Date::Date()
{
    reset_to_defaults();
}

Date::Date(
    const std::size_t day,
    const std::size_t month,
    const std::size_t year)
{
    m_year = year;
    m_month = month;
    m_day = day;
    m_format = DEFAULT_FORMAT;
    m_delimiter = DEFAULT_DELIMITER;

    if (!is_valid_date())
    {
        reset_to_defaults();
    }
}

Date::Date(
    const std::size_t day,
    const std::size_t month,
    const std::size_t year,
    const std::string format)
{
    m_year = year;
    m_month = month;
    m_day = day;
    m_format = format;
    m_delimiter = DEFAULT_DELIMITER;

    if (!is_valid_date())
    {
        reset_to_defaults();
    }
}

Date::Date(
    const std::size_t day,
    const std::size_t month,
    const std::size_t year,
    const std::string format,
    const std::string delimiter)
{
    m_year = year;
    m_month = month;
    m_day = day;
    m_format = format;
    m_delimiter = delimiter;

    if (!is_valid_date())
    {
        reset_to_defaults();
    }
}

void Date::increase()
{
    if (is_last_day_of_the_year())
    {
        ++m_year;
        m_month = 1;
        m_day = 1;
    }
    else if (is_last_day_of_the_month())
    {
        ++m_month;
        m_day = 1;
    }
    else
    {
        ++m_day;
    }
}

void Date::increase(int days)
{
    int totalDays = days + m_day;
    int totalMonths = 0;
    int totalYears = 0;

    while (totalDays > 0) {
        int daysInCurrentMonth = getDaysInMonth(m_month + totalMonths, m_year + totalYears);
        if (totalDays <= daysInCurrentMonth) {
            m_day = totalDays;
            break;
        }
        totalDays -= daysInCurrentMonth;
        totalMonths++;
    }

    totalMonths += m_month;
    while (totalMonths > 0) {
        if (totalMonths <= 12) {
            m_month = totalMonths;
            break;
        }
        totalMonths -= 12;
        totalYears++;
    }

    m_year += totalYears;
}

bool isleapyear(int year) {
  
        return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

size_t Date::getDaysInMonth(const std::size_t month, const std::size_t year) {
    switch (month) {
    case 1: return 31;
    case 3: return 31;
    case 5: return 31;
    case 7: return 31;
    case 8: return 31;
    case 10: return 31;
    case 12: return 31;
    case 2: return isleapyear(year) ? 29 : 28;
    case 4: return 30;
    case 6: return 30;
    case 9: return 30;
    case 11: return 30;
	default: return 0;
     }
}

void Date::decrease() {
    m_day--;

    // ≈сли день стал отрицательным, то переходим к предыдущему мес€цу
    if (m_day <= 0) {
        m_day = getDaysInMonth(m_month - 1, m_year);  // ѕолучаем количество дней в предыдущем мес€це
        m_month--;

        // ≈сли мес€ц стал отрицательным, то переходим к предыдущему году
        if (m_month <= 0) {
            m_month = 12;
            m_year--;
        }
    }
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        m_day = other.m_day;
        m_month = other.m_month;
        m_year = other.m_year;
        m_format = other.m_format;
        m_delimiter = other.m_delimiter;
    }
    return *this;
}
void Date::reset_to_defaults()
{
    m_year = DEFAULT_YEAR;
    m_month = DEFAULT_MONTH;
    m_day = DEFAULT_DAY;
    m_format = DEFAULT_FORMAT;
    m_delimiter = DEFAULT_DELIMITER;
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    if (d.m_format == "ddmmyyyy")
    {
        os << d.m_day << d.m_delimiter << d.m_month << d.m_delimiter << d.m_year;
    }
    else if (d.m_format == "mmddyyyy")
    {
        os << d.m_month << d.m_delimiter << d.m_day << d.m_delimiter << d.m_year;
    }
    else if (d.m_format == "yyyyddmm")
    {
        os << d.m_year << d.m_delimiter << d.m_day << d.m_delimiter << d.m_month;
    }
    else
    {
        os << d.m_year << d.m_delimiter << d.m_month << d.m_delimiter << d.m_day;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Date& d)
{
    is >> d.m_day >> d.m_month >> d.m_year;
    if (!d.is_valid_date())
    {
        d.reset_to_defaults();
    }
    return is;
}

bool Date::is_leap_year() const
{
    return ((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0);
}

bool Date::is_february() const
{
    return m_month == FEB;
}

bool Date::is_28day_february() const
{
    return m_month == FEB && !is_leap_year();
}

bool Date::is_29day_february() const
{
    return m_month == FEB && is_leap_year();
}

bool Date::is_30day_month() const
{
    return m_month == APR || m_month == JUN || m_month == SEP || m_month == NOV;
}

bool Date::is_31day_month() const
{
    return !is_february() && !is_30day_month();
}

bool Date::is_valid_date() const
{
    bool result = true;

    if (m_day > 31)
    {
        result = false;
    }

    if (m_month > 12)
    {
        result = false;
    }

    if (is_28day_february() && m_day > 28)
    {
        result = false;
    }

    if (is_29day_february() && m_day > 29)
    {
        result = false;
    }

    if (is_30day_month() && m_day > 30)
    {
        result = false;
    }

    return result;
}

bool Date::is_last_day_of_the_year() const
{
    return m_month == DEC && m_day == 31;
}

bool Date::is_last_day_of_the_month() const
{
    bool result = true;

    if (
        (is_28day_february() && m_day != 28) ||
        (is_29day_february() && m_day != 29) ||
        (is_30day_month() && m_day != 30) ||
        (is_31day_month() && m_day != 31)
        )
    {
        result = false;
    }

    return result;
}

bool Date::operator==(const Date& other) const {
    return (m_day == other.m_day && m_month == other.m_month && m_year == other.m_year);
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator>(const Date& other) const {
    if (m_year > other.m_year) {
        return true;
    }
    else if (m_year == other.m_year) {
        if (m_month > other.m_month) {
            return true;
        }
        else if (m_month == other.m_month) {
            return m_day > other.m_day;
        }
    }
    return false;
}

bool Date::operator<(const Date& other) const {
    if (m_year < other.m_year) {
        return true;
    }
    else if (m_year == other.m_year) {
        if (m_month < other.m_month) {
            return true;
        }
        else if (m_month == other.m_month) {
            return m_day < other.m_day;
        }
    }
    return false;
}

Date& Date::operator+=(const Date& other) {
    int daysToAdd = other.m_day;
    int monthsToAdd = other.m_month;
    int yearsToAdd = other.m_year;

    // ”читываем перенос дней
    int daysInCurrentMonth = getDaysInMonth(m_month, m_year);
    if (m_day + daysToAdd > daysInCurrentMonth) {
        daysToAdd -= (daysInCurrentMonth - m_day);
        monthsToAdd++;
    }

    // ”читываем перенос мес€цев
    if (m_month + monthsToAdd > 12) {
        monthsToAdd -= (12 - m_month);
        yearsToAdd++;
    }

    // ”читываем перенос лет
    if (m_year + yearsToAdd < 0) {
        yearsToAdd -= (1 - m_year);
    }

    // ќбновл€ем значени€ даты
    m_day += daysToAdd;
    m_month += monthsToAdd;
    m_year += yearsToAdd;

    return *this;
}

Date& Date::operator-=(const Date& other) {
    int daysToSubtract = other.m_day;
    int monthsToSubtract = other.m_month;
    int yearsToSubtract = other.m_year;

    // ”читываем перенос дней
    int daysInCurrentMonth = getDaysInMonth(m_month, m_year);
    if (m_day < daysToSubtract) {
        monthsToSubtract--;
        daysToSubtract = daysInCurrentMonth - (daysToSubtract - m_day);
    }
    else {
        daysToSubtract -= m_day;
    }

    // ”читываем перенос мес€цев
    if (monthsToSubtract < 0) {
        yearsToSubtract--;
        monthsToSubtract += 12;
    }

    // ”читываем перенос лет
    if (yearsToSubtract < 0) {
        yearsToSubtract -= (1 - m_year);
    }

    // ќбновл€ем значени€ даты
    m_day -= daysToSubtract;
    m_month -= monthsToSubtract;
    m_year -= yearsToSubtract;

    return *this;
}