#pragma once
#include <iostream>
#include <string>

class Scope
{
public:
    Scope(const auto &name = "") :
        m_name(name)
    {
        std::cout << "\nscope in: [" + m_name + "]\n";
    }

    ~Scope()
    {
        std::cout << "scope out: [" + m_name + "]\n";
    }

private:
    std::string m_name;
};