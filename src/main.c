/* Contador de palavras
 *
 * Este programa recebera uma serie de caracteres representando palavras em sua
 * entrada. Ao receber um caractere fim de linha ('\n'), deve imprimir na tela o
 * numero de palavras separadas que recebeu e, apos, encerrar.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

int *vetorNum;
int *vetorZ;

void *funcao_thread1(void *count);
void *funcao_thread2(void *count);
void *funcao_thread3(void *count);
void *funcao_thread4(void *count);

int verificaPrimo(int numero){
    if (numero == 1 || numero == 0){
        return 0;
    }
    for (int i = 2; i < numero; i++){
        if (!(numero % i)){
            return 0;
        }
    }
    return 1;
}


int main(){
    int n;
    int count = 0;
    vetorNum = malloc(100 * sizeof(int));
    vetorZ = malloc(100 * sizeof(int));

    while (scanf("%d", &n) != EOF){
        vetorNum[count] = n;
        vetorZ[count] = 0;
        count++;
    }

    pthread_t p1, p2, p3, p4;

    void *arg = malloc(sizeof(int));
    *((int *)arg) = count;

    pthread_create(&(p1), NULL, funcao_thread1, arg);
    pthread_create(&(p2), NULL, funcao_thread1, arg);
    pthread_create(&(p3), NULL, funcao_thread1, arg);
    pthread_create(&(p4), NULL, funcao_thread1, arg);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    int primos = 0;

    for (int i = 0; i < count; i++)
    {
        if (vetorZ[i] == 2)
        {
            primos++;
        }
    }

    printf("%d\n", primos);
    return 0;
}

void *funcao_thread1(void *arg){
    int* count = (int*)arg;
    for (int i = 0; i < *(count); i++)
    {
        if (vetorZ[i] == 0)
        {
            vetorZ[i] = 1;
            if (verificaPrimo(vetorNum[i]))
            {
                vetorZ[i] = 2; //quer dizer que é primo
            }
        }
    }
    return NULL;
}
