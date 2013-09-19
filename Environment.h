/********************************************************
  Environment.h

  Header File for the environment class
  
  Gina Guerrero - Fall 2013 
********************************************************/


#ifndef _ENV_H
#define _ENV_H

#include "Model.h"
#include "Vector.h"

class Environment {
	private:
		// figure out the forces involved?
		Vector3d G;
		double CoeffofR;
		double CoeffofF;
		
		Vector3d Wind;
		double Viscosity;
		
	public:
		Environment();		// just pass in an environment specific file?
		
		
};

#endif
