#include <iostream>
using namespace std;

#define MAX 100

class Pila {
private:
    int elemento[MAX];
    int indice = 0;

public:
    bool Vacio() {
        return indice == 0;
    }

    bool Lleno() {
        return indice == MAX;
    }

    void Push(int valor) {
        if (Lleno()) {
            cout << "No se puede ingresar\n";
            return;
        }
        elemento[indice++] = valor;
    }

    int Pop() {
        if (Vacio()) {
            cout << "Pila vacía\n";
            return -1;
        }
        return elemento[--indice];
    }

    void Clean() {
        indice = 0;
    }

    void Imprimir() {
        if (Vacio()) {
            cout << "Pila vacía\n";
            return;
        }
        cout << "Pila:\n";
        for (int i = indice - 1; i >= 0; i--) {
            cout << elemento[i] << endl;
        }
    }
};

int main() {
    Pila p;
    int opcion;
    int dato;

    do {
        cout << "\n--- MENU PILA ---\n";
        cout << "1. Insertar valor\n";
        cout << "2. Eliminar valor\n";
        cout << "3. Mostrar pila\n";
        cout << "4. Limpiar pila\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> dato;
                p.Push(dato);
                break;

            case 2:
                cout << "Elemento eliminado: " << p.Pop() << endl;
                break;

            case 3:
                p.Imprimir();
                break;

            case 4:
                p.Clean();
                break;

            case 0:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }

    } while (opcion != 0);

    return 0;
}
