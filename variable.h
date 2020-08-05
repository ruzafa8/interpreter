#pragma once
#include"bool.h"

typedef struct Variable{
	char * name;
	int value;
	struct Variable *next;
} Variable;

Variable * createTable();

bool insertVariable(char *, int, Variable**);
bool valueOf(char *, int*, const Variable*);
bool modify(char *, int, Variable*);

void printTable(const Variable *);
