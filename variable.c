#include "variable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Variable * createTable(){
	return NULL;
}

void insertVariable(char * name, int value, Variable** table){
	Variable * new = (Variable*) malloc(sizeof(Variable));
	new->name = strdup(name);
	new->value = value;
	new->next = *table;
	*table = new;
}

int valueOf(char * name, const Variable* table){
	while(table != NULL && strcmp(table->name, name) != 0)
		table = table->next;
	if(table != NULL) 
		return table->value;
	return 0;
}

void printTable(const Variable *t){
	while(t != NULL){
		printf("%s = %d\n",t->name,t->value);
		t = t->next;
	}
}
