#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Implementation.cpp"
#include "Implementation2.cpp"  
#include "User.cpp"
#include "Secure.cpp"

class AuthenticationSystem {
private:
    vector<User> users;
    string usersFile = "users.dat";
    int maxAttempts = 3;
    int attempts = 0;
public:
    AuthenticationSystem(){
        loadUsers();
    }

    // Function to check if Username already have once.
    bool registerUser(const std::string& username) {
        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getUsername() == username;
        });

        if (it != users.end()) {
            std::cout << "\nUsername already exists. Please choose another one." << std::endl;
            Secure::waitForKeypress();
            system("cls");
            menu();
        }
        return true;
    }

    // Function to check Username and Password 
    bool loginUser(const std::string& username, const std::string& password) { 
        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getUsername() == username && user.getPassword() == password;
        });
        attempts++;
        if (it != users.end()){
            std::cout << "\nLogin successful. Welcome, " << " " << it->getUsername() << "!" << std::endl; 
            system("cls");
            mainMenu();
        }else if(attempts >= maxAttempts){
            std::cout << "Login failed. Attempt " << std::endl;
            Secure::waitForKeypress();
            system("cls");
        }
        return true;
    }

    //                           "Function set Username and Password in Login" 
    // bool loginProof(const std::string& user, const int& pass) {
    //     return (user == "Somnang" && pass == 21102000);
    // }
    // void login(){
    //     string user;
    //     int pass;
    //     user = Secure::getStringInput("Enter username: ");
    //     pass = Secure::getIntInput("Enter password: ");
    //     if (loginProof(user, pass)) {
    //     system("cls");
    //     std::cout << "\nLogin successful!" << std::endl;
    //     mainMenu();
    //     }else{
    //         std::cout << "Invalid username or password. Please try again!" << std::endl;
    //     }
    // }


    // Register Method
    void regis() {
        string username, password;
        username = Secure::getStringInput("Enter username: ");
        password = Secure::getIntInput("Enter password: ");
        if(!registerUser(username)){
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        users.push_back(User(username, password));
        saveUsers();
        system("cls");
        cout << "\nUser register successfully! Back to login." << endl;
        Secure::waitForKeypress();
        system("cls");
    }

    // Login Method 
    void login() {
        string username, password;
        username = Secure::getStringInput("Enter username: ");
        password = Secure::getIntInput("Enter password: ");
        system("cls");
        if(!loginUser(username, password)){ 
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }else {
            std::cout << "Invalid username or password.\nPlease Login again!"<<std::endl;
        }
    }
    
    // Function to manage on Student amd Course Management
    void mainMenu(){
    enum Option{STUDENT = 1, COURSE, EXIT = 0};
        int choice;
        do{
            cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~ System Management System ~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout <<"1. Student Management"<<endl;
            cout <<"2. Course Management"<<endl;
            cout <<"0. Exit Program"<<endl;
            cout <<endl;
            cout <<"Enter your choice<0-2>: ";
            cin  >> choice;
            system("cls"); 
        try{ 
            switch(choice){
                case STUDENT: Implementation student; 
                        student.run();
                        break;
                case COURSE: Implementation2 course;
                        course.run2();
                        break; 
                case EXIT:
                        cout <<"Exit the program!"<<endl;
                        Secure::waitForKeypress();
                        system("cls");
                        break;
                default : cout <<"Invalid choice."<<endl;
            }
            }catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        }while(choice != EXIT);
    }

    // Function manage over Login and register
    void menu() {
    enum Option{LOGIN = 1, REGISTER, EXIT = 0};
        int choice;
        do {
            cout << "\nMain Menu\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case LOGIN: 
                login();
                break;
            case REGISTER:
                regis();
                break;
            case EXIT: cout <<"\nLog out."<<endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != EXIT);
    }

    // Function Read From file
    void loadUsers() {
        ifstream file(usersFile, ios::binary);
        if (file.is_open()) {
            User user;
            while (file.read((char*)&user, sizeof(User))) {
                users.push_back(user);
            }
            file.close();
        }
    }
    
    // Function Write to file
    void saveUsers() {
        ofstream file(usersFile, ios::binary | ios::trunc);
        if (file.is_open()) {
            for (const auto& user : users) {
                file.write((char*)&user, sizeof(User));
            }
            file.close();
        }
    }

};