/*
compila con:
	g++ threadex2.cpp -lpthread -o thread2
   
esegui con:
	./thread2
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

// dichiara la funzione incrementCounter

// inizializza il mutex

// queste variabili servono per creare una race condition
int counter = 0;
int temp;

int main()
{
    int rc1, rc2;
   
    // dichiara gli ID del thread 1 e del thread 2

    // crea due thread indipendenti, ognuno dei quali eseguirà la funzione incrementCounter

    // attende che i thread siano completati prima che main continui 

    return 0; 
}
 
void* incrementCounter(void *)
{
    for (int i=0; i < 100; i++)
    {
        // blocca il mutex (prova a vedere come cambia il comportamento se il mutex è presente o assente)

	// aggiorno temp e lo incremento di uno
        temp = counter; 
        temp = temp + 1;
   	
        // introduco in questo punto un ritardo di un secondo per aumentare la probabilità che avvenga una preemption
        // tra l'aggiornamento di temp e il conseguente aggiornamento di counter

        counter = temp;

        // stampo il valore del contatore

        // sblocco il mutex (prova a vedere come cambia il comportamento se il mutex è presente o assente)
    }
    return NULL;
}  
