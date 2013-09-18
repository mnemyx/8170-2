/********************************************************
  Pgenerator.cpp

  Source File for the particle generator class 
  
  Gina Guerrero - Fall 2013 
********************************************************/

#include "Pgenerator.h"

using namespace std;

Pgenerator::Pgenerator(int type) { 
	Type = type;
}

void Pgenerator::SetCenterRadius(Vector3d center, double radius) {
	Center = center;
	Radius = radius;
}

void Pgenerator::SetModel(int orientation) {
	switch (Type) {
		case CIRCLE: Shape.BuildCircle(Radius, orientation, Center.x, Center.y, Center.z); break;
		case SPHERE: Shape.BuildSphere(Radius, 3, Center.x, Center.y, Center.z); break;
	}
}


void Pgenerator::GenerateAttr(double vmin, double vmax) {
	switch(Type) {
		case POINT:
			// get random theta and phi
			double theta = drand48();
			double phi = drand48();
			
			Vector3d 
			
			break;
		default:
			// need random triangle index
			int triIndx = (int) drand48() * (Shape.GetNtriangles() - 1);
			
			// need the points
			Vector3d vertices, p0, p1, p2;
			
			vertices = Shape.GetTriangle(triIndx);
			p0 = Shape.GetVertex(vertices.x);
			p1 = Shape.GetVertex(vertices.y);
			p2 = Shape.GetVertex(vertices.z);
			
			// need random u & v under 1
			double u, v, smallr;
			
			u = drand48();
			v = drand48() * (1 - u);
			
			while(u + v >= 1) {
				u = drand48();
				v = drand48() * (1 - u);
			}
			
			smallr = drand48() * drand48();
			
			// calculate new point by turning it back to cartesian coordinates
			return p2 + u * (p0 - p2) + v * (p1 - p2) + smallr * Shape.GetNormal(triIndx);
			break;
	}
}

// generate random velocity, center, color, mass
Vector3d Pgenerator::GenV0(double min, double max) {
	// generate the center & velocity
	switch(Type) {
		case POINT:
			break;
		default:
			
			break;
	}
}

Vector3d Pgenerator::GenC0() {
	// mrand * max;
	
	
}

double* Pgenerator::GenCol() {}

double Pgenerator::GenMass() {}