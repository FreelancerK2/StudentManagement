#pragma once
#include <iostream>

using namespace std;

class User { 
    private:
    string username, password;
    public:
    User() {}      
    User(string u, string p) : username(u), password(p) {}
    //Access username
    string getUsername() const{
        return username;
    }
    // Access password
    string getPassword() const{
        return password; 
    }
    // Modify username
    void setUsername(string user){
        username=user;
    }
    // Modify password
    void setPassword(string pass){
        password=pass;
    }
}; 