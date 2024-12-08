#include "employees.h"
#include "bin_manip.h"
#include <fstream>
#include <iostream>
#include <string>

namespace StaffTeam
{
    std::ostream &operator<<(std::ostream &os, const Employee &employee)
    {
        employee.printConsole(os);
        return os;
    }

    std::istream &operator>>(std::istream &is, Employee &employee)
    {
        employee.readConsole(is);
        return is;
    }

     std::ofstream &operator<<(std::ofstream &ofs, const Employee &employee)
    {
        employee.writeBinary(ofs);
        return ofs;
    }

    std::ifstream &operator>>(std::ifstream &ifs, Employee &employee)
    {
        employee.readBinary(ifs);
        return ifs;
    }

    void Employee::printConsole(std::ostream &os) const
    {
        os << "Name: " << _name << std::endl;
        os << "Base Salary: " << _base_salary << std::endl;
    }

    void Employee::readConsole(std::istream &is) 
    { 
        is >> _name >> _base_salary; 
    }

    void Employee::writeBinary(std::ostream &os) const
    {
        os << manip::write_c_str(_name.c_str()) << manip::write_le_int32(_base_salary);
    }

    void Employee::readBinary(std::istream &is)
    {
        char name[101];
        is >> manip::read_c_str(name, sizeof(name)) >> manip::read_le_int32(_base_salary);
        _name = name;
    }
    // SalesManager

       int SalesManager::salary() const
    {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    void SalesManager::printConsole(std::ostream &os) const
    {
        os << "Sales Manager" << std::endl;
        Employee::printConsole(os);
        os << "Sold items: " << _sold_nm << std::endl;
        os << "Item price: " << _price;
    }

    void SalesManager::readConsole(std::istream &is)
    {
        Employee::readConsole(is);
        is >> _sold_nm >> _price;
    }

    void SalesManager::writeBinary(std::ostream &os) const
    {
        os << manip::write_le_int32(2);
        Employee::writeBinary(os);
        os << manip::write_le_int32(_sold_nm) << manip::write_le_int32(_price);
    }

    void SalesManager::readBinary(std::istream &is)
    {
        Employee::readBinary(is);
        is >> manip::read_le_int32(_sold_nm) >> manip::read_le_int32(_price);
    }

    //Developer 
    
    void Developer::printConsole(std::ostream &os) const
    {
        os << "Developer" << std::endl;
        Employee::printConsole(os);
        os << "Has bonus: " << (_has_bonus ? "+" : "-");
    }

    int Developer::salary() const
    {
        int salary = _base_salary;
        if (_has_bonus)
            salary += 1000;
        return salary;
    }

    void Developer::readConsole(std::istream &is)
    {
        Employee::readConsole(is);
        is >> _has_bonus;
    }

    void Developer::writeBinary(std::ostream &os) const
    {
        os << manip::write_le_int32(1);
        Employee::writeBinary(os);
        os << manip::write_bool(_has_bonus);
    }

    void Developer::readBinary(std::istream &is)
    {
        Employee::readBinary(is);
        is >> manip::read_bool(_has_bonus);
    }

    void EmployeesArray::add(const Employee *e)
    {
        _employees.push_back(e);
    }

    EmployeesArray::~EmployeesArray()
    {
        while (_employees.size())
        {
            delete _employees.back();
            _employees.pop_back();
        }
    }

    int EmployeesArray::total_salary() const
    {
        int salary_sum = 0;
        for (auto &employee : _employees)
            salary_sum += employee->salary();
        return salary_sum;
    }

    int32_t EmployeesArray::get_size() const
    {
        return _employees.size();
    }

    const Employee *EmployeesArray::get_employee(size_t index) const
    {
        return _employees[index];
    }

    std::ostream &operator<<(std::ostream &os, const EmployeesArray &arr)
    {
        for (size_t i = 1; i <= arr._employees.size(); i++)
            std::cout << i << ". " << *arr._employees[i - 1] << std::endl;
        os << "== Total salary: " << arr.total_salary() << std::endl;
        return os;
    }
}