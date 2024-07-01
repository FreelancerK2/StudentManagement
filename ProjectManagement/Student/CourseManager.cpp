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
            throw invalid_argument("Course ID already exists. Cannot add duplicate.");
            delete course; // Prevent memory leak
        } else {
            courses.push_back(course);
            cout << "\nCourse added successfully." << endl;
        }
    }

    // View all students
    void viewCourses(){
    enum option{PROGRAM = 1 , DESIGN, EXIT = 0};
    int choice;
    int i =1;
    std::cout << "Choose a course to view:\n1. Programming\n2. Design\n0. Exit\nEnter your choice<0-2>: ";
    std::cin >> choice;
    system("cls");
    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ View Course ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
    cout <<"No."<< setw(11) << "Name" << setw(19) << "CourseID" << setw(20) << "Duration(Years)"<< setw(15) <<"Type" << setw(28) << "Project/Tools"<< endl;
    cout << string(97, '-') << endl;

    if (courses.empty()) {
        throw std::invalid_argument("No courses available");
        return;
    }  

    switch (choice) {
        case PROGRAM:
            for (auto course : courses) {
            Programming* program = dynamic_cast<Programming*>(course);
                if (program != nullptr) {
                    cout <<i;
                    course->displayInfo();
                    i++;
                }
            }
            break; 
        case DESIGN:
            for (auto course : courses) {
            Design* design = dynamic_cast<Design*>(course);
                if (design != nullptr) {
                    cout <<i;
                    course->displayInfo();;
                    i++;
                }
            }
            break;
        case EXIT: cout <<"You Exiting..."<<endl;
            Secure::waitForKeypress();
            system("cls");
            break;
        default:
            throw invalid_argument("Invalid choice. Please enter number from 0-2.");
       }
    }

    // Function to update course
    void updateCourse(int id) {
    enum UpdateOption{NAME = 1, DURATION, ID, OTHER, EXIT = 0};
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
                case NAME: {
                    std::string newName = Protect::getStringInput("Enter new name: ");
                    (*it)->setName(newName);
                    break;
                } 
                case DURATION: {
                    double newDuration = Protect::getDoubleInput("Enter new duration: ");
                     (*it)->setDuration(newDuration);
                    break;
                }
                case ID: {
                    int newId = Protect::getIntInput("Enter new ID: ");
                    (*it)->setId(newId);
                    break;
                }
                case OTHER: {
                    if (program) {   
                        std::string newProject = Protect::getStringInput("Enter new Project: ");
                        program->setProject(newProject);
                    } else if (design) {      
                        std::string newTools = Protect::getStringInput("Enter new Tools: ");
                        design->setTools(newTools);
                    }
                    break;
                case EXIT: cout <<"\n Exit update."<<endl;
                    break;
                }
                default: 
                    throw std::invalid_argument("Invalid input. Pleas enter number 0-4.");
            }
        } else {
            throw std::invalid_argument("Course not found. Wrong ID input");
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
            std::cout << "You are going to delete Course with ID: " << id << "? (y/n): ";
            std::cin >> response;
            response = std::tolower(static_cast<unsigned char>(response));
            response == 'y' ? courses.erase(it, courses.end()), std::cout << "\nCourse deleted successfully.\n" : std::cout << "Deletion cancelled.\n";
        } else {
            throw std::invalid_argument("Course not found. Please try again!");
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
            throw invalid_argument("Unable to open file for reading!");
        }
    }

    // destroy pointer
    ~CourseManager() {
        for (auto course : courses) {
            delete course;
        }
    }
};










