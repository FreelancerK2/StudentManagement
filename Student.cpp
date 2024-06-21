#pragma once
#include<iostream>
#include <fstream>
#include <sstream>
#include "Secure.cpp"
using namespace std;
class Student {
protected: 
    string firstName, lastName , dob;
    int studentID;

public:                                        
    Student() : firstName(""), lastName(""), dob(""), studentID(0) {}
    // Constructor              
    Student(string f, string l, string date, int id) : firstName(f), lastName(l), dob(date), studentID(id) {
    }

    // Virtual function to display student details
    virtual void displayDetails(){
        cout << setw(15) << Secure::concatStrings(firstName,lastName) << setw(15) << dob << setw(14) << studentID << setw(24) << getType()<<setw(27);
    }

    // Function GetType Course
    virtual string getType() const = 0;

    // Write to file
    virtual std::string toString() const {
        std::ostringstream oss;
        oss << firstName << "," << lastName << "," << dob<< ","<< studentID;
        return oss.str();
    }
    // Read from file
    virtual void fromString(const std::string &str) {
        std::istringstream iss(str);
        std::string token;
        getline(iss, token, ',');
        firstName = token;
        getline(iss, token, ',');
        lastName = token;
        getline(iss, token, ',');
        dob = token;
        getline(iss, token, ',');
        studentID = std::stoi(token); 
    }


    // Accessor for student FirstName
    string getFirstName() const {
        return firstName;
    }

    // Accessor for student LastName
    string getLastName() const {
        return lastName;
    }

    // Accessor for student Name
    string getDob() const {
        return dob;
    } 

    // Accessor for student ID
    int getStudentID() const {
        return studentID;
    }
 
    // Update FirstName
    void setFirstName(const string& first){
        firstName = first;
    }

    // Update LastName
    void setLastName(const string& last){
        lastName = last;
    }

    //Update Age
    void setDob(string date) {
        dob = date;
    }

    // Update ID
    void setID(int id) {
        studentID = id;
    }

    // Virtual destructor
    virtual ~Student() = default;
}; 