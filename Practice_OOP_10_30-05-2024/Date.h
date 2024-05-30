#pragma once
#include <iostream>
#include <cstddef>
#include <string>

// 

class Date
{
public:
    Date();

    Date(
        const std::size_t day,
        const std::size_t month,
        const std::size_t year);

    Date(
        const std::size_t day,
        const std::size_t month,
        const std::size_t year,
        const std::string format);

    Date(
        const std::size_t day,
        const std::size_t month,
        const std::size_t year,
        const std::string format,
        const std::string delimiter);

    void set_year(const std::size_t year) { m_year = year; }
    void set_month(const std::size_t month) { m_month = month; }
    void set_day(const std::size_t day) { m_day = day; }
    void set_format(const std::string format) { m_format = format; }
    void set_delimiter(char delimiter) { m_delimiter = delimiter; }

    std::size_t get_year() const { return m_year; }
    std::size_t get_month() const { return m_month; }
    std::size_t get_day() const { return m_day; }
    std::string get_format() const { return m_format; }
    std::string get_delimiter() const { return m_delimiter; }

    size_t getDaysInMonth(const std::size_t month, const std::size_t year);  // Получаем количество дней в месяце, доп. параметр год

    void increase();
    void increase(int); //Увеличиваем дату на кол-во дней 
    void decrease();
    void reset_to_defaults();
    bool is_leap_year() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& d);
    friend std::istream& operator>>(std::istream& is, Date& d);
    
    Date& operator=(const Date& other);
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
    Date& operator++() {
        increase();
        return *this;
    }
    Date operator++(int) {
        Date copy(*this);
        increase();
        return copy;
    }

	Date& operator--() {
		decrease();
		return *this;
	}
	Date operator--(int) {
		Date copy(*this);
		decrease();
		return copy;
	}
    Date& operator+=(const Date& other);
    Date& operator-=(const Date& other);
    

private:
    std::size_t m_year;
    std::size_t m_month;
    std::size_t m_day;
    std::string m_format;
    std::string m_delimiter;

    const std::size_t DEFAULT_YEAR = 1970;
    const std::size_t DEFAULT_MONTH = 1;
    const std::size_t DEFAULT_DAY = 1;
    const std::string DEFAULT_FORMAT = "ddmmyyyy";
    const std::string DEFAULT_DELIMITER = ".";
    enum { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };

    bool is_february() const;
    bool is_28day_february() const;
    bool is_29day_february() const;
    bool is_30day_month() const;
    bool is_31day_month() const;
    bool is_valid_date() const;

    bool is_last_day_of_the_year() const;
    bool is_last_day_of_the_month() const;
};

