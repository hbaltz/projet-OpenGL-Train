#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <vector>
#include "Triangle.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h>

using namespace std;

class Triangulation {
    public:
        Triangulation();
        virtual ~Triangulation();

        // Methode :
        void ajouterTriangle(Triangle triangle);

        // Variables :
        vector<Triangle> triangles;
    protected:
    private:
};

#endif // TRIANGULATION_H
