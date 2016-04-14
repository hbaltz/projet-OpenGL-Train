#include "../../Include/Class/Triangulation.h"

Triangulation::Triangulation()
{
    //ctor
}

Triangulation::~Triangulation()
{
    //dtor
}

void Triangulation::ajouterTriangle(Triangle triangle) {
    // On ajoute le triangle à la liste :
    triangles.push_back(triangle);
}
