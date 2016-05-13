#include "../../Include/Class/Triangulation.h"


/*************************************
************ Constructeurs : *********
*************************************/
Triangulation::Triangulation()
{
    //ctor
}

Triangulation::~Triangulation()
{
    //dtor
}


/*************************************
************ Méthodes : **************
*************************************/

void Triangulation::ajouterTriangle(Triangle triangle) {
    // On ajoute le triangle à la liste :
    triangles.push_back(triangle);
}
