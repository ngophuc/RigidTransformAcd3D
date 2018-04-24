cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)
project(RigidTransform3D)

option(NO_OPENCL "NO_OPENCL" OFF)
option(NO_OPENMP "NO_OPENMP" OFF)

message("NO_OPENCL " ${NO_OPENCL})
message("NO_OPENMP " ${NO_OPENMP})

# SOURCE LIST
set(CMAKE_COMMON_INC "${CMAKE_SOURCE_DIR}/scripts/cmake_common.cmake")
aux_source_directory(. SRC_LIST)
file(GLOB SOURCES
    VHACD_Lib/inc/*.h VHACD_Lib/src/*.cpp
    )

# INCLUDE LIST
include_directories ("${PROJECT_SOURCE_DIR}/VHACD_Lib/public")
include_directories ("${PROJECT_SOURCE_DIR}/VHACD_Lib/inc")

#Required in DGtal
FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

#Required in CGAL
# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )
if ( NOT CGAL_FOUND )
  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()
endif()
# include helper file
include( ${CGAL_USE_FILE} )

#Required in Boost
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
    message(STATUS "Boost and boost_program_options found.")
    include_directories( ${Boost_INCLUDE_DIRS} )
    SET(DGtalToolsLibDependencies ${DGtalToolsLibDependencies}
        ${Boost_LIBRAIRIES}
        ${Boost_PROGRAM_OPTIONS_LIBRARY})
    SET(DGtalLibInc ${Boost_INCLUDE_DIRS})
endif( Boost_FOUND)

add_definitions(-g)
add_definitions(-DWITH_VISU3D_QGLVIEWER -DWITH_QT5)

add_executable(decomposeShapeAcd3d acd3d_main.cpp oclHelper.cpp oclHelper.h ${SOURCES})
target_link_libraries(decomposeShapeAcd3d)

add_executable(transformDecomShape3d transformDecomShape.cpp Halfplane.cpp Halfplane.h Boundingbox.cpp Boundingbox.h Utility.cpp Utility.h)
target_link_libraries(transformDecomShape3d ${DGTAL_LIBRARIES} ${DGtalToolsLibDependencies} ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

add_executable(transformDecomShape3d_gui transformDecomShape_gui.cpp Halfplane.cpp Halfplane.h Boundingbox.cpp Boundingbox.h Utility.cpp Utility.h myViewer.h myViewer.cpp)
target_link_libraries(transformDecomShape3d_gui ${DGTAL_LIBRARIES} ${DGtalToolsLibDependencies} ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
