/*
 * CPointAnnexe.h
 *
 *  Created on: 22 d�c. 2009
 *      Author: girouxi
 */

#ifndef CPOINTANNEXE_H_
#define CPOINTANNEXE_H_
#include "CPoint3f.h"
class CPointAnnexe:public CPoint3f
{
public:
	int id_point_annex;
	CPointAnnexe();
	CPointAnnexe(int, const CPoint3f&);
	std::string toString();
	virtual ~CPointAnnexe();
};

#endif /* CPOINTANNEXE_H_ */
