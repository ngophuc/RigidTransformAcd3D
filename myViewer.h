#ifndef MYVIEWER_H
#define MYVIEWER_H

#ifdef WITH_VISU3D_QGLVIEWER
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#endif

#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/boards/Board3D.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "definition.h"
#include "Boundingbox.h"

class myViewer : public DGtal::Viewer3D<> {
    private:
        bool showVoxels;
        unsigned int saveObj;
        string file;
        vector<vector<Point3D> > vecFacets, vecVertices,vecConvexShape;
    public:
        myViewer() : saveObj(0), showVoxels(true){};
        myViewer(string f, bool s, vector<vector<Point3D> >& v1, vector<vector<Point3D> >& v2, const vector<vector<Point3D> > v3) :
            saveObj(0), showVoxels(s), file(f),
            vecFacets(v1), vecVertices(v2), vecConvexShape(v3){};
        const bool getShowVoxels() const {return showVoxels;}
        void drawMesh();
        void drawVoxel();
    protected:
        void saveObjet();
        //virtual void draw();
        virtual void init();
        virtual void keyPressEvent(QKeyEvent *e);
};

#endif //MYVIEWER_H
