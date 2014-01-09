//
// Created by Brett Beers on 1/6/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#include "Configurator.h"

Configurator::Configurator(){

}


/*
 This function expects key/value pairs seperated by equal signs. Example

 the max line length is 1024 by default

 key = value
 # ignored key = value some crap
 key = value # ignored
 key = "value value value"
 key=value
 key =value
 key= value

 */
int Configurator::LoadConfigFile(const std::string filename, const int bufferSize = 1024) {
    //std::fstream fs;
    //fs.open(filename.c_str(), std::ios::in);

    //if(!fs.is_open()){
    //    return COULD_NOT_OPEN_FILE;
    //}

    //std::string line = 0;
    //while(std::getline(fs, line)){

    //    line = MeadowFrost::trim(line);
    //}

    return RETURN_OK;

}