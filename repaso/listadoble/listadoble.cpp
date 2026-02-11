#include <iostream>
using namespace std;

class Nodo {
private:
    int dato;
    Nodo* siguiente;
    Nodo* anterior;

public:
    Nodo(int d) {
        dato = d;
        siguiente = nullptr;
        anterior = nullptr;
    }

    int getDato() { return dato; }
    Nodo* getSiguiente() { return siguiente; }
    Nodo* getAnterior() { return anterior; }

    void setSiguiente(Nodo* sig) { siguiente = sig; }
    void setAnterior(Nodo* ant) { anterior = ant; }
};

class ListaDoble {
private:
    Nodo* inicio;
    Nodo* fin;

public:
    ListaDoble() {
        inicio = nullptr;
        fin = nullptr;
    }

    void addInicio(int dato) {
        Nodo* nuevo = new Nodo(dato);

        if (inicio == nullptr) {
            inicio = fin = nuevo;
        } else {
            nuevo->setSiguiente(inicio);
            inicio->setAnterior(nuevo);
            inicio = nuevo;
        }
    }

    void addFinal(int dato) {
        Nodo* nuevo = new Nodo(dato);

        if (fin == nullptr) {
            inicio = fin = nuevo;
        } else {
            fin->setSiguiente(nuevo);
            nuevo->setAnterior(fin);
            fin = nuevo;
        }
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

        if (actual == nullptr || actual == fin) {
            addFinal(dato);
            return;
        }

        Nodo* nuevo = new Nodo(dato);
        nuevo->setSiguiente(actual->getSiguiente());
        nuevo->setAnterior(actual);

        actual->getSiguiente()->setAnterior(nuevo);
        actual->setSiguiente(nuevo);
    }

    void dropInicio() {
        if (inicio == nullptr) return;

        Nodo* temp = inicio;

        if (inicio == fin) {
            inicio = fin = nullptr;
        } else {
            inicio = inicio->getSiguiente();
            inicio->setAnterior(nullptr);
        }

        delete temp;
    }

    void dropFinal() {
        if (fin == nullptr) return;

        Nodo* temp = fin;

        if (inicio == fin) {
            inicio = fin = nullptr;
        } else {
            fin = fin->getAnterior();
            fin->setSiguiente(nullptr);
        }

        delete temp;
    }

    void dropPos(int pos) {
        if (inicio == nullptr || pos < 0) return;

        if (pos == 0) {
            dropInicio();
            return;
        }

        Nodo* actual = inicio;
        int i = 0;

        while (actual != nullptr && i < pos) {
            actual = actual->getSiguiente();
            i++;
        }

        if (actual == nullptr) return;

        if (actual == fin) {
            dropFinal();
            return;
        }

        actual->getAnterior()->setSiguiente(actual->getSiguiente());
        actual->getSiguiente()->setAnterior(actual->getAnterior());
        delete actual;
    }

    void printAdelante() {
        Nodo* aux = inicio;

        if (aux == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        while (aux != nullptr) {
            cout << aux->getDato() << " <-> ";
            aux = aux->getSiguiente();
        }
        cout << "NULL\n";
    }

    void printAtras() {
        Nodo* aux = fin;

        if (aux == nullptr) {
            cout << "Lista vacia\n";
            return;
        }

        while (aux != nullptr) {
            cout << aux->getDato() << " <-> ";
            aux = aux->getAnterior();
        }
        cout << "NULL\n";
    }

    ~ListaDoble() {
        while (inicio != nullptr) {
            dropInicio();
        }
    }
};

int main() {
    ListaDoble l;
    int opcion, dato, pos;

    do {
        cout << "\n===== MENU LISTA DOBLE =====\n";
        cout << "1. Agregar al inicio\n";
        cout << "2. Agregar al final\n";
        cout << "3. Agregar en posicion\n";
        cout << "4. Eliminar al inicio\n";
        cout << "5. Eliminar al final\n";
        cout << "6. Eliminar en posicion\n";
        cout << "7. Mostrar hacia adelante\n";
        cout << "8. Mostrar hacia atras\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
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
                l.printAdelante();
                break;

            case 8:
                l.printAtras();
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
