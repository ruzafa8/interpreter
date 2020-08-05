fuente = interprete
c:
	flex lexer.l
	bison parser.y -yd
	gcc -o $(fuente) lex.yy.c y.tab.c expression_ast.c variable.c statement_ast.c -lfl -ly
e:
	./$(fuente)

ce: c e

clean:
	rm lex.yy.c y.tab.c y.tab.h $(fuente)
