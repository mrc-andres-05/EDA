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

class Cola {
private:
    Lista lista;

public:
    void enqueue(int dato) {
        lista.addFinal(dato);
    }

    void dequeue() {
        lista.dropInicio();
    }

    void print() {
        lista.print();
    }
};
int main() {
    Cola c;
    int opcion, dato;

    do {
        cout << "\n===== MENU COLA =====\n";
        cout << "1. Enqueue (insertar)\n";
        cout << "2. Dequeue (eliminar)\n";
        cout << "3. Mostrar cola\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Dato: ";
                cin >> dato;
                c.enqueue(dato);
                break;

            case 2:
                c.dequeue();
                break;

            case 3:
                c.print();
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
