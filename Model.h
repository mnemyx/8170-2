/*
  Model.h

  Header File for Geometric Model Class
  Provides for construction of cuboid, cylinder and cone shapes tiled by triangles
  
  BIHE Computer Graphics    Donald H. House     6/22/06
  Modified - Gina Guerrero - Fall 2013 
*/

#ifndef _MODEL_H_
#define _MODEL_H_

#include "Vector.h"

#define MAXVERTICES   10000		  // shapes limited to 1000 vertices
#define MAXTRIANGLES  (MAXVERTICES / 3)

#define FRONTBACK		0
#define SIDES			1
#define TOPBOTTOM		2

#define VERTICALX 0
#define VERTICALZ 1
#define HORIZONTAL 2

class Model{
protected:
  Vector3d vertices[MAXVERTICES];   // vertex coordinates
  int nvertices;		    		// count of the number of vertices
  int triangles[MAXTRIANGLES][3];   // 3 vertex indices for each triangle
  Vector3d normals[MAXTRIANGLES];   // unit normal vector for each triangle
  int ntriangles;		    		// count of the number of triangles
  Vector3d overtices[MAXVERTICES];  // original set of vertices for the isohedron
  int onvertices;					// count of the number of original verices for the isohedron

  void Clean();			    		// bookkeeping, remove all vertices and triangles
  
  int AddVertex(const Vector3d &v); 	 	// insert a simple vertex into vertex table
  int AddOVertex(const Vector3d &v); 		// insert a simple vertex into vertex table
  int AddTriangle(int v0, int v1, int v2);  // insert a triangle, and its normal
  void Subdivide(int triangleIndex, int depth, float radius, Vector3d center);
  
public:
  // Constructor, make sure model is empty
  Model();
  
  // Make a sphere
  void BuildSphere(float r = 1.0, int depth = 3, double x = 0, double y = 0, double z = 0);
  
  // Make a cuboid model
  void BuildCuboid(float width = 1.0, float height = 1.0, float depth = 1.0, double x = 0, double y = 0, double z = 0);
  
  // Make a plane
  void BuildPlane(float length = 1.0, float width = 1.0, int orientation = 1, double x = 0, double y = 0, double z = 0);  
  
  // Make a cylinder model
  void BuildCylinder(float radius = 0.5, float height = 1.0);
  
  // Make a cone model
  void BuildCone(float radius = 0.5, float height = 1.0);
  
  // build the triangles for a circle
  void BuildCircle(float radius = 1.0, int orientation = 2, double x = 0, double y = 0, double z = 0);
  
  // draw the current model
  void Draw(int wireframe = 1);
  void Draw(const float* color);
  void Draw(const float* frontC, const float* backC);
  
  // get triangle @ index & vertex @ index
  Vector3d GetTriangle(int indx);
  Vector3d GetVertex(int indx);
  int GetNtriangles();
  Vector3d GetNormal(int indx);
};

#endif

