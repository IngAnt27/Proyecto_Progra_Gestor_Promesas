#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// ============================================================
//  ESTRUCTURAS
// ============================================================
struct Promesa {
    int    id;
    string nombre;
    float  precio;
    float  multa;
};

struct Usuario {
    string username;
    string password;
};

struct Venta {
    int    id;
    string cliente;
    int    promesaId;
    string nombrePromesa;
    float  total;
    string estado;  // Activa / Cumplida / Rota
    string fecha;
};

// ============================================================
//  ARREGLOS GLOBALES
// ============================================================
Promesa  catalogo[100];
int      totalPromesas = 0;

Usuario  usuarios[100];
int      totalUsuarios = 0;

Venta    ventas[100];
int      totalVentas = 0;

// ============================================================
//  CARGAR Y GUARDAR ARCHIVOS
// ============================================================

// --- PROMESAS ---
void cargarPromesas() {
    totalPromesas = 0;
    ifstream f("promesas.txt");
    if (!f.is_open()) return;
    while (f >> catalogo[totalPromesas].id
        >> catalogo[totalPromesas].nombre
        >> catalogo[totalPromesas].precio
        >> catalogo[totalPromesas].multa) {
        totalPromesas++;
    }
    f.close();
}

void guardarPromesas() {
    ofstream f("promesas.txt");
    for (int i = 0; i < totalPromesas; i++) {
        f << catalogo[i].id << " "
            << catalogo[i].nombre << " "
            << catalogo[i].precio << " "
            << catalogo[i].multa << endl;
    }
    f.close();
}

void inicializarPromesas() {
    cargarPromesas();
    if (totalPromesas == 0) {
        catalogo[0] = { 1, "El_Arrepentido",   50.0f,  100.0f };
        catalogo[1] = { 2, "La_Amnesia_Total", 100.0f, 200.0f };
        catalogo[2] = { 3, "El_Busca_Perdon",  150.0f, 300.0f };
        catalogo[3] = { 4, "El_Inmortal",      250.0f, 500.0f };
        totalPromesas = 4;
        guardarPromesas();
    }
}

// --- USUARIOS ---
void cargarUsuarios() {
    totalUsuarios = 0;
    ifstream f("usuarios.txt");
    if (!f.is_open()) return;
    while (f >> usuarios[totalUsuarios].username
        >> usuarios[totalUsuarios].password) {
        totalUsuarios++;
    }
    f.close();
}

void guardarUsuarios() {
    ofstream f("usuarios.txt");
    for (int i = 0; i < totalUsuarios; i++) {
        f << usuarios[i].username << " "
            << usuarios[i].password << endl;
    }
    f.close();
}

// --- VENTAS ---
void cargarVentas() {
    totalVentas = 0;
    ifstream f("ventas.txt");
    if (!f.is_open()) return;
    while (f >> ventas[totalVentas].id
        >> ventas[totalVentas].cliente
        >> ventas[totalVentas].promesaId
        >> ventas[totalVentas].nombrePromesa
        >> ventas[totalVentas].total
        >> ventas[totalVentas].estado
        >> ventas[totalVentas].fecha) {
        totalVentas++;
    }
    f.close();
}

void guardarVentas() {
    ofstream f("ventas.txt");
    for (int i = 0; i < totalVentas; i++) {
        f << ventas[i].id << " "
            << ventas[i].cliente << " "
            << ventas[i].promesaId << " "
            << ventas[i].nombrePromesa << " "
            << ventas[i].total << " "
            << ventas[i].estado << " "
            << ventas[i].fecha << endl;
    }
    f.close();
}

// ============================================================
//  PANTALLA DE INICIO
// ============================================================
void pantallaInicio() {
    system("cls");
    system("color 06");
    cout << "==================================================" << endl;
    cout << "     PROYECTO: LA TABERNA DE LAS PROMESAS        " << endl;
    cout << "   Integrantes: Antonio, Luis, Waldemar, Oscar   " << endl;
    cout << "==================================================" << endl;
    cout << "                _.._..,_,_                       " << endl;
    cout << "               (          )                      " << endl;
    cout << "                ]..---..[                        " << endl;
    cout << "              .'          '.                     " << endl;
    cout << "             /   _.._       \\        PROMESA DE  " << endl;
    cout << "            /   (    )       \\        MENIQUE    " << endl;
    cout << "           (     ]..[         )         _        " << endl;
    cout << "            \\   '    '       /         | |       " << endl;
    cout << "             \\              /       _  | |       " << endl;
    cout << "              '.._      _..'       | |_| |       " << endl;
    cout << "                  |____|           |     |       " << endl;
    cout << "                                   |_____|       " << endl;
    cout << "==================================================" << endl;
    cout << "        PRESIONE ENTER PARA CONTINUAR...         " << endl;
    cout << "==================================================" << endl;
    cin.ignore();
    cin.get();
}

// ============================================================
//  TICKET
// ============================================================
void imprimirTicket(string cliente, int idVenta, string nombrePromesa,
    float precio, float multa) {
    time_t t = time(0);
    char* fecha = ctime(&t);
    system("cls");
    system("color 0F");
    cout << "**************************************************" << endl;
    cout << "       TICKET: LA TABERNA DE LAS PROMESAS        " << endl;
    cout << "**************************************************" << endl;
    cout << " No. Certificado : " << idVenta << endl;
    cout << " Fecha           : " << fecha;
    cout << " Cliente         : " << cliente << endl;
    cout << " Promesa         : " << nombrePromesa << endl;
    cout << "--------------------------------------------------" << endl;
    cout << " Subtotal        : Q" << precio << endl;
    cout << " IVA (12%)       : Q" << precio * 0.12f << endl;
    cout << " TOTAL A PAGAR   : Q" << precio * 1.12f << endl;
    cout << "--------------------------------------------------" << endl;
    cout << " Multa si rompe  : Q" << multa << endl;
    cout << "**************************************************" << endl;
    cout << " Antonio | Luis | Waldemar | Oscar               " << endl;
    cout << " Si la rompe... le cobramos. Prometido.          " << endl;
    cout << "**************************************************" << endl;
    system("pause");
}

// ============================================================
//  MENU USUARIO — CRUD DE VENTAS + CATALOGO
// ============================================================
void menuUsuario(string nombreU) {
    int opU = 0;
    while (opU != 6) {
        system("cls");
        system("color 0E");
        cout << "**************************************************" << endl;
        cout << "        --- LA TABERNA DE LAS PROMESAS ---       " << endl;
        cout << "        BIENVENIDO/A: " << nombreU << endl;
        cout << "**************************************************" << endl;
        cout << " 1. Ver catalogo de promesas                     " << endl;
        cout << " 2. Certificar una promesa (genera ticket)       " << endl;
        cout << " 3. Ver mis promesas certificadas                " << endl;
        cout << " 4. Actualizar estado de mi promesa              " << endl;
        cout << " 5. Cambiar mi contrasena                        " << endl;
        cout << " 6. Cerrar sesion                                " << endl;
        cout << "**************************************************" << endl;
        cout << " Seleccione: "; cin >> opU;

        // --- VER CATALOGO ---
        if (opU == 1) {
            system("cls");
            system("color 0E");
            cout << "==================================================" << endl;
            cout << "            CATALOGO DE PROMESAS                  " << endl;
            cout << "==================================================" << endl;
            cout << " ID  | Nombre                | Precio  | Multa   " << endl;
            cout << "--------------------------------------------------" << endl;
            for (int i = 0; i < totalPromesas; i++) {
                cout << " " << catalogo[i].id
                    << "   | " << catalogo[i].nombre
                    << "\t\t| Q" << catalogo[i].precio
                    << "\t | Q" << catalogo[i].multa << endl;
            }
            cout << "==================================================" << endl;
            system("pause");
        }

        // --- CERTIFICAR PROMESA ---
        else if (opU == 2) {
            system("cls");
            system("color 0E");
            cout << "==================================================" << endl;
            cout << "           CERTIFICAR PROMESA                     " << endl;
            cout << "==================================================" << endl;
            for (int i = 0; i < totalPromesas; i++) {
                cout << " " << catalogo[i].id
                    << ". " << catalogo[i].nombre
                    << " - Q" << catalogo[i].precio << endl;
            }
            cout << "--------------------------------------------------" << endl;
            int idSel;
            cout << " Seleccione ID de promesa: "; cin >> idSel;

            int pos = -1;
            for (int i = 0; i < totalPromesas; i++) {
                if (catalogo[i].id == idSel) { pos = i; break; }
            }
            if (pos == -1) {
                cout << " ID no encontrado." << endl;
                system("pause");
            }
            else {
                // Registrar venta
                time_t t = time(0);
                char* fecha = ctime(&t);
                string fechaStr = string(fecha);
                // quitar el salto de linea del ctime
                if (!fechaStr.empty()) fechaStr.pop_back();
                // reemplazar espacios por guion para guardar sin problemas
                for (char& c : fechaStr) if (c == ' ') c = '_';

                int nuevoId = totalVentas + 1;
                ventas[totalVentas].id = nuevoId;
                ventas[totalVentas].cliente = nombreU;
                ventas[totalVentas].promesaId = catalogo[pos].id;
                ventas[totalVentas].nombrePromesa = catalogo[pos].nombre;
                ventas[totalVentas].total = catalogo[pos].precio * 1.12f;
                ventas[totalVentas].estado = "Activa";
                ventas[totalVentas].fecha = fechaStr;
                totalVentas++;
                guardarVentas();

                imprimirTicket(nombreU, nuevoId, catalogo[pos].nombre,
                    catalogo[pos].precio, catalogo[pos].multa);
            }
        }

        // --- VER MIS PROMESAS ---
        else if (opU == 3) {
            system("cls");
            system("color 0E");
            cout << "==================================================" << endl;
            cout << "         MIS PROMESAS CERTIFICADAS               " << endl;
            cout << "==================================================" << endl;
            int encontradas = 0;
            for (int i = 0; i < totalVentas; i++) {
                if (ventas[i].cliente == nombreU) {
                    cout << " #" << ventas[i].id
                        << " | " << ventas[i].nombrePromesa
                        << " | Q" << ventas[i].total
                        << " | Estado: " << ventas[i].estado << endl;
                    encontradas++;
                }
            }
            if (encontradas == 0) cout << " No tienes promesas certificadas aun." << endl;
            cout << "==================================================" << endl;
            system("pause");
        }

        // --- ACTUALIZAR ESTADO ---
        else if (opU == 4) {
            system("cls");
            system("color 0E");
            cout << "==================================================" << endl;
            cout << "         ACTUALIZAR ESTADO DE PROMESA            " << endl;
            cout << "==================================================" << endl;
            int encontradas = 0;
            for (int i = 0; i < totalVentas; i++) {
                if (ventas[i].cliente == nombreU) {
                    cout << " #" << ventas[i].id
                        << " | " << ventas[i].nombrePromesa
                        << " | Estado: " << ventas[i].estado << endl;
                    encontradas++;
                }
            }
            if (encontradas == 0) {
                cout << " No tienes promesas certificadas." << endl;
                system("pause");
            }
            else {
                int idSel;
                cout << "--------------------------------------------------" << endl;
                cout << " Ingrese el # de la promesa a actualizar: ";
                cin >> idSel;
                int pos = -1;
                for (int i = 0; i < totalVentas; i++) {
                    if (ventas[i].id == idSel && ventas[i].cliente == nombreU) {
                        pos = i; break;
                    }
                }
                if (pos == -1) {
                    cout << " Promesa no encontrada." << endl;
                }
                else {
                    cout << " 1. Activa   2. Cumplida   3. Rota" << endl;
                    int nuevoE; cout << " Nuevo estado: "; cin >> nuevoE;
                    if (nuevoE == 1) ventas[pos].estado = "Activa";
                    else if (nuevoE == 2) ventas[pos].estado = "Cumplida";
                    else if (nuevoE == 3) ventas[pos].estado = "Rota";
                    guardarVentas();
                    cout << " Estado actualizado a: " << ventas[pos].estado << endl;
                }
                system("pause");
            }
        }

        // --- CAMBIAR CONTRASENA ---
        else if (opU == 5) {
            string nueva;
            cout << " Ingrese nueva contrasena: "; cin >> nueva;
            for (int i = 0; i < totalUsuarios; i++) {
                if (usuarios[i].username == nombreU) {
                    usuarios[i].password = nueva;
                    guardarUsuarios();
                    cout << " Contrasena actualizada exitosamente!" << endl;
                    break;
                }
            }
            system("pause");
        }
    }
}

// ============================================================
//  MENU ADMINISTRADOR — CRUD COMPLETO
// ============================================================
void menuAdministrador() {
    int opAdmin = 0;
    while (opAdmin != 6) {
        system("cls");
        system("color 0C");
        cout << "==================================================" << endl;
        cout << "         PANEL DE CONTROL: ADMINISTRADOR         " << endl;
        cout << "==================================================" << endl;
        cout << " --- CATALOGO DE PROMESAS ---                    " << endl;
        cout << " 1. Ver catalogo                                 " << endl;
        cout << " 2. Agregar promesa al catalogo                  " << endl;
        cout << " 3. Editar promesa del catalogo                  " << endl;
        cout << " 4. Eliminar promesa del catalogo                " << endl;
        cout << " --- USUARIOS ---                                " << endl;
        cout << " 5. Ver usuarios registrados                     " << endl;
        cout << " 6. Agregar usuario                              " << endl;
        cout << " 7. Editar contrasena de usuario                 " << endl;
        cout << " 8. Eliminar usuario                             " << endl;
        cout << " --- REPORTES ---                                " << endl;
        cout << " 9. Ver reporte general de ventas                " << endl;
        cout << " 0. Salir al menu principal                      " << endl;
        cout << "==================================================" << endl;
        cout << " Seleccione: "; cin >> opAdmin;

        // === CATALOGO ===

        // --- VER CATALOGO ---
        if (opAdmin == 1) {
            system("cls");
            cout << "==================================================" << endl;
            cout << "            CATALOGO DE PROMESAS                  " << endl;
            cout << "==================================================" << endl;
            cout << " ID  | Nombre                | Precio  | Multa   " << endl;
            cout << "--------------------------------------------------" << endl;
            for (int i = 0; i < totalPromesas; i++) {
                cout << " " << catalogo[i].id
                    << "   | " << catalogo[i].nombre
                    << "\t\t| Q" << catalogo[i].precio
                    << "\t | Q" << catalogo[i].multa << endl;
            }
            cout << "==================================================" << endl;
            system("pause");
        }

        // --- AGREGAR PROMESA ---
        else if (opAdmin == 2) {
            system("cls");
            cout << "--- AGREGAR PROMESA ---" << endl;
            catalogo[totalPromesas].id = totalPromesas + 1;
            cout << " Nombre (sin espacios, usa_guiones): ";
            cin >> catalogo[totalPromesas].nombre;
            cout << " Precio Q: ";
            cin >> catalogo[totalPromesas].precio;
            cout << " Multa Q si rompe la promesa: ";
            cin >> catalogo[totalPromesas].multa;
            totalPromesas++;
            guardarPromesas();
            cout << " Promesa agregada correctamente!" << endl;
            system("pause");
        }

        // --- EDITAR PROMESA ---
        else if (opAdmin == 3) {
            system("cls");
            cout << "--- EDITAR PROMESA ---" << endl;
            for (int i = 0; i < totalPromesas; i++) {
                cout << " " << catalogo[i].id << ". " << catalogo[i].nombre
                    << " - Q" << catalogo[i].precio << endl;
            }
            int idSel; cout << " ID a editar: "; cin >> idSel;
            int pos = -1;
            for (int i = 0; i < totalPromesas; i++) {
                if (catalogo[i].id == idSel) { pos = i; break; }
            }
            if (pos == -1) {
                cout << " ID no encontrado." << endl;
            }
            else {
                cout << " Nuevo nombre (sin espacios): "; cin >> catalogo[pos].nombre;
                cout << " Nuevo precio Q: ";             cin >> catalogo[pos].precio;
                cout << " Nueva multa Q: ";              cin >> catalogo[pos].multa;
                guardarPromesas();
                cout << " Promesa actualizada!" << endl;
            }
            system("pause");
        }

        // --- ELIMINAR PROMESA ---
        else if (opAdmin == 4) {
            system("cls");
            cout << "--- ELIMINAR PROMESA ---" << endl;
            for (int i = 0; i < totalPromesas; i++) {
                cout << " " << catalogo[i].id << ". " << catalogo[i].nombre << endl;
            }
            int idSel; cout << " ID a eliminar: "; cin >> idSel;
            int pos = -1;
            for (int i = 0; i < totalPromesas; i++) {
                if (catalogo[i].id == idSel) { pos = i; break; }
            }
            if (pos == -1) {
                cout << " ID no encontrado." << endl;
            }
            else {
                // Desplazar hacia atras
                for (int i = pos; i < totalPromesas - 1; i++) {
                    catalogo[i] = catalogo[i + 1];
                }
                totalPromesas--;
                guardarPromesas();
                cout << " Promesa eliminada correctamente!" << endl;
            }
            system("pause");
        }

        // === USUARIOS ===

        // --- VER USUARIOS ---
        else if (opAdmin == 5) {
            system("cls");
            cout << "--- USUARIOS REGISTRADOS ---" << endl;
            for (int i = 0; i < totalUsuarios; i++) {
                cout << " > Usuario: " << usuarios[i].username
                    << "  |  Pass: " << usuarios[i].password << endl;
            }
            system("pause");
        }

        // --- AGREGAR USUARIO ---
        else if (opAdmin == 6) {
            system("cls");
            cout << "--- AGREGAR USUARIO ---" << endl;
            string usr, pwd;
            cout << " Nuevo username  : "; cin >> usr;
            // verificar si ya existe
            bool existe = false;
            for (int i = 0; i < totalUsuarios; i++) {
                if (usuarios[i].username == usr) { existe = true; break; }
            }
            if (existe) {
                cout << " Ese usuario ya existe." << endl;
            }
            else {
                cout << " Nueva contrasena: "; cin >> pwd;
                usuarios[totalUsuarios].username = usr;
                usuarios[totalUsuarios].password = pwd;
                totalUsuarios++;
                guardarUsuarios();
                cout << " Usuario creado exitosamente!" << endl;
            }
            system("pause");
        }

        // --- EDITAR USUARIO ---
        else if (opAdmin == 7) {
            system("cls");
            cout << "--- EDITAR CONTRASENA DE USUARIO ---" << endl;
            for (int i = 0; i < totalUsuarios; i++) {
                cout << " " << (i + 1) << ". " << usuarios[i].username << endl;
            }
            string usr; cout << " Username a editar: "; cin >> usr;
            int pos = -1;
            for (int i = 0; i < totalUsuarios; i++) {
                if (usuarios[i].username == usr) { pos = i; break; }
            }
            if (pos == -1) {
                cout << " Usuario no encontrado." << endl;
            }
            else {
                cout << " Nueva contrasena: "; cin >> usuarios[pos].password;
                guardarUsuarios();
                cout << " Usuario actualizado!" << endl;
            }
            system("pause");
        }

        // --- ELIMINAR USUARIO ---
        else if (opAdmin == 8) {
            system("cls");
            cout << "--- ELIMINAR USUARIO ---" << endl;
            for (int i = 0; i < totalUsuarios; i++) {
                cout << " " << (i + 1) << ". " << usuarios[i].username << endl;
            }
            string usr; cout << " Username a eliminar: "; cin >> usr;
            int pos = -1;
            for (int i = 0; i < totalUsuarios; i++) {
                if (usuarios[i].username == usr) { pos = i; break; }
            }
            if (pos == -1) {
                cout << " Usuario no encontrado." << endl;
            }
            else {
                for (int i = pos; i < totalUsuarios - 1; i++) {
                    usuarios[i] = usuarios[i + 1];
                }
                totalUsuarios--;
                guardarUsuarios();
                cout << " Usuario eliminado correctamente!" << endl;
            }
            system("pause");
        }

        // === REPORTE ===
        else if (opAdmin == 9) {
            system("cls");
            system("color 0C");
            float totalCaja = 0;
            int activas = 0, cumplidas = 0, rotas = 0;
            cout << "==================================================" << endl;
            cout << "          REPORTE GENERAL DE VENTAS               " << endl;
            cout << "==================================================" << endl;
            cout << " # | Cliente       | Promesa            | Total  | Estado    " << endl;
            cout << "--------------------------------------------------" << endl;
            for (int i = 0; i < totalVentas; i++) {
                cout << " " << ventas[i].id
                    << " | " << ventas[i].cliente
                    << "\t| " << ventas[i].nombrePromesa
                    << "\t| Q" << ventas[i].total
                    << " | " << ventas[i].estado << endl;
                totalCaja += ventas[i].total;
                if (ventas[i].estado == "Activa")   activas++;
                else if (ventas[i].estado == "Cumplida") cumplidas++;
                else if (ventas[i].estado == "Rota")     rotas++;
            }
            cout << "==================================================" << endl;
            cout << " Total de certificaciones : " << totalVentas << endl;
            cout << " Activas                  : " << activas << endl;
            cout << " Cumplidas                : " << cumplidas << endl;
            cout << " Rotas                    : " << rotas << endl;
            cout << "--------------------------------------------------" << endl;
            cout << " TOTAL RECAUDADO EN CAJA  : Q" << totalCaja << endl;
            cout << "==================================================" << endl;
            system("pause");
        }
    }
}

// ============================================================
//  MAIN — LOGIN Y REGISTRO
// ============================================================
int main() {
    // Cargar datos al iniciar
    cargarUsuarios();
    inicializarPromesas();
    cargarVentas();

    pantallaInicio();

    int menuIni = 0;
    while (menuIni != 4) {
        system("cls");
        system("color 0B");
        cout << "==================================================" << endl;
        cout << "       SISTEMA DE PROMESAS DE BORRACHERA         " << endl;
        cout << "==================================================" << endl;
        cout << " 1. Iniciar Sesion                               " << endl;
        cout << " 2. Registrarse (Nuevo Usuario)                  " << endl;
        cout << " 3. Modo Administrador                           " << endl;
        cout << " 4. Salir                                        " << endl;
        cout << "==================================================" << endl;
        cout << " Seleccione: "; cin >> menuIni;

        // --- LOGIN ---
        if (menuIni == 1) {
            string u, p;
            bool loginOk = false;
            int intentos = 3;
            while (intentos > 0 && !loginOk) {
                cout << " Usuario   : "; cin >> u;
                cout << " Contrasena: "; cin >> p;
                for (int i = 0; i < totalUsuarios; i++) {
                    if (usuarios[i].username == u && usuarios[i].password == p) {
                        loginOk = true; break;
                    }
                }
                if (!loginOk) {
                    intentos--;
                    cout << " Credenciales incorrectas. Intentos restantes: "
                        << intentos << endl;
                    system("pause");
                }
            }
            if (loginOk) menuUsuario(u);
            else {
                cout << " Demasiados intentos fallidos. Acceso bloqueado." << endl;
                system("pause");
            }
        }

        // --- REGISTRO ---
        else if (menuIni == 2) {
            string u, p;
            cout << " Crea tu usuario   : "; cin >> u;
            // verificar si ya existe
            bool existe = false;
            for (int i = 0; i < totalUsuarios; i++) {
                if (usuarios[i].username == u) { existe = true; break; }
            }
            if (existe) {
                cout << " Ese usuario ya existe." << endl;
            }
            else {
                cout << " Crea tu contrasena: "; cin >> p;
                usuarios[totalUsuarios].username = u;
                usuarios[totalUsuarios].password = p;
                totalUsuarios++;
                guardarUsuarios();
                cout << " Registro exitoso!" << endl;
            }
            system("pause");
        }

        // --- ADMINISTRADOR ---
        else if (menuIni == 3) {
            string claveAdmin;
            cout << " Clave de administrador: "; cin >> claveAdmin;
            if (claveAdmin == "admin123") {
                menuAdministrador();
            }
            else {
                cout << " Clave incorrecta. Acceso denegado." << endl;
                system("pause");
            }
        }
    }
    return 0;
}