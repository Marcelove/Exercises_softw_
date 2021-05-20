#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "b.h"

int main(int argc, char * argv[])
{

        resultado = fopen("result.txt", "w");

        errorr = 0;

        char c;

        int **maximum;
        int **allocation;
        int **need;

        //------------------------
        int **allocation2;
        //------------------------


        int clienteAtual;

        int resourcesFlag[argc-1];
        int resources[argc-1];
        int duplicatas[argc-1];

        int a, b, limite = argc, clientes;

        //Register resources
        for (a=1; a < limite; a++){ 
                resources[a-1] = atoi(argv[a]);
                resourcesFlag[a-1] = resources[a-1];
        }

        limite = argc-1;//update resources range

        customer = fopen("customer.txt", "r");
        clientes = lines(customer)+1; //ler numero de clientes 
        fclose(customer);

        maximum = malloc(clientes * sizeof * maximum);
        for (a=0; a<clientes; a++)
        {
                maximum[a] = malloc(clientes* sizeof * maximum[a]);
        }

        allocation = malloc(clientes * sizeof * allocation);
        for (a=0; a<clientes; a++)
        {
                allocation[a] = malloc(clientes * sizeof * allocation[a]);
        }

        need = malloc(clientes * sizeof * need);
        for (a=0; a<clientes; a++)
        {
                need[a] = malloc(clientes * sizeof * need[a]);
        }

        //---------------------------------------

        allocation2 = malloc(clientes * sizeof * allocation2);
        for (a=0; a<clientes; a++)
        {
                allocation2[a] = malloc(clientes * sizeof * allocation2[a]);
        }

        //---------------------------------------

        customer = fopen("customer.txt", "r");
        pegadigitos(customer, maximum, clientes, limite);//coletar os maximos e jogar na matriz
        fclose(customer);

        updateneed(maximum, allocation, need, clientes, limite);
        
        commands = fopen("commands.txt", "r");

        updateavailable(allocation, resources, clientes, limite);

        int request = 0;
        int release = 0;

        while((c = getc(commands)) != EOF){

                updateneed(maximum, allocation, need, clientes, limite);

                if (c== 'R'){
                        request++;
                        release++;
                }

                else if ((c == 'Q') && (request != 0)){
                        request = 2;
                        release = 0;
                }

                else if ((c == 'L') && (release != 0)){
                        request = 0;
                        release = 2;
                }

                else if (request == 2){

                        for(a=0; a<clientes; a++){
                                for(b=0; b<limite; b++){
                                        allocation2[a][b] = allocation[a][b];
                                }
                        }

                        //takeRequest(commands, matriz, clientes, limite, resources);
                        clienteAtual = takeRequest(commands, allocation, clientes, limite, duplicatas);

                        //verifica se os recursos disponíveis ficariam OK
                        verifyavailable(allocation, resourcesFlag, clientes, limite);

                        if(errorr == 0){

                                //reseta resources
                                for(a=0; a<limite; a++){
                                        resources[a] = resourcesFlag[a];

                                }

                                updateavailable(allocation, resources, clientes, limite);
                                updateneed(maximum, allocation, need, clientes, limite);

                                verifysafety(need, resources, clientes, limite);

                                if (errorr == 5){//The customer 0 request 0 2 0 was denied because result in an unsafe state
                                    fprintf(resultado,"The customer %d request ", clienteAtual);

                                    for(a=0; a<limite; a++){
                                        fprintf(resultado,"%d ", duplicatas[a]);
                                    }

                                    fprintf(resultado,"was denied because result in an unsafe state\n");

                                    for(a=0; a<clientes; a++){
                                        for(b=0; b<limite; b++){
                                                allocation[a][b] = allocation2[a][b];
                                        }
                                    }

                                }

                                else{

                                        verifymaximum(allocation, maximum, clientes, limite);

                                        if(errorr == 7){

                                                fprintf(resultado,"The customer %d request ", clienteAtual);

                                                for(a=0; a<limite; a++){
                                                        fprintf(resultado,"%d ", duplicatas[a]);
                                                }

                                                fprintf(resultado,"was denied because exceed its maximum allocation\n");

                                                for(a=0; a<clientes; a++){
                                                        for(b=0; b<limite; b++){
                                                                allocation[a][b] = allocation2[a][b];
                                                        }
                                                }
                                        }

                                        else{
                                                fprintf(resultado,"Allocate to customer %d the resources ", clienteAtual);

                                                for(a=0; a<limite; a++){
                                                        fprintf(resultado,"%d ", duplicatas[a]);
                                                }

                                                fprintf(resultado,"\n");
                                        }


                                }
                        }
                        else{

                                if(errorr == 2){
                                        fprintf(resultado,"The resources ");

                                        for(a=0; a<limite; a++){
                                                fprintf(resultado,"%d ", resources[a]);
                                        }

                                        fprintf(resultado,"are not enough to costumer %d request ", clienteAtual);

                                        for(a=0; a<limite; a++){
                                                fprintf(resultado,"%d ", duplicatas[a]);
                                        }

                                        fprintf(resultado,"\n");


                                }

                                for(a=0; a<clientes; a++){
                                        for(b=0; b<limite; b++){
                                                allocation[a][b] = allocation2[a][b];
                                        }
                                }
                        
                        }

                        request = 0;
                        errorr=0;
                }

                else if (release == 2){
                        //takeRelease(commands, matriz, clientes, limite);
                        clienteAtual = takeRelease(commands, allocation, clientes, limite, duplicatas);

                        if(errorr == 0){

                                fprintf(resultado,"Release from customer %d the resources ", clienteAtual);

                                for(a=0; a<limite; a++){
                                        fprintf(resultado,"%d ", duplicatas[a]);
                                }

                                fprintf(resultado,"\n");
                        }

                        release = 0;
                        errorr=0;
                }

                else if (c == '*'){

                        printaMatriz(maximum, allocation, need, clientes, limite);

                        
                        fprintf(resultado,"AVAILABLE ");
                        
                        for(a=0; a<limite; a++){
                                fprintf(resultado,"%d ", resources[a]);
                                //resources[a] = resourcesFlag[a];
                        }


                       fprintf(resultado,"\n");
                       
                }
                
                
        }

        fclose(commands);
        fclose(resultado);

}
