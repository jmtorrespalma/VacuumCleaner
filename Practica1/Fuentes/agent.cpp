#include "agent.h"
#include "environment.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void Agent::ImprimirMapa(){
    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j){
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
}

int HacerPositivoMod(const int & entero){
    int resultado = entero;
    while (resultado < 0)
        resultado = resultado + 10;
    return resultado;
}

// -----------------------------------------------------------
Agent::Agent()
{
        bump_ = false;
	    dirty_ = false;
	    last_action = 5;
	    pos_x = 0;
	    pos_y = 0;
	    for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j){
                mapa[i][j] = 0;
            }

}

Agent::ActionType Agent::CalcularSiguiente(){
    //Busca cual de las casillas que le rodea es la mas sucia.

    int vec[4], *vec_posiciones, num_apariciones = 1, mayor, resultado;

    vec[0] = mapa[pos_x][HacerPositivoMod((pos_y - 1) % 10)];
    vec[1] = mapa[pos_x][(pos_y + 1) % 10];
    vec[2] = mapa[HacerPositivoMod((pos_x - 1) % 10)][pos_y];
    vec[3] = mapa[(pos_x + 1) % 10][pos_y];

    mayor = vec[0];
    resultado = 0;

    for (int i = 1; i < 4; ++i){
        if (vec[i] > mayor){
            mayor = vec[i];
            num_apariciones = 1;
            resultado = i;
        }
        else if (vec[i] == mayor)
            ++num_apariciones;
    }

    cout << "\nNumero apariciones " << num_apariciones << endl;

    if (num_apariciones != 1){//El maximo esta repetido. Guardamos en otro vector las posiciones para luego ver cual es la que sale.

        vec_posiciones = new int [num_apariciones];

        for (int i = 0, j = 0; i < 4; ++i)
            if (vec[i] == mayor){
                vec_posiciones[j] = i;
                cout << "\nAñadiendo "<< i << endl;
                ++j;
            }
        int x = rand() % num_apariciones;
        cout << "\nX = " << x << endl;
        for (int i = 0; i < num_apariciones; ++i)
            cout << "\nPosiciones = " << vec_posiciones[i] << endl;
        resultado = vec_posiciones[x];
        delete [] vec_posiciones;
    }

    switch(resultado){
        case 0:
            cout << " Ire Arriba" << endl;
            pos_y = HacerPositivoMod((pos_y - 1) % 10);
            return actUP;
            break;

        case 1:
            cout << "Ire Abajo" << endl;
            pos_y = (pos_y + 1) % 10;
            return actDOWN;
            break;

        case 2:
            cout << " Ire Izq" << endl;
            pos_x = HacerPositivoMod((pos_x - 1) % 10);
            return actLEFT;
            break;

        case 3:
            cout << "Ire Der" << endl;
            pos_x = (pos_x + 1) % 10;
            return actRIGHT;
            break;

    }

    /*int arriba, abajo, izquierda, derecha,;

    arriba = mapa[pos_x][HacerPositivoMod((pos_y - 1) % 10)];
    abajo = mapa[pos_x][(pos_y + 1) % 10];
    izquierda = mapa[HacerPositivoMod((pos_x - 1) % 10)][pos_y];
    derecha = mapa[(pos_x + 1) % 10][pos_y];


    if (arriba > abajo && arriba > izquierda && arriba > derecha){
        cout << " Ire Arriba" << endl;
        pos_y = HacerPositivoMod((pos_y - 1) % 10);
        return actUP;
    }
    if (abajo > arriba && abajo > izquierda && abajo > derecha){
        cout << "Ire Abajo" << endl;
        pos_y = (pos_y + 1) % 10;
        return actDOWN;
    }
    if (izquierda > abajo && izquierda > arriba && izquierda > derecha){
        cout << " Ire Izq" << endl;
        pos_x = HacerPositivoMod((pos_x - 1) % 10);
        return actLEFT;
    }
    if
        cout << "Ire Der" << endl;
        pos_x = (pos_x + 1) % 10;
        return actRIGHT;
    }*/
}

void Agent::ActualizarMapa(){
    //Va actualizando el grado de suciedad (tiempo sin pasar por esa zona).

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j){
            if (i == pos_x && j == pos_y)
                    mapa[i][j] = 0;
            else
                if (mapa[i][j] != -1)
                    mapa[i][j] = mapa[i][j] + 1;
        }
}

void Agent::DetectarMuro(){
    //Este metodo actua en caso de choque, de manera que guarda la posicion de la pared
    //y devuelve al agente a su posicion real.
    cout << "\nChoque\n";

    mapa[pos_x][pos_y] = -1;
    switch (last_action){
        case 0:
            pos_y = (pos_y + 1) % 10;
            break;
        case 1:
            pos_y = HacerPositivoMod((pos_y - 1) % 10);
            break;
        case 2:
            pos_x = (pos_x + 1) % 10;
            break;
        case 3:
            pos_x = HacerPositivoMod((pos_x - 1) % 10);
            break;
    }
    cout << "Hay un muro " << pos_x << " " << pos_y << endl;
}

Agent::ActionType Agent::Think()
{
    int next_action;

    cout << "\nComenzamos" << endl;

    ActualizarMapa();

    if (dirty_){
        last_action = 4;
        return actSUCK;
    }

    if (bump_)
        DetectarMuro();

    cout << pos_x << " " << pos_y << " Ultima accion " << last_action << endl;

    next_action = CalcularSiguiente();

    ImprimirMapa();

    last_action = next_action;

    return static_cast<ActionType> (next_action);

}

// -----------------------------------------------------------







// -----------------------------------------------------------
// -----------------------------------------------------------
// -----------------------------------------------------------

















// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Agent::ActionType action)
{
	switch (action)
	{
	case Agent::actUP: return "UP";
	case Agent::actDOWN: return "DOWN";
	case Agent::actLEFT: return "LEFT";
	case Agent::actRIGHT: return "RIGHT";
	case Agent::actSUCK: return "SUCK";
	case Agent::actIDLE: return "IDLE";
	default: return "???";
	}
}
