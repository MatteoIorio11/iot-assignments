## Room Sensor-Board (esp)
Componente che si occupa di gestire la stanza. Sensori che lo compongono : 
 1) Green Led
 2) Pir
 3) Photoresistor
 
 Se qualcuno entra all'interno della stanza e la stanza è buia la luce deve accendersi e quando la persona esce si spegne. 
 La board ESP comunica con Room Service attraverso MQTT/HTTP fornendogli le informazioni riguardo.
 
 Room Sensor-Board -- MQTT/HTTP --> Room Service
 
 Deve inviare un messaggio al server quando la luce si accende e quando la luce si spegne. 

 
 ----
 
## Room Controller (arduino)
Controller che si interfaccia tra server e applicazione mobile. Componenti hardware : 
 1) Green Led
 2) 1 Servomotor
 3) 1 Bluetooth module 
Il servo motore controlla la simulazione del motore per la tapparella, 0 gradi vuol dire che è completamente su, 180 gradi vuol dire che è completamente giù. Il led va acceso o spento tramite l'applicazione android. 

Room Service <-- SERIAL --> Room Controller <-- BLUETOOTH -- Room Mobile App


----

## Room Service 
 Comunicazione HTTP con il Room Sensor Board
 Comunicazione Seriale con il Room Controller
 
 Riceve le informazioni dal Room Sensor e inoltra queste informazioni al Room Dashboard
 <pre>

  Room Sensor-Board -- MQTT/HTTP --> Room Service <-- HTTP/TCP -- Room Dashboard
                                            |
                                            |
                                            |
                                            |
                                            V
                                      Room Controller 

</pre>
 


 ----
 
## Room App 
 La comunicazione con Arduino è attraverso BT, attraverso l'applicazione deve essere possibile accendere/spegnere il led del Room Controller e controllare il motore per le tapparelle. 
 
 
 ----
 
## Room Dashboard
Attraverso questo applicativo deve essere possibile controllare per quanto tempo la luce è stata accesa/spenta e deve inoltre essere possibile controllare la luce e il motore delle tapparelle. 
