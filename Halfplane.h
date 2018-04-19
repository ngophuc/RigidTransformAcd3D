#ifndef NEWHALFPLANE_H
#define NEWHALFPLANE_H

#include "definition.h"
#include "Utility.h"

class HalfPlane
{
    private:
        Point3D p1;
        Point3D p2;
        Point3D p3;
        //ax+by+cz+d=0
        int a;
        int b;
        int c;
        int d;
        int sign; //-1 (lower) < and 1 (upper) >

    public:
        HalfPlane():a(0),b(0),c(0),d(0),sign(0),p1(0,0,0),p2(0,0,0),p3(0,0,0){}
        HalfPlane(int a, int b, int c, int d, int s,Point3D p1, Point3D p2, Point3D p3);

        const Point3D getP1() const {return p1;}
        const Point3D getP2() const {return p2;}
        const Point3D getP3() const {return p3;}
        const int getA() const {return a;}
        const int getB() const {return b;}
        const int getC() const {return c;}
        const int getD() const {return d;}
        const int getSign() const {return sign;}
        void setSign(int s){sign=s;}

        bool isBelong(const Point3D& p);
        vector<Point3D> getPoints(const Point3D min, const Point3D max);

        HalfPlane transformHalfplane(const transformation3D t) const;
        HalfPlane transformPoint(const transformation3D t) const;
        double distancePoint(const Point3D p);
};

double distancePoint3D(HalfPlane hp, Point3D p);

#endif // NEWHALFPLANE_H

