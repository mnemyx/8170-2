/********************************************************
  Pmanager.h

  Header File for particle manager class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PMANAGER_H_
#define _PMANAGER_H_

#define MAXPART		10000

#include "Particle.h"

class Pmanager {
	private:
		Particle Particles[MAXPART];	// matrix of particles...
		int nused;						// count of used particles
				
	public:
		Pmanager();
		
		// determines if it has free particles
		int HasFreeParticles();					
		
		// assigns particle an initial velocity and center...
		void UseParticle(Vector3d c0, Vector3d v0, int ts, Vector4d color, double m);
		
		// frees a used particle @ given index		
		void FreeParticle(int indx);
			
		// draws all the used particles
		void DrawSystem();						
		
		void CheckCollision(Vector3d normal, Vector3d p0, Vector3d p1, Vector3d p2);
};

#endif
