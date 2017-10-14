//
// Created by arturocv on 13/10/17.
//

#include "RMLib.h"


RMLib* RMLib::instance = nullptr;
SocketClient* RMLib::server = nullptr;
SocketClient* RMLib::serverHA = nullptr;

RMLib::RMLib() {
}

/// Metodo para obtener la unica instancia de RMLib
/// \return
RMLib* RMLib::getInstance() {
    if (instance == nullptr){ //Caso en el que no se ha creado
        instance = new RMLib(); //Se instancia el RMLib
    }

    return instance;
}

/// Metodo para enviar un mensaje al servidor y recibir la respuesta
/// \param message Mensaje a enviar
/// \return La respuesta del servidor
string RMLib::sendRequest(string message) {
    //Se intenta conectar con los servidores si no estan conectados
    if(serverOnline == false){
        server->connect();
    }
    if(serverHAOnline == false){
        serverHA->connect();
    }

    int i = server->sendMessage(message.c_str()); //Se envia el mensaje al servidor activo
    string response;

    if(i < 0) { //Hubo un error al enviar el mensaje
        serverOnline = false; //Se indica que esta offline
        int j = serverHA->sendMessage(message.c_str()); //Se envia el mensaje al servidor pasivo
        if (j > 0){ //No hubo error al enviar el mensaje
            response = serverHA->getResponse();
        } else{ //Los dos servidores no estan disponibles
            serverHAOnline = false; //Se indica que esta offline
            response = "All servers offline";
        }
    } else{
        response = server->getResponse();
    }

    return response;
}

/// Metodo para conectarse a los servidores
/// \param ip IP del servidor activo
/// \param port Puerto del servidor activo
/// \param ipHA IP del servidor pasivo
/// \param portHA Port del servidor pasivo
void RMLib::rm_init(char *ip, int port, char *ipHA, int portHA) {
    server = new SocketClient(ip, port); //Se crea un nuevo socket para el servidor activo
    serverHA = new SocketClient(ipHA, portHA); //Se crea un nuevo socket para el servidor pasivo

    if(server->connect()){ //Se establece conexion con el servidor activo
        serverOnline = true;
    }
    if(serverHA->connect()){ //Se establece conexion con el servidor pasivo
        serverHAOnline = true;
    }
}

/// Metodo para almacenar una nueva referencia en el servidor
/// \param key Llave deseada para el nuevo elemento
/// \param value Valor del nuevo elemento
/// \param value_size Tamaño del nuevo elemento
/// \return La respuesta del servidor
string RMLib::rm_new(char *key, char *value, int value_size) {
    RMRef_H ref_h = RMRef_H(key, value, value_size); //Se forma una referencia

    std::string message = "store,";//Variable en la que guardar el mensaje
    std::string ref = ref_h.createString(); //Se obtiene el string de la referencia
    message.append(ref);

    return sendRequest(message); //Se envia el mensaje
}


/// Metodo para obtener una referencia del servidor
/// \param key Llave de la referencia a obtener
/// \return La referencia obtenida
RMRef_H RMLib::rm_get(char *key) {
    string message = "get,";//Variable en la que guardar el mensaje
    message.append(key);
    string response = sendRequest(message); //Se recibe la referencia

    LinkedList<char*> list = LinkedList<char*>(); //Lista en la que se guardar los elementos

    char *charRef = strdup(response.c_str()); //Se transforma el mensaje a char*
    char* element = strtok(charRef, ","); //Separa el char cuando lea la coma;
    while (element != NULL) {
        list.insertAtEnd(element); // Se guarda el dato en la lista
        element = strtok (NULL, ",");  // Separa el resto de la cadena cuando lea la coma
    }

    char* resp = list.getElement(0)->getData(); //Se obtiene la respuesta

    if(strcmp(resp, "obtained") == 0){
        //Se crea la referencia con los datos recibidos
        RMRef_H ref1 = RMRef_H(list.getElement(1)->getData(), list.getElement(2)->getData(), atoi(list.getElement(3)->getData()));
        return ref1;
    } else {
        RMRef_H ref2 = RMRef_H("null", "null", 0); //Se retorna una referncia nula
        return ref2;
    }
}

/// Metodo para eliminar una referencia
/// \param key Llave de la referencia
/// \return Respuesta enviada por el servidor
string RMLib::rm_delete(char *key) {
    string message = "erase,"; //Variable en la que se guarda el mensaje
    message.append(key); //Se el agrega el key de la referencia
    message.append(",value,0");
    string response = sendRequest(message); //Se envia la solicitud

    return response; //Se retorna la respuesta
}

///Metodo para desconectar la conexion con los servidores
void RMLib::close() {
    server->disconnect(); //Se desconecta del servidor activo
    serverHA->disconnect(); //Se desconecta del servidor pasivo
}