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

/**
* D�fintion de la classe Triangulation :
* Elle poss�de :
* - Deux constructeurs
* - Une m�thode ajouterTriangle(Triangle triangle) pour ajouter un triangle � la Triangulation
* - Une variable : vector<Triangle> triangles conteant l'ensemble des triangles formant la triangulation
**/

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
