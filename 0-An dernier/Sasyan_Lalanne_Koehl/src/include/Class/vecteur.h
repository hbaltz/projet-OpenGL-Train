#ifndef VECTEUR_H
#define VECTEUR_H

#include "../API/CPoint3f.h"

class Vecteur
{
private:
    // Coordonnées du vecteur
    float X,Y,Z;
public:
    // constructeurs
    Vecteur(float x, float y, float z);
    Vecteur(CPoint3f p1, CPoint3f p2);
    Vecteur(Vecteur const& vect);
    Vecteur();
    // opérateurs
    Vecteur& operator+=(Vecteur const& vect);
    Vecteur& operator-=(Vecteur const& vect);
    Vecteur& operator+(Vecteur const& vect);
    Vecteur& operator-(Vecteur const& vect);
    bool operator==(Vecteur const& vect);
    bool operator!=(Vecteur const& vect);
    // méthodes
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
