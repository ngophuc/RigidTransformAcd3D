#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "definition.h"

#define EPSILON 1e-6
//#define EPSILON 0.05

class BoundingBox
{
        Point3D pointMin;
        Point3D pointMax;

    public:
        BoundingBox();
        BoundingBox(Point3D min, Point3D max);

        const Point3D getPointMin() const {return pointMin;}
        const Point3D getPointMax() const {return pointMax;}

        void getBoundingBox(Point3D& min, Point3D& max) const;
        BoundingBox getBoundingBox() const;
        Point3D getSize();

        void setPointMin(const Point3D p){pointMin=p;}
        void setPointMax(const Point3D p){pointMax=p;}
        void setBoundingBox(const Point3D min, const Point3D max);

        bool isInside(const Point3D &p) const;
        vector<Point3D> getInsidePoints() const;
};

BoundingBox findBoundingBox(const vector<Point3D>& vec);
Point3D findCentroid(const vector<Point3D>& vec);

#endif // BOUNDINGBOX_H
