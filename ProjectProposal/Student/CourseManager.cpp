#include <fstream>
#include "Course.cpp"
#include "CourseRepository.cpp"
#include "Programming.cpp"
#include "Design.cpp"
#include "Protect.cpp "
using namespace std;  

class CourseManager : public CourseRepository {
private:
    std::vector<Course*> courses;
    string filename;
    // Find ID by each course
    vector<Course*>::iterator findCourseById(int id) {
        return std::find_if(courses.begin(), courses.end(), [id](Course* course) {
            return course->getCourseID() == id;
        });
    }
    // Check over Duplicate ID
    bool isDuplicateId(int id) const {
        return any_of(courses.begin(), courses.end(), [id](Course* course) { return course->getCourseID() == id; });
    }
 
public:
       // default constructor
       CourseManager(const std::string& filename) : filename(filename) {
    }

    // Function to add more course
    void addCourse(Course* course) {
        if (isDuplicateId(course->getCourseID())) {
            cout << "Course with ID " << course->getCourseID() << " already exists. Cannot add duplicate." << endl;
            delete course; // Prevent memory leak
        } else {
            courses.push_back(course);
            cout << "\nCourse added successfully." << endl;
        }
    }

    // Function to Display all course
    void viewCourses() override {                                                                                                
        cout <<"No."<< setw(11) << "Name" << setw(19) << "CourseID" << setw(20) << "Duration(Years)"<< setw(15) <<"Type" << setw(28) << "Project/Tools"<< endl;
        cout << string(97, '-') << endl;
        // Check for valid input
        if (courses.empty()) {
            throw std::invalid_argument("No courses available");
            return;
        } 
        int i = 1;     // applies a given function to each element in a range.
        std::for_each(courses.begin(), courses.end(), [&i](Course* course) {
        cout <<i++;
        course->displayInfo();
        }); 
    }
    // Function to update course
    void updateCourse(int id) {
    auto it = findCourseById(id);
        if (it != courses.end()) {
            std::cout << "Which item do you want to update?\n"
                      << "1. Name\n2. Duration\n3. CourseID\n";
            Programming* program = dynamic_cast<Programming*>(*it);
            Design* design = dynamic_cast<Design*>(*it);
            if (program) {            
                std::cout << "4. Project\n0. Exit\n\nEnter your choice: ";
            } 
            else if (design) {   
                std::cout << "4. Tools\n0. Exit\n\nEnter your choice:";
            }
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::string newName = Protect::getStringInput("Enter new name: ");
                    (*it)->setName(newName);
                    break;
                } 
                case 2: {
                    double newDuration = Protect::getDoubleInput("Enter new duration: ");
                     (*it)->setDuration(newDuration);
                    break;
                }
                case 3: {
                    int newId = Protect::getIntInput("Enter new ID: ");
                    Protect::validateId(id);
                    (*it)->setId(newId);
                    break;
                }
                case 4: {
                    if (program) {   
                        std::string newProject = Protect::getStringInput("Enter new Project: ");
                        program->setProject(newProject);
                    } else if (design) {      
                        std::string newTools = Protect::getStringInput("Enter new Tools: ");
                        design->setTools(newTools);
                    }
                    break;
                case 0: cout <<"\n Exit update."<<endl;
                    break;
                }
                default: 
                    throw std::invalid_argument("Invalid input.");
            }
        } else {
            throw std::invalid_argument("Course not found.\n");
        }
    }
    // Function Delete Course
    void deleteCourse(int id) override {
        auto it = std::remove_if(courses.begin(), courses.end(), [id](Course* course) {
            return course->getCourseID() == id;
        });
        // Execute if encounter ID
        if (it != courses.end()) {
            char response;
            std::cout << "You are going to delete Course with ID: " << id << "? (yes/no): ";
            std::cin >> response;
            response = std::tolower(static_cast<unsigned char>(response));
            response == 'y' ? courses.erase(it, courses.end()), std::cout << "\nCourse deleted successfully.\n" : std::cout << "Deletion cancelled.\n";
        } else {
            throw std::invalid_argument("\nCourse not found.\n");
        }
    } 
    // Function write to file
    void saveToFile(const std::string &filename) const {
        std::ofstream outFile(filename, std::ios::binary);
        for (const auto &course : courses) {
            course->save(outFile);
        } 
        cout <<"\nData saved successfully"<<endl;
        outFile.close();
    }
    // Function read from file
    void loadFromFile(const string& filename) {
        ifstream file(filename, ios::binary);
        if (file.is_open()) {
            while (!file.eof()) {
                string type;
                size_t typelength;
                file.read(reinterpret_cast<char*>(&typelength), sizeof(typelength));
                type.resize(typelength);
                file.read(&type[0], typelength);
                Course*course = nullptr;
                if (type == "Programming") {
                    course = new Programming();
                    course->load(file);
                    courses.push_back(course);
                } else if (type == "Design") {
                    course = new Design();
                    course->load(file);
                    courses.push_back(course);
                }
                cout <<"\nData loaded successfully"<<endl;
            }
            file.close();
        } else {
            cout << "Unable to open file for reading!" << endl;
        }
    }

    // destroy pointer
    ~CourseManager() {
        for (auto course : courses) {
            delete course;
        }
    }
};










