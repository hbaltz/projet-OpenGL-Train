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
************ M�thodes : **************
*************************************/

void Triangulation::ajouterTriangle(Triangle triangle) {
    // On ajoute le triangle � la liste :
    triangles.push_back(triangle);
}
