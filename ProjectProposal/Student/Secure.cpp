#pragma once
#include <iomanip>
#include <iostream>
#include <vector>
#include "Student.cpp"
using namespace std;

class Secure {
public:
    // Make option to Major
    static string inputMajor(string n){ 
          int choice;
        do{
            cout <<"Enter major: "<<endl;
            cout <<"1. Programming"<<endl;
            cout <<"2. Design"<<endl;
            cout <<"3. Cybersecurity"<<endl;
            cout <<"\nEnter your choice: ";
            cin >> choice;
            switch(choice){
                case 1: return "Programming";
                        break;
                case 2 : return "Design";
                        break;
                case 3 : return "Cybersecurity";
                        break;
                default : return "Invalid input";
                        break;
            }
        }while(!choice);
    }

    // Method input date
    static string validateAge() {
        int day, month, year;
        string dobInput; 
        // Regular expression for DD MM YYYY format
        regex pattern("\\b(0?[1-9]|[12][0-9]|3[01])\\s(0?[1-9]|1[0-2])\\s((?:19|20)\\d{2})\\b");
        do {
            cout << "Enter date of birth (DD MM YYYY): ";
            getline(cin, dobInput);

            if (regex_match(dobInput, pattern)) {
                stringstream ss(dobInput);
                vector<int> dob;
                int num;
                while (ss >> num) {
                    dob.push_back(num);
                }
                if (dob.size() == 3) {
                    day = dob[0];
                    month = dob[1];
                    year = dob[2];
                    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
                }
            } else {
                throw invalid_argument ("Invalid input. Please enter date in DD MM YYYY format.");
            }
        } while (true);
        // Return an empty string (though loop should never exit without valid input)
        return "";
    }
 

    // Function to input integer
    static int getIntInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input."<<endl;
            cout <<prompt;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }
 
    // Function to input String
    static std::string getStringInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        cin >> input;
        std::regex numberPattern("[0-9]"); // Regex to match of 10 digit

        while (input.length() <= 1 || std::regex_search(input, numberPattern)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. "<<endl;
            cout <<prompt;
            cin >> input;

            // Check if the input contains any numbers
            if (std::regex_search(input, numberPattern)) {
                std::cout << "The string should not contain numbers! ";
            } else if(input.length() <= 1){
                cout <<"The string length not less than one or equal once! ";
            }else{
                break;
            } 
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    // Ask user to repeat action
    static bool askToAddMore() {
        char choice;
        while (true) {
            std::cout << "\nDo you want to make more (y/n)? ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

            // Convert choice to lowercase to handle 'Y' and 'N'
            choice = std::tolower(static_cast<unsigned char>(choice));

            if (choice == 'y') {
                return true;
            } else if (choice == 'n') {
                return false;
            } else {
                std::cout << "\nInvalid input! Please enter 'y' or 'n'." << std::endl;
            }
        }
    }

    // Combine Firstname and Lastname
    static std::string concatStrings(const std::string &firstName, const std::string &lastName) {
    return firstName + " " + lastName;
    }

    // Check if ID is less than Zero or ID in letter
    static void validateId(int id) {
        if (cin.fail() || id <= 0) {
            throw std::invalid_argument("ID must be a positive integer.");
        }
    }
};