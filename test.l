%{
#include "test.tab.h"
#include <string.h>
%}

%%

amrtype             { return MYTYPE; }
dekhao              { return SHOW; }
binimoy             { return SWAP; }
function            { return FUNCTION; }
return              { return RETURN; }
jodi                { return IF; }
nahole              { return ELSE; }
jotokkhon           { return WHILE; }
"++"                { return CONCAT; }

strlen              { return STRLEN; }


shonkha             { return INTTYPE; }
vognangsho          { return FLOATTYPE; }/*Planned not added yet.*/
akkhor              { return CHARTYPE; }
lekha               { return STRINGTYPE; }
talika              { return ARRAYTYPE; }

"/\*"([^*]|\*+[^*/])*"\*/"   { /* Ignore C-style comments */ }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
[0-9]+              { yylval.num = atoi(yytext); return NUMBER; }

"&&"                { return AND; }
"=="                { return EQ; }
"!="                { return NE; }
">="                { return GE; }
"<="                { return LE; }
">"                 { return '>'; }
"<"                 { return '<'; }
"||"                { return OR; }
"!"                 { return NOT; }
"<<"                { return LSHIFT; }
">>"                { return RSHIFT; }
"&"                 { return BAND; }
"|"                 { return BOR; }
"^"                 { return BXOR; }
"~"                 { return BNOT; }
"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return TIMES; }
"/"                 { return DIVIDE; }
"="                 { return '='; }
","                 { return ','; }
";"                 { return ';'; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }

\"([^\\\"]|\\.)*\"     { yylval.str = strdup(yytext); return STRING_LITERAL; }
\'([^\\\']|\\.)\'     { yylval.str = strdup(yytext); return CHAR_LITERAL; }

[ \t\n]+            { /* Ignore whitespace */ }
.                   { return yytext[0]; }

%%

int yywrap(void) { return 1; }