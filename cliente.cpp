#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

using namespace std;

// Función para crear el socket TCP/IP
int crearSocket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error al crear el socket" << endl;
    }
    return sockfd;
}

// Función para configurar la dirección del servidor
bool configurarDireccion(struct sockaddr_in &serv_addr, const char* ip, int puerto) {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto);
    
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        cerr << "Direccion invalida o no soportada" << endl;
        return false;
    }
    return true;
}

// Función para conectar con el servidor
bool conectarServidor(int sockfd, const struct sockaddr_in &serv_addr) {
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        cerr << "Error al conectar" << endl;
        return false;
    }
    return true;
}

// Función para recibir los datos
vector<float> recibirDatos(int sockfd) {
    vector<float> floats;
    float buffer;
    
    // El cliente recibe los datos con recv() en un bucle hasta que el servidor finaliza
    while (recv(sockfd, &buffer, sizeof(buffer), 0) > 0) {
        floats.push_back(buffer); // Los datos recibidos se almacenan en un vector (array dinámico) en memoria
    }
    return floats;
}

// Función para guardar los datos en archivo
void guardarDatos(const vector<float>& datos, const string& nombreArchivo) {
    ofstream archivoSalida(nombreArchivo); // Los datos se guardan en un archivo de texto (ofstream)
    if (archivoSalida.is_open()) {
        for (float f : datos) {
            archivoSalida << f << "\n";
        }
        archivoSalida.close();
        cout << "Los datos se han guardado correctamente en: " << nombreArchivo << endl;
    } else {
        cerr << "Error al abrir el archivo para escritura." << endl;
    }
}

// Función para imprimir los resultados
void imprimirResultados(const vector<float>& datos) {
    cout << "Numeros de punto flotante recibidos:" << endl;
    for (float f : datos) {
        cout << f << endl; // El cliente muestra los datos por pantalla para su verificación
    }
}

int main() {
    // 1. Crear un socket TCP/IP
    int sockfd = crearSocket();
    if (sockfd == -1) {
        return 1;
    }

    // 2. Configurar la dirección y el puerto del servidor
    struct sockaddr_in serv_addr;
    // La dirección IP corresponde a la que se muestra en el código base
    if (!configurarDireccion(serv_addr, "127.0.0.1", 12345)) {
        close(sockfd);
        return 1;
    }

    // 3. Conectar al servidor
    if (!conectarServidor(sockfd, serv_addr)) {
        close(sockfd);
        return 1;
    }
    cout << "Conectado al servidor con exito." << endl;

    // 4. Recibir los datos del servidor
    vector<float> datos_recibidos = recibirDatos(sockfd);

    // 5. Guardar los datos en un archivo de texto
    guardarDatos(datos_recibidos, "datos_temperatura.txt");

    // 6. Imprimir los números recibidos
    imprimirResultados(datos_recibidos);

    // 7. Cerrar la conexión y finalizar
    close(sockfd);
    cout << "Conexion cerrada. Fin del programa." << endl;

    return 0;
}