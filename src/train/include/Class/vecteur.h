#ifndef VECTEUR_H
#define VECTEUR_H

#include "../API/CPoint3f.h"

/**
* Défintion de la classe Vecteur :
* Elle possède :
* - Trois variables : X,Y,Z formant un vecteur 3D
* - Quatres constructeurs ( à partir de float, de poins 3D, d'un vecteur ou vide)
* - Six opérateurs (+=, -=, +, -, ==, !=)
* - Douze méthodes (3 getters et 3 setters, prodVect, moyenne, prodScal, Normalise, norm, Equal)
**/

class Vecteur
{
private:
    // Coordonnées du vecteur :
    float X,Y,Z;

public:
    // Constructeurs :
    Vecteur(float x, float y, float z);
    Vecteur(CPoint3f p1, CPoint3f p2);
    Vecteur(Vecteur const& vect);
    Vecteur();

    // Opérateurs :
    Vecteur& operator+=(Vecteur const& vect);
    Vecteur& operator-=(Vecteur const& vect);
    Vecteur& operator+(Vecteur const& vect);
    Vecteur& operator-(Vecteur const& vect);
    bool operator==(Vecteur const& vect);
    bool operator!=(Vecteur const& vect);

    // Méthodes :
    Vecteur prodVect(Vecteur const& vect);
    Vecteur moyenne(Vecteur const& vect);
    Vecteur prodScal(float const& a);
    void Normalise();
    float norm();
    float getX();
    float getY();
    float getZ();
    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    bool Equal(Vecteur vect);
};

#endif // VECTEUR_H
