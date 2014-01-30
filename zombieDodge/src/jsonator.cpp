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
cJSON* Jsonator::GetNode(cJSON *_jsonNode, std::string target) {

    if (_jsonNode == NULL)
        _jsonNode = json;

    cJSON *nodeData = cJSON_GetObjectItem(_jsonNode,target.c_str());

    return nodeData;

}

std::string Jsonator::GetString(std::string parent,std::string target,cJSON *_data) {

    std::string value;
    cJSON* jData;
    cJSON* tData;

    if (_data == NULL) {

         jData = json;

    } else {

        jData = _data;

    }
    if (parent != "") {

        tData = cJSON_GetObjectItem(jData,parent.c_str());
    } else {
        tData = _data;

    }
   // std::cout << "GET VALUE " << std::endl;
    value = cJSON_GetObjectItem(tData,target.c_str())->valuestring;


    //free(jData);

    return value;
}


int Jsonator::GetInt(std::string parent,std::string target,cJSON *_data) {

    int value;
    cJSON* jData;
    cJSON* tData;

    if (_data == NULL) {

        jData = json;

    } else {

        jData = _data;

    }
    if (parent != "") {

        tData = cJSON_GetObjectItem(jData,parent.c_str());
    } else {
        tData = _data;

    }
    //std::string configUrl = "config/" + _playerTarget + ".config";
    value = cJSON_GetObjectItem(tData,target.c_str())->valueint;


    //free(jData);

    return value;
}


double Jsonator::GetDouble(std::string parent,std::string target,cJSON *_data) {

    double value;
    cJSON* jData;
    cJSON* tData;

    if (_data == NULL) {

        jData = json;

    } else {

        jData = _data;

    }
    if (parent != "") {

        tData = cJSON_GetObjectItem(jData,parent.c_str());
    } else {
        tData = _data;

    }
    //std::string configUrl = "config/" + _playerTarget + ".config";
    value = cJSON_GetObjectItem(tData,target.c_str())->valuedouble;


    //free(jData);

    return value;
}
