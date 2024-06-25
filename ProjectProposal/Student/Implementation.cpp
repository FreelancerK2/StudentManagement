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
    StudentManager manager("students.txt");
    char choice;
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

                    try{
                        switch(choice) {
                            case '1': {
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
                                switch(choice){
                                    case '1':
                                        do{
                                            firstName = Secure::getStringInput("Enter Firstname: ");
                                            lastName = Secure::getStringInput("Enter Lastname: ");
                                            id = Secure::getIntInput("Enter ID: ");
                                            Secure::validateId(id);
                                            date = Secure::validateAge();  
                                            topic = Secure::getStringInput("Enter research Topic: ");                                        
                                            manager.addStudent(new Graduate(firstName, lastName, date, id, topic));
                                        }while(Secure::askToAddMore());                         
                                            break;
                                    case '2':
                                        do{
                                            firstName = Secure::getStringInput("Enter Firstname: ");
                                            lastName = Secure::getStringInput("Enter Lastname: ");
                                            id = Secure::getIntInput("Enter ID: ");
                                            Secure::validateId(id);
                                            date = Secure::validateAge();  
                                            major = Secure::inputMajor(major);
                                            manager.addStudent(new Undergraduate(firstName, lastName, date, id, major));
                                        }while(Secure::askToAddMore());                              
                                            break;
                                    case '0':
                                            cout <<"Back to Menu."<<endl;
                                            break;
                                    default : cout <<"Invalid choice!"<<endl; 
                                            break;
                                  }
                                }while(choice != '0');
                                break;
                            } 
                            case '2':
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ View Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;                                    
                                    manager.viewStudents();
                                    break;
                            case '3': {
                                    string newFirstName, newLastName, newMajor, newTopic ,date;
                                    int id; 
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl; 
                                    cout <<"\nAccess update specify by ID: "<<endl;
                                 do{
                                    id = Secure::getIntInput("Enter ID: ");
                                    Secure::validateId(id); 
                                    manager.updateStudent(id);
                                }while(Secure::askToAddMore());                         
                                    break;
                                }  
                            case '4': { 
                                    int id;
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delete Student ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl; 
                                do{
                                    cout << "\nEnter student ID to delete: ";
                                    cin >> id;
                                    manager.deleteStudent(id);
                                }while(Secure::askToAddMore());    
                                    break;
                                }
                            case '5': manager.saveToFile();
                                    break;
                            case '6': manager.loadFromFile();
                                    break;
                            case '7':
                                cout << "You are exiting program...\n";
                                break;
                            default:
                                cout << "Invalid choice! Please enter again.\n";
                                break;
                        }
                        } catch (const std::exception& e) {
                            std::cout << "\nError: " << e.what() << std::endl;
                        }
                    }while(choice != '7');
    }
};




