#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Variable * createTable(){
	return NULL;
}

bool exists(char * name, Variable* table){
	bool exists = false;
	while(table != NULL && !(exists = strcmp(table->name,name) == 0)) table = table->next;
	return exists;
}

bool insertVariable(char * name, int value, Variable** table){
	bool notExists = !exists(name, *table);
	if(notExists){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(name);
		new->value = value;
		new->next = *table;
		*table = new;
	}
	return notExists;
}

bool valueOf(char * name, int* value, const Variable* table){
	while(table != NULL && strcmp(table->name, name) != 0)
		table = table->next;
	if(table != NULL) 
		*value = table->value;
	return table != NULL;
}

bool modify(char *name, int value, Variable* table){
	while(table != NULL && strcmp(table->name, name) != 0)
		table = table->next;
	if(table != NULL) 
		table->value = value;

	return table != NULL;
}

void printTable(const Variable *t){
	printf("\n"); printf("--------------- TABLA DE VARIABLES ---------------\n");
	while(t != NULL){
		printf("%s = %d\n",t->name,t->value);
		t = t->next;
	}
	printf("---------------------------------------------------");
}
