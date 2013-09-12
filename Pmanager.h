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
		Particle Particles[MAXPART];
				
	public:
		Pmanager();
		
};

#endif
