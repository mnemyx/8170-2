/********************************************************
  Pmanager.h

  Header File for particle manager class

  Gina Guerrero - Fall 2013
********************************************************/


#ifndef _PMANAGER_H_
#define _PMANAGER_H_

#include "Particle.h"

#define MAXPART		10000

class Pmanager {
	private:
		int nused;						// count of used particles
		int Stopped;					// simulation is paused.
		int Started;					// simulation is started...
		int Step;						// simulation is step mode

	public:
        Particle Particles[MAXPART];	// matrix of particles...

		Pmanager();

		void SetStopped(int type);
		void SetStarted(int type);
		void SetStep(int type);

		int IsStopped();
		int IsStarted();
		int IsStep();
		int GetNused();

		// determines if it has free particles
		int HasFreeParticles();

		// frees a used particle @ given index
		void FreeParticle(int indx);

        // kill off particles..
        void KillAll();
        int KillParticles(double timestep);

		// assigns particle an initial velocity and center...
		void UseParticle(Vector3d c0, Vector3d v0, double ts, Vector4d color, double m, double coefff, double coeffr, int blend);



		// draws all the used particles
		void DrawSystem();
};

#endif
