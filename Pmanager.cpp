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
int Pmanager::GetNused() { return nused; }


int Pmanager::HasFreeParticles() {
    return MAXPART-nused;
}

int Pmanager::KillParticles(double ts) {
    int i;
    int cnt = 0;

    for (i = 0; i < nused; i++) {
        if(Particles[i].GetAge(ts) > 25) {
            FreeParticle(i);
            cnt++;
        }
    }
    //cout << "cnt of those killed: "<< cnt << endl;
    return cnt;
}

void Pmanager::UseParticle(Vector3d c0, Vector3d v0, double ts, Vector4d color, double m, double coefff, double coeffr) {

	Particles[nused].SetInUse(true);
	Particles[nused].SetC0(c0);
	Particles[nused].SetCenter(c0);
	Particles[nused].SetV0(v0);
    Particles[nused].SetVelocity(v0);
    Particles[nused].SetBirth(ts);
	Particles[nused].SetColor(color);
	Particles[nused].SetMass(m);
	Particles[nused].SetCoefff(coefff);
	Particles[nused].SetCoeffr(coeffr);

	//Particles[nused].PrintAttr();

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




