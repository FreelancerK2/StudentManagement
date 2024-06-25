#pragma once
#include "CourseManager.cpp"
#include "Protect.cpp"
using namespace std;

class Implementation2 {
public: 
        void run2(){
            CourseManager manager("courses.dat");
            char choice;
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

                try{
                    switch(choice) {
                        case '1': { 
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
                                switch(choice){
                                    case '1': 
                                          do{
                                                name = Protect::inputProgram("Select course: ");
                                                duration = Protect::getDoubleInput("Enter Duration: ");
                                                project = Protect::getStringInput("Enter Project: ");
                                                id = Protect::getIntInput("Enter ID: ");
                                                Protect::validateId(id);
                                                manager.addCourse(new Programming(name, id, duration, project));
                                          }while(Protect::askToAddMore());
                                            break;
                                    case '2':
                                           do{
                                                name = Protect::inputDesignCourse("Select course: ");
                                                duration = Protect::getDoubleInput("Enter Duration: ");
                                                tools = Protect::getStringInput("Enter Tools: ");
                                                id = Protect::getIntInput("Enter ID: ");
                                                manager.addCourse(new Design(name, id, duration, tools));
                                           }while(Protect::askToAddMore());
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
                                cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ View Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;                                    
                                manager.viewCourses();
                                break;
                        case '3':{
                                int id;
                                cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Update Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                                // manager.viewCourses();
                                cout <<"\nAccess update specify by ID: "<<endl;
                            do{ 
                                id = Protect::getIntInput("Enter ID: ");
                                Protect::validateId(id);
                                manager.updateCourse(id);

                            }while(Protect::askToAddMore()); 
                                break;
                            } 
                          
                        case '4':{
                                int id;
                                    cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Delete Courses ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "<<endl;
                                 do{
                                    cout <<"\nAccess delete specify by ID: "<<endl;
                                    cout << "\nEnter Course ID to delete: ";
                                    cin >> id;
                                    manager.deleteCourse(id);
                                }while(Protect::askToAddMore());    
                                    break;
                            } 
                        case '5': manager.saveToFile("Course.dat");
                                break;
                        case '6': manager.loadFromFile("Course.dat");
                                break;
                        case '7':
                                cout << "You are exiting program...\n";
                                break;
                        default:
                                throw std::invalid_argument("Invalid choice! Please enter again.\n");
                                break;

                    }

                }catch (const std::exception& e) {
                    std::cout << "\nError: " << e.what() << std::endl;
                }
             }while(choice != '7');
        }
};