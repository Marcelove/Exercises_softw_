#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "b.h"


void updateneed(int **maximum, int **allocation, int **need, int clientes, int limite)//atualizar o need
{
    int a, b;

    for(a = 0; a<clientes; a++){
        
        for(b=0; b<limite; b++){
            need[a][b] = maximum[a][b] - allocation[a][b];
        }
        
    }
}

int isDigit(char a)//indentificar digitos
{

        if ((a == '0') || (a == '1') || (a == '2') || (a == '3') || (a == '4') || (a == '5') || (a == '6') || (a == '7') || (a == '8') || (a == '9'))
                return 1;
        else
                return 0;
}



void pegadigitos(FILE *fp, int **matriz, int clientes, int limite)//extrair digitos
{
        int clienteAtual = 0, limiteAtual = 0, digitoAtual = 0;
        char c;

        for (c = getc(fp); c != EOF; c = getc(fp)){

                //printf("Estou lendo o %c\n", c);

                if (c == '\n'){
                        matriz[clienteAtual][limiteAtual] = digitoAtual;
                        //printf("peguei o %d\n", digitoAtual);

                        digitoAtual = 0;
                        clienteAtual++;
                        limiteAtual = 0;
                }

                else if (isDigit(c)){
                        digitoAtual = (digitoAtual *10) + (c - '0');
                }

                else if (c == ','){

                        matriz[clienteAtual][limiteAtual] = digitoAtual;

                        //printf("peguei o %d\n", digitoAtual);

                        digitoAtual = 0;
                        limiteAtual++;
                }

                else {
                        printf("Error: wrong format at customer.txt.\n");
                        exit(1);
                }
               
        }

       matriz[clienteAtual][limiteAtual] = digitoAtual;
}

void printaMatriz(int **maximum, int **allocation, int **need, int clientes, int limite)//printa as matrizes
{
        int a, b, yesirrr = limite*2, yesirrr2 = limite*2;

        //| ALLOCATION | NEED\n");

        fprintf(resultado,"MAXIMUM");

        for(a=0; a< (limite*2) -7; a++)
                fprintf(resultado," ");

        fprintf(resultado,"| ");

        fprintf(resultado,"ALLOCATION");

        for(a=0; a< (limite*2) -10; a++)
                fprintf(resultado," ");

        fprintf(resultado,"| ");

        fprintf(resultado,"NEED\n");

        for (a=0; a < clientes; a++){

                for(b=0; b < limite; b++){

                        fprintf(resultado,"%d ", maximum[a][b]);
                }

                while(yesirrr < 7){
                        fprintf(resultado," ");
                        yesirrr++;
                }
                yesirrr = limite*2;

                fprintf(resultado,"| ");

                for(b=0; b < limite; b++){

                        fprintf(resultado,"%d ", allocation[a][b]);
                }

                while(yesirrr2 < 10){
                        fprintf(resultado," ");
                        yesirrr2++;
                }
                yesirrr2 = limite*2;

                fprintf(resultado,"| ");

                for(b=0; b < limite; b++){

                        fprintf(resultado,"%d ", need[a][b]);
                }



                fprintf(resultado,"\n");
        }
}

int lines (FILE *fp)//retornar o número de clientes
{
        int count = 0;
        int prev = 0;
        char c;

        for (c = getc(fp); c != EOF; c = getc(fp)){
                if (c == '\n'){

                        count ++;
                        prev = 0;
                }

                else {
                        prev = 0;       
                }

                if (prev)
                        count ++;
        }
        return count;
}

void updateavailable(int **allocation, int *resources, int clientes, int limite)//atualizar recursos
{
        int a, b;
        int acumulador[limite];

        for(a=0; a<limite; a++){
                acumulador[a] = 0;
        }

        for(b=0; b<limite; b++){

                for(a=0; a<clientes; a++){
                        acumulador[b] += allocation[a][b];
                }
        }

        for(a=0; a<limite; a++){
                resources[a] -= acumulador[a];
        }

}

void verifyavailable(int **allocation, int *resources, int clientes, int limite)//atualizar recursos
{
        int a, b;
        int acumulador[limite];

        for(a=0; a<limite; a++){
                acumulador[a] = 0;
        }

        for(b=0; b<limite; b++){

                for(a=0; a<clientes; a++){
                        acumulador[b] += allocation[a][b];
                }
        }

        for(a=0; a<limite; a++){
                if ((resources[a] - acumulador[a]) < 0){
                        //printf("%d menos %d deu ruim\n",resources[a] , acumulador[a] );
                        errorr = 2;
                }
        }



}

int takeRequest(FILE *fp, int **allocation, int clientes, int limite, int *duplicatas)//realizar request
{
        int clienteAtual = 0, limiteAtual = 0, digitoAtual = 0, passada=0, a;
        char c;

        for (c = getc(fp); c != EOF; c = getc(fp)){

                if (c == '\n'){
                        allocation[clienteAtual][limiteAtual] += digitoAtual;
                        duplicatas[passada-1] = digitoAtual;

                        return clienteAtual;
                       
                }

                else if (isDigit(c)){

                        if(passada == 0)
                                clienteAtual = (clienteAtual *10) + (c - '0');
                        else
                                digitoAtual = (digitoAtual *10) + (c - '0');
                }

                else if (c == ' '){

                        if (passada == 0){
                                passada++;
                        }

                        else if(passada > limite){
                                printf("Error: mismatched number of arguments.\n");
                                exit(1);
                        }

                        else{

                                allocation[clienteAtual][limiteAtual] += digitoAtual;
                                duplicatas[passada-1] = digitoAtual;

                                digitoAtual = 0;
                                limiteAtual++;
                                passada++;
                        }
                }

                else {
                        printf("Error: wrong format at customer.txt.\n");
                        errorr=1;
                        return 0;
                }
               
        }

        allocation[clienteAtual][limiteAtual] += digitoAtual;
        duplicatas[passada-1] = digitoAtual;
       
        return clienteAtual;
}

int takeRelease(FILE *fp, int **allocation, int clientes, int limite, int *duplicatas)//realizar release
{
        int clienteAtual = 0, limiteAtual = 0, digitoAtual = 0, passada=0, a;
        char c;

        for (c = getc(fp); c != EOF; c = getc(fp)){

                if (c == '\n'){
                        allocation[clienteAtual][limiteAtual] -= digitoAtual;
                        duplicatas[passada-1] = digitoAtual;

                        return clienteAtual;
                       
                }

                else if (isDigit(c)){

                        if(passada == 0)
                                clienteAtual = (clienteAtual *10) + (c - '0');
                        else
                                digitoAtual = (digitoAtual *10) + (c - '0');
                }

                else if (c == ' '){

                        if (passada == 0){
                                passada++;
                        }

                        else if(passada > limite){
                                printf("Error: mismatched number of arguments.\n");
                                errorr=1;
                                return 0;
                        }

                        else{

                                allocation[clienteAtual][limiteAtual] -= digitoAtual;
                                duplicatas[passada-1] = digitoAtual;
                                
                                digitoAtual = 0;
                                limiteAtual++;
                                passada++;
                        }
                }

                else {
                        printf("Error: wrong format at customer.txt.\n");
                        errorr=1;
                        return 0;
                }
               
        }
       
}

void verifysafety (int **need, int *resources, int clientes, int limite)
{
    int a, b, count=0;

    for(a=0; a<clientes; a++){

        for(b=0; b<limite; b++){

            if((need[a][b] - resources[b]) <=0)
                count++;
        }

        if (count == limite)
            return;

        count = 0;
    }

    errorr = 5;

}

void verifymaximum(int **allocation, int **maximum, int clientes, int limite)
{
    int a, b;

    for(a=0; a<clientes; a++){

        for(b = 0; b < limite; b ++){

            if(allocation[a][b] > maximum[a][b]){
                errorr = 7;
                return;
            }
        }
    }
}
