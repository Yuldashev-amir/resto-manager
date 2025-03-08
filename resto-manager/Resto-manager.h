#ifndef RESTO-MANAGER_H_INCLUDED
#define RESTO-MANAGER_H_INCLUDED
#include <iostream>

class Restorant
{
private:
    double revenue;
    int tables;
public:
    Restorant();
    Restorant(double rev, int tab);
    ShowRest();
};

#endif // RESTO-MANAGER_H_INCLUDED
