/********************************************************
  Particle.h

  Header File for Particle Class

  Gina Guerrero - Fall 2013
********************************************************/


#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Vector.h"
#include "Attributes.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define MAXHIST		15

class Particle {
	private:
		int InUse;						// particle off/on

		double Birth;					// store NTimeSteps of when the particle is "born" (for age)

		Vector3d History[MAXHIST];		// particle's history of centers
		int nhistory;					// history indx

		int Blend;                      // draw in blend mode toggle

	public:
        Attributes A;                   // attributes class

		Particle();						// defaults...
		void Reset();					// gets called by the constructor. kind of cleans up..
		void Draw();					// draws the particle
        void AddHistory(Vector3d c);	// adds history

		//////////// SETTERS //////////////
		void SetBirth(double timestep);
		void SetInUse(int type);
		void SetBlend(int blend);

		//////////// GETTERS ///////////////
        double GetBirth();
		double GetAge(double currentTimestep);
		int IsInUse();

        //////////// DEBUGGING ///////////////
        void PrintAttr();
};

#endif
