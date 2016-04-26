/*
 * CPoint3.cpp
 *
 *  Created on: 22 d�c. 2009
 *      Author: girouxi; modifié par V. Sasyan (ajout de la fonction distance)
 */

#include "../../Include/API/CPoint3f.h"
#include "../../Include/API/consts.h"
#include <stdio.h>

using namespace std;

CPoint3f::CPoint3f(const float &x, const float &y, const float &z):X(x), Y(y), Z(z) {}

CPoint3f::CPoint3f(const float &a):X(a), Y(a), Z(a){}

CPoint3f::CPoint3f():X(RNOVA), Y(RNOVA), Z(RNOVA) {}

CPoint3f::CPoint3f(const CPoint3f &p):X(p.X), Y(p.Y), Z(p.Z) {}

bool CPoint3f::operator !=(CPoint3f const& point) {
    return not Equal(point);
}

bool CPoint3f::operator ==(CPoint3f const& point) {
    return Equal(point);
}

bool CPoint3f::Equal(CPoint3f point) {
    return (X == point.X and Y == point.Y and Z == point.Z);
}

string CPoint3f::toString(){
	char data[1024] = "";
	sprintf(data, "`->coord. : %f %f %f", X, Y, Z);
	string str(data);
	return str;
}

float CPoint3f::distance(CPoint3f point) {
    float dX = X-point.X;
    float dY = Y-point.Y;
    float dZ = Z-point.Z;

    return sqrt(dX * dX + dY * dY + dZ * dZ);
}

float CPoint3f::distance2D(CPoint3f point) {
    float dX = X-point.X;
    float dY = Y-point.Y;

    return sqrt(dX * dX + dY * dY);
}
