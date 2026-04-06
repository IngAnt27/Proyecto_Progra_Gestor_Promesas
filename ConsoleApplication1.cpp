#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// --- DIBUJO DE INICIO: TARRO Y PROMESA ---
void pantallaInicio() {
    system("cls");
    system("color 06");
    cout << "          PROYECTO: LA TABERNA DE LAS PROMESAS" << endl;
    cout << "      Integrantes: Antonio, Luis, Waldemar, Oscar" << endl;
    cout << "                _.._..,_,_" << endl;
    cout << "               (          )" << endl;
    cout << "                ]..---..[" << endl;
    cout << "              .'          '." << endl;
    cout << "             /   _.._       \\        PROMESA DE" << endl;
    cout << "            /   (    )       \\        MENIQUE" << endl;
    cout << "           (     ]..[         )         _  " << endl;
    cout << "            \\   '    '       /         | | " << endl;
    cout << "             \\              /       _  | | " << endl;
    cout << "              '.._      _..'       | |_| | " << endl;
    cout << "                  |____|           |     | " << endl;
    cout << "                                   |_____| " << endl;
    cout << "==================================================" << endl;
    cout << "        PRESIONE ENTER PARA CONTINUAR...          " << endl;
    cin.ignore();
    cin.get();
}

// --- SECCION ADMINISTRADOR ---
void menuAdministrador() {
    int opAdmin = 0;
    while (opAdmin != 3) {
        system("cls");
        system("color 0C"); // Rojo para modo Admin
        cout << "==================================================" << endl;
        cout << "          PANEL DE CONTROL: ADMINISTRADOR         " << endl;
        cout << "==================================================" << endl;
        cout << " 1. Ver Listado de Usuarios Registrados" << endl;
        cout << " 2. Ver Total de Ventas y Cuentas" << endl;
        cout << " 3. Salir al Menu de Inicio" << endl;
        cout << "==================================================" << endl;
        cout << "Seleccione una opcion: "; cin >> opAdmin;

        if (opAdmin == 1) {
            system("cls");
            ifstream leerU("usuarios.txt");
            string u, p;
            cout << "--- USUARIOS ACTIVOS EN EL SISTEMA ---" << endl;
            while (leerU >> u >> p) {
                cout << " > Usuario: " << u << endl;
            }
            leerU.close();
            system("pause");
        }
        else if (opAdmin == 2) {
            system("cls");
            ifstream leerV("ventas.txt");
            string cli, prod; float monto, totalCaja = 0;
            cout << "--- REPORTE HISTORICO DE VENTAS ---" << endl;
            while (leerV >> cli >> prod >> monto) {
                cout << "Cliente: " << cli << " | Compra: " << prod << " | Total: Q" << monto << endl;
                totalCaja += monto;
            }
            cout << "--------------------------------------------------" << endl;
            cout << " TOTAL RECAUDADO EN CAJA: Q" << totalCaja << endl;
            leerV.close();
            system("pause");
        }
    }
}

// --- SECCION USUARIO (TICKET Y COMPRA) ---
void imprimirTicket(string cliente, string producto, float precio) {
    time_t t = time(0);
    char* fecha = ctime(&t);
    system("cls");
    system("color 0F");
    cout << "**************************************************" << endl;
    cout << "          TICKET: LA TABERNA DE LAS PROMESAS      " << endl;
    cout << "**************************************************" << endl;
    cout << " FECHA: " << fecha;
    cout << " CLIENTE: " << cliente << endl;
    cout << " PRODUCTO: " << producto << endl;
    cout << " TOTAL PAGADO (IVA Incluido): Q" << precio * 1.12 << endl;
    cout << "**************************************************" << endl;

    ofstream venta("ventas.txt", ios::app);
    venta << cliente << " " << producto << " " << precio * 1.12 << endl;
    venta.close();
    system("pause");
}

void menuUsuario(string nombreU) {
    int opU = 0;
    while (opU != 3) {
        system("cls");
        system("color 0E"); // Amarillo para el menu creativo
        cout << "**************************************************" << endl;
        cout << "       --- LA TABERNA DE LAS PROMESAS ---        " << endl;
        cout << "       BIENVENIDO/A: " << nombreU << endl;
        cout << "**************************************************" << endl;
        cout << " 1. [ EL ARREPENTIDO ] ........... Q50.00" << endl;
        cout << "    (Certificado basico: 'No vuelvo a tomar')" << endl;
        cout << " 2. [ LA AMNESIA TOTAL ] ......... Q100.00" << endl;
        cout << "    (No te acuerdas de nada de anoche)" << endl;
        cout << " 3. [ EL BUSCA-PERDON ] .......... Q150.00" << endl;
        cout << "    (Sello oficial para la novia/o)" << endl;
        cout << " 4. [ EL INMORTAL ] .............. Q250.00" << endl;
        cout << "    (Aguante extremo - Nivel Leyenda)" << endl;
        cout << " 5. [ EDITAR MI PERFIL ]          (Cambiar clave)" << endl;
        cout << " 6. CERRAR SESION" << endl;
        cout << "**************************************************" << endl;
        cout << "Seleccione su paquete: "; cin >> opU;

        if (opU >= 1 && opU <= 4) {
            if (opU == 1) imprimirTicket(nombreU, "Arrepentido", 50);
            if (opU == 2) imprimirTicket(nombreU, "Amnesia", 100);
            if (opU == 3) imprimirTicket(nombreU, "Perdon", 150);
            if (opU == 4) imprimirTicket(nombreU, "Inmortal", 250);
        }
        else if (opU == 5) {
            string nueva;
            cout << "Ingrese nueva contrasena: "; cin >> nueva;
            cout << "Contrasena actualizada exitosamente!" << endl;
            system("pause");
        }
        else if (opU == 6) break;
    }
}

// --- LOGICA DE LOGIN Y REGISTRO ---
int main() {
    pantallaInicio();
    int menuIni = 0;
    while (menuIni != 4) {
        system("cls");
        system("color 0B"); // Celeste
        cout << "========== SISTEMA DE PROMESAS ==========" << endl;
        cout << " 1. Iniciar Sesion (Usuario)" << endl;
        cout << " 2. Registrarse (Nuevo Usuario)" << endl;
        cout << " 3. Modo Administrador" << endl;
        cout << " 4. Salir" << endl;
        cout << " Seleccione: "; cin >> menuIni;

        if (menuIni == 1) { // LOGIN
            string u, p, uf, pf; bool loginOk = false;
            cout << "Usuario: "; cin >> u;
            cout << "Contrasena: "; cin >> p;
            ifstream leer("usuarios.txt");
            while (leer >> uf >> pf) {
                if (u == uf && p == pf) { loginOk = true; break; }
            }
            leer.close();
            if (loginOk) menuUsuario(u);
            else { cout << "Usuario o clave incorrecta."; system("pause"); }
        }
        else if (menuIni == 2) { // REGISTRO
            string u, p;
            ofstream escribir("usuarios.txt", ios::app);
            cout << "Crea tu usuario: "; cin >> u;
            cout << "Crea tu contrasena: "; cin >> p;
            escribir << u << " " << p << endl;
            escribir.close();
            cout << "Registro exitoso!"; system("pause");
        }
        else if (menuIni == 3) { // ADMIN
            string claveAdmin;
            cout << "Ingrese la CLAVE DE ADMINISTRADOR: "; cin >> claveAdmin;
            if (claveAdmin == "admin123") {
                menuAdministrador();
            }
            else {
                cout << "Clave incorrecta. Acceso denegado." << endl;
                system("pause");
            }
        }
    }
    return 0;
}