//
// Created by Matt Jacobs on 1/9/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//

#ifndef __JSONATOR_H_
#define __JSONATOR_H_

#include "cJSON.h"
#include <stdio.h>
#include <iostream>


/*

PARSE ARRAY IN JSON ***

        cJSON* name = NULL;
        cJSON* index = NULL;
        cJSON* optional = NULL;

        int i;

        cJSON *item = cJSON_GetObjectItem(json,"items");
        for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
        {
            cJSON * subitem = cJSON_GetArrayItem(item, i);
            name = cJSON_GetObjectItem(subitem, "name");
            index = cJSON_GetObjectItem(subitem, "index");
            optional = cJSON_GetObjectItem(subitem, "optional");
        }

 */

class Jsonator {

public:
    Jsonator();
    ~Jsonator();

    char *data;
    cJSON *json;

    void ParseIt(char *text);
    void LoadData(std::string filename);
    cJSON* GetNode(cJSON *_jsonNode, std::string target);

    std::string GetString(std::string parent,std::string target,cJSON *_data);
    int GetInt(std::string parent,std::string target,cJSON *_data);
    double GetDouble(std::string parent,std::string target,cJSON *_data);

    int GetSize(cJSON *_data);

private:

};

#endif