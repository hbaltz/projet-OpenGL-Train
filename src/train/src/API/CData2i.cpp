/*
 * CPoint2.cpp
 *
 *  Created on: 22 d�c. 2009
 *      Author: girouxi
 */

#include "../../Include/API/CData2i.h"
#include "../../Include/API/consts.h"
CData2i::CData2i(int x, int y):colonne_1(x), colonne_2(y) {
}
CData2i::CData2i():colonne_1(NOVAL), colonne_2(NOVAL) {
}
CData2i::CData2i(const CData2i &data2i):colonne_1(data2i.colonne_1), colonne_2(data2i.colonne_2){

}
