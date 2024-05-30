// Practice_OOP_10_30-05-2024.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Date.h"

int main()
{
    Date defaultDate;
    std::cout << defaultDate << "\n";

    const std::size_t FIVE_WEEKS = 35;

    for (std::size_t i = 0; i < FIVE_WEEKS; ++i)
    {
        defaultDate.increase();
        std::cout << defaultDate << "\n";
    }

    Date today(31,5,2024);
    std::cout << "\n\n" << today << "\n";
    today.increase();

    std::cout << "Tomorrow is " << today << "\n";
    today.increase(100);
    std::cout << "Today + 100 days is " << today << "\n";

    for (std::size_t i = 0; i < FIVE_WEEKS; ++i)
    {
        today.increase();
        std::cout << today << "\n";
    }

    std::cout
        << "\nEnter your birthday date (use ddmmyyyy format)."
        << "\nPress <Enter> key after each token of date."
        << "\nFor example: 24<Enter>12<Enter>1980<Enter>):\n";
    Date yourBirthdayDate;
    std::cin >> yourBirthdayDate;
    std::cout << "You was born in " << yourBirthdayDate << "\n\n";
}




