#include "agent.h"
#include "environment.h"
#include "state.h"
#include <cstdlib>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>


using namespace std;

void Agent::ImprimirMapa(){
    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j){
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
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

int HacerPositivoMod(const int & entero){
    int resultado = entero;
    while (resultado < 0)
        resultado = resultado + 80;
    return resultado;
}

// -----------------------------------------------------------
Environment::ActionType Agent::AgenteReactivo()
{
 	Environment::ActionType next_action;

    cout << "\nComenzamos" << endl;


    ActualizarMapa();

    if (bump_)
        DetectarMuro();

    if (dirty_)
        return Environment::actSUCK;

    next_action = CalcularSiguiente();

    ImprimirMapa();

	return next_action;

}


Environment::ActionType Agent::CalcularSiguiente(){
    //Busca cual de las casillas que le rodea es la mas sucia.

    int vec[4], *vec_posiciones, num_apariciones = 1, mayor, resultado;

    vec[0] = mapa[pos_x][HacerPositivoMod((pos_y - 1) % 80)];
    vec[1] = mapa[(pos_x + 1) % 80][pos_y];
    vec[2] = mapa[pos_x][(pos_y + 1) % 80];
    vec[3] = mapa[(pos_x - 1) % 80][pos_y];

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
            switch(orientacion){
                case 0:
                    pos_y = HacerPositivoMod((pos_y - 1) % 80);
                    return Environment::actFORWARD;
                    break;
                case 1:
                    orientacion = 0;
                    return Environment::actTURN_L;
                    break;
                case 3:
                    orientacion = 0;
                    return Environment::actTURN_R;
                    break;
            }
            pos_y = HacerPositivoMod((pos_y - 1) % 80);
            return Environment::actFORWARD;
            break;

        case 1:
            switch(orientacion){
                case 2:
                    pos_y = (pos_y + 1) % 80;
                    return Environment::actFORWARD;
                    break;
                case 1:
                    orientacion = 2;
                    return Environment::actTURN_R;
                    break;
                case 3:
                    orientacion = 2;
                    return Environment::actTURN_L;
                    break;
            }
            pos_y = (pos_y + 1) % 80;
            return Environment::actFORWARD;
            break;


        case 2:
            switch(orientacion){
                case 0:
                    orientacion = 3;
                    return Environment::actTURN_L;
                    break;
                case 2:
                    orientacion = 3;
                    return Environment::actTURN_R;
                    break;
                case 3:
                    pos_x = HacerPositivoMod((pos_x - 1) % 80);
                    return Environment::actFORWARD;
                    break;
            }
            pos_x = HacerPositivoMod((pos_x - 1) % 80);
            return Environment::actFORWARD;
            break;


        case 3:
            switch(orientacion){
                case 0:
                    orientacion = 1;
                    return Environment::actTURN_R;
                    break;
                case 1:
                    pos_x = (pos_x + 1) % 80;
                    return Environment::actFORWARD;
                    break;
                case 2:
                    orientacion = 1;
                    return Environment::actTURN_L;
                    break;
            }
            pos_x = (pos_x + 1) % 80;
            return Environment::actFORWARD;
            break;
    }

}

void Agent::DetectarMuro(){
    //Este metodo actua en caso de choque, de manera que guarda la posicion de la pared
    //y devuelve al agente a su posicion real.
    cout << "\nChoque\n";

    mapa[pos_x][pos_y] = -1;
    switch (orientacion){
        case 0:
            pos_y = (pos_y + 1) % 80;
            break;
        case 2:
            pos_y = HacerPositivoMod((pos_y - 1) % 80);
            break;
        case 3:
            pos_x = (pos_x + 1) % 80;
            break;
        case 1:
            pos_x = HacerPositivoMod((pos_x - 1) % 80);
            break;
    }
    cout << "Hay un muro " << pos_x << " " << pos_y << endl;
}



// -----------------------------------------------------------
// Inserta un estado (st) en una lista de estados (lista) y devuelve un iterador a su posición en la lista (it)
// La función devuelve "true" e inserta el estado (st) al final de la lista si es estado no estaba ya en la lista.
// La función devuelve "false" si el estado (st) ya estaba en la lista, y NO LO INSERTA EN LA LISTA
// -----------------------------------------------------------
bool InsertarLista(list <state> &lista, const state &st, list<state>::iterator &it){
  char ch;
  it= lista.begin();
  bool salida=false;
  while (it!=lista.end() and !(*it==st) )
    it++;
  if (it==lista.end()){
    lista.push_back(st);
    it = lista.end();
    it--;
    salida=true;
  }
  return salida;
}






// -----------------------------------------------------------
// Busqueda en Profundidad
// -----------------------------------------------------------

Plan Agent::Busqueda_Profundidad(state start){
 Plan plan;
  typedef list<state>::iterator elemento_pila;

  int last_level=0; // Indica el nivel del grafo por donde va la búsqueda
  int estados_evaluados = 0; // Indica el número de nodos evaluados
  state aux = start; // start es el estado inicial
  state sigActions[4], mejor_solucion; // para almacenar las siguientes acciones y la mejor solución
  int n_act;

  list<state> lista;               // Lista que almacenara todos los estados
  list<state>::iterator p, padre;  // Declara dos iteradores a la lista
  stack <elemento_pila> pila; //Declaración de la pila

  elemento_pila siguiente; // Declara una variable del tipo almacenado en la pila

  InsertarLista(lista,aux,padre); // Inserta el estado inicial en la lista y (padre) es un iterador a su posición.

  while (!aux.Is_Solution()){
      // Indica si ha incrementado el nivel del grafo por donde está buscando
      if (aux.Number_of_actions()!=last_level){
        cout << "Level " << aux.Number_of_actions() << " Suciedad Pendiente: " << aux.Get_Pending_Dirty() <<endl;
        last_level = aux.Number_of_actions();
      }

      n_act=aux.Generate_New_States(sigActions); // Genera los nuevos estados a partir del estado (aux)

      // Para cada estado generado, pone un enlace al estado que lo genero,
      // lo inserta en la lista, y si no estaba ya en dicha lista, lo incluye en la pila.
      for (int i=n_act-1; i>=0; i--){
          sigActions[i].Put_Padre(padre);
          if (InsertarLista(lista, sigActions[i], p) ){
            pila.push( p );
         }
      }


      // Saca el siguiente estado de la pila.
      padre = pila.top();
      aux = *padre;
      pila.pop();
      estados_evaluados++; // Incremento del número de estados evaluados
  }

  // Llegados aquí ha encontrado un estado solución, e
  // incluye la solución en una variable de tipo plan.
  plan.AnadirPlan(aux.Copy_Road(), lista.size(), estados_evaluados );

  return plan; // Devuelve el plan
}





// -----------------------------------------------------------
// Busqueda en Anchura
// -----------------------------------------------------------
Plan Agent::Busqueda_Anchura(state start){
  Plan plan;
  typedef list<state>::iterator elemento_cola;

  state actual = start, sigActions[4];
  int estados_expandidos=0, estados_evaluados=0, n_act, last_level = 0;
  queue<elemento_cola> cola_estados;

  list<state> lista;               // Lista que almacenara todos los estados
  list<state>::iterator p, padre;  // Declara dos iteradores a la lista

  InsertarLista(lista,actual,padre); // Inserta el estado inicial en la lista y (padre) es un iterador a su posición.


  while(!actual.Is_Solution()){
    if (actual.Number_of_actions()!=last_level){
        cout << "Level " << actual.Number_of_actions() << " Suciedad Pendiente: " << actual.Get_Pending_Dirty() <<endl;
        last_level = actual.Number_of_actions();
    }

    n_act=actual.Generate_New_States(sigActions);

    for (int i = 0; i < n_act; ++i){
        sigActions[i].Put_Padre(padre);
          if (InsertarLista(lista, sigActions[i], p) ){
            cola_estados.push(p);
            ++estados_expandidos;
          }
    }
    padre = cola_estados.front();
    actual = *padre;
    cola_estados.pop();
    ++estados_evaluados;

  }

  // IMPLEMENTA AQUÍ EL MÉTODO DE BUSQUEDA EN ANCHURA

  plan.AnadirPlan(actual.Copy_Road(), estados_expandidos, estados_evaluados );
    return plan; // Devuelve el plan
}





// -----------------------------------------------------------
// Busqueda en Costo Uniforme
// -----------------------------------------------------------

Plan Agent::Busqueda_CosteUniforme(state start){
  Plan plan;
  typedef list<state>::iterator elemento_vector;


  state actual = start, sigActions[4];
  int estados_expandidos=0, estados_evaluados=0, n_act, last_level = 0;
  vector<elemento_vector> nodos_pendientes; //Aqui se guardan los nodos sin expandir.

  list<state> lista;               // Lista que almacenara todos los estados
  list<state>::iterator p;  // Declara dos iteradores a la lista

  InsertarLista(lista,actual,p); // Inserta el estado inicial en la lista y (padre) es un iterador a su posición.


  while(!actual.Is_Solution()){
      //actual.PrintState();
      //system("pause");
      //cout << actual.Get_Consumed_Energy() << endl;
    if (actual.Number_of_actions()!=last_level){
        cout << "Level " << actual.Number_of_actions() << " Suciedad Pendiente: " << actual.Get_Pending_Dirty() <<endl;
        last_level = actual.Number_of_actions();
    }

    n_act=actual.Generate_New_States(sigActions);

    for (int i = 0; i < n_act; ++i){
        //sigActions[i].Put_Padre(padre);
          if (InsertarLista(lista, sigActions[i], p) ){
            nodos_pendientes.push_back(p); //Se añaden los iteradores de los nodos nuevos.
            ++estados_expandidos;
          }
    }

    //Ahora buscamos en la lista de nodos pendientes aquel nodo que tenga una g menor
    //debido a que es el de menor coste energetico. Simula una cola con prioridad.

    int menor = (*(nodos_pendientes.at(0))).Get_g();
    int posicion = 0;

    for (int i = 1; i < nodos_pendientes.size(); ++i){
        if((*(nodos_pendientes.at(i))).Get_g() < menor){
            menor = (*(nodos_pendientes.at(i))).Get_g();
            posicion = i;
        }
    }



    //padre = nodos_pendientes.at(posicion);
    //actual = *padre;
    actual = *(nodos_pendientes.at(posicion));
    nodos_pendientes.erase(nodos_pendientes.begin()+posicion); //Lo borramos del vector.
    ++estados_evaluados;

  }

  plan.AnadirPlan(actual.Copy_Road(), estados_expandidos, estados_evaluados );
  return plan; // Devuelve el plan
}







// -----------------------------------------------------------
// --------------------- Busqueda Heuristica -----------------
// -----------------------------------------------------------


double Heuristica(const state &estado){
  return -(estado.SeeRoom(estado.Get_X(), estado.Get_Y()));
}


list<int> EncontrarSigSucio(state& estado, int& nodos_expandidos, int& nodos_evaluados){ //Esta funcion devuelve el recorrido generado.
    int last_level = 0, n_act;
    list<state> lista_estados;
    typedef list<state>::iterator nodos_vector;
    list<state>::iterator p;
    vector<nodos_vector> nodos_pendientes;
    state sigActions[4];



    if(estado.Is_Solution())
        return estado.Copy_Road();

    InsertarLista(lista_estados, estado, p);

    do{
        if (estado.Number_of_actions()!=last_level){
            cout << "Level " << estado.Number_of_actions() << " Suciedad Pendiente: " << estado.Get_Pending_Dirty() <<endl;
            last_level = estado.Number_of_actions();
        }

        n_act=estado.Generate_New_States(sigActions);

        for (int i = 0; i < n_act; ++i){
            sigActions[i].Put_h(Heuristica(sigActions[i]));
            if (InsertarLista(lista_estados, sigActions[i], p))
                nodos_pendientes.push_back(p);
                ++nodos_expandidos;
        }

        //Ahora buscamos en la lista de nodos pendientes aquel nodo que tenga una f menor
        //debido a que es el de menor coste energetico.

        int menor = (*(nodos_pendientes.at(0))).Evaluation();
        int posicion = 0;

        for (int i = 1; i < nodos_pendientes.size(); ++i){
            if((*(nodos_pendientes.at(i))).Evaluation() < menor){
                menor = (*(nodos_pendientes.at(i))).Evaluation();
                posicion = i;
            }
        }

        estado = *(nodos_pendientes.at(posicion));
        nodos_pendientes.erase(nodos_pendientes.begin()+posicion);
        ++nodos_evaluados;

    }while(!estado.SeeRoom(estado.Get_X(), estado.Get_Y()) && !estado.Is_Solution()); //Mientras la casilla no este sucia.
    lista_estados.clear();
    nodos_pendientes.clear();

    return EncontrarSigSucio(estado, nodos_expandidos, nodos_evaluados);

}

// -----------------------------------------------------------


Plan Agent::Escalada(state start){
    Plan plan;
    list<int> recorrido;
    int estados_expandidos = 0, estados_evaluados = 0;

    recorrido = EncontrarSigSucio(start, estados_expandidos, estados_evaluados);

    plan.AnadirPlan(recorrido, estados_expandidos, estados_evaluados );
    return plan; // Devuelve el plan

}





// -----------------------------------------------------------
Plan Agent::Think(const Environment &env, int option){
  state start(env);
  Plan plan;


  switch (option){
      case 0: //Agente Reactivo

              break;
      case 1: //Busqueda Profundidad
              plan = Busqueda_Profundidad(start);
              cout << "\n Longitud del Plan: " << plan.Get_Longitud_Plan() << endl;
              plan.Pinta_Plan();
              break;
      case 2: //Busqueda Anchura
              plan = Busqueda_Anchura(start);
              cout << "\n Longitud del Plan: " << plan.Get_Longitud_Plan() << endl;
              plan.Pinta_Plan();
              break;
      case 3: //Busqueda Coste Uniforme
              plan = Busqueda_CosteUniforme(start);
              cout << "\n Longitud del Plan: " << plan.Get_Longitud_Plan() << endl;
              plan.Pinta_Plan();
              break;
      case 4: //Busqueda Profundidad
              plan = Escalada(start);
              cout << "\n Longitud del Plan: " << plan.Get_Longitud_Plan() << endl;
              plan.Pinta_Plan();
              break;

  }

  return plan;
}






// -----------------------------------------------------------
void Agent::Perceive(const Environment &env)
{
	bump_ = env.isJustBump();
	dirty_ = env.isCurrentPosDirty();
}
// -----------------------------------------------------------
string ActionStr(Environment::ActionType action)
{
	switch (action)
	{
	case Environment::actFORWARD: return "FORWARD";
	case Environment::actTURN_L: return "TURN_LEF";
	case Environment::actTURN_R: return "TURN_RIGHT";
	case Environment::actSUCK: return "SUCK";
	case Environment::actIDLE: return "IDLE";
	default: return "???";
	}
}
