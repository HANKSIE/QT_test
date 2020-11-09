#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person
{
public:
    Person(std::string, int);
    std::string intro();
private:
    std::string name;
    int age;
};

#endif // PERSON_H
