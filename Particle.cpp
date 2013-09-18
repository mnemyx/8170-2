/********************************************************
  Particle.cpp

  Source File for Particle Class
  
  Gina Guerrero - Fall 2013 
********************************************************/

#include "Particle.h"
#include <cstdlib>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif#include "Vector.h"

using namespace std;

///////////////////// PRIVATE FUNCTIONS ///////////////////
void Particle::Reset() {
	InUse = false;
	nhistory = 0;
}

void Particle::AddHistory(Vector3d c) {	
	if(nhistory == MAXHISTORY){
		cerr << "Number of entries in particle history exceeds maximum of " << MAXHIST << endl;
		exit(1);
	}
  
	History[nhistory] = c;
	nhistory++;
}

//////////////////// PUBLIC FUNCTIONS /////////////////////

Particle::Particle(){
	Reset();
}

void Particle::Draw() {
    glColor4f(Color[0], Color[1], Color[2], Color[3]); 	
	
	glBegin(GL_POINTS);
		glVertex3f(Center.x, Center.y, Center.z);
	glEnd( );
}

//////////// SETTERS //////////////
void Particle::SetV0(Vector3d v) { V0 = v; }
void Particle::SetVelocity(Vector3d v) { Velocity = v; }
void Particle::SetC0(Vector3d c) { C0 = c; }
void Particle::SetCenter(Vector3d c) {
	Center = c;
	AddHistory(c);
}
void Particle::SetAcceleration(Vector3d a) { Acceleration = a; }
void Particle::SetBirth(int timestep) { Birth = timestep; }
void Particle::SetColor(double* c) { Color = c; }
void Particle::SetMass(double m) { Mass = m; }
void Particle::SetInUse(int switch) { InUse = switch; }

//////////// GETTERS ///////////////
Vector3d Particle::GetV0() { return V0; }
Vector3d Particle::GetVelocity() { return Velocity; }
Vector3d Particle::GetC0() { return C0; }
Vector3d Particle::GetCenter() { return Center; }
Vector3d Particle::GetAcceleration() { return Acceleration; }
int Particle::GetAge(int currentTimestep) { return Timestep - Birth; }
int Particle::IsInUse() { return InUse; }