#include <iostream>
#include <vector>
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
};

int main(){

    PlanoCartesiano plano;
    plano.setTamano();

    int opcion;

    do{
        cout<<"\nMENU\n";
        cout<<"1. Agregar punto\n";
        cout<<"2. Borrar punto\n";
        cout<<"3. Dibujar plano\n";
        cout<<"4. Salir\n";
        cout<<"Opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1: plano.agregarPunto(); break;
            case 2: plano.borrarPunto(); break;
            case 3: plano.dibujar(); break;
        }

    }while(opcion!=4);

    return 0;
}