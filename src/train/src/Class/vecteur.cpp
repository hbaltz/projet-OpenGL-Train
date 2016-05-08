#include "../../Include/Class/vecteur.h"
#include <cmath>

/**
* Constructeurs :
**/

Vecteur::Vecteur(float x, float y, float z)
{
    X = x;
    Y = y;
    Z = z;
}

Vecteur::Vecteur(CPoint3f p1, CPoint3f p2) {
    X = p1.X - p2.X;
    Y = p1.Y - p2.Y;
    Z = p1.Z - p2.Z;
}

Vecteur::Vecteur(Vecteur const& vect)
    : X(vect.X), Y(vect.Y), Z(vect.Z)
{

}

Vecteur::Vecteur()
{

}

/**
* Opérateurs :
**/

Vecteur& Vecteur::operator+=(Vecteur const& vect)
{
    X += vect.X;
    Y += vect.Y;
    Z += vect.Z;
    return *this;
}

Vecteur& Vecteur::operator-=(Vecteur const& vect)
{
    X -= vect.X;
    Y -= vect.Y;
    Z -= vect.Z;
    return *this;
}

Vecteur& Vecteur::operator+(Vecteur const& vect)
{
    Vecteur *V;
    V = new Vecteur(X,Y,Z);
    *V += vect;
    return *V;
}

bool Vecteur::operator ==(Vecteur const& vect)
{
    return Equal(vect);
}

bool Vecteur::operator !=(Vecteur const& vect)
{
    return not Equal(vect);
}

Vecteur& Vecteur::operator-(Vecteur const& vect)
{
    Vecteur *V;
    V = new Vecteur(X,Y,Z);
    *V -= vect;
    return *V;
}

/**
* Méthodes :
**/

Vecteur Vecteur::prodVect(Vecteur const& vect)
{
    Vecteur V(0,0,0);
    V.X = Y*vect.Z - Z*vect.Y;
    V.Y = Z*vect.X - X*vect.Z;
    V.Z = X*vect.Y - Y*vect.X;
    return V;
}

Vecteur Vecteur::moyenne(Vecteur const& vect)
{
    Vecteur V(0,0,0);
    V.X = (X+vect.X)/2;
    V.Y = (Y+vect.Y)/2;
    V.Z = (Z+vect.Z)/2;
    return V;
}

Vecteur Vecteur::prodScal(const float &a)
{
    Vecteur V = *this;
    V.setX(X*a);
    V.setY(Y*a);
    V.setZ(Z*a);
    return V;
}

void Vecteur::Normalise()
{
    float r = norm();
    X = X/r;
    Y = Y/r;
    Z = Z/r;
}

float Vecteur::getX()
{
    return X;
}

float Vecteur::getY()
{
    return Y;
}

float Vecteur::getZ()
{
    return Z;
}

float Vecteur::norm()
{
    return sqrt(pow(X,2)+pow(Y,2)+pow(Z,2));
}

void Vecteur::setX(float newX)
{
    X = newX;
};
void Vecteur::setY(float newY)
{
    Y = newY;
};
void Vecteur::setZ(float newZ)
{
    Z = newZ;
};

bool Vecteur::Equal(Vecteur vect)
{
    if(X==vect.getX() && Y==vect.getY() && Z==vect.getZ()) return true;
    return false;
}
