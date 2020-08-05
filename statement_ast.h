#pragma once
#include"expression_ast.h"

typedef enum {
	PRINT_ST, DECL_ASIG_ST, DOUBLE_ST, ASIG_ST
} StatementType;

typedef struct {
	ExpressionAST * e;
} PrintSt;

typedef struct {
	char * name;
	ExpressionAST * e;
}DeclAsigSt; //Declaracion y asignación

typedef struct {
	struct StatementAST* first;
	struct StatementAST* second;
} DoubleSt;

typedef struct {
	char * name;
	ExpressionAST* value;
} AsigSt;

typedef union { 
	PrintSt* print_st;
	DeclAsigSt* decl_asig_st;
	DoubleSt* double_st;
	AsigSt * asig_st;
} StatementUnion;

typedef struct StatementAST{
	StatementUnion statement;
	StatementType type;
} StatementAST;

StatementAST * createPrintSt(ExpressionAST *);
StatementAST * createDeclAsigSt(char*,ExpressionAST*);
StatementAST * createDoubleSt(StatementAST *,StatementAST *);
StatementAST * createAsigSt(char*,ExpressionAST*);

void execute(StatementAST*,Variable**);
