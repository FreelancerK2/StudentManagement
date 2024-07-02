#pragma once
using namespace std;
class StudentRepository {
public:
    // Add student
    virtual void addStudent(Student* student) = 0; 
    // View all students
    virtual void viewStudents() = 0;
    // Update student                                                             
    virtual void updateStudent(const int& id) = 0;
    // Delete student
    virtual void deleteStudent(const int& id) = 0;
};  