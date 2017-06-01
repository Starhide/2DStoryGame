#pragma once

#include <exception>
#include <string>

class MsgException: public std::exception {
    MsgException(std::string msg) : std::exception(), message(msg){
    }

    virtual const char* what() const throw(){
        return this->message.c_str();
    }

    private:
        std::string message;
}