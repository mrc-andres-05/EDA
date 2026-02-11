#include <iostream>
using namespace std;

class Nodo {
private:
    int dato;
    Nodo* siguiente;

public:
    Nodo(int d) {
        dato = d;
        siguiente = nullptr;
    }

    int getDato() {
        return dato;
    }

    Nodo* getSiguiente() {
        return siguiente;
    }

    void setSiguiente(Nodo* sig) {
        siguiente = sig;
    }
};

class Lista {
private:
    Nodo* inicio;

public:
    Lista() {
        inicio = nullptr;
    }

    void addInicio(int dato) {
        Nodo* nuevo = new Nodo(dato);
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
    }

    void addFinal(int dato) {
        Nodo* nuevo = new Nodo(dato);

        if (inicio == nullptr) {
            inicio = nuevo;
            return;
        }

        Nodo* actual = inicio;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }

    void addPos(int dato, int pos) {
        if (pos < 0) return;

        if (pos == 0) {
            addInicio(dato);
            return;
        }

        Nodo* actual = inicio;
        int i = 0;

        while (actual != nullptr && i < pos - 1) {
            actual = actual->getSiguiente();
            i++;
        }

        if (actual == nullptr) {
            cout << "Posicion invalida\n";
            return;
        }

        Nodo* nuevo = new Nodo(dato);
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
    }

    void dropInicio() {
        if (inicio == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        Nodo* temp = inicio;
        inicio = inicio->getSiguiente();
        delete temp;
    }

    void dropFinal() {
        if (inicio == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        if (inicio->getSiguiente() == nullptr) {
            delete inicio;
            inicio = nullptr;
            return;
        }

        Nodo* actual = inicio;
        Nodo* anterior = nullptr;

        while (actual->getSiguiente() != nullptr) {
            anterior = actual;
            actual = actual->getSiguiente();
        }

        anterior->setSiguiente(nullptr);
        delete actual;
    }

    void dropPos(int pos) {
        if (inicio == nullptr || pos < 0) return;

        if (pos == 0) {
            dropInicio();
            return;
        }

        Nodo* actual = inicio;
        Nodo* anterior = nullptr;
        int i = 0;

        while (actual != nullptr && i < pos) {
            anterior = actual;
            actual = actual->getSiguiente();
            i++;
        }

        if (actual == nullptr) {
            cout << "Posicion invalida\n";
            return;
        }

        anterior->setSiguiente(actual->getSiguiente());
        delete actual;
    }

    void print() {
        Nodo* aux = inicio;

        if (aux == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        while (aux != nullptr) {
            cout << aux->getDato() << " -> ";
            aux = aux->getSiguiente();
        }
        cout << "NULL\n";
    }

    ~Lista() {
        while (inicio != nullptr) {
            dropInicio();
        }
    }
};

int main() {
    Lista l;
    int opcion, dato, pos;

    do {
        cout << "\n===== MENU LISTA =====\n";
        cout << "1. Agregar al inicio\n";
        cout << "2. Agregar al final\n";
        cout << "3. Agregar en posicion\n";
        cout << "4. Eliminar al inicio\n";
        cout << "5. Eliminar al final\n";
        cout << "6. Eliminar en posicion\n";
        cout << "7. Mostrar lista\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Dato: ";
                cin >> dato;
                l.addInicio(dato);
                break;

            case 2:
                cout << "Dato: ";
                cin >> dato;
                l.addFinal(dato);
                break;

            case 3:
                cout << "Dato: ";
                cin >> dato;
                cout << "Posicion: ";
                cin >> pos;
                l.addPos(dato, pos);
                break;

            case 4:
                l.dropInicio();
                break;

            case 5:
                l.dropFinal();
                break;

            case 6:
                cout << "Posicion: ";
                cin >> pos;
                l.dropPos(pos);
                break;

            case 7:
                l.print();
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
