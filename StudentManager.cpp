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
    StudentManager(const std::string& filename) : filename(filename) {
    } 

    // Function to add more course
    void addStudent(Student* student) {
        if (isDuplicateId(student->getStudentID())) {
            cout << "\nStudent with ID " << student->getStudentID() << " already exists. Cannot add duplicate." << endl;
            delete student; // Prevent memory leak
        } else {
            students.push_back(student);
            cout << "\nStudent added successfully." << endl;
        }
    }

    // View all students
    void viewStudents() override {                      
        cout <<"No."<< setw(11) << "Name" << setw(19) << "date of birth" << setw(15) << "Student ID"<< setw(18) <<"Type" << setw(30) << "Major/Research Topic"<< endl;
        cout << string(97, '-') << endl;

        if (students.empty()) {
            throw std::invalid_argument("No student available");
            return;
        }

        int i = 1;
        std::for_each(students.begin(), students.end(), [&i](Student* student) {
        cout <<i++;
        student->displayDetails();
        });
    } 

    // }// Function to update course
    void updateStudent(const int& id) {
    auto it = findStudentById(id);
        if (it != students.end()) {
            std::cout << "Which item do you want to update?\n"
                      << "1. Firstname\n2. Lastname\n3. Date of birth\n4. StudentID\n";
            Undergraduate* undergraduate = dynamic_cast<Undergraduate*>(*it);
            Graduate* graduate = dynamic_cast<Graduate*>(*it);
            if (undergraduate) {            
                std::cout << "5. Major\n\nEnter your choice: ";
            } 
            else if (graduate) {   
                std::cout << "5. ResearchTopic\n\nEnter your choice:";
            }
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1: {
                    std::string newFirstName = Secure::getStringInput("Enter new Firstname: ");
                    (*it)->setFirstName(newFirstName);
                    break;
                }
                case 2: {
                    std::string newLastName = Secure::getStringInput("Enter new Lastname: ");
                    (*it)->setLastName(newLastName);
                    break;
                }
                case 3: {
                    string date = Secure::validateAge();
                    (*it)->setDob(date);
                    break;
                }
                case 4: {
                    int newId = Secure::getIntInput("Enter new ID: ");
                    Secure::validateId(newId);
                    (*it)->setID(newId);
                    break;
                } 
                case 5: {
                    if (undergraduate) {   
                        std::string newMajor = Secure::getStringInput("Enter new Major: ");
                        std::cin.ignore();
                        undergraduate->setMajor(newMajor);
                    } else if (graduate) {      
                        std::string newTopic = Secure::getStringInput("Enter new Topic: ");
                        std::cin.ignore();
                        graduate->setResearchTopic(newTopic);
                    }
                    break;
                }
                default:
                    std::cout << "Invalid choice\n";
            }
        } else {
            std::cout << "Course not found.\n";
        }
    } 

    // function to delete student
    void deleteStudent(const int& id) override {
        auto it = std::remove_if(students.begin(), students.end(), [id](Student* student) {
            return student->getStudentID() == id;
        });
        if (it != students.end()) {
            students.erase(it, students.end());
            std::cout << "\nStudent deleted successfully.\n";
        } else {
            std::cout << "Student with ID " << id << " not found.\n";
        }
    }

    // Write to file
    void saveToFile() const {
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Cannot open file for writing");
        }

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
            stringstream ss(line);
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