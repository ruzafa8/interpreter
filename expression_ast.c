#include "expression_ast.h"
#include <stdlib.h>
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
	ast->type = NON_OPERATOR;
	ast->value.e = e;
	return ast;
}

/*********        EVALUATION        *********/

int evaluateUnary(UnaryExpressionAST * e){
	switch(e->op){
		case MINUS_UNARY_OP:
			return - evaluate(e->value);
	}
}

int evaluateBinary(BinaryExpressionAST * e){
	switch(e->op){
		case PLUS_OP:
			return evaluate(e->leftValue) + evaluate(e->rightValue);
		case MINUS_BINARY_OP:
			return evaluate(e->leftValue) - evaluate(e->rightValue);
		case BY_OP:
			return evaluate(e->leftValue) * evaluate(e->rightValue);
		case DIV_OP:
			return evaluate(e->leftValue) / evaluate(e->rightValue);
	}
}
int evaluate(ExpressionAST *e) {
	switch(e->type){
		case UNARY:
			return evaluateUnary(e->value.unary);
		case BINARY:
			return evaluateBinary(e->value.binary);
		case NON_OPERATOR:
			return e->value.e;
	}
}
