/********************************************************
  Particle.cpp

  Source File for Particle Class

  Gina Guerrero - Fall 2013
********************************************************/

#include "Particle.h"
#include <cstdlib>

#include "Vector.h"

using namespace std;

//////////////////// PUBLIC FUNCTIONS /////////////////////
void Particle::Reset() {
	InUse = false;
	nhistory = 0;
}

Particle::Particle(){
	Reset();
}

void Particle::Draw() {
    glDisable(GL_LIGHTING);
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);

    glColor4f(Color.x, Color.y, Color.z, Color.w);

	glBegin(GL_POINTS);
		glVertex3f(Center.x, Center.y, Center.z);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}

void Particle::AddHistory(Vector3d c) {
    int i;

	if(nhistory == MAXHIST){
		for (i = 0; i < nhistory - 1; i++) {
            History[i] = History[i+1];
		}
		History[nhistory - 1] = c;
	} else {
        History[nhistory] = c;
        nhistory++;
	}
}


//////////// SETTERS //////////////
void Particle::SetBirth(double timestep) { Birth = timestep; }
void Particle::SetInUse(int type) { InUse = type; }


//////////// GETTERS ///////////////
double Particle::GetBirth() { return Birth; }
double Particle::GetAge(double currentTimestep) { return currentTimestep - Birth; }
int Particle::IsInUse() { return InUse; }
