//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Configurator.h"

std::map<std::string, std::string>* Configurator::open(const std::string filepath)
{

    std::fstream ifp;
    ifp.open(filepath.c_str(), std::fstream::in);

    // TODO: This is incorrect as the file not being open DOES NOT mean
    // that the file could not be found.
    if(!ifp.is_open())
        throw ConfiguratorException::FileNotFoundException();

    while(!ifp.eof())
    {
        std::string line = Configurator::readline(ifp);
        std::cout << line << std::endl;

        // split the line by the '='
        Configurator::split(line, '=');
    }


    return new std::map<std::string, std::string>();
}

std::string Configurator::readline(std::fstream& f)
{
    if(!f.good())
        throw ConfiguratorException::BadStreamException();

    std::string str;
    while(!f.eof() && f.peek() != '\n')
    {
        char token = 0;
        f.read(&token, 1);
        str.append(&token);
    }

    return str;
}

std::vector<std::string> Configurator::split(std::string& str, const char t)
{
    std::vector<std::string> tokens;
    int index = 0;
    int startIndex = 0;
    for(std::string::iterator it = str.begin(); it != str.end(); ++it, ++index)
    {
        if((*it) == t)
        {
            std::string _s = str.substr(startIndex, index);
            std::cout << "substring: " << _s << std::endl;
            startIndex = index + 1;

            tokens.push_back(_s);
        }
    }
    std::string lastToken = str.substr(startIndex, index);
    std::cout << "last substring: " << lastToken << std::endl;

    tokens.push_back(lastToken);


    return tokens;
}

