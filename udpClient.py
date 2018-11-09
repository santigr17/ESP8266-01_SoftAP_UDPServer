"""
Instituto Tecnológico de Costa Rica
Area acdémica de Ingeniería en Computadores
omputer Engineering

Profesor: Milton Villegas Lemus
Curso: Taller de programación

Autor: Santiago Gamboa Ramírez

Versión python: 3.6.4
2018
"""
import socket
import sys
import time

UdpIp = "192.168.4.7"   # Dirección Ip estática del servidor
UdpPort = 7070          # Puerto por donde espera la conexión el servidor
bufferSize = 1024       # Tamaño máximo de bits leídos

def UdpMessage(mns):
    """
    Función que crea un cliente udp para conectar con el servidor, envía un mensaje y espera una respuesta.
    Todo mensaje tienen una respuesta.
    Se espera una respuesta por 2 segundos, si no se reciben datos se reintenta enviar el mensaje. se reintenta hasta un total de 10 veces.
    Sino retorna vacío.
    Si el mensaje proviene del serial comienza con "Serial:". Si no hay nada escrito en el serial, el servidor responde "ok;"
    
    Input: Mensjae que se desea enviar al servidor.
    Output: Respuesta del servidor
    Restrictions: El tamaño máximo del mensaje son 1024 bits. Se debe estar conectado a la red creada por el servidor.
    
    """
    count = 1
    msg = ""
    while count < 10:
        try:
            print("Try n°{0} to send message".format(count))
            myUdpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            myUdpSocket.sendto(mns.encode(),(UdpIp, 7070))    
            count+=1
            # Se configura para esperar 2 segundos por un mensaje de vuelta.
            myUdpSocket.settimeout(2)
            # Función para recibir datos del tamaño del buffer
            msgFromServer = myUdpSocket.recvfrom(bufferSize)
            #Convertir los bytes a string
            msg = msgFromServer[0].decode("utf-8")
            if('\x00' in msg): ### '\x00' carater nulo.
                ### rstrip elimina caracteres nulos agregados al final.
                msg = msg.rstrip('\x00')
            print("Message from Server {0}".format(msg))
            count = 10
        except socket.timeout:
            #Si no se logra conectar con el servidor
            print("Not response!")
            myUdpSocket.close()
    return msg


