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
	Started = true;
	Stopped = true;
	Step = false;
}

void Pmanager::SetStopped(int type) { Stopped = type; }
void Pmanager::SetStarted(int type) { Started = type;}
void Pmanager::SetStep(int type) { Step = type; }

int Pmanager::IsStopped() { return Stopped; }
int Pmanager::IsStarted() { return Started; }
int Pmanager::IsStep() { return Step; }


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

void Pmanager::CalcAccel(Vector3d g, Vector3d w, double v) {
	int i;
	Vector3d a;

	a = g;

	for (i = 0; i < nused; i++ ) {
		//Acceleration = Acceleration + Viscosity * (Wind - Velocity) / Mass;
		Particles[i].SetAcceleration(a = a + v * (w - Particles[i].GetVelocity()) / Particles[i].GetMass());
	}
}
