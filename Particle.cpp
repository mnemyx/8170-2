/********************************************************
  Particle.cpp

  Source File for Particle Class

  Gina Guerrero - Fall 2013
********************************************************/

#include "Particle.h"

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
    int i;
    glDisable(GL_LIGHTING);
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);

    if(!Blend) {
        glBegin(GL_POINTS);
            glColor4f(A.GetColor().x, A.GetColor().y, A.GetColor().z, A.GetColor().w);
            glVertex3f(A.GetCenter().x, A.GetCenter().y, A.GetCenter().z);
        glEnd();
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(nhistory == 1) {
            glBegin(GL_LINE);
                glColor4f(A.GetColor().x, A.GetColor().y, A.GetColor().z, 1);
                glVertex3f(history[1].x, history[1].y, history[1].z);
                glColor4f(A.GetColor().x, A.GetColor().y, A.GetColor().z, 0);
                glVertex3f(history[0].x, history[0].y, history[0].z);
        } else {
            glBegin(GL_LINE_STRIP);
            for (i = nhistory - 1; i >= 0; i--) {
                glColor4f(A.GetColor().x, A.GetColor().y, A.GetColor().z, (i/(nhistory-1)));
                glVertex3f(history[i].x, history[i].y, history[i].z);
            }
        }
        glEnd();
    }
	glDisable(GL_BLEND);
	glDisable(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}

void Particle::AddHistory(Vector3d c) {
    int i;
    cout << "nhistory before --- " << nhistory << endl;
	if(nhistory == MAXHIST){
		for (i = 0; i < nhistory - 1; i++) {
            history[i] = history[i+1];
		}
		history[nhistory - 1] = c;
	} else {
        history[nhistory] = c;
        nhistory++;
        cout << "nhistory after: "<< nhistory << endl;
	}
}


//////////// SETTERS //////////////
void Particle::SetBirth(double timestep) { Birth = timestep; }
void Particle::SetInUse(int type) { InUse = type; }
void Particle::SetBlend(int blend) { Blend = blend; }

//////////// GETTERS ///////////////
double Particle::GetBirth() { return Birth; }
double Particle::GetAge(double currentTimestep) { return currentTimestep - Birth; }
int Particle::IsInUse() { return InUse; }

int Particle::Getnhistory() { return nhistory; }
