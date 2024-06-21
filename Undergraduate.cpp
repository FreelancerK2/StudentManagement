#pragma once 
using namespace std;
class Undergraduate : public Student {
private:
    string major;
 
public:
    Undergraduate(): Student(),major("Unknown") {}
    // Constructor               
    Undergraduate(string f, string l, const string& date, int id, string major) : Student(f, l, date, id), major(major) {}

    // Override the displayDetails function
    void displayDetails() override{
        Student ::displayDetails();
        cout << major << endl;
    }
 
    // Function get type of student
    string getType() const override{
        return "Undergraduate";
    } 

    // Write to file
    std::string toString() const override {
        std::ostringstream oss;
        oss <<"Undergraduate,"<< firstName << ","<< lastName << "," << dob<< ","<< studentID<< "," <<major<<endl;
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
        major = token;
    }
 
    // Accessor for major
    string getMajor() const {
        return major;
    }

    // Mutator for major
    void setMajor(string major) {
       this->major = major;
    }
}; 