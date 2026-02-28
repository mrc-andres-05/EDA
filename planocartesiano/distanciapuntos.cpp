#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class PlanoCartesiano {
private:
    int tamano;
    vector<pair<int,int>> puntos;

public:

    void setTamano() {
        cout << "Ingrese tamano del plano: ";
        cin >> tamano;
    }

    void agregarPunto() {
        int x,y;
        cout << "Ingrese coordenadas (x y): ";
        cin >> x >> y;
        puntos.push_back({x,y});
    }

    void borrarPunto() {
        int x,y;
        cout << "Ingrese punto a borrar (x y): ";
        cin >> x >> y;

        for(int i=0;i<puntos.size();i++){
            if(puntos[i].first==x && puntos[i].second==y){
                puntos.erase(puntos.begin()+i);
                cout<<"Punto eliminado\n";
                return;
            }
        }
        cout<<"No se encontro el punto\n";
    }

    bool esPunto(int x,int y){
        for(auto p:puntos)
            if(p.first==x && p.second==y)
                return true;
        return false;
    }

    void dibujar(){
        for(int i=tamano;i>=-tamano;i--){
            for(int j=-tamano;j<=tamano;j++){

                if(esPunto(j,i))
                    cout<<"P ";
                else if(i==0 && j==0)
                    cout<<"0 ";
                else if(i==0)
                    cout<<"- ";
                else if(j==0)
                    cout<<"| ";
                else
                    cout<<". ";
            }
            cout<<endl;
        }
    }

    void puntoMasCercano() {

        if(puntos.size() < 2){
            cout << "Se necesitan al menos 2 puntos.\n";
            return;
        }

        int x,y;
        cout << "Ingrese uno de los puntos existentes (x y): ";
        cin >> x >> y;

        // Verificar que el punto exista
        bool existe = false;
        for(auto p : puntos){
            if(p.first == x && p.second == y){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout << "Ese punto no existe en la lista.\n";
            return;
        }

        double menorDist = -1;
        int mejorX = 0, mejorY = 0;

        for(auto p : puntos){

            // Saltar el mismo punto
            if(p.first == x && p.second == y)
                continue;

            double dist = sqrt(
                pow(p.first - x,2) +
                pow(p.second - y,2)
            );

            if(menorDist == -1 || dist < menorDist){
                menorDist = dist;
                mejorX = p.first;
                mejorY = p.second;
            }
        }

        cout << "\nPunto base: (" << x << ", " << y << ")";
        cout << "\nPunto mas cercano: (" 
            << mejorX << ", " << mejorY << ")";
        cout << "\nDistancia: " << menorDist << endl;
    }

};

int main(){

    PlanoCartesiano plano;
    plano.setTamano();

    int opcion;

    do{
        cout << "\nMENU\n";
        cout << "1. Agregar punto\n";
        cout << "2. Borrar punto\n";
        cout << "3. Dibujar plano\n";
        cout << "4. Punto mas cercano\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;

        switch(opcion){
            case 1: plano.agregarPunto(); break;
            case 2: plano.borrarPunto(); break;
            case 3: plano.dibujar(); break;
            case 4: plano.puntoMasCercano(); break;
        }

    }while(opcion!=5);

    return 0;
}