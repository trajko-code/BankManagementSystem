/**
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-09-30
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once

//#ifdef STUDENT_EXPORTS
#define STUDENT_API _declspec(dllexport)
//#else
//#define STUDENT_API _declspec(dllimport)
//#endif

#include "IDatabase.h"

class STUDENT_API Student {
public:
    /**
        * @brief Default contstructor
        *
        */
    Student(IDatabase* databaseConnector);

    /**
        * @brief Default destructor
        *
        */
    ~Student();

    Student(const Student&) = delete;
    Student& operator=(const Student&) = delete;
    Student(Student&&) = delete;
    Student& operator=(const Student&&) = delete;

    /**
        * @brief This is the function used to query index number
        *
        * @param std::string Name
        * @return int Index
        */
    int QueryIndex(std::string Name);

    /**
        * @brief This is the function used to query student name
        *
        * @param int index
        * @return std::string Name
        */
    std::string QueryName(int index);

private:
    IDatabase* m_databaseConnector;
};

