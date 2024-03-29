#ifndef GUI_H
#define GUI_H

#include<fstream>
#include"include/GL/glui.h"
namespace GUI{
	void myGlutReshape(int,int);
	void myGlutDisplay();
	void control_cb(int);
	int startDraw(int,char *[]);
	void showScore();

	void doOneStep();
	void newGame();

	void ReactivoSeleccionado();
	void AnchuraSeleccionado();
	void CosteSeleccionado();
	void ProfundidadSeleccionado();
	void EscaladaSeleccionado();

};
#endif
