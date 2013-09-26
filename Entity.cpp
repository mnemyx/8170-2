/***************************************************
  Entity.cpp

  Source file for Entity Class

  CPSC8170 - Proj 1   GBG   8/2013
****************************************************/

#include "Entity.h"

#include <cstdlib>
#include <cstdio>

using namespace std;

//
// Constructor
//
Entity::Entity(){
}


//
// Setters
//
void Entity::Rest(int type) { EntState.SetResting(type); }
void Entity::Start(int start) { EntState.SetStart(start); }
void Entity::Stopped(int stop) { EntState.SetStopped(stop); }
void Entity::Step(int step) { EntState.SetStep(step); }
void Entity::Trace(int trace) { EntState.SetTrace(trace); }
void Entity::Center(Vector3d newc) { EntState.SetCenter(newc); }
void Entity::Velocity(Vector3d newv) { EntState.SetVelocity(newv); }
void Entity::InitState(Vector3d vel, Vector3d cen, double mass, double radius, double coeffr, double coefff, float eps, double viscosity, Vector3d wind, Vector3d gravity) {
	BuildSphere(radius, 3, cen.x, cen.y, cen.z);
	EntState.SetInitialVelocity(vel);
	EntState.SetCenter(cen);
	EntState.SetInitialCenter(cen);
	EntState.SetMass(mass);
	EntState.SetRadius(radius);
	EntState.SetCoeffR(coeffr);
	EntState.SetCoeffF(coefff);
	EntState.SetEPS(eps);
	EntState.SetViscosity(viscosity);
	EntState.SetWind(wind);
	EntState.SetGravity(gravity);
}
void Entity::InitState(Vector3d plane, Vector3d cen, float eps) {
	BuildPlane(plane.x, plane.y, plane.z, cen.x, cen.y, cen.z);
	EntState.SetEPS(eps);
	EntState.SetCenter(cen);
	EntState.SetInitialCenter(cen);
}


//
// Getters
//
Vector3d Entity::InitialCenter() { return EntState.GetInitialCenter(); }
Vector3d Entity::InitialVelocity() { return EntState.GetInitialVelocity(); }
Vector3d Entity::Center() { return EntState.GetCenter(); }
Vector3d Entity::Velocity() { return EntState.GetVelocity(); }
Vector3d Entity::Acceleration() { return EntState.GetAcceleration(); }
double Entity::Radius() { return EntState.GetRadius(); }
Vector3d Entity::PlaneNormal() { return EntState.GetCollidedN(); }
Vector3d Entity::PlaneVertex(int indx) { return vertices[indx]; }
int Entity::Rest() { return EntState.IsResting(); }
int Entity::Start() { return EntState.IsStarted(); }
int Entity::Stopped() { return EntState.IsStopped(); }
int Entity::Step() { return EntState.IsStep(); }
int Entity::Trace() { return EntState.IsTrace(); }
int Entity::GetCollision(int indx) { return EntState.Collided(indx); }	// called by planes
Vector3d Entity::OldCenter(int indx) { return EntState.GetOldCenter(indx); }	// called by planes
float Entity::FudgeFactor() { return EntState.GetEPS(); }

//
// Functions
//
// calculate f to determine if the ball collided with the plane
// called by plane...
float Entity::PlaneBallColl(Vector3d bCenter, Vector3d bVelocity, Vector3d bNewCenter, float bRadius) {
	float f,t;
	float p;
	int i;
	Vector3d bCentMod;
	Vector3d bNewCentMod;
	Vector3d avgN;

	for (i = 0; i < ntriangles; i++) {
		avgN = avgN + normals[i];
	}

	avgN = avgN / 2;
	avgN.normalize();

	//planeNorma - Center - plaN * pV
	p = (bVelocity.normalize() * vertices[1]) - (bVelocity.normalize() * avgN);

	if(p < 0) { //we're behind the plane we're testing
		bCentMod.set(((bCenter * avgN) + bRadius) * avgN);
		bNewCentMod.set(((bNewCenter * avgN) + bRadius) * avgN);
	} else { // we're in front
		bCentMod.set(((bCenter * avgN) - bRadius) * avgN);
		bNewCentMod.set(((bNewCenter * avgN) - bRadius) * avgN);
	}

	f = ((bCenter - vertices[1]) * avgN / ((bCenter - bNewCentMod) * avgN));

	return f;
}

// fast triangle intersection test
// should be called by collidable objects
// uh...returns the index of the triangle that's closeset
// pass in as &fhit
int Entity::CheckCollision(Vector3d pcen, Vector3d pvel, Vector3d pnewcen) {
  int i, rtni;
  float f, fhit;
  double u, v, a;
  Vector3d p0, p1, p2;

  rtni = -1;
  fhit = 100;

  for (i = 0; i < ntriangles; i++) {
    p0.set(vertices[triangles[i][0]]);
    p1.set(vertices[triangles[i][1]]);
    p2.set(vertices[triangles[i][2]]);

    a = ((p2 - p1) % (p1 - p0)).norm();

    u = ((p2 - p1) % (pcen - p1)) * normals[i] / a;
    v = ((p0 - p2) % (pcen - p2)) * normals[i] / a;

    if(u >= 0.001 && v >= 0.001 && u + v <= 1 && u + v > -0.001) { // we hit...so now to calculate...
      f = ((pcen - p1) * normals[i] / ((pcen - pnewcen) * normals[i]));

      if(f >= 0 && f < 1 && f < fhit) {
        rtni = i;
      }
    }
  }

  return rtni;
}


// called by plane...
void Entity::RestingOnPlane(Vector3d bCenter, Vector3d bVelocity, float bRadius, double timeStep) {
	// t is the distance from the center of the ball to the intersection on the plane
	// t < 0 then it's behind the starting point
	// t == 0 then it's parallel and never hits
	// t= (Xn dot (PointOnPLANE - Raystart)) / (Xn dot Raydirection)-- NeHe Collision Detection
	//  Resting = Abs(timestep * Velocity.y) < EPS.y && Abs(Center.y - (Radius + miny)) < EPS.y;
	float t;
	int i;
	double vN;
	Vector3d avgN;

	for (i = 0; i < ntriangles; i++) {
		avgN = avgN + normals[i];
	}

	avgN = avgN / 2;
	avgN.normalize();

	t = avgN * (bCenter - vertices[1]);
	// account for radius
	t = t - bRadius;

	vN = bVelocity * avgN;
	EntState.SetCollidedN(avgN);
	// Don't I need to figure out the velocity in the direction of the normal and see if it's
	// below the threshold?  ...Added above.
	// kind of fudging it...
	EntState.SetResting(Abs(vN) < EntState.GetEPS() && Abs(t) < EntState.GetEPS());
	EntState.SetT(t);
}

// need to figure out magnitude...of acceleration in direction of the normal
// called by plane...
int Entity::AccelOnPlane(Vector3d bAccel) {
	double acceln;

	acceln = bAccel * EntState.GetCollidedN();

	if (acceln < EntState.GetEPS()) { return true; }
	else return false;
}

// need to figure out magnitude...of velocity in the direction of normal
// called by plane...
int Entity::VelOnPlane(Vector3d bVelocity) {
	if ((bVelocity * EntState.GetCollidedN()) < EntState.GetEPS()) return true;
	else return false;
}

// need to figure out the distance from collision < radius
// called by plane...
int Entity::CenOnPlane(float bRadius) {
	if((EntState.GetT() - bRadius) < EntState.GetEPS()) return true;
	else return false;
}

// For tracing, if we keep that feature
void Entity::AddOCenter(int nsteps) {
	EntState.AddOldCenter(nsteps);
}

// For tracing, if we keep that feature
void Entity::AddOCollision(int collision, int nsteps){
	EntState.AddCollision(collision, nsteps);
}

// for updating the model's triangles -- called by particle
void Entity::UpdateModel() {
	BuildSphere(EntState.GetRadius(), 3, EntState.GetCenter().x, EntState.GetCenter().y, EntState.GetCenter().z);
}

// acceleration -- called by particle.
void Entity::Accel() {
	EntState.CalcAcceleration();
}

// called by particle...hm.
void Entity::AdjustAVC(Vector3d pnormal, Vector3d pvertex) {
	EntState.AdjustAccVelPos(pnormal, pvertex);
}

// called by particle
Vector3d Entity::CalcVelocity(double timestep, double f) { return EntState.CalcNewVelocity(timestep, f); }
Vector3d Entity::CalcVelocity(double timestep) { return EntState.CalcNewVelocity(timestep); }
Vector3d Entity::CalcCenter(double timestep, double f) { return EntState.CalcNewPosition(timestep, f); }
Vector3d Entity::CalcCenter(double timestep) { return EntState.CalcNewPosition(timestep); }
void Entity::ScaleVel(Vector3d pnormal) { EntState.ScaleVelocity(pnormal); }


