%{
void yyerror(char *s);
#include "interface.h"
extern int yylex();
extern int yyparse();
void yyerrorFS();
%}

%union {int num; char* str;}

%token ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN FS NL NUM ASSIGN TO COMMA VAR IS STRING VALUE IN ERR
%type <num> NUM operation direction
%type <str> STRING

%%

s   : 
    | s exp
    | s error NL {yyerrok; yyclearin;}
    ;

exp : move 
    | assignval
    | assignnum
    | query
    ; 

move    : operation direction FS NL {action($2, $1);}
        | operation direction NL {yyerrorFS();}
        ;

assignval   : ASSIGN NUM TO NUM COMMA NUM FS NL{assignVal($4 - 1, $6 - 1, $2);}
            | ASSIGN NUM TO NUM COMMA NUM NL{yyerrorFS();}
            ;

assignnum   : VAR STRING IS NUM COMMA NUM FS NL{assignName($4-1,$6-1,$2);}
            | VAR STRING IS NUM COMMA NUM NL{yyerrorFS();}
            ;

query   : VALUE IN NUM COMMA NUM FS NL{queryTile($3-1, $5-1);}
        | VALUE IN NUM COMMA NUM NL{yyerrorFS();}
        ;

direction   : LEFT {$$ = 0;}
            | UP {$$ = 1;}
            | RIGHT {$$ = 2;}
            | DOWN {$$ = 3;}
            ;

operation   : ADD {$$ = 0;}
            | SUBTRACT {$$ = 1;}
            | MULTIPLY {$$ = 2;}
            | DIVIDE {$$ = 3;}
            ;
%%

int main(){
    init();
    yyparse();
}

void yyerror(char *s){
    printf("2048> Syntax error.\n");
    printf("----> ");
    fprintf(stderr, "-1\n");
	// yyparse();
}

void yyerrorFS(){
    printf("2048> You need to end a command with a full-stop.\n");
    printf("----> ");
    fprintf(stderr, "-1\n");
	yyparse();
}