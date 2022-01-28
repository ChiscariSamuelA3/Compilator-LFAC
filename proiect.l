%{
#include <stdio.h>
#include "y.tab.h"
%}
%option noyywrap
%%
"const" {return CONST;}
"TRUE"|"FALSE" {yylval.str=strdup(yytext); return BOOL;}
"start_main" {return START;}
"end_main" {return END;}
"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"end_if" {return ENDIF;}
"while" {return WHILE;}
"do" {return DO;}
"end_while" {return ENDWHILE;}
"for" {return FOR;}
"start_for" {return STARTFOR;}
"end_for" {return ENDFOR;}
"clasa" {return CLASS;}
"print" {return PRINT;}
"Print" {return SPECIAL_PRINT;}
"&&" {return AND;}
"||" {return OR;}
"==" {return EQ;}
":=" {return ASSIGN;}
"~" {return NOT;}
"!=" {return NE;}
"<" {return LT;}
"<=" {return LE;}
">" {return GT;}
">=" {return GE;}
"++" {return PLUS;}
"--" {return MINUS;}
"*" {return MULTIP;}
"/" {return DIVIDE;}
"@" {return *yytext;}
")" {return *yytext;}
"(" {return *yytext;}
"[" {return *yytext;}
"]" {return *yytext;}
"{" {return *yytext;}
"}" {return *yytext;}
";" {return *yytext;}
"," {return *yytext;}
"value of expression" {yylval.str = strdup(yytext); return TXT1;}
"is:" {yylval.str = strdup(yytext); return TXT2;}
\%[_a-zA-Z][_a-zA-Z0-9]* {yylval.str = strdup(yytext); return NUME_CLASA;}
"int"|"float"|"char"|"string"|"bool"|"void" {yylval.str = strdup(yytext); return TIP;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.str = strdup(yytext); return ID;}
[1-9][0-9]* {yylval.num=atoi(yytext); return INTEGER;}
[1-9]*[.][0-9]+ {yylval.fl = atof(yytext); return FLOAT;}
\#[a-zA-Z] { yylval.str=strdup(yytext); return CHAR;}
\"[_a-zA-Z ]+\" {yylval.str=strdup(yytext); return STRING;}
\$[1-9][0-9]* {yylval.str=strdup(yytext); return NR_INT;}


[ \t] ;
\n {yylineno++;}
. {return yytext[0];}

