/********************************************************
  Pmanager.h

  Header File for particle manager class

  Gina Guerrero - Fall 2013
********************************************************/


#ifndef _PMANAGER_H_
#define _PMANAGER_H_

#define MAXPART		10000

#include "Particle.h"

class Pmanager {
	private:
		int nused;						// count of used particles
		int Stopped;					// simulation is paused.
		int Started;					// simulation is started...
		int Step;						// simulation is step mode

	public:
		Pmanager();
		Particle Particles[MAXPART];	// matrix of particles...

		void SetStopped(int type);
		void SetStarted(int type);
		void SetStep(int type);

		int IsStopped();
		int IsStarted();
		int IsStep();
		int GetNused();

		// determines if it has free particles
		int HasFreeParticles();

        // kill off particles..
        void KillAll();
        int KillParticles(double timestep);

		// assigns particle an initial velocity and center...
		void UseParticle(Vector3d c0, Vector3d v0, double ts, Vector4d color, double m, double coefff, double coeffr, int blend);

		// frees a used particle @ given index
		void FreeParticle(int indx);

		// draws all the used particles
		void DrawSystem();
};

#endif
