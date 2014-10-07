#ifndef AGENT__
#define AGENT__

#include <string>
#include "environment.h"
#include "state.h"
#include "plan.h"

using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------

class Agent
{
public:

    Agent(){
        bump_=false;
        dirty_=false;
    }

    ~Agent(){
    }


	void Perceive(const Environment &env);
	Environment::ActionType AgenteReactivo();
	Plan Busqueda_Profundidad(state start);
    Plan Busqueda_Anchura(state start);
    Plan Busqueda_CosteUniforme(state start);
    Plan Escalada(state start);
    Plan Think(const Environment &env, int option);


private:
	bool bump_,
		 dirty_;

    int last_action, pos_x, pos_y;
    int mapa[80][80];
    int orientacion;
    Environment::ActionType CalcularSiguiente();
    void ActualizarMapa();
    void ImprimirMapa();
    void DetectarMuro();
};

string ActionStr(Environment::ActionType);

#endif
