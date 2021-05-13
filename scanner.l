%option noyywrap

%{
#include "parser.tab.h"
%}

%%

"ADD" {return ADD;}
"SUBTRACT" {return SUBTRACT;}
"MULTIPLY" {return MULTIPLY;}
"DIVIDE" {return DIVIDE;}
"UP" {return UP;}
"DOWN" {return DOWN;}
"LEFT" {return LEFT;}
"RIGHT" {return RIGHT;}
"ASSIGN" {return ASSIGN;}
"TO" {return TO;}
"VAR" {return VAR;}
"IS" {return IS;}
"VALUE" {return VALUE;}
"IN" {return IN;}
"," {return COMMA;}
[0-9]+ {yylval.num = atoi(yytext); return NUM;}
[a-zA-Z][a-zA-Z0-9]* {yylval.str = strdup(yytext); return STRING;}
\n {return NL;}
"." {return FS;}
[  \t]+
. {return ERR;}

%%