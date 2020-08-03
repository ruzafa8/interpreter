#pragma once

typedef struct Variable{
	char * name;
	int value;
	struct Variable *next;
} Variable;

Variable * createTable();

void insertVariable(char *, int, Variable**);

int valueOf(char *, const Variable*);

void printTable(const Variable *);
