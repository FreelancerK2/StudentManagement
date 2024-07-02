#pragma once
#include <iostream>
#include <string>
#include "Student.cpp"
using namespace std;
class Graduate : public Student {
private:
    string researchTopic;

public:
    //Default constructor
    Graduate() : Student(),researchTopic("Unknown"){}
    // Constructor           
    Graduate(string f, string l, const string& date, int id, string research) : Student(f, l, date, id), researchTopic(research) {}
 
    // Override the displayDetails function
    void displayDetails()override {
        Student ::displayDetails();
        cout << researchTopic << endl;
    } 

    // Function to Type of Student
    string getType() const override{
        return "Graduate";
    }

    // Write to file
    std::string toString() const override {
        std::ostringstream oss;
        oss <<"Graduate,"<< firstName << ","<< lastName << "," << dob<< ","<< studentID<< "," <<researchTopic<<endl;
        return oss.str();
    }

    // Read from file
    void fromString(const std::string &str) override {
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
        getline(iss, token, ',');
        researchTopic = token;
    }
 

    // Accessor for research topic
    string getResearchTopic() const {
        return researchTopic;
    }

    // Mutator for research topic
    void setResearchTopic(string research) {
        researchTopic = research;
    }
}; 