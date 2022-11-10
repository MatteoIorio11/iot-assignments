 Si ha un ponte sopra ad un fiume. Vogliamo modellare una soluzione di un ponte "smart".
  C'è un smart light system, rappresentato dai led. Queste luci devono attivarsi in base alla presenza di persone sul ponte. LED - La. 
  Le persone vengolo rilevate attraverso il pir P. La viene acceso o spento in base alla presenza di luce rilevata da Ls (foto-resistore)
  La luce viene accesa per T1 secondi e se non viene rilevata piu nessuna persona la luce deve essere spenta oppure se c'è abbastanza luce.


  La seconda parte che si vuole modellare è la misurazione dell'acqua. Si utilizza un sonar S per rilevare il livello dell'acqua. Lo si campiona con una frequenza X in base allo 
  stato in cui ci troviamo. 
  ( Il servomotre rappresenta una concezione di valvola per redirigere l'acqua in caso di pericolo, quando il livello è troppo alto. )
  Quando il livello misurato è sotto una certa soglia WaterLevel1 WL1, il led Lb è acceso ed il led rosso è spento.
  Non appena il livello dell'acqua sale ed è : WL1 =< LIVELLO_ACQUA < WL2 , si attiva uno stato di pre allarme. Si attiva Lc, lampeggiando e aumenta il periodo di campionamento 
  si attiva in oltre il display LCD, sul quale viene visualizato un messaggio riguardante il livello dell'acqua   
  Se il livello dell'acqua si abbassa si ritorna nello stato normale non di pericolo. Se il livello dell'acqua si alza ancora, si passa nello stato di allarme. Si spegne 
  completamente il sistema riguardante le luci attivate dalla presenza di uomini. Il led rosso è sempre acceso. 
  Attraverso il servo-motore si dovrà aprire una valvola che permetterà di scaricare l'acqua. L'angolo verrà deciso in base alla gravità della situazione, in base al 
  livello dell'acqua, per esempio WL2 angolo = 0, se siamo nel caso di WLMAX l'angolo = 180. Sul display verrà visualizzato l'angolo di apertura del nostro motore.

  Durante lo stato di allarme, si può premere il pulsante ed utilizzare il potenziometro per regolare l'angolo del servomotore, e ricliccando il bottone questa funzionalità si 
  blocca. 


  Il nostro arduino è conneso attraverso una linea seriale ad un altro PC, bisogna leggere lo stato del nostro ponte.
  * Visualizzare i dati su console
  * Output grafico, in cui viene visualizzato un grafico con l'andamento del water level, in base al tempo
  * Posso regolare il grado di angolazione del potenziometro dal PC fisico, quando si è nello stato di emergenza, per esempio attraverso uno slider.


  Ogni componente ha un proprio stato, verrà rappresentato attraverso l'implementazione di Tasks. Per ogni componente è obbligatorio avere il proprio diagramma di stato