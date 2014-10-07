#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}


// Funcion de valoracion para testear MiniMax y Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    if (jugador==1)
      return estado.Marcador(1);
    else
      return estado.Marcador(2);
}

// ------------------- Los tres metodos anteriores no se pueden modificar



// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j, int giros){
    j=0;
    for (int i=0; i<5; i++){
        if (aplicables[i]){
           if (i==0) { // Doy más probabilidad a usar actFORWARD
              for (int k=0; k<4; k++){
                  opciones[j]=0;
                  j++;
              }
           }
           if ( (i==1 or i==2) and  ( (!aplicables[4] and j==0) or giros==0  ) ){
                  opciones[j]=i;
                  j++;
           }
           if (i==4) { // Doy más probabilidad a usar actSHOOT
              for (int k=0; k<2; k++){
                  opciones[j]=4;
                  j++;
              }
           }
        }
    }
}



// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 10;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 16; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acción que se va a devolver
    bool aplicables[5]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si actFORWARD es aplicable
                        // aplicables[1]==true si actTURN_LEFT es aplicable
                        // aplicables[2]==true si actTURN_RIGHT es aplicable
                        // aplicables[3]==true si actIDLE es aplicable (aplicables[3] siempre es FALSE)
                        // aplicables[4]==true si actSHOOT es aplicable

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    cout << " Acciones aplicables para Jugador ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<5; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;



    //--------------------- COMENTAR Desde aqui
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones, actual_.Giros(jugador_));

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------
    // Opcion: Metodo Minimax
    // NOTA: La parametrizacion es solo orientativa
    // valor = MiniMax(actual_, jugador_, PROFUNDIDAD_MINIMAX, accion);



    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, PROFUNDIDAD_ALFABETA, accion, alpha, beta);


    return accion;
}

