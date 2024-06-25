#pragma once
#include "Course.cpp"
#include "Programming.cpp"
#include "Design.cpp"
using namespace std;

class Protect {
public:

    // Check if ID is less than Zero or ID in letter
    static void validateId(int id) {
        if (cin.fail() || id <= 0) {
            throw std::invalid_argument("ID must be a positive integer.");
        }
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

        std::regex numberPattern("[0-9]"); // Regex to match any digit
        while (input.length() <= 1 || std::regex_search(input, numberPattern)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw invalid_argument ("Invalid input. ");
            cout <<prompt;
            cin >> input;
            // Check if the input contains any numbers
            if (std::regex_search(input, numberPattern)) {
                std::cout << "The string should not contain numbers! ";
            } else if(input.length() <= 1){
                std::cout <<"The string length not less than one or equal once! ";
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
                std::cout << "Invalid input! Please enter 'y' or 'n'." << std::endl;
            }
        }
    }

    // Function to input double
    static double getDoubleInput(const std::string& prompt) {
        double value;
        cout <<prompt;
        while (!(std::cin >> value)) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid input.Please input only Number!"<<endl;
            cout<<prompt;
        } 
        return value;
    }

    // Make option of Programming Course
    static string inputProgram(string program){
        int choice;
        do{
            cout <<program<<endl;
            cout <<"1. Software Development."<<endl;
            cout <<"2. Language Python."<<endl; 
            cout <<"3. Web Development."<<endl;
            cout <<"4. IT Support."<<endl;
            cout <<"5. WordPress Website Development."<<endl;
            cout <<"0. Exit"<<endl;
            cout <<"\nEnter your choice<0-5>: ";
            cin >> choice;
            switch(choice){
                case 1 : return "Software Development.";
                        break;
                case 2 : return "Language Python.";
                        break;
                case 3 : return "Web Development.";
                        break;
                case 4 : return "IT Support.";
                        break;
                case 5 : return "WordPress WebDevelopment.";
                        break;
                case 0 : return "Exit";
                        break;
                default: return "Invalid Input";
                        break;
            }
        }while(choice != 0);
    }

    //Make option of Design Course
    static string inputDesignCourse(string design){
        int choice;
        do{
            cout <<design<<endl;
            cout <<"\t1. Graphic and Design."<<endl;
            cout <<"\t2. Adobe Photoshop."<<endl;
            cout <<"\t3. Video Editing."<<endl;
            cout <<"\t4. 3D Motion."<<endl;
            cout <<"\t5. UX/UI Design."<<endl;
            cout <<"\t0. Exit"<<endl;
            cout <<"\tEnter your choice<0-5>: ";
            cin >> choice;
            switch(choice){
                case 1 : return "Graphic and Design.";
                        break;
                case 2 : return "Adobe Photoshop.";
                        break;
                case 3 : return "Video Editing.";
                        break;
                case 4 : return "3D Motion.";
                        break;
                case 5 : return "UX/UI Design.";
                        break;
                case 0 : return "Exit";
                        break;
                default: return "Invalid Input";
                        break;
            }
        }while(choice != 0);
    }

};