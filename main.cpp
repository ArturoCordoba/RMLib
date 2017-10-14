#include <iostream>
#include <cstring>
#include "RMLib.h"
#include "DataStructures/RMRef_H.h"


using namespace std;

RMLib* rmLib;

int main() {
    rmLib = RMLib::getInstance();

    string ipServer;
    string portServer;
    string ipServerHA;
    string portServerHA;

    cout << "Ingrese los datos de los servidores" << endl;

    cout << "IP Activo: ";
    cin >> ipServer;
    cout << "Port Activo: ";
    cin >> portServer;

    cout << "IP Pasivo: ";
    cin >> ipServerHA;
    cout << "Port Pasivo: ";
    cin >> portServerHA;


    char *ip = strdup(ipServer.c_str());
    char *port = strdup(portServer.c_str());
    char *ipHA = strdup(ipServerHA.c_str());
    char *portHA = strdup(portServerHA.c_str());

    rmLib->rm_init(ip, atoi(port), ipHA, atoi(portHA));

    while (true) {
        string act;

        cout << "Selecciona la accion a realizar: " << endl;
        cout << "1. Store" << endl;
        cout << "2. Get" << endl;
        cout << "3. Erase" << endl;
        cout << "4. Exit" << endl;

        cin >> act;

        char* action = strdup(act.c_str());

        if (act.size() > 0) {
            if (strcmp(action, "1") == 0) {
                string key;
                string value;
                string value_size;

                cout << "Key: ";
                cin >> key;
                cout << "Value: ";
                cin >> value;
                cout << "Value Size: ";
                cin >> value_size;

                string response = rmLib->rm_new((char *) key.c_str(), (char *) value.c_str(), stoi(value_size));
                cout << "Respuesta: " << response << endl << endl;

            } else if(strcmp(action, "2") == 0){
                string key;
                cout << "Key: ";
                cin >> key;

                RMRef_H ref = rmLib->rm_get((char*)key.c_str());
                cout << "Respuesta: " << ref << endl << endl;

            } else if (strcmp(action, "3") == 0) {
                string key;
                cout << "Key: ";
                cin >> key;

                string response = rmLib->rm_delete((char*)key.c_str());
                cout << "Respuesta: " << response << endl << endl;

            } else if (strcmp(action, "4") == 0) {
                rmLib->close();
                break;
            }
        }
    }



    /*SocketClient* conexion = new SocketClient();
    conexion->connect("127.0.0.1", 4050);

    while(true) {
    string mensaje;
    cout << "Escriba su mensaje: ";
    cin >> mensaje;

    char* holaMundo = strdup(mensaje.c_str());

    if(mensaje.size() > 0)
        if(strcmp(holaMundo, "exit") == 0){
            break;
        }

    conexion->sendMessage(holaMundo);
    cout << conexion->getResponse() << endl;
    }*/
    return 0;
}