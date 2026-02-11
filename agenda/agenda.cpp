#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

string toLower(string texto) {
    for (char &c : texto)
        c = tolower(c);
    return texto;
}

class Persona {
private:
    int id;
    string nombre;
    string apellidoPaterno;
    string apellidoMaterno;
    vector<string> telefonos;
    string direccion;
    string correo;

public:
    Persona(int id,
            string nombre,
            string apP,
            string apM,
            vector<string> telefonos,
            string direccion,
            string correo) {

        this->id = id;
        this->nombre = nombre;
        this->apellidoPaterno = apP;
        this->apellidoMaterno = apM;
        this->telefonos = telefonos;
        this->direccion = direccion;
        this->correo = correo;
    }

    int getId() { return id; }
    string getNombre() { return nombre; }
    vector<string>& getTelefonos() { return telefonos; }

    void setNombre(string v) { nombre = v; }
    void setApellidoPaterno(string v) { apellidoPaterno = v; }
    void setApellidoMaterno(string v) { apellidoMaterno = v; }
    void setDireccion(string v) { direccion = v; }
    void setCorreo(string v) { correo = v; }

    void agregarTelefono(string tel) {
        telefonos.push_back(tel);
    }

    void editarTelefono(int index, string nuevo) {
        if (index >= 0 && index < (int)telefonos.size())
            telefonos[index] = nuevo;
    }

    void eliminarTelefono(int index) {
        if (index >= 0 && index < (int)telefonos.size())
            telefonos.erase(telefonos.begin() + index);
    }

    string toString() {
        string telConcat;
        for (size_t i = 0; i < telefonos.size(); i++) {
            telConcat += telefonos[i];
            if (i < telefonos.size() - 1)
                telConcat += ",";
        }

        return to_string(id) + "|" + nombre + "|" +
               apellidoPaterno + "|" + apellidoMaterno + "|" +
               telConcat + "|" + direccion + "|" + correo;
    }

    void mostrar() {
        cout << endl << "ID: " << id << endl;
        cout << "Nombre: " << nombre << " "
             << apellidoPaterno << " "
             << apellidoMaterno << endl;

        cout << "Telefonos:\n";
        for (size_t i = 0; i < telefonos.size(); i++) {
            cout << "  [" << i + 1 << "] " << telefonos[i] << endl;
        }

        cout << "Direccion: " << direccion << endl;
        cout << "Correo: " << correo << endl;
        cout << "---------------------------\n";
    }
};

class Agenda {
private:
    vector<Persona> personas;
    string archivo = "agenda.txt";
    int ultimoID = 0;

    void cargarArchivo() {
        ifstream file(archivo);
        if (!file.is_open()) return;

        string linea;
        while (getline(file, linea)) {
            string datos[7];
            int i = 0;
            string temp = "";

            for (char c : linea) {
                if (c == '|') {
                    datos[i++] = temp;
                    temp = "";
                } else {
                    temp += c;
                }
            }
            datos[i] = temp;

            vector<string> telefonos;
            string telTemp = "";

            for (char c : datos[4]) {
                if (c == ',') {
                    telefonos.push_back(telTemp);
                    telTemp = "";
                } 
                else { telTemp += c; }
            }

            if (!telTemp.empty())
            telefonos.push_back(telTemp);

            int id = stoi(datos[0]);
            personas.push_back(Persona(
                id, datos[1], datos[2], datos[3],
                telefonos, datos[5], datos[6]
            ));

            if (id > ultimoID)
                ultimoID = id;
        }
        file.close();
    }

    void guardarArchivo() {
        ofstream file(archivo);
        for (auto &p : personas)
            file << p.toString() << endl;
        file.close();
    }

public:
    Agenda() {
        cargarArchivo();
    }

    void agregarPersona() {
        vector<string> telefonos;
        string nombre, apP, apM, tel, dir, correo;

        cin.ignore();
        cout << "Nombre: "; getline(cin, nombre);
        cout << "Apellido paterno: "; getline(cin, apP);
        cout << "Apellido materno: "; getline(cin, apM);
        cout << "Ingrese telefonos (ENTER vacio para terminar)\n";
            while (true) {
                cout << "Telefono: ";
                getline(cin, tel);

                if (tel.empty())
            break;

            telefonos.push_back(tel);
        }
        cout << "Direccion: "; getline(cin, dir);
        cout << "Correo: "; getline(cin, correo);

        personas.push_back(Persona(++ultimoID, nombre, apP, apM, telefonos, dir, correo));
        guardarArchivo();

        cout << "Persona agregada correctamente.\n";
    }

    void eliminarPersona(int id) {
        for (auto it = personas.begin(); it != personas.end(); it++) {
            if (it->getId() == id) {
                personas.erase(it);
                guardarArchivo();
                cout << "Persona eliminada.\n";
                return;
            }
        }
        cout << "ID no encontrado.\n";
    }

    void editarPersona() {
    int id;
    cout << "Ingrese ID a editar: ";
    cin >> id;
    cin.ignore();

    for (auto &p : personas) {
        if (p.getId() == id) {

            cout << "\nDatos actuales:\n";
            p.mostrar();

            string input;

            cout << "Nuevo nombre (ENTER para mantener): ";
            getline(cin, input);
            if (!input.empty()) p.setNombre(input);

            cout << "Nuevo apellido paterno (ENTER para mantener): ";
            getline(cin, input);
            if (!input.empty()) p.setApellidoPaterno(input);

            cout << "Nuevo apellido materno (ENTER para mantener): ";
            getline(cin, input);
            if (!input.empty()) p.setApellidoMaterno(input);

            //editar numeros
            int opTel;
            do {
                cout << "\n--- TELEFONOS ---\n";
                auto &tels = p.getTelefonos();

                for (size_t i = 0; i < tels.size(); i++)
                    cout << i + 1 << ". " << tels[i] << endl;

                cout << "\n1. Agregar telefono";
                cout << "\n2. Editar telefono";
                cout << "\n3. Eliminar telefono";
                cout << "\n4. Salir\n";
                cout << "Opcion: ";
                cin >> opTel;
                cin.ignore();

                if (opTel == 1) {
                    cout << "Nuevo telefono: ";
                    getline(cin, input);
                    if (!input.empty())
                        p.agregarTelefono(input);
                }
                else if (opTel == 2) {
                    int pos;
                    cout << "Numero a editar: ";
                    cin >> pos;
                    cin.ignore();

                    if (pos >= 1 && pos <= (int)tels.size()) {
                        cout << "Nuevo valor: ";
                        getline(cin, input);
                        if (!input.empty())
                            p.editarTelefono(pos - 1, input);
                    }
                }
                    else if (opTel == 3) {
                        int pos;
                        cout << "Numero a eliminar: ";
                        cin >> pos;
                        cin.ignore();

                        if (pos >= 1 && pos <= (int)tels.size())
                            p.eliminarTelefono(pos - 1);
                    }

                } while (opTel != 4);

                    cout << "Nueva direccion (ENTER para mantener): ";
                    getline(cin, input);
                    if (!input.empty()) p.setDireccion(input);

                    cout << "Nuevo correo (ENTER para mantener): ";
                    getline(cin, input);
                    if (!input.empty()) p.setCorreo(input);

                    guardarArchivo();
                    cout << "\nPersona editada correctamente.\n";
                    return;
                }
            }

        cout << "ID no encontrado.\n";
    }

    void buscarID() {
        string texto;
        do {
            cout << "\nBuscar ID (ENTER para salir): ";
            getline(cin, texto);
            if (texto.empty()) break;

            bool encontrado = false;
            for (auto &p : personas) {
                if (to_string(p.getId()).find(texto) != string::npos) {
                    p.mostrar();
                    encontrado = true;
                }
            }
            if (!encontrado)
                cout << "No hay coincidencias.\n";

        } while (true);
    }

    void buscarNombre() {
        string texto;
        do {
            cout << "\nBuscar nombre (ENTER para salir): ";
            getline(cin, texto);
            if (texto.empty()) break;

            bool encontrado = false;
            string t = toLower(texto);

            for (auto &p : personas) {
                if (toLower(p.getNombre()).find(t) != string::npos) {
                    p.mostrar();
                    encontrado = true;
                }
            }
            if (!encontrado)
                cout << "No hay coincidencias.\n";

        } while (true);
    }

    void mostrarTodo() {
        for (auto &p : personas)
            p.mostrar();
    }
};

int main() {
    Agenda agenda;
    int opcion;

    do {
        cout << "\n========= AGENDA =========\n";
        cout << "1. Agregar persona\n";
        cout << "2. Eliminar persona\n";
        cout << "3. Editar persona\n";
        cout << "4. Buscar por ID\n";
        cout << "5. Buscar por nombre\n";
        cout << "6. Mostrar todas\n";
        cout << "7. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: agenda.agregarPersona(); break;
        case 2: {
            int id;
            cout << "ID a eliminar: ";
            cin >> id;
            agenda.eliminarPersona(id);
            break;
        }
        case 3: agenda.editarPersona(); break;
        case 4: cin.ignore(); agenda.buscarID(); break;
        case 5: cin.ignore(); agenda.buscarNombre(); break;
        case 6: agenda.mostrarTodo(); break;
        case 7: cout << "Saliendo...\n"; break;
        default: cout << "Opcion invalida\n";
        }

    } while (opcion != 7);

    return 0;
}
