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
18:24 
Generamos los datos del caso 2 para media 0.1 a 0.5 en saltos de 0.1

## 10-05-2023
Gastón:
Hoy modificamos el notebook del aula virtual para poder generar los gráficos
Generamos los gráficos de delay y de comparación de bufferSize

## 12-05-2023 
Gastón 00:24 
Hoy estuve a full con automatizar la corrida de las simulaciones  
En la carpeta lab3python hice un notebook que pide una banda de cosas y corre todo automatico
Las cosas que pide estan explicadas en el notebook y ojo que algunas son medio raras  
Fue dificil pero no fue PARA NADA en vano  

Gastón 15:24 
Hice una banda de gráficos que incluyen
Caso1 y caso2:
  - bufferSize 
  - Delays
Vemos en que punto cambian los graficos del paso 0.2 a 0.3  
Graficos para comparar como varia el segun el servicetime

18:10 
Empece el informe
Graficos para paqeutes
Graficos para carga util 
Espero mejorar la carga util

## 15-05 
Benja:
empezar los cambios parte 2 

Benja y Gaston:
Estuvimos pensando que algoritmo implementar y llegamos a dos opciones similares basadas en un umbral dado por los tamaños de los buffers: 
- Primera opcion: dar un umbral fijo al ejecutar que se puede cambiar de sim en sim  
- Segunda opcion: dar un umbral que arranca fijo y va incrementando de a poquito  
La idea es que una vez cruzado el ubmral se disminuye la tasa de envio.  


