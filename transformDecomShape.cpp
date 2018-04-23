#include <DGtal/io/readers/PointListReader.h>
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board3D.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "Halfplane.h"
#include "Boundingbox.h"

namespace po=boost::program_options;

using namespace mySpace;
using namespace std;

vector<Point3D> generateConvexShape(const vector<Point3D>& vecPoints, vector<HalfPlane>& vecHP, std::vector<Point3D> &vecVertices, std::vector<Point3D> &vecFacets, bool isVerbose=false);
vector<vector<Point3D> > generateConvexShape(const vector<vector<Point3D> >& vecPoints, vector<vector<HalfPlane> > &vHP, vector<vector<Point3D> > &vVertices, vector<vector<Point3D> > &vFacets, bool isVerbose);

int main(int argc, char** argv)
{
    /********** Parameters ********/
    po::options_description general_opt("Allowed options are: ");
    general_opt.add_options()
            ("help,h", "display this message")
            ("input,i", po::value<string>(), "input filename.")
            ("output,o", po::value<std::string>()->default_value("./"), "output dir (default ./).")
            ("dir,d", po::value<std::string>()->default_value("./"), "execute dir (default ./).")
            ("tx,x", po::value<double>()->default_value(0.0), "x-translation.")
            ("ty,y", po::value<double>()->default_value(0.0), "y-translation.")
            ("tz,z", po::value<double>()->default_value(0.0), "y-translation.")
            ("alpha,a", po::value<double>()->default_value(0.0), "rotation angle by x-axis.")
            ("beta,b", po::value<double>()->default_value(0.0), "rotation angle by y-axis.")
            ("gamma,g", po::value<double>()->default_value(0.0), "rotation angle by z-axis.")
            ("sampling,s", po::value<int>()->default_value(100), "sampling data.")
            ("resolution,r", po::value<int>()->default_value(100000), "ecomposition parameter resolution.")
            ("depth", po::value<int>()->default_value(20), "decomposition parameter depth.")
            ("minVolumePerCH,m", po::value<double>()->default_value(0.0001), "decomposition parameter minVolumePerCH.");

    bool parseOK=true;
    po::variables_map vm;
    try{
        po::store(po::parse_command_line(argc, argv, general_opt), vm);
    }catch(const exception& ex){
        trace.info()<< "Error checking program options: "<< ex.what()<< endl;
        parseOK=false;
    }

    po::notify(vm);
    if(vm.count("help")||argc<=1|| !parseOK || !vm.count("input") || !vm.count("output"))
    {
        trace.info()<< "Execution : " <<endl << "Options: "<<endl
                    << general_opt << "\n";
        return 0;
    }
    //bool paramTransf=vm.count("tx") && vm.count("ty") && vm.count("tz") && vm.count("alpha") && vm.count("beta") && vm.count("gramma");
    double a=0.0, b=0.0, c=0.0, alpha = 0.0, beta=0.0, gamma=0.0;
    //if (paramTransf) {
        a=vm["tx"].as<double>();
        b=vm["ty"].as<double>();
        c=vm["tz"].as<double>();
        alpha=vm["alpha"].as<double>();
        beta=vm["beta"].as<double>();
        gamma=vm["gamma"].as<double>();
    //}
    int sampling=vm["sampling"].as<int>();
    int resolution=vm["resolution"].as<int>();
    int depth=vm["depth"].as<int>();
    double minVolumePerCH=vm["minVolumePerCH"].as<double>();
    string dir=vm["dir"].as<string>();
    string inputFile=vm["input"].as<string>();
    string outputFile=vm["output"].as<string>();
    string infile = inputFile.substr(0, inputFile.find_last_of("."));
    string outfile = outputFile.substr(0, outputFile.find_last_of("."));
    //cout<<"inputFile="<<inputFile<<" infile="<<infile<<" outputFile="<<outputFile<<endl;
    /********** Parameters ********/

    /*** Use Acd3d decomposition ***/
    //input : *.obj (ex: BarbedThing.obj)
    //output : *-acd.obj (ex: BarbedThing-acd.obj) and *-acd.txt, *-acd_0.sdp, *-acd_1.sdp, ...
    char instruction[5*FILENAMESIZE];
    char filename[FILENAMESIZE];
    sprintf(filename,"%s-acd.obj",infile.c_str());
    //--input ../data/bunny.obj --output ../data/bunny-acd.obj --log log.txt
    sprintf(instruction,"%sdecomposeShapeAcd3d --input %s --output %s --log log.txt --resolution %d --depth %d --minVolumePerCH %f",dir.c_str(),inputFile.c_str(),filename,resolution,depth,minVolumePerCH);
    system(instruction);
    ifstream inFile;
    sprintf(filename,"%s-acd.txt",infile.c_str());
    inFile.open(filename);
    int nbFile;
    if (inFile.is_open()) {
        inFile >> nbFile;
        inFile.close();
    }
    else {
        cout << "Unable to open file"<<filename;
        exit(-1);
    }
    /*** Use Acd3d decomposition ***/

    /******* Read decomposition ************/
    vector<vector<Point3D> > vecPoints;
    for (int idFile=0; idFile<nbFile; idFile++) {
        sprintf(filename,"%s-acd_%d.dat",infile.c_str(),idFile);
        vector<Point3D> vPoints;
        vector<Point3DD> tmpVecPoints=PointListReader<Point3DD>::getPointsFromFile(filename);
        for(vector<Point3DD>::const_iterator it=tmpVecPoints.begin(); it!=tmpVecPoints.end(); it++) {
            Point3D p(round((*it)[0]*sampling),round((*it)[1]*sampling),round((*it)[2]*sampling));
            if(!isExist(vPoints,p))
                vPoints.push_back(p);
        }
        if(vPoints.size()<4) {
            cout<<"Error of sampling, not enough points for discretization";
            exit(-1);
        }
        vecPoints.push_back(vPoints);
    }
    /******* Read decomposition ************/

    /******* Generate convex shape ********/
    vector<vector<HalfPlane> > vecHP;
    vector<vector<Point3D> > vecFacets, vecVertices;
    vector<vector<Point3D> > vecConvexShape;
    vecConvexShape=generateConvexShape(vecPoints,vecHP,vecVertices,vecFacets,false);
    /******* Generate convex shape ********/

    /******* Write to obj file ******/
    HueShadeColorMap<double> hueMap(0.0,vecConvexShape.size());
    Board3D<> board;
    //Decomposition
    for(int id=0; id<nbFile; id++) {
        //board.setFillColor(hueMap(id));
        for(size_t i=0; i<vecFacets.at(id).size(); i++)
            board.addTriangle(vecVertices.at(id).at(vecFacets.at(id)[i][0]),vecVertices.at(id).at(vecFacets.at(id)[i][1]),vecVertices.at(id).at(vecFacets.at(id)[i][2]));
    }
    sprintf(filename,"%s_decomp.obj",outfile.c_str());
    cout<<filename<<endl;
    board.saveOBJ(filename);
    board.clear();
    //Digitization
    board << SetMode3D("PointVector", "Both");
    for(int id=0; id<nbFile; id++) {
        board << CustomColors3D(hueMap(id),hueMap(id));
        for(size_t it=0; it<vecConvexShape.at(id).size(); it++)
            board << vecConvexShape.at(id).at(it);
    }
    sprintf(filename,"%s_shape.obj",outfile.c_str());
    cout<<filename<<endl;
    board.saveOBJ(filename);
    board.clear();
    /******* Write to obj file ******/


    /****** Transformed convex shape ******/
    transformation3D T;
    T[0]=a;
    T[1]=b;
    T[2]=c;
    T[3]=alpha;
    T[4]=beta;
    T[5]=gamma;
    vector<vector<HalfPlane> > tvecHP;
    vector<vector<Point3D> > tvecFacets, tvecVertices,tvecConvexShape;
    for(size_t id=0; id<vecHP.size(); id++) {
        /****** Transform HP 3D ******/
        vector<HalfPlane> tempVecHP;
        for(size_t it=0; it<vecHP.at(id).size(); it++)
            tempVecHP.push_back(vecHP.at(id).at(it).transformPoint(T));
        vector<Point3D> tTriPoints;
        for(size_t it=0; it<tempVecHP.size(); it++) {
            tTriPoints.push_back(tempVecHP.at(it).getP1());
            tTriPoints.push_back(tempVecHP.at(it).getP2());
            tTriPoints.push_back(tempVecHP.at(it).getP3());
        }
        /****** Transform HP 3D ******/
        /******* Generate transformed polyedron and transformed convex shape ******/
        vector<HalfPlane> tmpVecHP;
        vector<Point3D> tmpVecFacets, tmpVecVertices;
        vector<Point3D> tmpVecConvexShape=generateConvexShape(tTriPoints,tmpVecHP,tmpVecVertices,tmpVecFacets,false);
        /******* Generate transformed polyedron and transformed convex shape ******/

        tvecHP.push_back(tmpVecHP);
        tvecFacets.push_back(tmpVecFacets);
        tvecVertices.push_back(tmpVecVertices);
        tvecConvexShape.push_back(tmpVecConvexShape);
    }
    /****** Transformed convex shape ******/

    /******* Write to sdp then obj file ******/
    board << SetMode3D("PointVector", "Both");//<< SetMode3D(domain.className(), "Paving")
    for(int id=0; id<nbFile; id++) {
        board << CustomColors3D(hueMap(id),hueMap(id));
        for(size_t it=0; it<tvecConvexShape.at(id).size(); it++)
            board << tvecConvexShape.at(id).at(it);
    }
    board.saveOBJ(outputFile.c_str());
    cout<<outputFile.c_str()<<endl;
    board.clear();
    /******* Write to sdp then obj file ******/

    return 0;
}

vector<Point3D> generateConvexShape(const vector<Point3D>& vecPoints, vector<HalfPlane>& vecHP, std::vector<Point3D> &vecVertices, std::vector<Point3D> &vecFacets, bool isVerbose)
{
    /******* calculate bounding box ********/
    BoundingBox BB=findBoundingBox(vecPoints);
    /******* calculate bounding box ********/

    /******* convert Point3D to Point_3 ***/
    std::vector<Point_3> points;
    for(vector<Point3D>::const_iterator it=vecPoints.begin(); it!=vecPoints.end(); it++)
        points.push_back(Point_3((*it)[0],(*it)[1],(*it)[2]));
    /******* convert Point3D to Point_3 ***/

    /******* calculate convex hull ********/
    Polyhedron_3 chull;
    CGAL::convex_hull_3(points.begin(), points.end(), chull);
    if(isVerbose)
        cout << "The convex hull contains " << chull.size_of_vertices() << " vertices"
             << " and "<< chull.size_of_facets()<<" facets"<<std::endl;
    /******* calculate convex hull ********/

    /******* vertices and facets of convex hull *******/
    int v1,v2,v3,dst,count;
    for(auto it=chull.vertices_begin();it!=chull.vertices_end(); it++)
        vecVertices.push_back(Point3D(it->point().x(),it->point().y(),it->point().z()));
    for (  Facet_iterator i = chull.facets_begin(); i != chull.facets_end(); ++i)
    {
        Halfedge_facet_circulator j = i->facet_begin();
        CGAL_assertion( CGAL::circulator_size(j) == 3);
        count=0;
        do {
            dst = std::distance(chull.vertices_begin(), j->vertex());
            if(count==0) v1=dst;
            else if(count==1) v2=dst;
            else v3=dst;
            count++;
        } while ( ++j != i->facet_begin());
        if(v1!=v2 && v2!=v3)
            vecFacets.push_back(Point3D(v1,v2,v3));
    }
    /******* vertices and facets of convex hull *******/

    /******* calculate halfplane from convex hull ******/
    Point3D p=findCentroid(vecPoints),p1,p2,p3,p1p2,p1p3;
    int a,b,c,d,sign;
    for(size_t i=0; i<vecFacets.size(); i++)
    {
        //cout<<"face "<<i<<": ("<<vecFacets.at(i)[0]<<","<<vecFacets.at(i)[1]<<","<<vecFacets.at(i)[2]<<")"<<endl;
        p1=vecVertices.at(vecFacets.at(i)[0]);
        p2=vecVertices.at(vecFacets.at(i)[1]);
        p3=vecVertices.at(vecFacets.at(i)[2]);
        p1p2=Point3D(p2[0]-p1[0],p2[1]-p1[1],p2[2]-p1[2]);
        p1p3=Point3D(p3[0]-p1[0],p3[1]-p1[1],p3[2]-p1[2]);
        //n(a,b,c)=p1p2xp1p3
        a=p1p2[1]*p1p3[2]-p1p2[2]*p1p3[1];
        b=p1p2[2]*p1p3[0]-p1p2[0]*p1p3[2];
        c=p1p2[0]*p1p3[1]-p1p2[1]*p1p3[0];
        d=-(a*p1[0]+b*p1[1]+c*p1[2]);
        sign=((a*p[0]+b*p[1]+c*p[2]+d))>0 ? 1:-1;
        vecHP.push_back(HalfPlane(a,b,c,d,sign,p1,p2,p3));
    }
    if(isVerbose)
    {
        cout<<"Number of halfplanes extracted="<<vecHP.size()<<endl;
        for(size_t it=0; it<vecHP.size(); it++)
            cout<<"("<<vecHP.at(it).getA()<<","<<vecHP.at(it).getB()<<","<<vecHP.at(it).getC()<<","<<vecHP.at(it).getD()<<","<<vecHP.at(it).getSign()<<")"<<endl;
    }
    /******* calculate halfplane from convex hull ******/

    /******* generate convexe objet from convex hull ******/
    Point3D min=BB.getPointMin();
    Point3D max=BB.getPointMax();
    vector<Point3D> vecPoint_CH;
    bool isGood;
    for(int i=min[0]; i<=max[0]; i++)
        for(int j=min[1]; j<=max[1]; j++)
            for(int k=min[2]; k<=max[2]; k++) {
                isGood=true;
                Point3D p(i,j,k);
                for(size_t it=0; it<vecHP.size(); it++)
                    if(!vecHP.at(it).isBelong(p))
                        isGood=false;
                if(isGood)
                    vecPoint_CH.push_back(p);
            }
    if(isVerbose)
        cout << vecPoint_CH.size() << " points in CH" << endl;
    /******* generate convexe objet from convex hull ******/
    return vecPoint_CH;
}

vector<vector<Point3D> > generateConvexShape(const vector<vector<Point3D> >& vecPoints, vector<vector<HalfPlane> >& vHP, vector<vector<Point3D> > &vVertices, vector<vector<Point3D> > &vFacets, bool isVerbose)
{
    vector<vector<Point3D> > vPoint_CH;
    for (size_t it=0; it<vecPoints.size(); it++)
    {
        vector<HalfPlane> vecHP;
        vector<Point3D> vecVertices;
        vector<Point3D> vecFacets;
        vector<Point3D> vecPoint_CH=generateConvexShape(vecPoints.at(it),vecHP,vecVertices,vecFacets,isVerbose);
        vHP.push_back(vecHP);
        vVertices.push_back(vecVertices);
        vFacets.push_back(vecFacets);
        vPoint_CH.push_back(vecPoint_CH);
    }
    return vPoint_CH;
}
