#include "agent.h"
#include "environment.h"
#include <cstdlib>

Environment::ActionType Agent::Think()
{
    /*int max=0,posm=0;
//Si se activa el sensor de choque retrocedo en la matriz y pongo esa casilla a -1
    if(bump_){
        posiciones[i][j]=-1;
        if(last_action_==0)
            i++;
        if(last_action_==1)
            i--;
        if(last_action_==2)
            j++;
        if(last_action_==3)
            j--;
    }

    if(dirty_){
        return Environment::actSUCK;
    }
//Pongo el contador de la poicion donde esta el robot a 0
    posiciones[i][j]=0;
//Incremento todas las casillas menos las que tengan un -1
    for(int f=0;f<30;f++)
            for(int c=0;c<30;c++)
                if(posiciones[f][c]!=-1)
                    posiciones[f][c]++;
//Almaceno los 4 posibles movimientos en un vector
    vec[0]=posiciones[i-1][j];
    vec[1]=posiciones[i+1][j];
    vec[2]=posiciones[i][j-1];
    vec[3]=posiciones[i][j+1];
//Busco en el vector la casilla con el mayor numero de contador
    for(int h=0;h<4;h++){
            if(vec[h]>=max){
                posm=h;
                max=vec[h];
            }
    }
//Muevo el robot hacia la casilla con en el mayor numero y tambien me desplazo en la matriz
    if(posm==0){
        i--;
        last_action_=0;
        return static_cast<Environment::ActionType> (last_action_);
    }
    if(posm==1){
        i++;
        last_action_=1;
        return static_cast<Environment::ActionType> (last_action_);
    }
    if(posm==2){
        j--;
        last_action_=2;
        return static_cast<Environment::ActionType> (last_action_);
    }
    if(posm==3){
        j++;
        last_action_=3;
        return static_cast<Environment::ActionType> (last_action_);
    }*/
}

// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump(jugador_);
	dirty_ = env.isCurrentPosDirty(jugador_);
}
// -----------------------------------------------------------
