#include"statement_ast.h"

StatementAST * createPrintSt(ExpressionAST * e){
	StatementAST* s = (StatementAST*) malloc(sizeof(StatementAST));
	s->type = PRINT_ST;
	s->statement.print_st = (PrintSt*) malloc(sizeof(PrintSt));
	s->statement.print_st->e = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	*(s->statement.print_st->e) = *e;
	return s;
}

StatementAST * createDeclAsigSt(char* n,ExpressionAST*e){
	StatementAST* s = (StatementAST*) malloc(sizeof(StatementAST));
	s->type = DECL_ASIG_ST;
	s->statement.decl_asig_st = (DeclAsigSt*) malloc(sizeof(DeclAsigSt));
	s->statement.decl_asig_st->e = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	*(s->statement.decl_asig_st->e) = *e;
	s->statement.decl_asig_st->name = strdup(n);
	return s;
}

StatementAST* createDoubleSt(StatementAST* s1,StatementAST* s2){
	StatementAST* s = (StatementAST*) malloc(sizeof(StatementAST));
	s->type = DOUBLE_ST;
	s->statement.double_st = (DoubleSt*) malloc(sizeof(DoubleSt));
	s->statement.double_st->first = s1;
	s->statement.double_st->second = s2;
	return s;
}

StatementAST * createAsigSt(char* name,ExpressionAST* value){
	StatementAST* s = (StatementAST*) malloc(sizeof(StatementAST));
	s->type = ASIG_ST;
	s->statement.asig_st = (AsigSt*) malloc(sizeof(AsigSt));
	s->statement.asig_st->name = strdup(name);
	s->statement.asig_st->value = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	*(s->statement.asig_st->value) = *value;
	
	return s;
}

// ---------------------------------------------------------------------------

void executePrintSt(PrintSt* st, Variable* context){
	printf("> %d", evaluate(st->e, context));
}

void executeDeclAsigSt(DeclAsigSt* st, Variable** context){
	bool inserted = insertVariable(st->name,evaluate(st->e, *context),context);
	if(!inserted) printf("La variable %s no se ha insertado porque ya existía",st->name);
}

void executeDoubleSt(DoubleSt* st, Variable** context){
	execute(st->first, context);
	execute(st->second, context);
}

void executeAsigSt(AsigSt* st, Variable* context){
	bool modified = modify(st->name, evaluate(st->value, context), context);
	if(!modified) printf("La variable %s no se ha modificado porque no existía",st->name);
}


void execute(StatementAST* s, Variable** context){
	switch(s->type){
		case PRINT_ST:
			executePrintSt(s->statement.print_st, *context);
			break;
		case DECL_ASIG_ST:
			executeDeclAsigSt(s->statement.decl_asig_st, context);
			break;
		case DOUBLE_ST:
			executeDoubleSt(s->statement.double_st, context);
			break;
		case ASIG_ST:
			executeAsigSt(s->statement.asig_st, *context);
			break;
	}
}
