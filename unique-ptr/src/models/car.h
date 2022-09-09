#pragma once

#include <string>
#include <iostream>

class Car
{
public:
    Car(const auto &name) :
        m_name(name)
    {
        std::cout << "---> created [" << m_name << "]\n";
    }

    ~Car()
    {
        std::cout << "<--- destroyed [" << m_name << "]\n";
    }

    void drive()
    {
        std::cout << "driving [" << m_name << "]\n";
    }

    void print_address()
    {
        std::cout << "car [" << m_name << "], address: " << this << "\n";
    }

private:
    std::string m_name;
};