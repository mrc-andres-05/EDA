#include <iostream>
using namespace std;

class plano_cartesiano {

private:
    int tamano;   // cambiado
    int x;
    int y;

public:

    void pedir_datos() {

        cout << "Colocar tamano: ";
        cin >> tamano;

        cout << "Colocar punto (x y): " << endl;
        cin >> x;
        cin >> y;
    }

    void dibujar() {

        for (int i = tamano; i >= -tamano; i--) {
            for (int j = -tamano; j <= tamano; j++) {

                if (i == y && j == x)
                    cout << "P ";
                else if (i == 0 && j == 0)
                    cout << "0 ";
                else if (i == 0)
                    cout << "- ";
                else if (j == 0)
                    cout << "| ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }
};

int main() {

    plano_cartesiano plano;

    plano.pedir_datos();
    plano.dibujar();

    return 0;
}
