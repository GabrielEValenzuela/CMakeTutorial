//
// Created by gabrielv on 9/4/20.
//

#include "../inc/system.h"
#include "../inc/database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE "../database.db"

void init_system(){
    printf("===== Bienvenido al sistema del banco de las islas caimán =====\n");
    printf("Changos hace muucho calor...\n");
    printf("Seleccione la operación a realizar:\n");
    char* input = (char*) calloc(4,sizeof(char));
    init_conn(DATABASE);

    do{
        display_commands();
        printf(">>> ");
        //scanf(" %16[^\n]%*c",input);
        scanf("%s",input);
        switch(choice(input)){
            case 1:
                display_balance();
                break;
            case 2:
                make_transfer();
                break;
            case -1:
                printf("\033[1;32m");
                printf("Gracias por usar el sistema del banco de Islas Caimán, por favor, no le diga al fisco\n");
                printf("\033[0m");
                free(input);
                close_conn();
                exit(0);
            default:
                printf("\033[1;31m");
                printf("Opción no valida, por seguridad se cerrará el sistema. Chau,chau\n");
                printf("\033[0m");
                free(input);
                close_conn();
                exit(0);
        }
    } while(1);
}

int8_t choice(char* input){
    if(strcmp(input,"01") == 0){
        return 1;
    }
    if(strcmp(input,"02") == 0){
        return 2;
    }
    if(strcmp(input,"99") == 0){
        return -1;
    }

    return 0;
}

void display_commands(){
    printf("\t 01 - Consultar balance\n");
    printf("\t 02 - Hacer transferencia a Krusty\n");
    printf("\t 99 - Salir del sistema\n");
}
