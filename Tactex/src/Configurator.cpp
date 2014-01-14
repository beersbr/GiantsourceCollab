//
// Created by Brett Beers on 1/12/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#include "Configurator.h"

std::map<std::string, std::string>* Configurator::open(const std::string filepath)
{

    std::fstream ifp;
    ifp.open(filepath.c_str(), std::fstream::in);

    system("pwd");
    std::ofstream ofp ("test", std::fstream::out | std::fstream::app);

    if(!ifp.is_open())
        throw ConfiguratorException::FileNotFoundException();

    while(!ifp.eof())
    {
        std::string line = Configurator::readline(ifp);
        std::cout << line << std::endl;
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
