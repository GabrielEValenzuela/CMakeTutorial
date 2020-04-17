#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <string.h>

static struct sqlite3* database;

int32_t init_conn(char* file_name){
    int32_t fd_db = sqlite3_open_v2(file_name,&database,SQLITE_OPEN_READWRITE,NULL);

    if(fd_db == SQLITE_OK){
        return 1;
    } else{
        return 0;
    }
}

void close_conn(){
    sqlite3_close(database);
}

void display_balance(){
	char account[8]={'\0'};
	printf("Ingrese número de cuenta (8 dígitos): ");
	scanf("%s",account);
	char* buffer = (char*)calloc(64,sizeof(char));
	snprintf(buffer,64,"SELECT balance FROM clients WHERE account='%s';",account);
	struct sqlite3_stmt* query_stmt;
	sqlite3_prepare_v2(database,buffer,-1,&query_stmt,NULL);
	int result =sqlite3_step(query_stmt);
	if(result == SQLITE_ERROR){
		sqlite3_finalize(query_stmt);
        free(buffer);
		return;
	}
	if(sqlite3_column_type(query_stmt,0) != SQLITE_INTEGER){
		sqlite3_finalize(query_stmt);
        free(buffer);
		return;
	}
	printf("El balance de la cuenta %s es de:US$ %d\n\n",account,sqlite3_column_int(query_stmt,0));
	sqlite3_finalize(query_stmt);
    free(buffer);
	return;
}

void make_transfer(){
	int32_t transfer = 0;
	printf("Ingrese cantidad: ");
	scanf("%d",&transfer);
	char* buffer = (char*)calloc(128,sizeof(char));
	snprintf(buffer,128,"UPDATE clients SET balance = ((SELECT balance FROM clients WHERE user='Krusty') + %d) WHERE user='Krusty';",transfer);
	struct sqlite3_stmt* query_stmt;
	sqlite3_prepare_v2(database,buffer,-1,&query_stmt,NULL);
    int result =sqlite3_step(query_stmt);
    if(result == SQLITE_ERROR){
		sqlite3_finalize(query_stmt);
		fprintf(stderr,"Error al realizar transferencia :( \n");
        free(buffer);
		return;
	}
	printf("Transferencia realizada con éxito !\n");
    free(buffer);
	sqlite3_finalize(query_stmt);
	return;
}
