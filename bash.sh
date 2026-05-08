#!/bin/bash

# Script para automatizar la ejecución de la Práctica 3
# Levanta el servidor, compila/ejecuta el cliente, y limpia los procesos al terminar.

SERVIDOR="ServidorCamara.py"
CLIENTE="cliente.cpp"
EJECUTABLE="./cliente"

echo "--- Iniciando entorno de pruebas ---"

# Comprobar que los archivos existan para no lanzar errores feos
if [ ! -f "$SERVIDOR" ]; then
    echo "Error: No encuentro el archivo $SERVIDOR. ¿Estás en la carpeta correcta?"
    exit 1
fi

if [ ! -f "$CLIENTE" ]; then
    echo "Error: No encuentro el archivo $CLIENTE."
    exit 1
fi

# 1. Compilar el código C++
echo "Compilando $CLIENTE..."
g++ $CLIENTE -o cliente

if [ $? -ne 0 ]; then
    echo "Error de compilación. Revisa la sintaxis de tu código C++."
    exit 1
fi

# 2. Levantar el servidor Python en segundo plano
echo "Iniciando servidor Python..."
python3 $SERVIDOR &
PID_PYTHON=$!

# Pausa de 2 segundos para asegurar que el socket del servidor esté escuchando
sleep 2

# 3. Ejecutar el cliente
echo "Ejecutando cliente..."
echo "------------------------------------------------"
$EJECUTABLE
ESTADO_CLIENTE=$?
echo "------------------------------------------------"

if [ $ESTADO_CLIENTE -eq 0 ]; then
    echo "Ejecución del cliente finalizada correctamente."
else
    echo "Aviso: El cliente terminó con código de error ($ESTADO_CLIENTE)."
fi

# 4. Matar el proceso del servidor para no dejar el puerto ocupado
echo "Limpiando procesos (cerrando PID $PID_PYTHON)..."
kill $PID_PYTHON 2>/dev/null

echo "--- Fin del script ---"