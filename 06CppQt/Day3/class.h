#ifndef _CLASS_H_
#define _CLASS_H_

#include <iostream>

using namespace std;

class Stu
{
private:
    string name;
    int age;
public:
    void init(string name,int age);
    void show();
};



#endif