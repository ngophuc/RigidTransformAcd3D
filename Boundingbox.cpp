#include "boundingbox.h"

BoundingBox::BoundingBox()
{
    pointMin=Point3D(0,0);
    pointMax=Point3D(0,0);
}

BoundingBox::BoundingBox(Point3D min, Point3D max)
{
    pointMin=min;
    pointMax=max;
}

void BoundingBox::getBoundingBox(Point3D &min, Point3D &max) const
{
    min=pointMin;
    max=pointMax;
}

BoundingBox BoundingBox::getBoundingBox() const
{
    return BoundingBox(pointMin,pointMax);
}

Point3D BoundingBox::getSize()
{
    return Point3D(abs(pointMin[0]-pointMax[0])+1,abs(pointMin[1]-pointMax[1])+1,abs(pointMin[2]-pointMax[2])+1);
}

void BoundingBox::setBoundingBox(const Point3D min, const Point3D max)
{
    pointMin=min;
    pointMax=max;
}

bool BoundingBox::isInside(const Point3D &p) const
{
    return (p[0] >= pointMin[0] && p[0] <= pointMax[0]) &&
            (p[1] >= pointMin[1] && p[1] <= pointMax[1]) &&
            (p[2] >= pointMin[2] && p[2] <= pointMax[2]);
}

vector<Point3D> BoundingBox::getInsidePoints() const
{
    vector<Point3D> points;
    //FIXME: To optimize !!!
    for(int x=pointMin[0];x<=pointMax[0];x++)//for(int x=(int)minX-1;x<=(int)maxX+1;x++)
        for(int y=pointMin[1];y<=pointMax[1];y++)//for(int y=(int)minY-1;y<=(int)maxY+1;y++)
            for(int z=pointMin[2];z<=pointMax[2];z++)//for(int y=(int)minY-1;y<=(int)maxY+1;y++)
            {
                Point3D p(x,y);
                if(isInside(p))
                    points.push_back(p);
            }
    return points;
}

BoundingBox findBoundingBox(const vector<Point3D>& vec)
{
    int minX=vec.at(0)[0], minY=vec.at(0)[1], minZ=vec.at(0)[2];
    int maxX=vec.at(0)[0], maxY=vec.at(0)[1], maxZ=vec.at(0)[2];
    for(vector<Point3D>::const_iterator it=vec.begin(); it!=vec.end(); it++)
    {
        if((*it)[0]<minX)
            minX=(*it)[0];
        if((*it)[1]<minY)
            minY=(*it)[1];
        if((*it)[2]<minZ)
            minZ=(*it)[2];

        if((*it)[0]>maxX)
            maxX=(*it)[0];
        if((*it)[1]>maxY)
            maxY=(*it)[1];
        if((*it)[2]>maxZ)
            maxZ=(*it)[2];
    }
    //cout<<"min=("<<minX<<","<<minY<<") and max=("<<maxX<<","<<maxY<<")"<<endl;
    return BoundingBox(Point3D(minX,minY,minZ),Point3D(maxX,maxY,maxZ));
}

Point3D findCentroid(const vector<Point3D>& vec)
{
    int centerX=0, centerY=0, centerZ=0;
    //for (size_t i =0; i< vec.size(); i++)
    //    cout<<"i: "<<vec.at(i)<<endl;
    for(vector<Point3D>::const_iterator it=vec.begin(); it!=vec.end(); it++)
    {
        centerX+=(*it)[0];
        centerY+=(*it)[1];
        centerZ+=(*it)[2];
    }
    //cout<<"centerX="<<centerX<<" centerY="<<centerY<<" centerZ="<<centerZ<<endl;
    centerX=round(centerX/(int)vec.size());
    centerY=round(centerY/(int)vec.size());
    centerZ=round(centerZ/(int)vec.size());
    return Point3D(centerX,centerY,centerZ);
}
