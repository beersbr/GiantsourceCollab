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

    std::map<std::string, std::string> *config = new std::map<std::string, std::string>();

    while(!ifp.eof())
    {
        std::string line = Configurator::readline(ifp);

        line = Configurator::strip(line);

        if(line.empty())
            break;

        // split the line by the '='
        std::vector<std::string> strings =  Configurator::split(line, '=');

//        std::cout << strings[0] << " " << strings[1] << std::endl;

        if(strings.size() == 2){
            std::string key = Configurator::strip(strings[0]);
            std::string value = Configurator::strip(strings[1]);

            (*config)[key] = value;
        }
        else {
            throw ConfiguratorException::ParseFileException();
        }
    }

    return config;
}

std::string Configurator::readline(std::fstream& f)
{
    if(!f.good())
        throw ConfiguratorException::BadStreamException();

    std::string str;
    char token = 0;
    while(!f.eof() && f.peek() != '\n')
    {
        f.read(&token, 1);
        str.append(&token);
        token = 0;
    }
    f.read(&token, 1);
    str.append(&token);

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
            startIndex = index + 1;

            tokens.push_back(_s);
        }
    }
    std::string lastToken = str.substr(startIndex, index);


//    std::cout << "last token: " << lastToken << std::endl;
    tokens.push_back(lastToken);

    return tokens;
}

std::string Configurator::strip(std::string& str)
{
    // remove from front of string
    int frontIndex = 0, endIndex = (str.length()-1);
    for(frontIndex; frontIndex < str.length(); ++frontIndex){
        if(!(str[frontIndex] == ' ' || str[frontIndex] == '\n' || str[frontIndex] == '\r'))
            break;
    }

    for(endIndex; endIndex < str.length(); --endIndex){
        if(!(str[frontIndex] == ' ' || str[frontIndex] == '\n' || str[frontIndex] == '\r'))
            break;
    }

    return (str.substr(frontIndex, endIndex));
}
