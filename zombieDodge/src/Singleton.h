//
// Created by Brett Beers on 1/6/14.
// Copyright (c) 2014 Brett Beers. All rights reserved.
//


#ifndef __Singleton_H_
#define __Singleton_H_

#include <iostream>

template <class T>
class Singleton
{
public:
    template <typename... Args>
    static T* get_instance(Args... args)
    {
        if (!_instance)
        {
            _instance = new T(std::forward<Args>(args)...);
        }

        return _instance;
    }

    static void destroy_instance()
    {
        delete _instance;
        _instance = nullptr;
    }

private:
    static T* _instance;
};


#endif //__Singleton_H_
