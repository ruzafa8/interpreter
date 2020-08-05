#include "expression_ast.h"
ExpressionAST* createUnary(UnaryOperator op, ExpressionAST* operand){
	ExpressionAST* ast = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	ast->type = UNARY;
	ast->value.unary = (UnaryExpressionAST*) malloc(sizeof(UnaryExpressionAST));
	ast->value.unary->op = op;
	ast->value.unary->value = operand;
	return ast;
}

ExpressionAST * createBinary(BinaryOperator op, ExpressionAST* left, ExpressionAST* right){
	ExpressionAST* ast = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	ast->type = BINARY;
	ast->value.binary = (BinaryExpressionAST*) malloc(sizeof(BinaryExpressionAST));
	ast->value.binary->op = op;
	ast->value.binary->leftValue = left;
	ast->value.binary->rightValue = right;
	return ast;
}

ExpressionAST* createLeaf(int e){
	ExpressionAST* ast = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	ast->type = LITERAL;
	ast->value.e = e;
	return ast;
}

ExpressionAST* createVariable(char * name){
	ExpressionAST* ast = (ExpressionAST*) malloc(sizeof(ExpressionAST));
	ast->type = VARIABLE;
	ast->value.name = strdup(name);
	return ast;
}

/*********        EVALUATION        *********/

int evaluateUnary(UnaryExpressionAST * e, Variable* context){
	switch(e->op){
		case MINUS_UNARY_OP:
			return - evaluate(e->value, context);
	}
}

int evaluateBinary(BinaryExpressionAST * e, Variable* context){
	switch(e->op){
		case PLUS_OP:
			return evaluate(e->leftValue, context) + evaluate(e->rightValue, context);
		case MINUS_BINARY_OP:
			return evaluate(e->leftValue, context) - evaluate(e->rightValue, context);
		case BY_OP:
			return evaluate(e->leftValue, context) * evaluate(e->rightValue, context);
		case DIV_OP:
			return evaluate(e->leftValue, context) / evaluate(e->rightValue, context);
	}
}

int evaluateVariable(char * name, Variable* context) {
	int value;
	if(!valueOf(name,&value,context)) {printf("La variable no existía"); exit(0);}
	return value;
}
int evaluate(ExpressionAST *e, Variable* context) {
	switch(e->type){
		case UNARY:
			return evaluateUnary(e->value.unary, context);
		case BINARY:
			return evaluateBinary(e->value.binary, context);
		case LITERAL:
			return e->value.e;
		case VARIABLE:
			return evaluateVariable(e->value.name, context);
	}
}
