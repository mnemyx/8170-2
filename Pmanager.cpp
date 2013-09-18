/********************************************************
  Pmanager.cpp

  Source File for the particle manager class
  
  Gina Guerrero - Fall 2013 
********************************************************/

#include "Pmanager.h"
#include "Vector.h"

using namespace std;

///////////////////////////// PUBLIC FUNCTIONS /////////////////////////
Pmanager::Pmanager() {
	nused = 0;
}

int Pmanager::HasFreeParticles() {
	if (nused >= MAXPART) return false;
	else return true;
}

void Pmanager::FreeParticle(int indx) {
	if (Particles[indx].IsInUse()) {
		Particles[indx].Reset();
		nused--;
	}
}

void Pmanager::DrawSystem() {
	int i;
	
	for ( i = 0; i < MAXPART; i++ ) {
		if (Particles[i].IsInUse()) Particles[i].Draw();
	}
}