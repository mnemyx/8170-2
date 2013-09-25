/********************************************************
  Pgenerator.cpp

  Source File for the particle generator class

  Gina Guerrero - Fall 2013
********************************************************/

#include "Pgenerator.h"

using namespace std;

Pgenerator::Pgenerator() {
	srand48(time(0));
	gauss(1,1,time(0));
}

void Pgenerator::SetBaseAttr(int type, double bs, double sd, double bm, double msd, Vector4d bc, double csd, double pnum) {
	Type = type;
	Mean = bs;
	StdDev = sd;
	BaseMass = bm;
	MStdDev = msd;
	BaseColor = bc;
	CStdDev = csd;
	PNum = pnum;
	cout << "HI?" << endl;
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

void Pgenerator::SetBaseColor(Vector4d newbc) { BaseColor = newbc; }


void Pgenerator::GenerateAttr() {
	double smallr = drand48() * drand48();
	Vector3d smallv;
	smallv.set(drand48() * drand48(), drand48() * drand48(), drand48() * drand48());

	// get random theta and phi
	double theta = drand48();
	double phi = drand48();
	Vector3d unit;

	// for triangles- need random index, need temp vectors, u & v
	int triIndx = (int) drand48() * (Shape.GetNtriangles() - 1);
	Vector3d vertices, p0, p1, p2;
	double u, v;

	switch(Type) {
		case POINT:
			unit.set(sin(theta) * cos(phi), sin(theta) * cos(phi), cos(phi));

			GeneratedC0 = Center + smallr * unit;
			GeneratedV0 = gauss(Mean, StdDev, 0) * unit + smallv;

			break;

		// most of my other stuff have triangles...
		default:
			vertices = Shape.GetTriangle(triIndx);
			p0 = Shape.GetVertex(vertices.x);
			p1 = Shape.GetVertex(vertices.y);
			p2 = Shape.GetVertex(vertices.z);

			u = drand48();
			v = drand48() * (1 - u);

			while(u + v >= 1) {
				u = drand48();
				v = drand48() * (1 - u);
			}

			// calculate new point by turning it back to cartesian coordinates
			GeneratedC0 = p2 + u * (p0 - p2) + v * (p1 - p2) + (smallr * Shape.GetNormal(triIndx));
			GeneratedV0 = gauss(Mean, StdDev, 0) * Shape.GetNormal(triIndx) + smallv;

			break;
	}

	// figure out a random mass and color
	GeneratedMass = gauss(BaseMass, MStdDev, 0);
	GeneratedColor.set(gauss(BaseColor.x, CStdDev, 0), gauss(BaseColor.y, CStdDev, 0), gauss(BaseColor.z, CStdDev, 0), gauss(BaseColor.w, CStdDev, 0));
}


// generate random velocity, center, color, mass
Vector3d Pgenerator::GenV0() { return GeneratedV0; }
Vector3d Pgenerator::GenC0() { return GeneratedC0; }
Vector4d Pgenerator::GenCol() { return GeneratedColor; }
double Pgenerator::GenMass() { return GeneratedMass; }
int Pgenerator::GetPNum() { return PNum; }
