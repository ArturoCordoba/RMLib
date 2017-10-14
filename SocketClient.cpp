//
// Created by arturocv on 18/09/17.
//

#include "SocketClient.h"
#include "RMLib.h"

SocketClient::SocketClient(char* ip, int port) {
    SocketClient::ip = ip;
    SocketClient::port = port;
}

/// Metodo para conectar el cliente al servidor
/// \param ip IP del servidor
/// \param port Puerto del servidor
/// \return True si se establecio una conexion, false si no se pudo establecer
bool SocketClient::connect(){
    socketNum = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Se crea el socket
    if(socketNum < 0) //Es menor a cero si ocurre un fallo al crear el socket
        return false;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr(ip); //IP del servidor
    info.sin_port = ntohs(port); //Puerto del servidor
    memset(&info.sin_zero,0,sizeof(info.sin_zero));

    if((::connect(socketNum,(sockaddr*)&info,(socklen_t)sizeof(info))) < 0) //Se intenta establecer la conexion
        return false; //Fallo al conectar

    return true; //Se logro establecer la conexion
}

/// Metodo para enviar un mensaje al servidor
/// \param message Mensaje a enviar
int SocketClient::sendMessage(const char *message) {
    int i = send(socketNum, message, strlen(message), 0); //Se envia el mensaje
    return i;
}

/// Metodo para recibir un mensaje del servidor
/// \return
string SocketClient::getResponse() {
    string response;
    while (true) {
        char buffer[10] = {0}; //Se leen 10 caracteres
        int bytes = recv(socketNum, buffer, 10, 0);
        response.append(buffer, bytes);

        if(bytes == 0){
            close(socketNum);
        }

        if (bytes < 10) //caso en el que se ha leido el mensaje entero
            break; //se finaliza el ciclo
    }
    return response;
}

///Metodo para cerrar la conexion
void SocketClient::disconnect() {
    close(socketNum); //Se cierra el socket
}

