#pragma once
#include "CourseManager.cpp"
#include "Protect.cpp"
#define RESET   "\033[0m"
#define BOLDRED "\033[1m\033[31m"
using namespace std;

class Implementation2 { 
public: 
        void run2(){
            enum Option{ADD = 1, VIEW, UPDATE, DELETE, SAVE , LOAD, EXIT};
            enum Option2{PROGRAM = 1, DESIGN, BACK = 0};
            CourseManager manager("courses.dat");
            int choice;
                do{
                    cout << "\nMenu:\n";
                    cout << "1. Add Course\n";
                    cout << "2. View All Course\n";
                    cout << "3. Update Course\n";
                    cout << "4. Delete Course\n";
                    cout << "5. Save to file\n";
                    cout << "6. load from file\n";
                    cout << "7. Exit\n";
                    cout << "\nEnter your choice: ";
                    cin >> choice;
                    system("cls");

                try{
                    switch(choice) {
                        case ADD: {      
                                string name, project, tools;
                                int id;
                                double duration; 
                                cout <<"\n~~~~~~~~~~~~~~~~~~~~~ Add Courses ~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                            do{
                                cout <<"\nSelect your program to add Course: "<<endl;
                                cout <<"1. Programming"<<endl;
                                cout <<"2. Design"<<endl;
                                cout <<"0. Exit."<<endl;
                                cout <<endl;
                                cout <<"\nEnter your choice<0-2>: ";
                                cin  >> choice;
                                system("cls");
                                switch(choice){
                                    case PROGRAM:  
                                          do{
                                                name = Protect::inputProgram("Select course: ");
                                                duration = Protect::getDoubleInput("Enter Duration: ");
                                                project = Protect::getStringInput("Enter Project: ");
                                                id = Protect::getIntInput("Enter ID: ");
                                                manager.addCourse(new Programming(name, id, duration, project));
                                          }while(Protect::askToAddMore());
                                          system("cls");
                                            break;
                                    case DESIGN:
                                           do{
                                                name = Protect::inputDesignCourse("Select course: ");
                                                duration = Protect::getDoubleInput("Enter Duration: ");
                                                tools = Protect::getStringInput("Enter Tools: ");
                                                id = Protect::getIntInput("Enter ID: ");
                                                manager.addCourse(new Design(name, id, duration, tools));
                                           }while(Protect::askToAddMore());
                                           system("cls");
                                    case BACK:
                                            cout <<"You are exiting..."<<endl;
                                            Protect::waitForKeypress();
                                            system("cls");
                                            break;
                                    default : throw invalid_argument("Invalid choice. Please try again1"); 
                                            break;
                                }
              
                            }while(choice != BACK); 
                            break;           
                        }
                        case VIEW:                        
                                manager.viewCourses();
                                Protect::waitForKeypress();
                                system("cls");
                                break;
                        case UPDATE:{     
                                int id;
                                cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                                cout <<"\nAccess update specify by ID: "<<endl;
                            do{ 
                                id = Protect::getIntInput("Enter ID: ");
                                manager.updateCourse(id);
                                cout << "\nCourse Update successfully." << endl;
                            }while(Protect::askToAddMore());
                            system("cls"); 
                                break;
                            } 
                          
                        case DELETE:{   
                                int id;
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delete Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                                 do{
                                    cout <<"\nAccess delete specify by ID: "<<endl;
                                    cout << "\nEnter Course ID to delete: ";
                                    cin >> id;
                                    manager.deleteCourse(id);
                                }while(Protect::askToAddMore());
                                system("cls");    
                                    break;
                            } 
                        case SAVE: manager.saveToFile("Course.dat");
                                Protect::waitForKeypress();
                                system("cls");  
                                break;
                        case LOAD: manager.loadFromFile("Course.dat");
                                Protect::waitForKeypress();
                                system("cls");  
                                break;
                        case EXIT:  
                                cout << "You are exiting program...\n";
                                Protect::waitForKeypress();
                                system("cls");
                                break;
                        default:
                                throw std::invalid_argument("Invalid choice. Please enter again!");
                                break;

                    } 

                }catch (const std::exception& e) {
                    std::cout<< BOLDRED << "\nError: " << e.what()<< RESET << std::endl;
                }
             }while(choice != EXIT);
        }
};