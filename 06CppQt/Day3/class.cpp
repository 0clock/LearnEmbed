#include "class.h"



void Stu::init(string name, int age)
{
    this->name=name;
    this->age=age;
}
void Stu::show()
{
    cout << "name:" << name <<endl;
    cout << age << endl;

}
