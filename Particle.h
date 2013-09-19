/********************************************************
  Particle.h

  Header File for Particle Class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#define MAXHIST		10000

#include "Vector.h"

class Particle {
	private:
		Vector3d V0;					// initial velocity
		Vector3d Velocity;				// (current) velocity
		Vector3d C0;					// initial position
		Vector3d Center;				// (current) position
		
		Vector3d Acceleration;			// acceleration...
		int Birth;						// store NTimeSteps of when the particle is "born" (for age)
		Vector4d Color;					// color
		double Mass;					// particle's mass
		int InUse;						// particle off/on

		Vector3d History[MAXHIST];		// particle's history of centers
		int nhistory;					// history indx
		
		void AddHistory(Vector3d c);	// gets called by SetCenter()...
		
	public:
		void Reset();					// gets called by the constructor. kind of cleans up..
		Particle();						// defaults...
		void Draw();					// draws the particle
		
		//////////// SETTERS //////////////
		void SetV0(Vector3d v);
		void SetVelocity(Vector3d v);
		void SetC0(Vector3d c);
		void SetCenter(Vector3d c);
		void SetAcceleration(Vector3d a);
		void SetBirth(int timestep);
		void SetColor(Vector4d color);
		void SetMass(double m);
		void SetInUse(int switch);

		//////////// GETTERS ///////////////
		Vector3d GetV0();
		Vector3d GetVelocity();
		Vector3d GetC0();
		Vector3d GetCenter();
		Vector3d GetAcceleration();
		int GetAge(int currentTimestep);
		int IsInUse();
		
};

#endif
