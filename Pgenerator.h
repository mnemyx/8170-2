/********************************************************
  Pgenerator.h

  Header File for the particle generator class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PGENERATOR_H_
#define _PGENERATOR_H_

#include "Vector.h"
#include "Model.h"
#include "gauss.h"

#define POINT 0
#define CIRCLE 1
#define SPHERE 2

class Pgenerator {
	private:
		Model Shape;
		Vector3d Center;
		//Vector3d Velocity;		// could be moving...but uh, for now, let's not move it.
		double Radius;
		int Type;
		
		GeneratedV0;
		GeneratedC0;
		GeneratedColor;
		GeneratedMas;
		
	public:
		Pgenerator(int type = CIRCLE);
		void SetCenterRadius(Vector3d center, double radius);
		void SetModel(int orientation = 2);

		// generate random velocity, center, color, mass
		void GenerateAttr(double vmin, double vmax);
		
		// technically getters
		Vector3d GenV0();
		Vector3d GenC0();
		double* GenCol();
		double GenMass();
		
};

#endif
