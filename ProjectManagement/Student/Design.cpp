#pragma once
class Design : public Course {
private:
    std::string tools; 
public: 
    // Default constructor
    Design() : Course() , tools("Unknown") {}
    // Constructor
    Design(const std::string& name, int id, double duration ,const std::string& tools)
        : Course(name, id, duration), tools(tools) {}
    // Show information
    void displayInfo() const override {
        Course::displayInfo();
        std::cout << tools << std::endl;
    } 
    // Function write to file
    void save(std::ofstream &out) const override{
        Course::save(out);
        size_t toolslength = tools.size();
        out.write(reinterpret_cast<const char*>(&toolslength), sizeof(toolslength));
        out.write(tools.c_str(), toolslength);
    } 
    // Function read from file
    void load(std::ifstream &in) override {
        Course::load(in);
        size_t toolslength;
        in.read(reinterpret_cast<char*>(&toolslength), sizeof(toolslength));
        tools.resize(toolslength);
        in.read(&tools[0], toolslength);
    } 
    // Function getType
    string getType() const override{
        return "Design";
    }
    // Function Access Object
    string getTools() const {
        return tools;
    }
    // Functon set new Tools
    void setTools(string tools){
        this->tools = tools;
    }
};