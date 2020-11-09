#include "person.h"

#include <iostream>
using namespace std;
Person::Person(string name, int age): name(name), age(age){}

string Person::intro() {
    return "name: "+name+", age: "+to_string(age);
}
