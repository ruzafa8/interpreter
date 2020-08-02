fuente = interprete
c:
	flex lexer.l
	bison parser.y -yd
	gcc -o $(fuente) lex.yy.c y.tab.c -lfl -ly
e:
	./$(fuente)

ce: c e

clean:
	rm lex.yy.c y.tab.c y.tab.h $(fuente)