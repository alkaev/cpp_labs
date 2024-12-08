#include "employees.h"
#include "bin_manip.h"
#include <iostream>
#include <fstream>
#include <vector>

void readEmployees(std::ifstream &ifs, int32_t size, StaffTeam::EmployeesArray &arr)
{
    StaffTeam::Employee *employee;

    for (size_t i = 0; i < size; i++)
    {
        int32_t type;
        ifs >> manip::read_le_int32(type);

        if (type == 1)
        {
            employee = new StaffTeam::Developer();
        }
        else if (type == 2) 
        {
            employee = new StaffTeam::SalesManager();
        }
        ifs >> *employee;
        arr.add(employee);
    }
}

int main()
{
    std::string command;
    StaffTeam::EmployeesArray arr;
    while (std::cin >> command) {

        if (command == "exit") 
            break;

        if (command == "add")
        {
            int type;
            std::cin >> type;

            StaffTeam::Employee *employee;

            if (type == 1)
            {
                employee = new StaffTeam::Developer();
            }
            else if (type == 2)
            {
                employee = new StaffTeam::SalesManager();
            }

            std::cin >> *employee;
            arr.add(employee);
        }
        else if (command == "list")
        {
            std::cout << arr << std::endl;
        }
        else if (command == "load")
        {
            std::string filename;
            std::cin >> filename;

            std::ifstream ifs(filename, std::ios::binary);

            if (!ifs)
                throw std::runtime_error("Unable to open file: " + filename);

            int32_t size;
            ifs >> manip::read_le_int32(size);

            readEmployees(ifs, size, arr);

            ifs.close();
        }
        else if (command == "save")
        {
            std::string filename;
            std::cin >> filename;

            std::ofstream ofs(filename, std::ios::binary);

            if (!ofs)
                throw std::runtime_error("Unable to open file: " + filename);

            ofs << manip::write_le_int32(arr.get_size());

            for (size_t i = 0; i < arr.get_size(); ++i)
                ofs << *arr.get_employee(i);

            ofs.close();
        }
        else
        {
            std::cerr << "Unknown command" << std::endl;
        }
    }
}