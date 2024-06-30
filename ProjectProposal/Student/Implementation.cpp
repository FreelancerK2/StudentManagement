#pragma once
#include <regex>
#include <iomanip>
#include <sstream>
#include "Graduate.cpp"
#include "Undergraduate.cpp"
#include "StudentManager.cpp"
using namespace std;

class Implementation { 
public:
    void run(){ 
    enum Option{ADD = 1, VIEW, UPDATE, DELETE, SAVE, LOAD, EXIT};
    enum Option2{GRADUATE = 1, UNDERGRADUATE, BACK = 0};
    StudentManager manager("students.txt");
    int choice;
                do {
                        cout << "\nMenu:\n";
                        cout << "1. Add Student\n";
                        cout << "2. View All Students\n";
                        cout << "3. Update Student\n";
                        cout << "4. Delete Student\n";
                        cout << "5. Save to file\n";
                        cout << "6. Load from file\n";
                        cout << "7. Exit\n";
                        cout << "\nEnter your choice: ";
                        cin >> choice;
                        system("cls");
                    try{
                        switch(choice) {
                            case ADD: {
                                string firstName, lastName, major,topic, date; 
                                int id; 
                                char response;
                                cout <<"\n~~~~~~~~~~~~~~~~~~~~~ Add Student ~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                            do{
                                cout <<"\nSelect your program to add Student: "<<endl;
                                cout <<"1. Graduate Student."<<endl;
                                cout <<"2. Undergraduate Student."<<endl;
                                cout <<"0. Exit."<<endl;
                                cout <<endl;
                                cout <<"Enter your choice<0-2>: ";
                                cin  >> choice;
                                system("cls");
                                switch(choice){
                                    case GRADUATE:
                                        do{
                                            firstName = Secure::getStringInput("Enter Firstname: ");
                                            lastName = Secure::getStringInput("Enter Lastname: ");
                                            id = Secure::getIntInput("Enter ID: ");
                                            Secure::validateId(id);
                                            date = Secure::validateAge();  
                                            topic = Secure::getStringInput("Enter research Topic: ");                                        
                                            manager.addStudent(new Graduate(firstName, lastName, date, id, topic));
                                        }while(Secure::askToAddMore());
                                         system("cls");                         
                                            break;
                                    case UNDERGRADUATE:
                                        do{
                                            firstName = Secure::getStringInput("Enter Firstname: ");
                                            lastName = Secure::getStringInput("Enter Lastname: ");
                                            id = Secure::getIntInput("Enter ID: ");
                                            Secure::validateId(id);
                                            date = Secure::validateAge();  
                                            major = Secure::inputMajor(major);
                                            manager.addStudent(new Undergraduate(firstName, lastName, date, id, major));
                                        }while(Secure::askToAddMore()); 
                                        system("cls");                             
                                            break;
                                    case BACK:
                                            cout <<"You are exiting..."<<endl;
                                            Secure::waitForKeypress();
                                            system("cls");
                                            break;
                                    default : cout <<"Invalid choice! Please try again."<<endl; 
                                            break;
                                  }
                                }while(choice != BACK);
                                break;
                            } 
                            case VIEW:                                     
                                    manager.viewStudents();
                                    Secure::waitForKeypress();
                                    system("cls");
                                    break;
                            case UPDATE: {
                                    string newFirstName, newLastName, newMajor, newTopic ,date;
                                    int id; 
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl; 
                                    cout <<"\nAccess update specify by ID: "<<endl;
                                 do{
                                    id = Secure::getIntInput("Enter ID: ");
                                    Secure::validateId(id); 
                                    manager.updateStudent(id);
                                    cout << "\nStudent Update successfully." << endl;
                                }while(Secure::askToAddMore()); 
                                system("cls");                        
                                    break;
                                }  
                            case DELETE: { 
                                    int id;
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delete Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl; 
                                do{
                                    cout << "\nEnter student ID to delete: ";
                                    cin >> id;
                                    manager.deleteStudent(id);
                                }while(Secure::askToAddMore());
                                system("cls");    
                                    break;
                                }
                            case SAVE: manager.saveToFile();
                                    Secure::waitForKeypress();
                                    system("cls");
                                    break;
                            case LOAD: manager.loadFromFile();
                                    Secure::waitForKeypress();
                                    system("cls");
                                    break;
                            case EXIT:
                                cout << "You are exiting program...\n";
                                Secure::waitForKeypress();
                                system("cls");
                                break;
                            default:
                                cout << "Invalid choice! Please enter again.\n";
                                break;
                        }
                        } catch (const std::exception& e) {
                            std::cout << "\nError: " << e.what() << std::endl;
                        }
                    }while(choice != EXIT);
    }
};




