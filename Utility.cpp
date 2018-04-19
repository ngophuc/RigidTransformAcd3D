#include "Utility.h"
#include <stdio.h>

/********** Conversion of transformation **********/
int pgcd(int a, int b)
{
    if(a==0 || b==0)
        return 1;
    int r;
    while (b != 0)
    {
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}


bool convertDecimal2Fraction(double DecimalNum, int& Numerator, int& Denominator)
{
    if(DecimalNum==(double)(int(DecimalNum)))
    {
        Numerator=DecimalNum;
        Denominator=1;
        return true;
    }
    const int MaxIntDigits=numeric_limits<int>::digits10;
    const int WholeDigits=int(log10(DecimalNum));
    const int FractionDigits=min(numeric_limits<double>::digits10 - WholeDigits, MaxIntDigits-1);

    //If number has too many digits, can't convert
    if(WholeDigits > MaxIntDigits)
        return false;

    //Separate into whole part and fraction
    int WholePart=int(DecimalNum);
    double DecimalPart=DecimalNum-WholePart;

    //Convert the decimal to a fraction
    Denominator=int(pow(10.0, FractionDigits));
    Numerator=int((DecimalPart * Denominator) + 0.5)+WholePart*Denominator;
    int p=pgcd(Numerator,Denominator);
    Numerator=Numerator/p;
    Denominator=Denominator/p;
    return true;
}

int findSmallestValue(double X, double Y)
{
    int start=0;
    int end=ceil(fabs(1.0/(Y-X)));//1e6;
    for(int i=start; i<=end; i++)
        if((int(X*i)+1)<Y*i)
            return i;
    return -1;
}
//FIXME: Angle=kPI/2 !!!!!
bool convertAngle2Pythagore(double B, int& a, int& b, int& c, double e)
{
    if(B==0)
    {
        a=0;
        b=0;
        c=0;
        return true;
    }
    int quart=0;
    double angle=B;
    while(angle>M_PI/2){angle-=M_PI/2;quart++;};//Get <= PI/2 angle
    double aa,bb;
    if(fabs(angle-M_PI/2)<e)
    {
        aa=1;
        bb=0;
        c=1;
    }
    else
    {
        double X=tan(angle-e)+1.0/cos(angle-e);
        double Y=tan(angle+e)+1.0/cos(angle+e);
        double Xp=1.0/tan(angle+e)+1.0/sin(angle+e);
        double Yp=1.0/tan(angle-e)+1.0/sin(angle-e);
        int V=findSmallestValue(X,Y);
        int Vp=findSmallestValue(Xp,Yp);
        if(V==-1 || Vp==-1)
            return false;
        int U=int(X*V)+1;
        int Up=int(Xp*Vp)+1;
        if((U*U+V*V)<(Up*Up+Vp*Vp))//quart=0
        {
            aa=2*U*V;
            bb=U*U-V*V;
            c=U*U+V*V;
            if(fabs(asin(aa/c)-angle)>e)
            {
                int tmp=aa;
                aa=bb;
                bb=tmp;
            }
        }
        else
        {
            aa=2*Up*Vp;
            bb=Up*Up-Vp*Vp;
            c=Up*Up+Vp*Vp;
        }
    }

    if(quart%4==0)
    {
        a=aa;//sinx
        b=bb;//cosx
    }
    else if(quart%4==1)
    {
        a=bb;//sin(x+pi/2)=cosx
        b=-aa;//cos(x+pi/2)=-sinx

    }
    else if(quart%4==2)
    {
        a=-aa;//sin(x+pi)=-sinx
        b=-bb;//cos(x+pi/2)=-cosx

    }
    else //if(quart%4==3)
    {
        a=-bb;//sin(x+pi/2)=-cosx
        b=aa;//cos(x+pi/2)=sinx
    }
    return true;
}
/********** Conversion of transformation **********/

/********** Distance ******/
double distancePoint3D(Point3D p1, Point3D p2)
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1])+(p1[2]-p2[2])*(p1[2]-p2[2]));
}
/********** Distance ******/

/********** Transformation ******/
Point3D transformPoint3D(Point3D p, transformation3D t) {
    double alpha=t[3],beta=t[4],gamma=t[5];
    double r11=cos(alpha)*cos(beta)*cos(gamma)-sin(alpha)*cos(gamma);
    double r12=-cos(alpha)*cos(beta)*sin(gamma)-sin(alpha)*cos(gamma);
    double r13=cos(alpha)*sin(beta);
    double r21=sin(alpha)*cos(beta)*cos(gamma)+cos(alpha)*sin(gamma);
    double r22=-sin(alpha)*cos(beta)*sin(gamma)+cos(alpha)*cos(gamma);
    double r23=sin(alpha)*sin(beta);
    double r31=-sin(beta)*cos(gamma);
    double r32=sin(beta)*sin(gamma);
    double r33=cos(beta);
    Point3D tp=Point3D(round(p[0]*r11+p[1]*r12+p[2]*r13+t[0]),round(p[0]*r21+p[1]*r22+p[2]*r23+t[1]),round(p[0]*r31+p[1]*r32+p[2]*r33+t[2]));
    return tp;
}

Point3D transformPoint3D(Point3D p, transformation3D t, double angle)
{
    double t_sin = std::sin ( angle );
    double t_cos = std::cos ( angle );
    Point3DD trans(t[0],t[1],t[2]), axis(t[3],t[4],t[5]), origin(0,0,0);
    ///cout<<"angle="<<angle<<" trans="<<trans<<" and axis="<<axis<<endl;
    Point3D tp;
    /* Backwards
    tp[0] = std::floor ( ( ( ( ( t_cos + ( axis[0] * axis[0] ) * ( 1. - t_cos ) ) * ( p[0] - trans[0] - origin[0] ) )
            + ( ( axis[2] * t_sin + axis[0] * axis[1] * ( 1. - t_cos ) ) * ( p[1] - trans[1] - origin[1] ) )
            + ( ( -axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos ) ) * ( p[2] - trans[2] - origin[2] ) ) ) ) + origin[0] + 0.5 );

    tp[1] = std::floor ( ( ( ( ( axis[0] * axis[1] * ( 1. - t_cos ) - axis[2] * t_sin )  * ( p[0] - trans[0] - origin[0] ) )
            + ( ( t_cos + ( axis[1] * axis[1] ) * ( 1. - t_cos ) ) * ( p[1] - trans[1] - origin[1] ) )
            + ( ( axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( p[2] - trans[2] - origin[2] ) ) ) ) + origin[1] + 0.5 );

    tp[2] = std::floor ( ( ( ( ( axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos )  ) * ( p[0] - trans[0] - origin[0] ) )
            + ( ( -axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( p[1] - trans[1] - origin[1] ) )
            + ( ( t_cos + ( axis[2] * axis[2] ) * ( 1. - t_cos ) ) * ( p[2] - trans[2] - origin[2] ) ) ) ) + origin[2] + 0.5 );
    */
    tp[0] = std::floor ( ( ( ( ( t_cos + ( axis[0] * axis[0] ) * ( 1. - t_cos ) ) * ( p[0] - origin[0] ) )
            + ( ( axis[0] * axis[1] * ( 1. - t_cos ) - axis[2] * t_sin ) * ( p[1] - origin[1] ) )
            + ( ( axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos )  ) * ( p[2] - origin[2] ) ) ) + trans[0] ) + origin[0] + 0.5 );

    tp[1] = std::floor ( ( ( ( ( axis[2] * t_sin + axis[0] * axis[1] * ( 1. - t_cos ) ) *  ( p[0] - origin[0] ) )
            + ( ( t_cos + ( axis[1] * axis[1] ) * ( 1. - t_cos ) ) * ( p[1] - origin[1] ) )
            + ( ( -axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( p[2] - origin[2] ) ) ) + trans[1] ) + origin[1] + 0.5 );

    tp[2] = std::floor ( ( ( ( ( -axis[1] * t_sin + axis[0] * axis[2] * ( 1. - t_cos ) ) * ( p[0] - origin[0] ) )
            + ( ( axis[0] * t_sin + axis[1] * axis[2] * ( 1. - t_cos ) ) * ( p[1] - origin[1] ) )
            + ( ( t_cos + ( axis[2] * axis[2] ) * ( 1. - t_cos ) ) * ( p[2] - origin[2] ) ) ) + trans[2] ) + origin[2] + 0.5 );

    return tp;
}
/********** Transformation ******/


bool isExist(const vector<Point3D>& vec, Point3D p)
{
    vector<Point3D>::const_iterator it=find(vec.begin(),vec.end(),p);
    if(it != vec.end())
        return true;
    else
        return false;
}
