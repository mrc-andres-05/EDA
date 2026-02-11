#include <iostream>
using namespace std;

class ColaCircular {
private:
    int *arr;
    int frente, final, capacidad;

public:
    ColaCircular(int cap) {
        capacidad = cap;
        arr = new int[capacidad];
        frente = -1;
        final = -1;
    }

    bool estaVacia() {
        return frente == -1;
    }

    bool estaLlena() {
        return (final + 1) % capacidad == frente;
    }

    void encolar(int valor) {
        if (estaLlena()) {
            cout << "Cola llena. No se puede encolar.\n";
            return;
        }

        if (estaVacia()) {
            frente = 0;
            final = 0;
        } else {
            final = (final + 1) % capacidad;
        }

        arr[final] = valor;
        cout << "Encolado: " << valor << endl;
    }

    void desencolar() {
        if (estaVacia()) {
            cout << "Cola vacia. No se puede desencolar.\n";
            return;
        }

        cout << "Desencolado: " << arr[frente] << endl;

        if (frente == final) {
            frente = -1;
            final = -1;
        } else {
            frente = (frente + 1) % capacidad;
        }
    }

    void mostrar() {
        if (estaVacia()) {
            cout << "Cola vacia.\n";
            return;
        }

        cout << "Cola: ";
        int i = frente;
        while (true) {
            cout << arr[i];
            if (i == final) break;
            cout << " -> ";
            i = (i + 1) % capacidad;
        }
        cout << endl;
    }

    ~ColaCircular() {
        delete[] arr;
    }
};

int main() {
    int cap;
    cout << "Ingrese la capacidad de la cola circular: ";
    cin >> cap;

    ColaCircular cola(cap);
    int opcion, valor;

    do {
        cout << "\n--- MENU COLA CIRCULAR ---\n";
        cout << "1. Encolar\n";
        cout << "2. Desencolar\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor a encolar: ";
                cin >> valor;
                cola.encolar(valor);
                break;

            case 2:
                cola.desencolar();
                break;

            case 3:
                cola.mostrar();
                break;

            case 4:
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 4);

    return 0;
}
