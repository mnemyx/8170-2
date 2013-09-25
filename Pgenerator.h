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
#include "time.h"

#define POINT 0
#define CIRCLE 1
#define SPHERE 2
#define LINE 3		// augh...I'm overwhelming myself

class Pgenerator {
	private:
		int Type;
		Model Shape;

		Vector3d Center;
		//Vector3d Velocity;		// could be moving...but uh, for now, let's not move it.

		double Radius;              // if it's a sphere?

		// i need a base for the stuff...
		double Mean;
		double StdDev;
		double BaseMass;
		double MStdDev;
		Vector4d BaseColor;
		double CStdDev;
		double BaseCoefff;
		double BaseCoeffr;

		// because I'm too lazy to create a struct? is the overhead going to be that bad?
		Vector3d GeneratedV0;
		Vector3d GeneratedC0;
		Vector4d GeneratedColor;
		double GeneratedMass;

		int PNum;

	public:
		Pgenerator();

		// setters
		void SetBaseAttr(int type, double bs, double sd, double bm, double msd, Vector4d bc, double csd, double pnum, double coefff, double coeffr);
		void SetCenterRadius(Vector3d center, double radius);
		void SetModel(int orientation = 2);
		void SetBaseColor(Vector4d newbc);

		// generate random velocity, center, color, mass
		void GenerateAttr();
		Vector4d GenerateColor(Vector4d c);

		// technically getters
		Vector3d GenV0();
		Vector3d GenC0();
		Vector4d GenCol();
		double GenMass();
		int GetPNum();
		double GetCoefff();
		double GetCoeffr();

};

#endif
