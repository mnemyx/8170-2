/********************************************************
  Particle.cpp

  Source File for Particle Class

  Gina Guerrero - Fall 2013
********************************************************/

#include "Particle.h"
#include <cstdlib>



#include "Vector.h"

using namespace std;

///////////////////// PRIVATE FUNCTIONS ///////////////////
void Particle::AddHistory(Vector3d c) {
	if(nhistory == MAXHIST){
		cerr << "Number of entries in particle history exceeds maximum of " << MAXHIST << endl;
		exit(1);
	}

	History[nhistory] = c;
	nhistory++;
}

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

void Particle::CalcAccel(Vector3d g, Vector3d w, double v) {
	Vector3d a;
    //Acceleration = Acceleration + Viscosity * (Wind - Velocity) / Mass;
    Acceleration = g + v * (w - Velocity) / Mass;
}

void Particle::CalcAttractAccel(double length, double radius, Vector3d p0, Vector3d p1, Vector3d g) {
    Vector3d a, unit, b, u;
    double l, d, f;

    unit = (p1 - p0).normalize();

    a = Center - p0;
    l = (unit * a);
    b = a - l * unit;

    u = b.normalize();
    d = b.norm();

    f = l / length;

    if (0 < f && f < 1 && d < radius) {
        Acceleration = Acceleration + (- g * (Mass / (d * d)) * u);
        //cout << "Acceleration Modified: ";
        //Acceleration.print();
        //cout << endl;
    }
}


void Particle::CalcTempCV(double ts) {
    //Velocity + timestep * Acceleration;
    //Center + timestep * Velocity;
    tempv = Velocity + ts * Acceleration;
    tempc = Center + ts * Acceleration;
}

void Particle::CalcTempCV(double ts, double f) {
    //Velocity + f * timestep * Acceleration;
    //Center + f * timestep * Velocity;
    tempv = Velocity + f * ts * Acceleration;
    tempc = Center + f * ts * Velocity;
}


// reflect velocity off of plane
void Particle::Reflect(Vector3d pnormal, Vector3d pvertex) {
    Vector3d vn;
    Vector3d smallr;
    smallr.set(.00001, .00001, .00001);
    double d;

    if (tempv * pnormal == 0) vn.set(0,0,0);
    else vn = (tempv * pnormal) * pnormal;

    //if (Velocity * pnormal == 0) vt = Velocity;
    //else vt = Velocity - (Velocity * pnormal) * pnormal;

    //Center.print();
    //cout << endl << "before ^ & after v" << endl;
    //Center = (fhit * Velocity) + smallr;  // need the center before we flip the velocity.
    Velocity = tempv - ((1 + Coeffr) * (vn));// - ((1 - Coefff) * vt);bary
    d = (tempc - pvertex) * vn + .0001;
    Center = tempc - d * vn;

    //Center.print();
    //cout << endl;

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
void Particle::SetBirth(double timestep) { Birth = timestep; }
void Particle::SetColor(Vector4d c) { Color = c; }
void Particle::SetMass(double m) { Mass = m; }
void Particle::SetInUse(int type) { InUse = type; }
void Particle::SetCoefff(double f) { Coefff = f; }
void Particle::SetCoeffr(double r) { Coeffr = r; }
void Particle::SetTempv(Vector3d v) { tempv = v; }
void Particle::SetTempc(Vector3d c) { tempc = c; }

//////////// GETTERS ///////////////
Vector3d Particle::GetV0() { return V0; }
Vector3d Particle::GetVelocity() { return Velocity; }
Vector3d Particle::GetC0() { return C0; }
Vector3d Particle::GetCenter() { return Center; }
Vector3d Particle::GetAcceleration() { return Acceleration; }
double Particle::GetAge(double currentTimestep) { return currentTimestep - Birth; }
int Particle::IsInUse() { return InUse; }
double Particle::GetMass() { return Mass; }
double Particle::GetCoefff() { return Coefff; }
double Particle::GetCoeffr() { return Coeffr; }
Vector3d Particle::GetTempc() { return tempc; }
Vector3d Particle::GetTempv() { return tempv; }
double Particle::GetBirth() { return Birth; }
Vector4d Particle::GetColor() { return Color; }

//////////// DEBUGGING ///////////////
void Particle::PrintAttr() {
    cout << "In Use? " << InUse << endl;
    cout << "Intial Velocity: "; V0.print();
    cout << endl << "Initial Center: "; C0.print();
    cout << endl << "Current Velocity: "; Velocity.print();
    cout << endl << "Current Center: "; Center.print();
    cout << endl << "Acceleration: "; Acceleration.print();
    cout << endl << "Color: "; Color.print();
    cout << endl << "Mass: " << Mass << endl;
    cout << "Coefff: " << Coefff << endl;
    cout << "Coeffr: " << Coeffr << endl;
    cout << "Birth: " << Birth << endl;
}
