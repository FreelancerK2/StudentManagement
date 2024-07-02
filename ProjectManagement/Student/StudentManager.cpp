#pragma once
#include "StudentRepository.cpp"
#include "Undergraduate.cpp"
#include "Graduate.cpp"
#include "Secure.cpp"
using namespace std;
class StudentManager : public StudentRepository {
private:
    vector<Student*> students;
    string filename;
    // Find Student use ID
    vector<Student*>::iterator findStudentById(int id) {
        return std::find_if(students.begin(), students.end(), [id](Student* student) {
            return student->getStudentID() == id;
        });
    } 
    // Check over Duplicate ID
    bool isDuplicateId(int id) const {
        return any_of(students.begin(), students.end(), [id](Student* student) { return student->getStudentID() == id; });
    }   
 
public: 
    // Constructor
    StudentManager(const std::string& filename) : filename(filename) {
    } 

    // Function to add more Student
    void addStudent(Student* student) {
        if (isDuplicateId(student->getStudentID())) {      // student->getStudentID()
            throw invalid_argument("Student ID already exists. Cannot add duplicate.");
            delete student; // Prevent memory leak
        } else {
            students.push_back(student);
            cout << "\nStudent added successfully." << endl;
        }
    } 
 

    // View all students
    void viewStudents(){
    enum option{GRADUATE = 1 , UNDERGRADUATE, EXIT = 0};
    int choice;
    int i =1;
    std::cout << "Choose a student to view:\n1. Graduate\n2. Undergraduate\n0. Exit\nEnter your choice<0-2>: ";
    std::cin >> choice;
    system("cls");
    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ View Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
    cout <<"No."<< setw(11) << "Name" << setw(19) << "date of birth" << setw(15) << "Student ID"<< setw(18) <<"Type" << setw(30) << "Major/Research Topic"<< endl;
    cout << string(97, '-') << endl;

    if (students.empty()) {
        throw std::invalid_argument("No student available");
        return;
    }


    switch (choice) {
        case GRADUATE:
            for (auto student : students) {
            Graduate* graduate = dynamic_cast<Graduate*>(student);
                if (graduate != nullptr) {
                    cout <<i;
                    student->displayDetails();
                    i++;
                }
            }
            break;
        case UNDERGRADUATE:
            for (auto student : students) {
            Undergraduate* undergraduate = dynamic_cast<Undergraduate*>(student);
                if (undergraduate != nullptr) {
                    cout <<i;
                    student->displayDetails();;
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
    void updateStudent(const int& id) {
    enum Option{FIRSTNAME = 1, LASTNAME, DATE, ID, OTHER, EXIT = 0};
    auto it = findStudentById(id);
        if (it != students.end()) {
            std::cout << "Which item do you want to update?\n"
                      << "1. Firstname\n2. Lastname\n3. Date of birth\n4. StudentID\n";
            Undergraduate* undergraduate = dynamic_cast<Undergraduate*>(*it);
            Graduate* graduate = dynamic_cast<Graduate*>(*it);
            if (undergraduate) {            
                std::cout << "5. Major\n0. Exit\n\nEnter your choice: ";
            } 
            else if (graduate) {   
                std::cout << "5. ResearchTopic\n0. Exit\n\nEnter your choice:";
            }
            int choice;
            std::cin >> choice;
            switch (choice) {
                case FIRSTNAME: {
                    std::string newFirstName = Secure::getStringInput("Enter new Firstname: ");
                    (*it)->setFirstName(newFirstName);
                    break;
                }
                case LASTNAME: {
                    std::string newLastName = Secure::getStringInput("Enter new Lastname: ");
                    (*it)->setLastName(newLastName);
                    break;
                }
                case DATE: {
                    string date = Secure::validateAge();
                    (*it)->setDob(date);
                    break;
                }
                case ID: {
                    int newId = Secure::getIntInput("Enter new ID: ");
                    (*it)->setID(newId);
                    break; 
                } 
                case OTHER: {
                    if (undergraduate) {   
                        std::string newMajor = Secure::getStringInput("Enter new Major: ");
                        undergraduate->setMajor(newMajor);
                    } else if (graduate) {      
                        std::string newTopic = Secure::getStringInput("Enter new Topic: ");
                        graduate->setResearchTopic(newTopic);
                    }
                    break;
                case EXIT: cout <<"\nExit update."<<endl;
                    break;
                }
                default:
                    throw invalid_argument("Invalid choice. Please enter number 0-5");
            }
        } else {
            throw invalid_argument ("Student not found. Wrong ID input");
        }
    } 

    // function to delete student 
    void deleteStudent(const int& id) override {
        auto it = std::remove_if(students.begin(), students.end(), [id](Student* student) {
            return student->getStudentID() == id;
        });
        if (it != students.end()) {
            char response;
            std::cout << "You are going to delete Student with ID: " << id << "? (y/n): ";
            std::cin >> response;
            response = std::tolower(static_cast<unsigned char>(response));
            response == 'y' ? students.erase(it, students.end()), std::cout << "\nStudent deleted successfully.\n" : std::cout << "\nDeletion cancelled.\n";
        } else {
            throw invalid_argument("Student not found. Please try again!");
        }
    }

    // Write to file
    void saveToFile() const {
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Cannot open file for writing");
        }
        // For_each loop
        for (const Student* student : students) {
            ofs<<student->toString();
        }
        cout <<"\nData saved successfully"<<endl; 
        ofs.close();
    }

    // Read from file
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) return;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line); // convert line of int to string
            string type;
            getline(ss, type, ',');
            Student* student = nullptr;
            if (type == "Undergraduate") {
                student = new Undergraduate();
            } else if (type == "Graduate") {
                student = new Graduate();
            }
            if (student) {
                student->fromString(line.substr(type.size() + 1));
                students.push_back(student);
            }
        }cout <<"\nData loaded successfully"<<endl;
    }

    // Destructor  
    ~StudentManager() {
        for (auto student : students) {
            delete student;
        }
    }
};