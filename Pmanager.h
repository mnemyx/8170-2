/********************************************************
  Pmanager.h

  Header File for particle manager class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PMANAGER_H_
#define _PMANAGER_H_

#define MAXPART		1000

#include "Particle.h"

class Pmanager {
	private:
		Particle Particles[MAXPART];	// matrix of particles...
		Pgenerator Generator;			// the manager's particle generator?
		int nused;						// count of used particles
				
	public:
		Pmanager();
		int HasFreeParticles();			// determines if it has free particles
		void FreeParticle(int indx);	// frees a used particle @ given index
		void DrawSystem();
		
		int UseParticle();				// returns an int for the generator to use?
		
};

#endif
