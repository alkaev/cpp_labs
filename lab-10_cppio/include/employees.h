#pragma once

#include <fstream>
#include <ostream>
#include <stdint.h>
#include <string>
#include <vector>

namespace StaffTeam
{

    class Employee
    {
    public:
        friend std::ostream &operator<<(std::ostream &os, const Employee &employee);
        friend std::istream &operator>>(std::istream &is, Employee &employee);
        friend std::ofstream &operator<<(std::ofstream &ofs, const Employee &employee);
        friend std::ifstream &operator>>(std::ifstream &ifs, Employee &employee);

        virtual int salary() const = 0;
        virtual ~Employee() = default;

    protected:
        virtual void printConsole(std::ostream &os) const = 0; // prints the information about the employees
        virtual void readConsole(std::istream &is) = 0;         // reads the information about the employees
        virtual void writeBinary(std::ostream &os) const = 0;  // prints in the binary format
        virtual void readBinary(std::istream &is) = 0;

        std::string _name;
        int32_t _base_salary;
    };

    class Developer : public Employee 
    {
    public:
        int salary() const;

    private:
        void printConsole(std::ostream &os) const override;
        void writeBinary(std::ostream &os) const override;
        void readConsole(std::istream &is) override;
        void readBinary(std::istream &is) override;

        bool _has_bonus;
    };

    class SalesManager : public Employee
    {
    public:
        int salary() const;

    private:
        void printConsole(std::ostream &os) const override;
        void writeBinary(std::ostream &os) const override;
        void readConsole(std::istream &is) override;
        void readBinary(std::istream &is) override;

        int32_t _sold_nm, _price;
    };

    class EmployeesArray
    {
    public:
        friend std::ostream &operator<<(std::ostream &os, const EmployeesArray &arr);      
        const Employee *get_employee(size_t index) const;

        void add(const Employee *e);
        int32_t get_size() const;
        int total_salary() const;      
        ~EmployeesArray();

    private:
        std::vector<const Employee*> _employees;
    };
}