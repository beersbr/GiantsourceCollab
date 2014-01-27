#include "jsonator.h"


Jsonator::Jsonator() {


}

Jsonator::~Jsonator(){

    free(json);

}

void Jsonator::LoadData(std::string filename) {

    FILE *f=fopen(filename.c_str(),"rb");
    fseek(f,0,SEEK_END);
    long len=ftell(f);
    fseek(f,0,SEEK_SET);

    data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
    json =cJSON_Parse(data);
    free(data);

}

void Jsonator::ParseIt(char *text) {

    json =cJSON_Parse(text);

}

int Jsonator::GetSize(cJSON *_data) {


    return cJSON_GetArraySize(_data);

}
cJSON* Jsonator::GetNode(std::string target) {

    cJSON *nodeData = cJSON_GetObjectItem(json,target.c_str());

    return nodeData;

}

std::string Jsonator::GetString(std::string parent,std::string target,cJSON *_data) {

    std::string value;

    if (_data == NULL) {

        _data = cJSON_GetObjectItem(json,parent.c_str());

    }

    value = cJSON_GetObjectItem(_data,target.c_str())->valuestring;

    return value;
}


int Jsonator::GetInt(std::string parent,std::string target,cJSON *_data) {

    int value;

    if (_data == NULL) {

        _data = cJSON_GetObjectItem(json,parent.c_str());

    }

    value = cJSON_GetObjectItem(_data,target.c_str())->valueint;

    return value;
}


double Jsonator::GetDouble(std::string parent,std::string target,cJSON *_data) {

    double value;

    if (_data == NULL) {

        _data = cJSON_GetObjectItem(json,parent.c_str());

    }

    value = cJSON_GetObjectItem(_data,target.c_str())->valuedouble;

    return value;
}
