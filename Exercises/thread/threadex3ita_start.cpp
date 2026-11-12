/*
compila con:
    g++ threadex3.cpp -lpthread -o thread3
   
esegui con:
    ./thread3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Inizializza il mutex utilizzato per proteggere la condizione e la variabile count

// Inizializza la variabile di condizione

// Dichiara le funzioni dei thread: functionCount1 e functionCount2

int count = 0;
int go = 0;
#define COUNT_DONE 10

int main()
{
    // Dichiara gli ID dei thread 1 e 2

    int rc1, rc2;

    // Crea due thread indipendenti, uno esegue functionCount1 e l'altro functionCount2

    // Attende che i thread siano completati prima che main continui

    printf("Valore finale del contatore: %d\n", count);
    return 0;
}

void* functionCount1(void*)
{
    // Continua solo fino al raggiungimento del limite
    while (count < COUNT_DONE)
    {
        // Blocca il mutex 

        // Finché la variabile go è 0, aspetta sulla condizione. Questo previene 
        // che segnali spurie facciano eseguire il thread in modo scorretto

        // Imposta la variabile go a 0
        
        // Incrementa count
        count++;
        printf("Valore del contatore functionCount1: %d\n", count);
        
        // Sblocca il mutex 
    }
    
    // Esci
}

void* functionCount2(void*)
{
    // Continua solo fino al raggiungimento del limite
    while (count < COUNT_DONE)
    {
        // Blocca il mutex 

        // Incrementa e stampa count
        count++;
        printf("Valore del contatore functionCount2: %d\n", count);

        // Imposta la variabile go a 1
        
        // Segnala all'altro thread

        // Sblocca il mutex

        // Dorme 1 secondo
        sleep(1);
    }

    // Assicura che il thread in attesa possa uscire se sta ancora aspettando

    // Esci
}

