/*
 * CPoint3.h
 *
 *  Created on: 22 d�c. 2009
 *      Author: girouxi
 */

#ifndef CPOINT3_H_
#define CPOINT3_H_
#include <string>
#include <ctgmath>

class CPoint3f {
public:
	float X;
	float Y;
	float Z;
	CPoint3f(const float&, const float&, const float&);
	CPoint3f(const float&);
	CPoint3f();
    bool operator==(CPoint3f const& point);
    bool operator!=(CPoint3f const& point);
    bool Equal(CPoint3f point);
	CPoint3f(const CPoint3f&);
	float distance(CPoint3f point);
	float distance2D(CPoint3f point);
	std::string toString();
};

#endif /* CPOINT3_H_ */
