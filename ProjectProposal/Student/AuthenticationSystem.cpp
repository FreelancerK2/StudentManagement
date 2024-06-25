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
            std::cout << "Username already exists. Please choose another one." << std::endl;
            return false;
        }
        return true;
    }

    // Function to check Username and Password 
    bool loginUser(const std::string& username, const std::string& password) {
        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getUsername() == username && user.getPassword() == password;
        });
        if (it != users.end()){
            std::cout << "\nLogin successful. Welcome, " << " " << it->getUsername() << "!" << std::endl; 
                mainMenu();
            }
        return true;
    }
 
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
        cout << "\nUser added successfully!" << endl;
    }

    // Login Method 
    void login() {
        string username, password;
        username = Secure::getStringInput("Enter username: ");
        password = Secure::getIntInput("Enter password: ");;
        if(!loginUser(username, password)){
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }else {
            std::cout << "Invalid username or password."<<std::endl;
        }
    }
    
    // Function to manage on Student amd Course Management
    void mainMenu(){
        char choice;
        do{
            cout <<"\n~~~~~~~~~~~~~~~~~~~~~~~ System Management System ~~~~~~~~~~~~~~~~~~~~~~"<<endl;
            cout <<"1. Student Management"<<endl;
            cout <<"2. Course Management"<<endl;
            cout <<"0. Exit Program"<<endl;
            cout <<endl;
            cout <<"Enter your choice<0-2>: ";
            cin  >> choice; 
        try{ 
            switch(choice){
                case '1': Implementation student; 
                        student.run();
                        break;
                case '2': Implementation2 course;
                        course.run2();
                        break; 
                case '0':
                        cout <<"Exit the program!"<<endl;
                        break;
                default : cout <<"Invalid choice."<<endl;
            }
            }catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        }while(choice != '0');
    }
    // Function manage over Login and register
    void menu() {
        int choice;
        do {
            cout << "\nMain Menu\n";
            cout << "1. Login\n";
            cout << "2. Register\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: 
                login();
                break;
            case 2:
                regis();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
            }
        } while (choice != 0);
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