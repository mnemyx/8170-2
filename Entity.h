/***************************************************
  Entity.h

  Header file for Entity Class

  CPSC8170 - Proj 1   GBG   8/2013
****************************************************/

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Attributes.h"
#include "Model.h"

#define MAXSTEPS	10000
#define SPDEPTH		3


class Entity : public Model {		// entity is a model but has various variables to it...
  private:
      int Rest;
      int Stop;
      int Step;
      int Start;

  public:
    Attributes A;

    // Constructor
    Entity();

	// Setters
	void SetRest(int type);
	void SetStop(int type);
	void SetStart(int type);
	void SetStep(int type);

	// Getters
	int IsRest();
	int IsStop();
	int IsStart();
	int IsStep();

	// Functions
	// FOR SECOND PROJECT:
	int CheckCollision(Vector3d pcen, Vector3d pvel, Vector3d pnewcen);
};

#endif
