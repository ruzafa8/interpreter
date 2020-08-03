#pragma once

typedef enum {
	PLUS_OP, MINUS_BINARY_OP, BY_OP, DIV_OP
} BinaryOperator;

typedef enum {MINUS_UNARY_OP} UnaryOperator;

typedef enum {UNARY, BINARY, NON_OPERATOR} OperatorType;

typedef struct {
	BinaryOperator op;
	struct ExpressionAST * leftValue;
	struct ExpressionAST * rightValue;
} BinaryExpressionAST;

typedef struct {
	UnaryOperator op;
	struct ExpressionAST * value;
} UnaryExpressionAST;

union UnionExpressionAST{
	int e;
	BinaryExpressionAST * binary;
	UnaryExpressionAST  * unary;
};

typedef struct ExpressionAST {
	OperatorType type;
	union UnionExpressionAST value;
} ExpressionAST;


ExpressionAST* createLeaf(int);

ExpressionAST* createBinary(BinaryOperator, ExpressionAST*, ExpressionAST*);

ExpressionAST* createUnary(UnaryOperator, ExpressionAST*);

int evaluate(ExpressionAST*);

