## 03-05-2023
### Análisis de código y división de tareas parte 1
Modificar el .ned: Benja
Modificar los .cc: Gastón
Correr los experimentos: Facu
Avanzar con el informe: todos a la par

## 04-05-2023 
22:44 Gastón:  
cambios en los .cc, especificamente:
- cambios del tipo cMessage a cPacket en Generator.cc según como dicta la consigna
- cambios en Queue.cc para solo encolar paquetes de tamaño aceptable también como dicta la consigna

22:50 Benjamin:
- Modificacion en el network.ned acorde a la consigna
- Primer modificacion del omnetpp.ini 

23:30 Benjamin:
- El network.ned tenia una falla la cual no note y Gaston pudo solucionar (Me olvide de dos ;)
- Modificacion del omnetpp.ini acorde a la consigna.

23:51 Gastón:
- Compilamos y falló. En `Queue.cc` cambiaos en la linea 60:
`par("bufferSize").longValue` por `.intValue()`
- Agregamos los parametros que faltaban a los .ned

## 06-05-2023
19:31 Todos:
- Tuvimos una profunda reflexion sobre Stuart Little
- En base a la profunda reflexion tuvimos un debate sobre el valor del arte

20:20 Todos:
Fuimos decicidiendo que valores registrar para hacer los analisis.
- packetes enviaos desde generador (packetGenVector)
- packetes recibidos en sink (packetsReceivedVector)
- estos dos parametros ayudan a ver la carga transmitida vs la carga recibida 
- ya de la parte anterior registranmos el tamaño de la queue y los paquetes dropeados.
  
21:28 Todos:
Genereamos la primera tanda de datos para el caso 1 con media 0.1
nota imporante para los formatos:
el formato de archivo es `CasoNUMERODECASO_MEDIASINPUNTO`
la media sin punto es en vez de `0.1` ponemos `01`

## 07-05-2023
18:18 Gastón:
Generamos los datos del caso 1 para media 0.2 a 0.5 en saltos de 0.1 


