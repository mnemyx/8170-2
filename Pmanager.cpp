/********************************************************
  Pmanager.cpp

  Source File for the particle manager class

  Gina Guerrero - Fall 2013
********************************************************/

#include "Pmanager.h"

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

void Pmanager::UseParticle(Vector3d c0, Vector3d v0, double ts, Vector4d color, double m, double coefff, double coeffr, int blend) {

	Particles[nused].SetInUse(true);
	Particles[nused].A.SetC0(c0);
	Particles[nused].A.SetCenter(c0);
	Particles[nused].A.SetV0(v0);
    Particles[nused].A.SetVelocity(v0);
    Particles[nused].SetBirth(ts);
	Particles[nused].A.SetColor(color);
	Particles[nused].A.SetMass(m);
	Particles[nused].A.SetCoefff(coefff);
	Particles[nused].A.SetCoeffr(coeffr);
	Particles[nused].SetBlend(blend);
    Particles[nused].AddHistory(c0);

	//Particles[nused].A.PrintAttr();

	nused++;
}

void Pmanager::FreeParticle(int indx) {
    if (indx < nused) {
        if (indx < nused - 1) {
            cout << "!! freeing indx: " << indx << " from nused: " << nused << endl;
            Particles[indx] = Particles[nused-1];
            Particles[nused-1].Reset();
            nused--;
        } else {
            cout << "-- freeing indx: " << indx << " from nused: " << nused << endl;
            Particles[indx].Reset();
            nused--;
        }
        cout << "new nused: " << nused << endl;
	}
}

void Pmanager::KillAll() {
    int i;
        for (i = 0; i < nused; i++)
            Particles[i].Reset();
    nused = 0;
}

int Pmanager::KillParticles(double ts) {
    int i;
    int cnt = 0;
    Vector3d center;
    int onused = nused;

    for (i = 0; i < onused; i++) {
        if (Particles[i].IsInUse()) {
            center = Particles[i].A.GetCenter();

            if(Particles[i].GetAge(ts) > 15
                || center.x > 80 || center.x < -80
                || center.y > 80 || center.y < -80
                || center.z > 80 || center.z < -80)
            {
                FreeParticle(i);
                cnt++;
            }
        }
    }
    //cout << "cnt of those killed: "<< cnt << endl;
    return cnt;
}

void Pmanager::DrawSystem() {
	int i;

	for ( i = 0; i < nused; i++ ) Particles[i].Draw();
}




