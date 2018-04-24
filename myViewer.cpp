#include "myViewer.h"

#include <QCursor>
#include <QKeyEvent>
#include <QMap>
#include <QMenu>
#include <QMouseEvent>

#include <math.h>

using namespace std;

/******* Write to sdp and obj file ******/
void myViewer::saveObjet() {
    //Find bounding box of convex shape
    int nbFile=vecConvexShape.size();
    BoundingBox BB;
    Point3D pmin, pmax;
    vector<Point3D> pBB;
    for(int id=0; id<nbFile; id++) {
        BB=findBoundingBox(vecConvexShape.at(id));
        pmin=BB.getPointMin();
        pmax=BB.getPointMax();
        pBB.push_back(pmin);
        pBB.push_back(pmax);
    }
    BB=findBoundingBox(pBB);
    pmin=BB.getPointMin();
    pmax=BB.getPointMax()-pmin;

    char filename[FILENAMESIZE];
    sprintf(filename,"%s.sdp",file.c_str());
    ofstream myfile (filename);
    if (myfile.is_open()) {
        myfile <<"# sdp file generate from convex decomposition"<<endl;
        myfile <<"# format: x y z"<<endl;
        for(int id=0; id<nbFile; id++) {
            for(size_t it=0; it<vecConvexShape.at(id).size(); it++)
                myfile << vecConvexShape.at(id).at(it)[0]-pmin[0]
                        <<" "<<vecConvexShape.at(id).at(it)[1]-pmin[1]
                        <<" "<<vecConvexShape.at(id).at(it)[2]-pmin[2]<<endl;
        }
        myfile.close();
        cout<<"Save to "<<filename<<endl;
    }
    else {
        cout << "Unable to open file"<<filename;
        exit(-1);
    }
    HueShadeColorMap<double> hueMap(0.0,vecConvexShape.size());
    Board3D<> board;
    board << SetMode3D("PointVector", "Paving");//Both
    for(int id=0; id<nbFile; id++) {
        board << CustomColors3D(hueMap(id),hueMap(id));
        for(size_t it=0; it<vecConvexShape.at(id).size(); it++)
            board << vecConvexShape.at(id).at(it);
    }
    sprintf(filename,"%s.obj",file.c_str());
    cout<<"Save to "<<filename<<endl;
    board.saveOBJ(filename);
    cout<<"Save to "<<filename<<endl;;
    board.clear();
}
/******* Write to sdp and obj file ******/

void myViewer::drawMesh() {
    HueShadeColorMap<double> hueMap(0.0,vecConvexShape.size());
    for(int id=0; id<vecConvexShape.size(); id++) {
        (*this) << CustomColors3D(hueMap(id),hueMap(id));
        for(size_t i=0; i<vecFacets.at(id).size(); i++)
            (*this).addTriangle(vecVertices.at(id).at(vecFacets.at(id)[i][0]),vecVertices.at(id).at(vecFacets.at(id)[i][1]),vecVertices.at(id).at(vecFacets.at(id)[i][2]));
    }
}

void myViewer::drawVoxel(){
    HueShadeColorMap<double> hueMap(0.0,vecConvexShape.size());
    (*this) << SetMode3D("PointVector", "Paving");//Both
    for(int id=0; id<vecConvexShape.size(); id++) {
        (*this) << CustomColors3D(hueMap(id),hueMap(id));
        for (size_t i=0; i<vecConvexShape.at(id).size(); i++)
            (*this) << vecConvexShape.at(id).at(i);
    }
}

///////////////////////////////////////////////
//      Define new key bindings : S & V      //
///////////////////////////////////////////////
void myViewer::keyPressEvent(QKeyEvent *e) {
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = e->modifiers();
    bool handled = false;
    if ((e->key() == Qt::Key_S) && (modifiers == Qt::NoButton)) {
        saveObj++;
        if(saveObj==1)
            saveObjet();
        else
            cout<<"Files already save"<<endl;
        handled = true;
        update();
    }
    /*
    else if ((e->key() == Qt::Key_V) && (modifiers == Qt::NoButton)) {
        showVoxels = !showVoxels;
        cout<<"Key V pressed ==> "<<vecConvexShape.size()<<" and "<<showVoxels<<endl;
        draw();
        handled = true;
        update();
    }
    */
    if (!handled)
        QGLViewer::keyPressEvent(e);
}
/*
void myViewer::draw() {
    DGtal::Viewer3D<>::draw();
    if(showVoxels)
        drawVoxel();
    else
        drawMesh();
}
*/
void myViewer::init() {
    DGtal::Viewer3D<>::init();
    setKeyDescription(Qt::Key_S, "Save result in sdp and obj file.");
}

