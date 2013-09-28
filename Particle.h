/********************************************************
  Particle.h

  Header File for Particle Class

  Gina Guerrero - Fall 2013
********************************************************/


#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define MAXHIST		25

#include "Vector.h"

class Particle {
	private:
		Vector3d V0;					// initial velocity
		Vector3d Velocity;				// (current) velocity
		Vector3d C0;					// initial position
		Vector3d Center;				// (current) position

		Vector3d Acceleration;			// acceleration...
		double Birth;					// store NTimeSteps of when the particle is "born" (for age)
		Vector4d Color;					// color
		double Mass;					// particle's mass
		double Coefff;					// coefficient of friction for particle
		double Coeffr;					// coefficient of restitution for particle
		int InUse;						// particle off/on

		Vector3d History[MAXHIST];		// particle's history of centers
		int nhistory;					// history indx

		Vector3d tempv;                 // temporary velocity
		Vector3d tempc;                 // temporary center

		void AddHistory(Vector3d c);	// gets called by SetCenter()...

		int Blend;                      // draw in blend mode toggle

	public:
		void Reset();					// gets called by the constructor. kind of cleans up..
		Particle();						// defaults...
		void Draw();					// draws the particle
		void CalcAccel(Vector3d g, Vector3d w, double v);   // calculate acceleration - need to consider how to handle accel ops
		void CalcTempCV(double ts);     // calculate temp velocity & center;
		void CalcTempCV(double ts, double f);   // calculate temp velocity & center;
		void CalcAttractAccel(Vector3d p0, Vector3d g);
		void Reflect(Vector3d pnormal, Vector3d pvertex);    // reflect the particle given the triangle's normal and vertex index

		//////////// SETTERS //////////////
		void SetV0(Vector3d v);
		void SetVelocity(Vector3d v);
		void SetC0(Vector3d c);
		void SetCenter(Vector3d c);
		void SetAcceleration(Vector3d a);
		void SetBirth(double timestep);
		void SetColor(Vector4d color);
		void SetMass(double m);
		void SetInUse(int type);
		void SetCoefff(double f);
		void SetCoeffr(double r);
		void SetTempv(Vector3d v);
		void SetTempc(Vector3d c);

		//////////// GETTERS ///////////////
		Vector3d GetV0();
		Vector3d GetVelocity();
		Vector3d GetC0();
		Vector3d GetCenter();
		Vector3d GetAcceleration();
		double GetAge(double currentTimestep);
		double GetMass();
		int IsInUse();
		double GetCoefff();
		double GetCoeffr();
		Vector3d GetTempc();
		Vector3d GetTempv();
        double GetBirth();
        Vector4d GetColor();

        //////////// DEBUGGING ///////////////
        void PrintAttr();
};

#endif
