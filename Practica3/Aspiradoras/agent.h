
#ifndef AGENT__
#define AGENT__

#include <string>
#include "environment.h"

using namespace std;
// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Agent
{
public:
	Agent(int jug):bump_(false), dirty_(false), i(10), j(10) {

    jugador_ = jug;
    //Inicializo la matriz
        for(int i=0;i<30;i++)
            for(int j=0;j<30;j++)
                posiciones[i][j]=15;
    }

	//enum ActionType { actUP, actDOWN, actLEFT, actRIGHT, actSUCK, actIDLE };

	void Perceive(const Environment &env);
	Environment::ActionType Think();
private:
	bool bump_,
		 dirty_;
    int last_action_,i,j,vec[4];
    int posiciones[30][30];
    int jugador_;
};

//string ActionStr(Environment::ActionType);

#endif
