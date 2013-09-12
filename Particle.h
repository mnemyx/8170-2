/********************************************************
  Particle.h

  Header File for Particle Class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#define MAXHIST		1000

#include "Vector.h"

class Particle {
	private:
		Vector3d V0;					// initial velocity
		Vector3d Velocity;				// (current) velocity
		Vector3d C0;					// initial position
		Vector3d Center;				// (current) position
		
		int Birth;						// store NTimeSteps of when the particle is "born" (for age)
		double Color[4];				// color
		double Mass;					// particle's mass
		int Status;						// particle off/on

		Vector3d History[MAXHIST];		// particle's history
		
	public:
		Particle();
		
		// draws the particle
		Draw();
};

#endif
