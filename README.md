# Descripción del Proyecto
Este repositorio contiene la implementación de una arquitectura de red basada en el modelo cliente-servidor. El proyecto simula un escenario real de supervisión industrial donde un servidor transmite datos de un sensor de temperatura a un cliente desarrollado en C++ mediante sockets TCP/IP.

El flujo de trabajo automatiza el despliegue de un servidor en Python que actúa como una cámara térmica industrial, la conexión de un cliente en C++ para la ingesta de los datos en tiempo real, y el posterior volcado de esta información en un archivo de texto local para su almacenamiento.

# Estructura de Archivos
cliente.cpp: Código fuente del programa cliente desarrollado en C++. Se encarga de crear el socket, establecer la conexión, recibir los datos mediante la función recv(), almacenarlos temporalmente en un vector dinámico y finalmente guardarlos en disco.

ServidorCamara.py: Script en Python que simula el dispositivo Edge (cámara térmica). Levanta un servidor TCP/IP en la dirección IP local (127.0.0.1) y el puerto 12345, enviando un array de 768 valores de punto flotante (float) al cliente que se conecte.  

bash.sh: Script de automatización en Bash para compilar el código fuente, ejecutar los procesos de forma sincronizada y limpiar el entorno al finalizar.  

datos_temperatura.txt: Archivo generado automáticamente por el cliente tras una ejecución exitosa, el cual contiene las lecturas térmicas almacenadas secuencialmente. 

# Requisitos Previos (Prerrequisitos)
Para ejecutar este proyecto correctamente en un entorno Linux o similar, asegúrate de contar con los siguientes componentes instalados en tu sistema:

Compilador g++ (para compilar el código C++).

Intérprete de Python 3 (para ejecutar el servidor).

Consola compatible con Bash (para lanzar el script de automatización).

## Instrucciones de Ejecución
Opción 1: Ejecución Automatizada (Recomendada)

Para evitar problemas de sincronización entre el cliente y el servidor, se recomienda encarecidamente utilizar el script Bash proporcionado.

Abre una terminal y navega hasta el directorio donde se encuentran los archivos.

Otorga permisos de ejecución al script:
chmod +x bash.sh

Ejecuta el script:
./bash.sh

El script se encargará automáticamente de compilar el cliente, iniciar el servidor Python en segundo plano, ejecutar el binario C++, y finalmente limpiar los procesos y liberar el puerto de red.

## Opción 2: Ejecución Manual

Si deseas ejecutar los procesos de manera manual para observar el flujo paso a paso, sigue este orden estricto:

Compila el cliente C++:
g++ cliente.cpp -o cliente

En una terminal, inicia el servidor Python:
python3 ServidorCamara.py

Abre una nueva terminal y ejecuta el cliente:
./cliente

Una vez finalizada la ejecución, vuelve a la terminal del servidor Python y detenlo usando Ctrl+C.

# Salida Esperada
Al ejecutar el proyecto de forma exitosa, observarás lo siguiente en tu terminal:

Mensajes de confirmación de establecimiento de conexión TCP/IP.

El cliente C++ mostrará los datos por pantalla para su verificación.  

El programa generará (o sobrescribirá) el archivo datos_temperatura.txt en el mismo directorio de ejecución, confirmando que la persistencia de datos se ha realizado correctamente.