#ifndef DEFINITION_H
#define DEFINITION_H

#include <numeric>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "DGtal/geometry/curves/ArithmeticalDSS.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
#include <DGtal/io/readers/PointListReader.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/algorithm.h>
#include <CGAL/convex_hull_3.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel      K;
typedef K::Point_3                                              Point_3;
typedef CGAL::Delaunay_triangulation_3<K>                       Delaunay;
typedef Delaunay::Vertex_handle                                 Vertex_handle;
typedef Delaunay::Cell_handle                                   Cell_handle;
typedef CGAL::Polyhedron_3<K>                                   Polyhedron_3;
typedef Polyhedron_3::Facet_iterator                   Facet_iterator;
typedef Polyhedron_3::Halfedge_around_facet_circulator Halfedge_facet_circulator;
typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Polyhedron_3<K>                     Polyhedron_3;
typedef K::Segment_3                              Segment_3;
typedef CGAL::Creator_uniform_3<double, Point_3>  PointCreator;
//a functor computing the plane containing a triangular facet
struct Plane_from_facet {
        Polyhedron_3::Plane_3 operator()(Polyhedron_3::Facet& f) {
            Polyhedron_3::Halfedge_handle h = f.halfedge();
            return Polyhedron_3::Plane_3( h->vertex()->point(),
                                          h->next()->vertex()->point(),
                                          h->opposite()->vertex()->point());
        }
};

using namespace std;
using namespace DGtal;
using namespace Z2i;

#define OUTPUT "Result"
//#define CONTOURSIZE 50
#define IS_PLOT true
#define FILENAMESIZE 200

#define ERROR 1e-5

#define SAVE_SVG
//#define SAVE_EPS
//#define SAVE_PS
//#define SAVE_PNG
#define SAVE_PGM

//#define FILL_HP
//#define DRAW_GRID

//black
#define BGR 0
#define BGG 0
#define BGB 0
//white
#define OJR 255
#define OJG 255
#define OJB 255

#define BACKGROUND 255
#define FOREGROUND 0

//Red
#define CONTOUR_TRANSF_R 255
#define CONTOUR_TRANSF_G 0
#define CONTOUR_TRANSF_B 0
//Blue
#define TC_DSS_TRANSF_R 0
#define TC_DSS_TRANSF_G 0
#define TC_DSS_TRANSF_B 255
//Green
#define COMNONP_TRANSF_R 0
#define COMNONP_TRANSF_G 255
#define COMNONP_TRANSF_B 0

#define INSIDEP_TRANSF_R FOREGROUND
#define INSIDEP_TRANSF_G FOREGROUND
#define INSIDEP_TRANSF_B FOREGROUND

#define BACKGROUND_R BACKGROUND
#define BACKGROUND_G BACKGROUND
#define BACKGROUND_B BACKGROUND

#define FOREGROUND_R FOREGROUND
#define FOREGROUND_G FOREGROUND
#define FOREGROUND_B FOREGROUND

typedef double transformation[3]; // a transformation 2D : (tx,ty,theta) !
typedef double transformation3D[6]; // a transformation 3D : (tx,ty,tz,alpha,beta,gamma) !

namespace mySpace {
    typedef PointVector<2, double> PointD;
    typedef PointVector<2,int> Point;
    typedef PointVector<3, double> Point3DD;
    typedef PointVector<3,int> Point3D;
    typedef std::vector<Point> Range;
    typedef std::vector<Point>::const_iterator ConstIterator;
    typedef std::vector<PointD>::const_iterator ConstIteratorD;
    typedef std::vector<Point3D>::const_iterator ConstIterator3D;
    typedef std::vector<Point3DD>::const_iterator ConstIterator3DD;
}

using namespace mySpace;

#endif // DEFINITION_H
