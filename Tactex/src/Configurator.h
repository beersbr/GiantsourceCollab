//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __Configurator_H_
#define __Configurator_H_

#include <iostream>
#include <fstream>
#include <map>
#include <exception>
#include <vector>

namespace ConfiguratorException
{
    class FileNotFoundException : public std::exception {
        virtual const char* what() const throw(){
            return "Configurator :: Could not find specified file.\n";
        }
    };

    class EOFExcpetion : public std::exception {
        virtual const char* what() const throw(){
            return "Configurator :: Unexpectedly reached the end of the stream.\n";
        }
    };

    class ParseFileException : public std::exception {
        virtual const char* what() const throw(){
            return "Configurator :: Could not parse file.\n";
        }
    };

    class BadStreamException : public std::exception {
        virtual const char* what() const throw(){
            return "Configurator :: The stream went bad in the middle of reading.\n";
        }
    };
}


class Configurator {
public:
    static std::map<std::string, std::string>* open(const std::string filepath);
    static std::string readline(std::fstream& );
    static std::vector<std::string> split(std::string& str, const char t);

};

#endif //__Configurator_H_
