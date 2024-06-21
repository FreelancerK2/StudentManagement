#pragma once
#include <fstream>
using namespace std;
// Base class
class Course {
protected:
    std::string courseName;
    int courseID;  
    double duration;
 
public:
    // Default Constructor
    Course() : courseName("Unknown"), courseID(0), duration(0) {}
 
    // Constructor
    Course(const std::string& name, int id,double duration )
        : courseName(name), courseID(id), duration(duration) {}

    // Function to string type Course
    virtual string getType() const = 0;

    // Function to display Course details
    virtual void displayInfo() const {
        std::cout <<setw(20)<< courseName <<setw(12)<< courseID<<setw(12)<<duration<<setw(25)<<getType()<<setw(25);
    } 

    // Function write to file
    virtual void save(std::ofstream &out) const {
        out.write(reinterpret_cast<const char*>(&courseID), sizeof(courseID));
        size_t nameLength = courseName.size();
        out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        out.write(courseName.c_str(), nameLength);
        out.write(reinterpret_cast<const char*>(&duration), sizeof(duration));
    }

    //Function read from file
    virtual void load(std::ifstream &in) {
        in.read(reinterpret_cast<char*>(&courseID), sizeof(courseID));
        size_t nameLength;
        in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        courseName.resize(nameLength);
        in.read(&courseName[0], nameLength);
        in.read(reinterpret_cast<char*>(&duration), sizeof(duration));
    }
    // Access CourseID
    int getCourseID() const {
        return courseID;
    }
    // Access CourseName
    std::string getName() const { 
        return courseName;
    }
    // Access duration
    double getDuration() const {
        return duration;
    }
    // Set new Duration
    void setDuration(double duration){
        this->duration = duration;
    } 
    // Set new Name
    void setName(std::string name) {
        courseName = name;
    }
    // Set new ID
    void setId(int id) {
        courseID = id;
    }
    // Destructor
    virtual ~Course() {}  
};