Room Sensor-Board (esp) : Componente che si occupa di gestire la stanza. Sensori che lo compongono : 
 1) Green Led
 2) Pir
 3) Photoresistor
 
 Se qualcuno entra all'interno della stanza e la stanza è buia la luce deve accendersi e quando la persona esce si spegne. 
 La board ESP comunica con Room Service attraverso MQTT/HTTP fornendogli le informazioni riguardo 
 
 Room Controller (arduino) : Controller che si interfaccia tra server e applicazione mobile. Componenti hardware : 
 1) Green Led
 2) 1 Servomotor
 3) 1 Bluetooth module 
