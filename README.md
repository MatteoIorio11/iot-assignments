## Room Sensor-Board (esp)
Componente che si occupa di gestire la stanza. Sensori che lo compongono : 
 1) Green Led
 2) Pir
 3) Photoresistor
 
 Se qualcuno entra all'interno della stanza e la stanza è buia la luce deve accendersi e quando la persona esce si spegne.
 La board ESP comunica con Room Service attraverso MQTT/HTTP fornendogli le indicazioni riguardo quando la luce si è accesa e quando la luce si è spenta facendo, calcolando quindi per quanto tempo la luce è rimasta accesa.
 
 <pre>
 Room Sensor-Board -- MQTT/HTTP --> Room Service
 </pre>
 
 
 ----
 
## Room Controller (arduino)
Controller che si interfaccia tra server e applicazione mobile. Componenti hardware : 
 1) Green Led
 2) 1 Servomotor
 3) 1 Bluetooth module 

Il servo motore controlla la simulazione del motore per la tapparella, 0 gradi vuol dire che è completamente su, 180 gradi vuol dire che è completamente giù. Il led va acceso o spento tramite l'applicazione android.
Le tapparelle (Servo) vengono tirate su automaticamente dopo le 8.00 se qualcuno entra e vengono tirate giù alle 19.00 se sono su e non c'è nessuno nella stanza in qual caso vengono tirate giù non appena la stanza viene liberata.
 
 <pre>
Room Service <-- SERIAL --> Room Controller <-- BLUETOOTH -- Room Mobile App
 </pre>


----

## Room Service (python)
 Comunicazione HTTP con il Room Sensor Board
 Comunicazione Seriale con il Room Controller
 
 Riceve le informazioni dal Room Sensor e inoltra queste informazioni al Room Dashboard.
 La comunicazione seriale serve per poter comandare il servomotore da remoto attraverso la Room Dashboard
 <pre>

  Room Sensor-Board -- MQTT/HTTP --> Room Service <-- HTTP/TCP -- Room Dashboard
                                            ┴
                                            |
                                            |
                                          SERIAL
                                            |
                                            |
                                            V
                                      Room Controller 

</pre>
 


 ----
 
## Room App (android)
 La comunicazione con Arduino è attraverso BT, attraverso l'applicazione deve essere possibile accendere/spegnere il led del Room Controller e controllare il motore per le tapparelle. 

 <pre>
 Room Controller <-- BLUETOOTH -- Room Mobile App
 </pre>


 
 ----
 
## Room Dashboard (js usando axios)
Attraverso questo applicativo deve essere possibile controllare per quanto tempo la luce è stata accesa/spenta ( Room Sensor Board ). Deve inoltre essere possibile controllare la luce e il motore delle tapparelle (Room Controller). 

 <pre>
Room Service <-- HTTP/TCP --> Room Dashboard
 </pre>

