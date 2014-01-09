//
// Created by Brett Beers on 1/6/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __Configurator_H_
#define __Configurator_H_

#include "common.h"

#include <map>
#include <iostream>
#include <fstream>

enum CONFIGURATOR_ERROR {
    COULD_NOT_OPEN_FILE = -100,

    RETURN_OK = 1
};

class Configurator {
public:
    Configurator();

    int LoadConfigFile(const std::string filename, const int bufferSize);
    std::string operator[](const std::string key) const;

private:

    std::string filename;
    std::map<std::string, std::string> proxy;

};


#endif //__Configurator_H_
