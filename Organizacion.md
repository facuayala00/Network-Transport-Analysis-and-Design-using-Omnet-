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

## 06-04-2023
19:31 Todos:
- Tuvimos una profunda reflexion sobre Stuart Little
- En base a la profunda reflexion tuvimos un debate sobre el valor del arte
 
