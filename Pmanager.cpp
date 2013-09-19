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

void Pmanager::UseParticle(Vector3d c0, Vector3d v0, int ts, Vector4d color, double m) {
	
	Particles[nused].SetInUse(true);
	Particles[nused].SetC0(c0);
	Particles[nused].SetV0(v0);
    Particles[nused].SetBirth(ts);
	Particles[nused].SetColor(color);
	Particles[nused].SetMass(m);
	
	nused++;
}

void Pmanager::FreeParticle(int indx) {
	if (Particles[indx].IsInUse() && Particles[nused-1].IsInUse()) {
		Particles[indx] = Particles[nused-1];
		Particles[nused-1].Reset();
		nused--;
	}
}

void Pmanager::DrawSystem() {
	int i;
	
	for ( i = 0; i < nused; i++ ) Particles[i].Draw();
}

