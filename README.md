PROJECT
==================================================================

	Gina Guerrero
	
	CpSc8170 - Fall 2013
	
	Project #2 - Particles Everywhere
	
	C++/OpenGL



DESCRIPTION
==================================================================

	Particle system simulation

	Guass/Matrix/Vector/Utility by Dr. House
	Model Class modified to create an isosphere & plane

	Usage: psystem
	
	
KEY COMMANDS
==================================================================
	m or M		IMPORTANT: transforming camera view to simulation control (default: camera)
	p or P		switches from ortho to perspective views (default: perspective)
	q or ESC	quit
	
	
MOUSE COMMANDS
==================================================================
	SIMULATION:
	RMB			opens menu
	LMB 		triggers selected option
	
	CAMERA: 		  left button		 |	   middle button  	|		right button
	left drag	(-) rotation: model's y	 |  (+)-r: camera's y	|  (+) translation: camera's z
	right drag	(+) rotation: model's y	 |  (-)-r: camera's y	|  (-) translation: camera's z
	down drag	(+) rotation: model's x	 |  (+)-r: camera's x	|  (+) translation: camera's z
	up drag		(-) rotation: model's x	 |  (-)-r: camera's x	|  (-) translation: camera's z
	
	
MENU COMMANDS
==================================================================
	Continuous/Step		changes simulation between continuous or step
	Reset				resets the ball
	Clean				cleans the simulation history & resets ball
	Quit				quit


FILES
==================================================================
	psystem.cpp (main program)
	Model.cpp, Model.h
	
	
MISC FILES
==================================================================
	README.md
	Makefile
	Matrix.cpp, Matrix.h
	Utility.cpp, Utility.h
	Vector.cpp, Vector.h
	
	
SAMPLE OUTPUT FILES
==================================================================
	N/A
	

TOTAL FILE COUNT
==================================================================
	
