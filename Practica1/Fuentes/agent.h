
#ifndef AGENT__
#define AGENT__

#include <string>
using std::string;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent();

	enum ActionType { actUP, actDOWN, actLEFT, actRIGHT, actSUCK, actIDLE };

	void Perceive(const Environment &env);

	ActionType Think();

private:
	bool bump_,
		 dirty_;
    int last_action, pos_x, pos_y;
    int mapa[10][10];
    ActionType CalcularSiguiente();
    void ActualizarMapa();
    void ImprimirMapa();
    void DetectarMuro();
};

string ActionStr(Agent::ActionType);

#endif
