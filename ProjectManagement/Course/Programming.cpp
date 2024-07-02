#pragma once
using namespace std;

class Programming : public Course {
private: 
    std::string project;

public: 
    // Defautl constructor 
    Programming() : Course(), project("Unknown") {}

    // Constructor
    Programming(const std::string& name, int id, double duration ,std::string project)
        : Course(name, id, duration), project(project) {}
    // Display information
    void displayInfo() const override {
        Course::displayInfo();
        std::cout<< project << std::endl;
    } 
    // Function write to file
    void save(std::ofstream &out) const override{
        Course::save(out);
        size_t projectlength = project.size();
        out.write(reinterpret_cast<const char*>(&projectlength), sizeof(projectlength));
        out.write(project.c_str(), projectlength);
    }  
    // Function Read from file
    void load(std::ifstream &in) override {
        Course::load(in);
        size_t projectlength;
        in.read(reinterpret_cast<char*>(&projectlength), sizeof(projectlength));
        project.resize(projectlength);
        in.read(&project[0], projectlength);
    }
    // Access getType
    string getType() const override{
        return "Programming";
    } 
    // Accedd Object
    string getProject() const {
        return project;
    }
    // Set new Project
    void setProject(string project){
        this->project = project;
    }
};