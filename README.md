Room Sensor-Board (esp) : Componente che si occupa di gestire la stanza. Sensori che lo compongono : 
 1) Green Led
 2) Pir
 3) Photoresistor
 
 Se qualcuno entra all'interno della stanza e la stanza è buia la luce deve accendersi e quando la persona esce si spegne. 
 La board ESP comunica con Room Service attraverso MQTT/HTTP fornendogli le informazioni riguardo 
 i periodi nella quale la luce era accesa e per quanto tempo
 "
 {
   "STATUS":"ON"
   "TIME":"xx:yy"
 }
 
 {
   "STATUS":"OFF
   "TIME":"xx:yy"
 }
 
 "
 
 ----
 
 Room Controller (arduino) : Controller che si interfaccia tra server e applicazione mobile. Componenti hardware : 
 1) Green Led
 2) 1 Servomotor
 3) 1 Bluetooth module 
Il servo motore controlla la simulazione del motore per la tapparella, 0 gradi vuol dire che è completamente su, 180 gradi vuol dire che è completamente giù. Il led emula il sistema di illuminazione


----

 Room Service : 
 Comunicazione HTTP con il Room Sensor Board
 Comunicazione Seriale con il Room Controller
 
 
 ----
 
 Room App : 
 La comunicazione con Arduino è attraverso BT
 
 
 ----
 
 Room Dashboard : 
 Puo per esempio essere una web app che mostra 
