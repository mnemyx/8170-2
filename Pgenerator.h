/********************************************************
  Pgenerator.h

  Header File for the particle generator class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _PGENERATOR_H_
#define _PGENERATOR_H_

#include "Model.h"

#define MAXPART 1000

class Pgenerator {
	private:
		Model Shape;
		int Pindex[MAXPART];
		
	public:
		Pgenerator();
		void GenerateParticle();
		
};

#endif
