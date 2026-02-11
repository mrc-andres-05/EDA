#include <iostream>
using namespace std;

#define MAX 5

class Cola {
private:
    int elemento[MAX];
    int inicio = 0;
    int fin = 0;

public:
    bool Vacio() {
        return inicio == fin;
    }

    bool Lleno() {
        return fin == MAX;
    }

    void Push(int valor) {
        if (Lleno()) {
            cout << "Cola llena\n";
            return;
        }
        elemento[fin++] = valor;
    }

    int Pop() {
        if (Vacio()) {
            cout << "Cola vacia\n";
            return -1;
        }
        return elemento[inicio++];
    }

    void Clean() {
        inicio = 0;
        fin = 0;
    }

    void Imprimir() {
        if (Vacio()) {
            cout << "Cola vacia\n";
            return;
        }

        cout << "Cola: ";
        for (int i = inicio; i < fin; i++) {
            cout << elemento[i];
            if (i < fin - 1) cout << " -> ";
        }
        cout << endl;
    }
};

int main() {
    Cola c;
    int opcion;
    int dato;

    do {
        cout << "\n--- MENU COLA ---\n";
        cout << "1. Insertar valor\n";
        cout << "2. Eliminar valor\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Limpiar cola\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> dato;
                c.Push(dato);
                break;

            case 2:
                cout << "Elemento eliminado: " << c.Pop() << endl;
                break;

            case 3:
                c.Imprimir();
                break;

            case 4:
                c.Clean();
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
