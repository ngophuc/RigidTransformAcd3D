#include "Halfplane.h"

HalfPlane::HalfPlane(int a, int b, int c, int d, int s,Point3D p1, Point3D p2, Point3D p3)
{
    this->a=a;
    this->b=b;
    this->c=c;
    this->d=d;
    this->sign=s;
    this->p1=p1;
    this->p2=p2;
    this->p3=p3;
}

bool HalfPlane::isBelong(const Point3D& p)
{
    return (sign*(a*p[0]+b*p[1]+c*p[2]+d)) >= 0;
}

vector<Point3D> HalfPlane::getPoints(const Point3D min, const Point3D max)
{
    vector<Point3D> vecP;
    for(int i=min[0]; i<=max[0]; i++)
        for(int j=min[1]; j<=max[1]; j++)
            for(int k=min[2]; k<=max[2]; j++)
            {
                Point3D p(i,j,k);
                if(isBelong(p))
                    vecP.push_back(p);
            }
    return vecP;
}

HalfPlane HalfPlane::transformHalfplane(const transformation3D t) const
{
    //Conversion of transformation
    int txa,txb,tya,tyb,tza,tzb;
    convertDecimal2Fraction(t[0],txa,txb);
    convertDecimal2Fraction(t[1],tya,tyb);
    convertDecimal2Fraction(t[2],tza,tzb);
    int alphaA,alphaB,alphaC;//alpha
    convertAngle2Pythagore(t[3],alphaA,alphaB,alphaC,ERROR);
    int betaA,betaB,betaC;//beta
    convertAngle2Pythagore(t[4],betaA,betaB,betaC,ERROR);
    int gammaA,gammaB,gammaC;//beta
    convertAngle2Pythagore(t[5],gammaA,gammaB,gammaC,ERROR);

    ///cout<<"Translation x "<<t[0]<<" equivalent "<<txa<<"/"<<txb<<endl;
    ///cout<<"Translation y "<<t[1]<<" equivalent "<<tya<<"/"<<tyb<<endl;
    ///cout<<"Translation z "<<t[2]<<" equivalent "<<tya<<"/"<<tyb<<endl;
    ///cout<<"Rotation alpha "<<t[3]<<" equivalent "<<alphaA<<","<<alphaB<<","<<alphaC<<endl;
    ///cout<<"Rotation beta "<<t[4]<<" equivalent "<<betaA<<","<<betaB<<","<<betaC<<endl;
    ///cout<<"Rotation gamma "<<t[5]<<" equivalent "<<gammaA<<","<<gammaB<<","<<gammaC<<endl;

    /**** Discrete version *******
    //Translation
    int ta=a;
    int tb=b;
    int tc=c;
    int td=d+ceil(a*(double)txa/txb+b*(double)tya/tyb+c*(double)tza/tzb);
    cout<<"o=>("<<a<<","<<b<<","<<c<<","<<d<<","<<sign<<")"<<endl;
    cout<<"t=>("<<ta<<","<<tb<<","<<tc<<","<<td<<","<<sign<<")"<<endl;
    //Rotation
    if((alphaA==0 && alphaB==0)&&(betaA==0 && betaB==0)&&(gammaA==0 && gammaB==0))
        return HalfPlane(ta,tb,tc,td,sign,p1,p2,p3);
    //Rotation by Rz gamma
    Point3D rp1=Point3D(p1[0]*gammaB-p1[1]*gammaA,p1[0]*gammaA+p1[1]*gammaB,p1[2]*gammaC);
    Point3D rp2=Point3D(p2[0]*gammaB-p2[1]*gammaA,p2[0]*gammaA+p2[1]*gammaB,p2[2]*gammaC);
    Point3D rp3=Point3D(p3[0]*gammaB-p3[1]*gammaA,p3[0]*gammaA+p3[1]*gammaB,p3[2]*gammaC);
    cout<<"r=>("<<ra<<","<<rb<<","<<rc<<","<<rd<<","<<sign<<")"<<endl<<endl;
    /**** Discrete version *******/

    /**** Approximation version ****/
    //Rotation by Rz gamma
    /*
    Point3D rp1=Point3D(round(p1[0]*cos(t[5])-p1[1]*sin(t[5])+t[0]),round(p1[0]*sin(t[5])+p1[1]*cos(t[5])+t[1]),round(p1[2]+t[2]));
    Point3D rp2=Point3D(round(p2[0]*cos(t[5])-p2[1]*sin(t[5])+t[0]),round(p2[0]*sin(t[5])+p2[1]*cos(t[5])+t[1]),round(p2[2]+t[2]));
    Point3D rp3=Point3D(round(p3[0]*cos(t[5])-p3[1]*sin(t[5])+t[0]),round(p3[0]*sin(t[5])+p3[1]*cos(t[5])+t[1]),round(p3[2]+t[2]));
    */
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
    Point3D rp1=Point3D(round(p1[0]*r11+p1[1]*r12+p1[2]*r13+t[0]),round(p1[0]*r21+p1[1]*r22+p1[2]*r23+t[1]),round(p1[0]*r31+p1[1]*r32+p1[2]*r33+t[2]));
    Point3D rp2=Point3D(round(p2[0]*r11+p2[1]*r12+p2[2]*r13+t[0]),round(p2[0]*r21+p2[1]*r22+p2[2]*r23+t[1]),round(p2[0]*r31+p2[1]*r32+p2[2]*r33+t[2]));
    Point3D rp3=Point3D(round(p3[0]*r11+p3[1]*r12+p3[2]*r13+t[0]),round(p3[0]*r21+p3[1]*r22+p3[2]*r23+t[1]),round(p3[0]*r31+p3[1]*r32+p3[2]*r33+t[2]));

    /**** Approximation version ****/
    Point3D rp1p2=Point3D(rp2[0]-rp1[0],rp2[1]-rp1[1],rp2[2]-rp1[2]);
    Point3D rp1p3=Point3D(rp3[0]-rp1[0],rp3[1]-rp1[1],rp3[2]-rp1[2]);
    ///cout<<"rp1="<<rp1<<" rp2="<<rp2<<" rp3="<<rp3<< " rp1p2="<<rp1p2<<" rp1p3="<<rp1p3<<endl;
    //n(a,b,c)=p1p2xp1p3
    int ra=rp1p2[1]*rp1p3[2]-rp1p2[2]*rp1p3[1];
    int rb=rp1p2[2]*rp1p3[0]-rp1p2[0]*rp1p3[2];
    int rc=rp1p2[0]*rp1p3[1]-rp1p2[1]*rp1p3[0];
    int rd=-(ra*rp1[0]+rb*rp1[1]+rc*rp1[2]);
    int rPgcd=abs(pgcd(ra,abs(pgcd(rb,rc))));
    ///cout<<"("<<ra<<","<<rb<<","<<rc<<","<<rd<<","<<sign<<") and pgcd="<<rPgcd<<endl<<endl;
    if(rPgcd!=1 && rPgcd!=0)
    {
        ra=ra/rPgcd;
        rb=rb/rPgcd;
        rc=rc/rPgcd;
        rd=rd/rPgcd;
    }
    cout<<"rp1="<<rp1<<" rp2="<<rp2<<" rp3="<<rp3<<endl;
    cout<<"("<<ra<<","<<rb<<","<<rc<<","<<rd<<","<<sign<<")"<<endl<<endl;
    return (HalfPlane(ra,rb,rc,rd,sign,rp1,rp2,rp3));
}

HalfPlane HalfPlane::transformPoint(const transformation3D t) const
{
    double alpha=t[3],beta=t[4],gamma=t[5];
    if(alpha==0 && beta==0 && gamma==0 && t[0]==0 && t[1]==0 && t[2]==0)
        return (HalfPlane(0,0,0,0,0,p1,p2,p3));

    double r11=cos(alpha)*cos(beta)*cos(gamma)-sin(alpha)*cos(gamma);
    double r12=-cos(alpha)*cos(beta)*sin(gamma)-sin(alpha)*cos(gamma);
    double r13=cos(alpha)*sin(beta);
    double r21=sin(alpha)*cos(beta)*cos(gamma)+cos(alpha)*sin(gamma);
    double r22=-sin(alpha)*cos(beta)*sin(gamma)+cos(alpha)*cos(gamma);
    double r23=sin(alpha)*sin(beta);
    double r31=-sin(beta)*cos(gamma);
    double r32=sin(beta)*sin(gamma);
    double r33=cos(beta);
    Point3D rp1=Point3D(round(p1[0]*r11+p1[1]*r12+p1[2]*r13+t[0]),round(p1[0]*r21+p1[1]*r22+p1[2]*r23+t[1]),round(p1[0]*r31+p1[1]*r32+p1[2]*r33+t[2]));
    Point3D rp2=Point3D(round(p2[0]*r11+p2[1]*r12+p2[2]*r13+t[0]),round(p2[0]*r21+p2[1]*r22+p2[2]*r23+t[1]),round(p2[0]*r31+p2[1]*r32+p2[2]*r33+t[2]));
    Point3D rp3=Point3D(round(p3[0]*r11+p3[1]*r12+p3[2]*r13+t[0]),round(p3[0]*r21+p3[1]*r22+p3[2]*r23+t[1]),round(p3[0]*r31+p3[1]*r32+p3[2]*r33+t[2]));
    return (HalfPlane(0,0,0,0,0,rp1,rp2,rp3));
}

double HalfPlane::distancePoint(const Point3D p)
{
    return ((double(a*p[0]+b*p[1]+c*p[2]))/sqrt(a*a+b*b+c*c));
}

double distancePoint3D(HalfPlane hp, Point3D p)
{
    return ((hp.getA()*p[0]+hp.getB()*p[1]+hp.getC()*p[2]+hp.getD())/sqrt(hp.getA()*hp.getA()+hp.getB()*hp.getB()+hp.getC()*hp.getC()));
}
