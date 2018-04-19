#ifndef MYFUNCTIONS
#define MYFUNCTIONS

#include "definition.h"
#
/********** Conversion of transformation **********/
int pgcd(int a, int b);
bool convertDecimal2Fraction(double DecimalNum, int& Numerator, int& Denominator);
int findSmallestValue(double X, double Y);
bool convertAngle2Pythagore(double B, int& a, int& b, int& c, double e);
/********** Conversion of transformation **********/

/********** Distance ******/
double distancePoint3D(Point3D p1, Point3D p2);
/********** Distance ******/

/********** Transformation ******/
Point3D transformPoint3D(Point3D p, transformation3D t);
Point3D transformPoint3D(Point3D p, transformation3D t, double angle);
/********** Transformation ******/

bool isExist(const vector<Point3D>& vec, Point3D p);

#endif // MYFUNCTIONS

