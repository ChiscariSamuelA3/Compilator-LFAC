/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "proiect.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE * yyin;
extern char *yytext;
extern int yylineno;

struct node
{
	int type;
	char* info;
	struct node* left;
	struct node* right;
};

/*
struct expr
{
	int nrExp;
	char *data;
	float value;
	
}evalExpr[256];
*/

struct variabila
{
	int int_val;
	float float_val;
	char char_val;
	char *string_val;
	char *nume;
	char *tip_var;
	_Bool isTrue;
	_Bool isBool;
	_Bool isConst;
	_Bool isInit; 
    _Bool inFunc;
};

struct functie
{
	char *tip_funct;
	char *nume;
	int nrParam;
	
	struct parametrii_functie 
	{
		char *tip_var[100];
		char *nume_var[100];

		int int_val;
		float float_val;
		char char_val;
		char *string_val;

	}argumente;

	char *signatura;
};

struct apel
{
	int nrParam;

	char *tip_var[100]; 
	char *nume_var[100];
};

struct clasaVar
{
	int nrVar;
	char *nume;
	char *valori[100];
	char *variabile[100];
	char *tip_var[100];
};

struct array
{
	int vector[100];
	int matrice[100][100];
	int size1, size2;
	char *tip_array;
	char *nume;
};

struct clasaVar claseStr[200];
int nr_clase = 0;

struct variabila variabile[200];
int nr_var = 0;
int nr_var_table = 0;

struct functie functii[200];
int nr_funct = 0;
int nr_funct_table = 0; 

struct apel calls[400];

struct array arrays[200];
int nr_arr = 0;
int nr_arr_table = 0;

struct node* buildAST(struct node* root, struct node* left, struct node* right, int type)
{
	root->left = left;
	root->right = right;
	root->type = type;
	
	return root;
}

int evalAST(struct node* ast)
{
    if(ast->type == 0)
    {

        int left_value,right_value;
        if(ast->left != NULL) left_value = evalAST(ast->left);
        if(ast->right != NULL) right_value = evalAST(ast->right);
        switch(ast->info[0])
        {
        case '+':
            return left_value + right_value;
        case '-':
            return left_value - right_value;
        case '*':
            return left_value * right_value;
        case '/':
            return left_value / right_value;
        case '%':
            return left_value % right_value;
        }
    }
    else
    {
        switch(ast->type)
        {
        	case 2: 
            	return 0;
        	default: // case 1
            	if(ast->info != NULL)
                	return atoi(ast->info);
            	else return 0;
        }
    }
}

int arrays_declarate(char *nume)
{
	for (int i = 0; i < nr_arr; i++)
	{
		if (strcmp(arrays[i].nume, nume) == 0) 
			return i;
	}

	return -1;
}

void save_arr_data(char *tip, char *nume, int size1, int size2)
{
	arrays[nr_arr].tip_array = strdup(tip);
	arrays[nr_arr].nume = strdup(nume);
	arrays[nr_arr].size1 = size1;
	arrays[nr_arr].size2 = size2;
}

void declaratieArray_neinit(char *tip, char *nume, int size1, int size2)
{
	if (arrays_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Array %s este declarat anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	save_arr_data(tip, nume, size1, size2);
	nr_arr++;

}

void declaratieArray_init(char *tip, char *nume, int size1, int size2, char *elemente)
{
	if (arrays_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Array %s este deja declarat", nume);
		yyerror(buffer);
		exit(0);
	}

	save_arr_data(tip, nume, size1, size2);

	if (arrays[nr_arr].size2 > 0) // tablou bi-dimensional
	{
		char *p;
		int i = 1, j = 1;
		p = strtok(elemente, ",");
		while (p)
		{
			strcpy(p, p + 1);
			int nmb = atoi(p);

			if (i > size1)
			{
				break;
			}

			arrays[nr_arr].matrice[i][j] = nmb;
			if (j >= size2)
			{
				j = 1;
				i++;
			}
			else j++;

			p = strtok(NULL, ",");
		}
	}
	else // tablou uni-dimensional
	{
		char *p;
		int i = 1;
		p = strtok(elemente, ",");
		while (p)
		{
			strcpy(p, p + 1);
			if (i <= size1)
			{
				int nmb = atoi(p);
				arrays[nr_arr].vector[i] = nmb;
				i++;
				p = strtok(NULL, ",");
			}
			else
			{
				break;
			}
		}
	}

	nr_arr++;
}

int variabile_declarate(char *nume)
{
	for (int i = 0; i < nr_var; i++)
	{
		if (strcmp(variabile[i].nume, nume) == 0) 
			return i;
	}

	return -1;
}

void save_var_data(char *tip_var, char *nume, _Bool isConst, _Bool isInit)
{
	variabile[nr_var].tip_var = strdup(tip_var);
	variabile[nr_var].nume = strdup(nume);
	variabile[nr_var].isInit = isInit;
	variabile[nr_var].isConst = isConst;
}

void declaratie_neinit(char *tip_var, char *nume, _Bool isConst)
{
	if (!strcmp(tip_var, "void"))
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s nu poate fi declarata de tipul [void]", nume);
		yyerror(buffer);
		exit(0);
	}

	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (isConst == 1)
	{
		char buffer[256];
		sprintf(buffer, "Nu puteti declara variabile de tip [const %s] fara a fi initializate", nume);
		yyerror(buffer);
		exit(0);
	}

	save_var_data(tip_var, nume, isConst, 0);
	nr_var++;
}

void declaratie_int(char *tip_var, char *nume, int valoare, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(tip_var, "int") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este de tip [%s], iar valoarea asignata este de tip [int].", nume, tip_var);
		yyerror(buffer);
		exit(1);
	}

	save_var_data(tip_var, nume, isConst, 1);
	variabile[nr_var].int_val = valoare;
	nr_var++;
}

void declaratie_float(char *tip_var, char *nume, float valoare, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(tip_var, "float") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este de tip [%s], iar valoarea asignata este de tip [float].", nume, tip_var);
		yyerror(buffer);
		exit(1);
	}

	save_var_data(tip_var, nume, isConst, 1);
	variabile[nr_var].float_val = valoare;
	nr_var++;
}

void declaratie_char(char *tip_var, char *nume, char *valoare, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(tip_var, "char") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este de tip [%s], iar valoarea asignata este de tip [char].", nume, tip_var);
		yyerror(buffer);
		exit(1);
	}

	save_var_data(tip_var, nume, isConst, 1);
	variabile[nr_var].char_val = valoare[1];
	nr_var++;
}

void declaratie_string(char *tip_var, char *nume, char *valoare, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(tip_var, "string") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este de tip [%s], iar valoarea asignata este de tip [string].", nume, tip_var);
		yyerror(buffer);
		exit(1);
	}

	save_var_data(tip_var, nume, isConst, 1);
	variabile[nr_var].string_val = strdup(valoare);
	nr_var++;
}

void declaratie_bool(char *tip_var, char *nume, char *valoare, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(tip_var, "bool") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este de tip [%s], iar valoarea asignata este de tip [bool].", nume, tip_var);
		yyerror(buffer);
		exit(1);
	}

	save_var_data(tip_var, nume, isConst, 1);
	variabile[nr_var].string_val = strdup(valoare);
	nr_var++;
}

void declaratie_id(char *tip_var, char *nume, char *variabila, _Bool isConst)
{
	if (variabile_declarate(nume) != -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s este declarata anterior in program", nume);
		yyerror(buffer);
		exit(0);
	}

	int pozitie = variabile_declarate(variabila);
	if (pozitie == -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila %s nu poate fi initializata cu o variabila nedeclarata", nume);
		yyerror(buffer);
		exit(1);
	}

	if (strcmp(tip_var, variabile[pozitie].tip_var) != 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabilele %s si %s au tipuri diferite.", nume, variabile[pozitie].nume);
		yyerror(buffer);
		exit(2);
	}

	if (variabile[pozitie].isInit == 0)
	{
		char buffer[256];
		
		sprintf(buffer, "Nu se poate initializa variabila %s cu variabila %s - nu are nicio valoare.", nume, variabile[pozitie].nume);
		yyerror(buffer);
		exit(3);
	}

	save_var_data(tip_var, nume, isConst, 1);

	if (strcmp(tip_var, "int") == 0)
	{
		variabile[nr_var].int_val = variabile[pozitie].int_val;
	}
	else
	if (strcmp(tip_var, "float") == 0)
	{
		variabile[nr_var].float_val = variabile[pozitie].float_val;
	}
	else
	if (strcmp(tip_var, "char") == 0)
	{
		variabile[nr_var].char_val = variabile[pozitie].char_val;
	}
	else
	{
		variabile[nr_var].string_val = variabile[pozitie].string_val;
	}

	nr_var++;
}

float get_var_value(char *nume)
{
	int poz = variabile_declarate(nume);
	if (poz == -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila [%s] nu a fost declarata", nume);
		yyerror(buffer);
		exit(0);
	}

	if (variabile[poz].isInit == 0)
	{
		char buffer[256];
		sprintf(buffer, "Variabila [%s] nu are nicio valoare", nume);
		yyerror(buffer);
		exit(0);
	}

	if (strcmp(variabile[poz].tip_var, "int") == 0)
	{
		return variabile[poz].int_val;
	}
	else
	{
		if (strcmp(variabile[poz].tip_var, "float") == 0)
		{
			return variabile[poz].float_val;
		}
	}
}

void exprAssignment(char *nume, float valoare)
{
	int pozitie = variabile_declarate(nume);

	if (pozitie == -1)
	{
		char buffer[256];
		sprintf(buffer, "Variabila [%s] nu a fost declarata", nume);
		yyerror(buffer);
		exit(0);
	}

	if (variabile[pozitie].isConst == 1)
	{
		char buffer[256];
		sprintf(buffer, "Nu se poate asigna o noua valoare variabilei constante %s.", nume);
		yyerror(buffer);
		exit(1);
	}

	// cuprinde toate valorile
	if (strcmp(variabile[pozitie].tip_var, "float") != 0 &&
		strcmp(variabile[pozitie].tip_var, "int") != 0)
	{
		char buffer[256];
		sprintf(buffer, "Nu se poate asigna o valoare numerica variabilei %s.", nume);
		yyerror(buffer);
		exit(2);
	}

	if (strcmp(variabile[pozitie].tip_var, "float") == 0)
	{
		variabile[pozitie].float_val = valoare;
		variabile[pozitie].isInit = 1;
	}
	else
	{
		variabile[pozitie].int_val = valoare;
		variabile[pozitie].isInit = 1;
	}
}

int functii_declarate(char *nume)
{
	for (int i = 0; i < nr_funct; i++)
	{
		if (strcmp(functii[i].nume, nume) == 0) 
			return i;
	}

	return -1;
}

void save_funct_data(char *tip, char *nume)
{
	functii[nr_funct].tip_funct = strdup(tip);
	functii[nr_funct].nume = strdup(nume);
}

void save_parameters(char *tip, char *nume)
{
	int *p = &functii[nr_funct].nrParam;

	functii[nr_funct].argumente.tip_var[*p] = strdup(tip);
	functii[nr_funct].argumente.nume_var[*p] = strdup(nume);

	(*p)++;
}


/*
void save_var_clasa(char *nume)
{
	int *p = &claseStr[nr_clase].nrVar;

	claseStr[nr_clase].variabile[*p] = strdup(nume);
}
*/

void declaratieFunctie(char *tip, char *nume)
{
	int poz_declar = functii_declarate(nume);

	if (poz_declar != -1)
	{
		if(functii[nr_funct].nrParam == functii[poz_declar].nrParam)
		{
			for(int j = 0; j < functii[nr_funct].nrParam; j++)
			{
				if(strcmp(functii[poz_declar].argumente.tip_var[j], functii[nr_funct].argumente.tip_var[j]))
				{
					save_funct_data(tip, nume);
					nr_funct++;
					return;
				}
			}
		}
		else
		{	
			save_funct_data(tip, nume);
			nr_funct++;
			return;
		}
		
		char buffer[200];
		sprintf(buffer, "Nu se pot declara mai multe functii %s cu aceeasi signatura", nume);
		yyerror(buffer);
		exit(0);
	}
	else
	{
		save_funct_data(tip, nume);
		nr_funct++;
	}
}

int nrCall = 0;

void save_call_param(char *var)
{
	int *p = &calls[nrCall].nrParam;

	calls[nrCall].nume_var[*p] = strdup(var);
	
	(*p)++;
}


void apelareFunctie(char *nume)
{
	for(int i = 0; i < calls[nrCall].nrParam; i++)
	{
		int poz_var = variabile_declarate(calls[nrCall].nume_var[i]);

		if (poz_var == -1)
		{
			char buffer[256];
			sprintf(buffer, "Variabila [%s] nu a fost declarata", calls[nrCall].nume_var[i]);
			yyerror(buffer);
			exit(0);
		}
	}

	for (int i = 0; i < nr_funct; i++)
	{
		if (!strcmp(functii[i].nume, nume)) 
		{
			// daca nu au acelasi nr de param, mai este posibilitatea sa existe o functie cu acelasi nume dar overloaded
			if(functii[i].nrParam == calls[nrCall].nrParam) 
			{
				int ok = 1;
				for(int j = 0; j < calls[nrCall].nrParam; j++)
				{
					int poz_var = variabile_declarate(calls[nrCall].nume_var[j]);

					if (poz_var == -1)
					{
						char buffer[256];
						sprintf(buffer, "Variabila [%s] nu a fost declarata", calls[nrCall].nume_var[i]);
						yyerror(buffer);
						exit(0);
					}

					if(strcmp(functii[i].argumente.tip_var[j], variabile[poz_var].tip_var))
					{
						ok = 0;
						break;
					}
				}

				if(ok == 1)
				{
					// apel functie corect -> putem salva valorile parametrilor cu care s-a facut apelul ...
					return;
				}

			}
		}
	}

	char buffer[200];
	sprintf(buffer, "Nu a fost gasita nicio functie [%s] care poate fi apelata cu variabilele introduse", nume);
	yyerror(buffer);
	exit(0);
}

void var_symbol(FILE* g, char *scop)
{
	if (nr_var - nr_var_table != 0)
	{
		fprintf(g, "Variabile declarate %s: \n", scop);
		for (int i = nr_var_table; i < nr_var; i++)
		{
			if (variabile[i].isInit)
			{
				if (strstr(variabile[i].tip_var, "int")) 
					fprintf(g, "[%s] [%s] [=] [%d] \n", variabile[i].tip_var, variabile[i].nume, variabile[i].int_val);
				if (strstr(variabile[i].tip_var, "float")) 
					fprintf(g, "[%s] [%s] [=] [%.5f] \n", variabile[i].tip_var, variabile[i].nume, variabile[i].float_val);
				if (strstr(variabile[i].tip_var, "char")) 
					fprintf(g, "[%s] [%s] [=] [%c] \n", variabile[i].tip_var, variabile[i].nume, variabile[i].char_val);
				if (strstr(variabile[i].tip_var, "string")) 
					fprintf(g, "[%s] [%s] [=] [%s] \n", variabile[i].tip_var, variabile[i].nume, variabile[i].string_val);
				if (strstr(variabile[i].tip_var, "bool"))
					fprintf(g, "[%s] [%s] [=] [%s] \n", variabile[i].tip_var, variabile[i].nume, variabile[i].string_val);
			}
			else
			{
				fprintf(g, "[%s] [%s] \n", variabile[i].tip_var, variabile[i].nume);
			}
		}
	}
	else
	{
		fprintf(g, "Nu exista variabile declarate %s.\n", scop);
	}

	nr_var_table = nr_var;

	fprintf(g, "\n");
}

void array_symbol(FILE *g, char *scop)
{
	if (nr_arr - nr_arr_table != 0)
	{
		fprintf(g, "Arrays declarate %s: \n", scop);
		for (int i = nr_arr_table; i < nr_arr; i++)
		{
			if (arrays[i].size2 == 0)
			{
				int j = 0;
				fprintf(g, "<%s > %s[%d] = {", arrays[i].tip_array, arrays[i].nume, arrays[i].size1);
				for (j = 1; j < arrays[i].size1; j++)
				{
					fprintf(g, " %d,", arrays[i].vector[j]);
				}

				fprintf(g, " %d }\n", arrays[i].vector[j]);
			}
			else
			{
				fprintf(g, "<%s > %s[%d][%d] = \n", arrays[i].tip_array, arrays[i].nume, arrays[i].size1, arrays[i].size2);
				fprintf(g, "{\n");
				for (int j = 1; j <= arrays[i].size1; j++)
				{
					for (int k = 1; k <= arrays[i].size2; k++)
					{
						fprintf(g, "  [%d]  ", arrays[i].matrice[j][k]);
					}

					if (j < arrays[i].size1)
					{
						fprintf(g, "\n");
					}
				}

				fprintf(g, "\n}");
			}

			fprintf(g, "\n");
		}
	}
	else
	{
		fprintf(g, "Nu exista arrays declarate %s.\n", scop);
	}

	nr_arr_table = nr_arr;

	fprintf(g, "\n");
}

void funct_symbol(FILE *f, char *scop)
{
	if (nr_funct - nr_funct_table != 0)
	{
		if(strstr(scop, "clasa"))
		{
			fprintf(f, "Functii declarate %s: \n", scop);
		}
		else
		{
			fprintf(f, "Functie declarata %d:\n", nr_funct);
		}
		
		for (int i = nr_funct_table; i < nr_funct; i++)
		{
			fprintf(f, "<%s > %s :: ", functii[i].tip_funct, functii[i].nume);
			for(int j = 0; j < functii[i].nrParam; j++)
			{
				fprintf(f, " %s %s .", functii[i].argumente.tip_var[j], functii[i].argumente.nume_var[j]);
			}
			fprintf(f, "\n");
		}
	}
	else
	{
		if(!strstr(scop, "in functie") && strcmp(scop, "local"))
		{
			fprintf(f, "Nu exista functii declarate %s.\n", scop);
		}
	}

	nr_funct_table = nr_funct;

	fprintf(f, "\n");
}

char scopActual[100];

void get_symbol_table(char *scop)
{
	strcpy(scopActual, scop);
	FILE *g = fopen("symbol_table.txt", "a");
	FILE *f = fopen("symbol_table_functions.txt", "a");

	if(!strstr(scop, "in functie"))
	{
		var_symbol(g, scop);
		array_symbol(g, scop);
		funct_symbol(f, scop);
	}
	else
	{
		funct_symbol(f, scop);
		var_symbol(f, scop);
		array_symbol(f, scop);
	}
	
	fclose(g);
	fclose(f);
}

int eval[300], e = 0;

void Print()
{
	for (int i = 0; i < e; i++)
	{
		printf("Valoarea expresiei [%d] este %d\n", i + 1, eval[i]);
	}
}

void Eval(int value)
{
	eval[e++] = value;
}

void type_validation(int a, float b)
{
	int rezultat;
	rezultat = b *100 - a * 100;
	if (rezultat == 0) 
		Eval(a);
}

int get_array_value(char *nume, int size1, int size2)
{
	int poz = arrays_declarate(nume);
	if (poz == -1)
	{
		char buffer[256];
		sprintf(buffer, "Array %s este deja declarat", nume);
		yyerror(buffer);
		exit(0);
	}

	if (size2 == 0)
	{
		if (size1 <= arrays[poz].size1 && size1 > 0) return arrays[poz].vector[size1];
	}
	else
	{
		if (size1 <= arrays[poz].size1 && size1 > 0 && size2 <= arrays[poz].size2 && size2 > 0)
			return arrays[poz].matrice[size1][size2];
	}
}


void verificareExpresiiPrint(char *exp1, char *exp2, float val)
{
	if(strcmp(exp1, exp2))
	{
		char buffer[256];
		sprintf(buffer, "Expresiile [%s] si [%s] din Print nu coincid", exp1, exp2);
		yyerror(buffer);
		exit(0); 
	}

	printf("\nvalue of expression %s is: %f\n", exp1, val);
}

void save_class_name(char *nume)
{
	claseStr[nr_clase++].nume = strdup(nume);
}

void check_class_name(char *nume)
{
	strcpy(nume, nume + 1);
	for(int i = 0; i < nr_clase; i++)
	{
		if(!strcmp(nume, claseStr[i].nume))
		{
			return;
		}
	}

	char buffer[256];
	sprintf(buffer, "Nu exista clasa cu numele [%s]", nume);
	yyerror(buffer);
	exit(0); 
}




#line 993 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    START = 259,
    CONST = 260,
    END = 261,
    IF = 262,
    THEN = 263,
    ELSE = 264,
    ENDIF = 265,
    WHILE = 266,
    DO = 267,
    ENDWHILE = 268,
    FOR = 269,
    STARTFOR = 270,
    ENDFOR = 271,
    CLASS = 272,
    AND = 273,
    OR = 274,
    EQ = 275,
    ASSIGN = 276,
    NOT = 277,
    NE = 278,
    LT = 279,
    LE = 280,
    GT = 281,
    GE = 282,
    PLUS = 283,
    MINUS = 284,
    MULTIP = 285,
    DIVIDE = 286,
    TIP = 287,
    ID = 288,
    INTEGER = 289,
    CHAR = 290,
    FLOAT = 291,
    STRING = 292,
    NR_INT = 293,
    PRINT = 294,
    SPECIAL_PRINT = 295,
    TXT1 = 296,
    TXT2 = 297,
    NUME_CLASA = 298
  };
#endif
/* Tokens.  */
#define BOOL 258
#define START 259
#define CONST 260
#define END 261
#define IF 262
#define THEN 263
#define ELSE 264
#define ENDIF 265
#define WHILE 266
#define DO 267
#define ENDWHILE 268
#define FOR 269
#define STARTFOR 270
#define ENDFOR 271
#define CLASS 272
#define AND 273
#define OR 274
#define EQ 275
#define ASSIGN 276
#define NOT 277
#define NE 278
#define LT 279
#define LE 280
#define GT 281
#define GE 282
#define PLUS 283
#define MINUS 284
#define MULTIP 285
#define DIVIDE 286
#define TIP 287
#define ID 288
#define INTEGER 289
#define CHAR 290
#define FLOAT 291
#define STRING 292
#define NR_INT 293
#define PRINT 294
#define SPECIAL_PRINT 295
#define TXT1 296
#define TXT2 297
#define NUME_CLASA 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 938 "proiect.y"

    int num;
    float fl;
    char* str;
	_Bool bl;
	struct expp
	{
		float val;
		char* exp;
	}expres;

#line 1143 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   357

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

#define YYUNDEFTOK  2
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,     2,
      45,    46,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
       2,     2,     2,     2,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   956,   956,   959,   960,   963,   964,   965,   966,   967,
     968,   969,   970,   971,   972,   973,   974,   975,   976,   977,
     980,   981,   984,   987,   988,   991,   994,   995,   998,   999,
    1001,  1004,  1005,  1007,  1008,  1010,  1013,  1014,  1017,  1018,
    1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,
    1029,  1030,  1031,  1032,  1035,  1036,  1037,  1038,  1041,  1042,
    1045,  1048,  1049,  1052,  1053,  1054,  1055,  1056,  1057,  1058,
    1063,  1064,  1065,  1066,  1067,  1068,  1069,  1070,  1071,  1072,
    1073,  1076,  1077,  1078,  1079,  1080,  1083,  1084,  1087,  1090,
    1091,  1095,  1099,  1103,  1107
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "START", "CONST", "END", "IF",
  "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE", "FOR", "STARTFOR",
  "ENDFOR", "CLASS", "AND", "OR", "EQ", "ASSIGN", "NOT", "NE", "LT", "LE",
  "GT", "GE", "PLUS", "MINUS", "MULTIP", "DIVIDE", "TIP", "ID", "INTEGER",
  "CHAR", "FLOAT", "STRING", "NR_INT", "PRINT", "SPECIAL_PRINT", "TXT1",
  "TXT2", "NUME_CLASA", "';'", "'('", "')'", "'{'", "'}'", "'@'", "','",
  "'['", "']'", "'&'", "$accept", "compilator", "program", "global",
  "clase", "clasa", "functii", "functie", "param_list_dec", "parametrii",
  "param_dec", "param_list_call", "call_list", "param_call", "declaratii",
  "declaratie", "array", "elemente_int", "main", "blocuri", "bloc",
  "conditii", "operand", "operatii", "asignare_expresie", "expresie", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    59,    40,    41,   123,   125,    64,
      44,    91,    93,    38
};
# endif

#define YYPACT_NINF (-179)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,   -26,    20,    64,    91,    25,   102,   138,  -179,   146,
      72,  -179,    72,  -179,    72,  -179,   136,  -179,   214,   140,
     112,    55,   137,   143,   148,  -179,  -179,  -179,    36,    36,
     115,  -179,   115,    -2,    -2,  -179,  -179,   158,   170,   171,
     169,     2,   175,  -179,   150,  -179,   167,   179,    90,    76,
     215,  -179,    80,   190,   186,    84,   120,  -179,  -179,  -179,
      76,   204,    76,   221,   206,   204,   221,   207,   207,   211,
      55,   129,   212,   249,  -179,   223,  -179,   244,  -179,    30,
     219,   -27,   220,   226,   231,   235,  -179,   250,  -179,   126,
    -179,   233,   214,  -179,  -179,  -179,   237,   245,  -179,   248,
     236,  -179,  -179,     8,   242,    38,   238,   239,   129,  -179,
     243,   129,  -179,   268,   251,   252,   253,   254,   255,  -179,
    -179,   258,  -179,  -179,  -179,  -179,  -179,  -179,   261,    -9,
      96,   267,  -179,   256,  -179,   207,   207,   286,   248,   248,
     248,   248,   248,   248,   289,   269,   214,   166,   129,   129,
     129,   129,   202,  -179,  -179,  -179,  -179,  -179,   257,  -179,
     259,   270,  -179,   214,  -179,  -179,   260,  -179,  -179,  -179,
    -179,  -179,  -179,   263,   262,   111,  -179,    29,    29,  -179,
    -179,   264,   265,   273,   266,   135,   223,   214,   274,  -179,
     129,   278,  -179,    32,   281,  -179,   156,   174,   271,   230,
     272,  -179,   275,   276,   104,   306,   305,   277,  -179,  -179,
     273,   279,  -179,  -179,   280,  -179,    73,   223,   214,  -179,
     165,   194,   312,   309,  -179,  -179
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     0,
       9,    20,    10,    23,    11,    36,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     1,     3,    21,     7,     8,
      18,    24,     6,    14,    13,    37,    52,     0,     0,     0,
       0,     0,     0,    68,     0,    61,    67,     0,     0,     0,
       0,    38,     0,     0,     0,     0,     0,    33,    51,    40,
       5,    17,    15,    16,     0,    19,    12,     0,     0,     0,
       0,     0,     0,     0,    62,     0,    86,     0,    47,     0,
       0,    81,    84,     0,    85,     0,    39,     0,    26,     0,
      28,     0,     0,    35,    31,    32,     0,     0,    71,     0,
      81,    84,    85,     0,    70,     0,     0,     0,     0,    89,
      88,     0,    60,     0,     0,     0,     0,     0,     0,    45,
      46,     0,    41,    44,    42,    43,    30,    27,     0,    54,
       0,     0,    34,     0,    72,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    50,    48,    49,    22,     0,    29,
       0,     0,    25,     0,    79,    80,     0,    73,    78,    76,
      74,    77,    75,     0,     0,     0,    94,    90,    91,    92,
      93,     0,    82,     0,     0,     0,     0,     0,     0,    53,
       0,     0,    58,     0,    55,    25,     0,     0,     0,     0,
       0,    56,     0,     0,     0,     0,     0,     0,    83,    59,
       0,     0,    64,    66,     0,    69,     0,     0,     0,    57,
       0,     0,     0,     0,    65,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,   157,    -5,   123,    37,   -30,  -179,
     200,  -179,  -179,   234,     1,     4,  -179,   119,   322,   -91,
     -44,   -61,   -48,  -178,   282,  -105
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,    54,    89,
      90,    23,    56,    57,    14,    43,    16,   193,    17,    44,
      45,   103,   109,    46,    47,   110
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      74,   130,    86,   147,    15,    27,   152,   105,   196,     1,
       2,    29,   160,    32,    15,     3,    15,   120,    35,   104,
     104,    18,     3,    71,   121,    27,   135,   136,    27,    60,
      64,    62,    15,    35,    15,     2,    35,     4,     5,   220,
     107,     2,   161,   177,   178,   179,   180,    22,     6,    31,
      79,   134,    19,    15,   137,   175,   135,   136,    27,   150,
     151,    27,    40,     5,    35,    31,    35,   133,     4,     5,
      22,    31,   185,     6,   164,   165,    50,     2,   118,     6,
     201,     2,   202,    35,   144,   199,    74,   104,   104,     3,
     167,   168,   169,   170,   171,   172,   197,    20,    31,    51,
      52,     2,    31,    37,     4,     5,    53,    38,    40,     5,
      39,    77,    87,   211,   212,     6,     2,    93,    37,     6,
       2,   219,    38,   202,    21,    39,    88,   221,    40,    41,
      94,    74,     3,    28,    78,    24,    42,    34,    25,     6,
       2,    74,    37,    40,    41,   162,    38,    40,     5,    39,
       1,    42,    61,    74,     6,     2,    65,    37,     6,    49,
     189,    38,   100,   101,    39,   102,    95,    40,    41,    30,
      96,    33,   127,    48,   108,    42,   128,    74,     6,     2,
      36,    37,    40,    41,   195,    38,    55,    58,    39,    63,
      42,    66,    59,     6,   148,   149,   150,   151,    73,     2,
      75,    37,    70,    67,   204,    38,    40,    41,    39,    75,
      98,    75,   176,   222,    42,    68,    69,     6,    80,     2,
      72,    37,   205,    76,    91,    38,    40,    41,    39,    99,
     148,   149,   150,   151,    42,    92,    64,     6,     3,    97,
     100,   101,   223,   102,   181,   106,    40,    41,    81,    82,
      83,    84,    85,   111,    42,   112,   113,     6,   148,   149,
     150,   151,   138,   119,   122,   139,   140,   141,   142,   143,
     123,   148,   149,   150,   151,   124,   207,   115,   116,   125,
     117,   100,   101,   126,   102,   129,   131,   121,   146,    71,
      52,   145,   158,    87,   166,   153,   154,   155,   156,   157,
      93,   173,   203,   174,   184,   163,   183,   186,   198,   182,
     187,   192,   200,   209,   190,   188,   191,   206,   194,   213,
     214,   215,   224,   210,   208,   225,   217,   218,   159,   216,
     132,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114
};

static const yytype_int16 yycheck[] =
{
      44,    92,    50,   108,     0,    10,   111,    68,   186,     4,
       5,    10,    21,    12,    10,    17,    12,    44,    14,    67,
      68,    47,    17,    21,    51,    30,    18,    19,    33,    28,
      32,    30,    28,    29,    30,     5,    32,    32,    33,   217,
      70,     5,    51,   148,   149,   150,   151,    45,    43,    12,
      49,    99,    32,    49,    46,   146,    18,    19,    63,    30,
      31,    66,    32,    33,    60,    28,    62,    97,    32,    33,
      45,    34,   163,    43,   135,   136,    21,     5,    48,    43,
      48,     5,    50,    79,    46,   190,   130,   135,   136,    17,
     138,   139,   140,   141,   142,   143,   187,    33,    61,    44,
      45,     5,    65,     7,    32,    33,    51,    11,    32,    33,
      14,    21,    32,     9,    10,    43,     5,    33,     7,    43,
       5,    48,    11,    50,    33,    14,    46,   218,    32,    33,
      46,   175,    17,    10,    44,    33,    40,    14,     0,    43,
       5,   185,     7,    32,    33,    49,    11,    32,    33,    14,
       4,    40,    29,   197,    43,     5,    33,     7,    43,    47,
      49,    11,    33,    34,    14,    36,    46,    32,    33,    12,
      50,    14,    46,    33,    45,    40,    50,   221,    43,     5,
      44,     7,    32,    33,    49,    11,    49,    44,    14,    32,
      40,    34,    44,    43,    28,    29,    30,    31,    48,     5,
      44,     7,    33,    45,    48,    11,    32,    33,    14,    44,
       3,    44,    46,    48,    40,    45,    45,    43,     3,     5,
      45,     7,    48,    44,    34,    11,    32,    33,    14,    22,
      28,    29,    30,    31,    40,    49,    32,    43,    17,    33,
      33,    34,    48,    36,    42,    34,    32,    33,    33,    34,
      35,    36,    37,    41,    40,     6,    33,    43,    28,    29,
      30,    31,    20,    44,    44,    23,    24,    25,    26,    27,
      44,    28,    29,    30,    31,    44,    46,    33,    34,    44,
      36,    33,    34,    33,    36,    52,    49,    51,    49,    21,
      45,    53,    34,    32,     8,    44,    44,    44,    44,    44,
      33,    12,    21,    34,    34,    49,    47,    47,    34,    52,
      47,    38,    34,    38,    50,    53,    51,    46,    52,    13,
      15,    44,    10,    47,    52,    16,    47,    47,   128,   210,
      96,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,    17,    32,    33,    43,    55,    56,    57,
      58,    59,    60,    61,    68,    69,    70,    72,    47,    32,
      33,    33,    45,    65,    33,     0,    72,    59,    60,    68,
      58,    61,    68,    58,    60,    69,    44,     7,    11,    14,
      32,    33,    40,    69,    73,    74,    77,    78,    33,    47,
      21,    44,    45,    51,    62,    49,    66,    67,    44,    44,
      68,    60,    68,    58,    32,    60,    58,    45,    45,    45,
      33,    21,    45,    48,    74,    44,    44,    21,    44,    68,
       3,    33,    34,    35,    36,    37,    76,    32,    46,    63,
      64,    34,    49,    33,    46,    46,    50,    33,     3,    22,
      33,    34,    36,    75,    76,    75,    34,    62,    45,    76,
      79,    41,     6,    33,    78,    33,    34,    36,    48,    44,
      44,    51,    44,    44,    44,    44,    33,    46,    50,    52,
      73,    49,    67,    62,    76,    18,    19,    46,    20,    23,
      24,    25,    26,    27,    46,    53,    49,    79,    28,    29,
      30,    31,    79,    44,    44,    44,    44,    44,    34,    64,
      21,    51,    49,    49,    75,    75,     8,    76,    76,    76,
      76,    76,    76,    12,    34,    73,    46,    79,    79,    79,
      79,    42,    52,    47,    34,    73,    47,    47,    53,    49,
      50,    51,    38,    71,    52,    49,    77,    73,    34,    79,
      34,    48,    50,    21,    48,    48,    46,    46,    52,    38,
      47,     9,    10,    13,    15,    44,    71,    47,    47,    48,
      77,    73,    48,    48,    10,    16
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    66,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    73,    73,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    76,    76,    76,    77,    77,    78,    79,
      79,    79,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     2,     2,     2,     1,
       1,     1,     3,     2,     2,     3,     3,     3,     2,     3,
       1,     2,     6,     1,     2,     6,     2,     3,     1,     3,
       2,     3,     3,     1,     3,     2,     1,     2,     3,     4,
       3,     5,     5,     5,     5,     5,     5,     4,     6,     6,
       6,     3,     2,     6,     5,     8,     9,    12,     1,     3,
       5,     1,     2,    13,     9,    13,     9,     1,     1,     9,
       1,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     7,     1,     1,     2,     4,     3,     1,
       3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 956 "proiect.y"
                     {printf("\nProgramul este corect sintactic! \n\n"); Print();}
#line 2490 "y.tab.c"
    break;

  case 5:
#line 963 "proiect.y"
                                  {get_symbol_table("global");}
#line 2496 "y.tab.c"
    break;

  case 6:
#line 964 "proiect.y"
                            {get_symbol_table("global");}
#line 2502 "y.tab.c"
    break;

  case 7:
#line 965 "proiect.y"
                       {get_symbol_table("global");}
#line 2508 "y.tab.c"
    break;

  case 8:
#line 966 "proiect.y"
                          {get_symbol_table("global");}
#line 2514 "y.tab.c"
    break;

  case 9:
#line 967 "proiect.y"
               {get_symbol_table("global");}
#line 2520 "y.tab.c"
    break;

  case 10:
#line 968 "proiect.y"
                 {get_symbol_table("global");}
#line 2526 "y.tab.c"
    break;

  case 11:
#line 969 "proiect.y"
                    {get_symbol_table("global");}
#line 2532 "y.tab.c"
    break;

  case 12:
#line 970 "proiect.y"
                                      {get_symbol_table("global");}
#line 2538 "y.tab.c"
    break;

  case 13:
#line 971 "proiect.y"
                                {get_symbol_table("global");}
#line 2544 "y.tab.c"
    break;

  case 14:
#line 972 "proiect.y"
                              {get_symbol_table("global");}
#line 2550 "y.tab.c"
    break;

  case 15:
#line 973 "proiect.y"
                                      {get_symbol_table("global");}
#line 2556 "y.tab.c"
    break;

  case 16:
#line 974 "proiect.y"
                                      {get_symbol_table("global");}
#line 2562 "y.tab.c"
    break;

  case 17:
#line 975 "proiect.y"
                                      {get_symbol_table("global");}
#line 2568 "y.tab.c"
    break;

  case 18:
#line 976 "proiect.y"
                           {get_symbol_table("global");}
#line 2574 "y.tab.c"
    break;

  case 19:
#line 977 "proiect.y"
                                      {get_symbol_table("global");}
#line 2580 "y.tab.c"
    break;

  case 22:
#line 984 "proiect.y"
                                        {save_class_name((yyvsp[-4].str));  (yyval.str) = malloc(256); strcpy((yyval.str),"in clasa "); strcat((yyval.str), (yyvsp[-4].str)); get_symbol_table((yyval.str));}
#line 2586 "y.tab.c"
    break;

  case 25:
#line 991 "proiect.y"
                                                { char tmp[256]; sprintf(tmp, "in functie %d", nr_funct+1); get_symbol_table(tmp); declaratieFunctie((yyvsp[-5].str),(yyvsp[-4].str));}
#line 2592 "y.tab.c"
    break;

  case 26:
#line 994 "proiect.y"
                         { (yyval.str)=malloc(200); (yyval.str)[0]=0;}
#line 2598 "y.tab.c"
    break;

  case 27:
#line 995 "proiect.y"
                                    { (yyval.str) = (yyvsp[-1].str);}
#line 2604 "y.tab.c"
    break;

  case 30:
#line 1001 "proiect.y"
                   {save_parameters((yyvsp[-1].str), (yyvsp[0].str));}
#line 2610 "y.tab.c"
    break;

  case 31:
#line 1004 "proiect.y"
                              { (yyval.str)=malloc(200); (yyval.str)[0]=0; }
#line 2616 "y.tab.c"
    break;

  case 32:
#line 1005 "proiect.y"
                                                {(yyval.str) = (yyvsp[-1].str);}
#line 2622 "y.tab.c"
    break;

  case 35:
#line 1010 "proiect.y"
                     {save_call_param((yyvsp[0].str));}
#line 2628 "y.tab.c"
    break;

  case 38:
#line 1017 "proiect.y"
                        { declaratie_neinit((yyvsp[-2].str),(yyvsp[-1].str),0); }
#line 2634 "y.tab.c"
    break;

  case 40:
#line 1019 "proiect.y"
                                       {check_class_name((yyvsp[-2].str));}
#line 2640 "y.tab.c"
    break;

  case 41:
#line 1020 "proiect.y"
                                       {declaratie_int((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].num),0);}
#line 2646 "y.tab.c"
    break;

  case 42:
#line 1021 "proiect.y"
                                     {declaratie_float((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].fl),0);}
#line 2652 "y.tab.c"
    break;

  case 43:
#line 1022 "proiect.y"
                                      {declaratie_string((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str),0);}
#line 2658 "y.tab.c"
    break;

  case 44:
#line 1023 "proiect.y"
                                    {declaratie_char((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str),0);}
#line 2664 "y.tab.c"
    break;

  case 45:
#line 1024 "proiect.y"
                                            {declaratie_bool((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str),0);}
#line 2670 "y.tab.c"
    break;

  case 46:
#line 1025 "proiect.y"
                                  {declaratie_id((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str),0);}
#line 2676 "y.tab.c"
    break;

  case 47:
#line 1026 "proiect.y"
                              {declaratie_neinit((yyvsp[-2].str),(yyvsp[-1].str),1);}
#line 2682 "y.tab.c"
    break;

  case 48:
#line 1027 "proiect.y"
                                             {declaratie_int((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].num),1);}
#line 2688 "y.tab.c"
    break;

  case 49:
#line 1028 "proiect.y"
                                           {declaratie_float((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].fl),1);}
#line 2694 "y.tab.c"
    break;

  case 50:
#line 1029 "proiect.y"
                                        {declaratie_id((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str),1);}
#line 2700 "y.tab.c"
    break;

  case 51:
#line 1030 "proiect.y"
                                    {apelareFunctie((yyvsp[-2].str)); nrCall++;}
#line 2706 "y.tab.c"
    break;

  case 53:
#line 1032 "proiect.y"
                                                           { declaratieFunctie((yyvsp[-5].str),(yyvsp[-4].str));}
#line 2712 "y.tab.c"
    break;

  case 54:
#line 1035 "proiect.y"
                               {declaratieArray_neinit((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].num),0);}
#line 2718 "y.tab.c"
    break;

  case 55:
#line 1036 "proiect.y"
                                               {declaratieArray_neinit((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].num),(yyvsp[-1].num));}
#line 2724 "y.tab.c"
    break;

  case 56:
#line 1037 "proiect.y"
                                                           {declaratieArray_init((yyvsp[-8].str),(yyvsp[-7].str),(yyvsp[-5].num),0,(yyvsp[-1].str));}
#line 2730 "y.tab.c"
    break;

  case 57:
#line 1038 "proiect.y"
                                                                           {declaratieArray_init((yyvsp[-11].str),(yyvsp[-10].str),(yyvsp[-8].num),(yyvsp[-5].num),(yyvsp[-1].str));}
#line 2736 "y.tab.c"
    break;

  case 58:
#line 1041 "proiect.y"
                      {(yyval.str) = (yyvsp[0].str);}
#line 2742 "y.tab.c"
    break;

  case 59:
#line 1042 "proiect.y"
                                       {(yyval.str) = (yyvsp[-2].str); strcat((yyval.str),",");strcat((yyval.str),(yyvsp[0].str));}
#line 2748 "y.tab.c"
    break;

  case 60:
#line 1045 "proiect.y"
                                 {get_symbol_table("local");}
#line 2754 "y.tab.c"
    break;

  case 63:
#line 1052 "proiect.y"
                                                                                   {}
#line 2760 "y.tab.c"
    break;

  case 69:
#line 1058 "proiect.y"
                                                                     {
		 	verificareExpresiiPrint((yyvsp[-5].expres).exp, (yyvsp[-2].expres).exp, (yyvsp[-2].expres).val);
		 }
#line 2768 "y.tab.c"
    break;

  case 81:
#line 1076 "proiect.y"
             {(yyval.expres).val=get_var_value((yyvsp[0].str)); (yyval.expres).exp = strdup((yyvsp[0].str));}
#line 2774 "y.tab.c"
    break;

  case 82:
#line 1077 "proiect.y"
                             {(yyval.expres).val=get_array_value((yyvsp[-3].str),(yyvsp[-1].num),0); char tmp[256]; sprintf(tmp, "%s[%d]", (yyvsp[-3].str), (yyvsp[-1].num)); (yyval.expres).exp = strdup(tmp);}
#line 2780 "y.tab.c"
    break;

  case 83:
#line 1078 "proiect.y"
                                             {(yyval.expres).val=get_array_value((yyvsp[-6].str),(yyvsp[-4].num),(yyvsp[-1].num)); char tmp[256]; sprintf(tmp, "%s[%d][%d]", (yyvsp[-6].str), (yyvsp[-4].num), (yyvsp[-1].num)); (yyval.expres).exp = strdup(tmp);}
#line 2786 "y.tab.c"
    break;

  case 84:
#line 1079 "proiect.y"
                  {(yyval.expres).val = (yyvsp[0].num); char tmp[100]; sprintf(tmp, "%d", (yyvsp[0].num)); (yyval.expres).exp = strdup(tmp);}
#line 2792 "y.tab.c"
    break;

  case 85:
#line 1080 "proiect.y"
                {(yyval.expres).val = (yyvsp[0].fl); char tmp[100]; sprintf(tmp, "%f", (yyvsp[0].fl)); (yyval.expres).exp = strdup(tmp);}
#line 2798 "y.tab.c"
    break;

  case 88:
#line 1087 "proiect.y"
                                       {/*int exp = evalAST($3);*/ exprAssignment((yyvsp[-2].str),(yyvsp[0].expres).val); }
#line 2804 "y.tab.c"
    break;

  case 90:
#line 1091 "proiect.y"
                                  {
			 	(yyval.expres).exp=malloc(200); sprintf((yyval.expres).exp, "%s + %s", (yyvsp[-2].expres).exp, (yyvsp[0].expres).exp); 
			 	(yyval.expres).val = (yyvsp[-2].expres).val + (yyvsp[0].expres).val; type_validation((yyval.expres).val,(yyval.expres).val);
			 }
#line 2813 "y.tab.c"
    break;

  case 91:
#line 1095 "proiect.y"
                                   {
			 (yyval.expres).exp=malloc(200); sprintf((yyval.expres).exp, "%s - %s", (yyvsp[-2].expres).exp, (yyvsp[0].expres).exp); 
			 (yyval.expres).val = (yyvsp[-2].expres).val - (yyvsp[0].expres).val; type_validation((yyval.expres).val,(yyval.expres).val);
			 }
#line 2822 "y.tab.c"
    break;

  case 92:
#line 1099 "proiect.y"
                                    {
			 (yyval.expres).exp=malloc(200); sprintf((yyval.expres).exp, "%s * %s", (yyvsp[-2].expres).exp, (yyvsp[0].expres).exp); 
			 (yyval.expres).val = (yyvsp[-2].expres).val * (yyvsp[0].expres).val; type_validation((yyval.expres).val,(yyval.expres).val);
			 }
#line 2831 "y.tab.c"
    break;

  case 93:
#line 1103 "proiect.y"
                                    {
			 (yyval.expres).exp=malloc(200); sprintf((yyval.expres).exp, "%s / %s", (yyvsp[-2].expres).exp, (yyvsp[0].expres).exp); 
			 (yyval.expres).val = (yyvsp[-2].expres).val / (yyvsp[0].expres).val; type_validation((yyval.expres).val,(yyval.expres).val);
			 }
#line 2840 "y.tab.c"
    break;

  case 94:
#line 1107 "proiect.y"
                                    {
			 (yyval.expres).exp=malloc(200); sprintf((yyval.expres).exp, "(%s)", (yyvsp[-1].expres).exp); 
			 (yyval.expres).val = (yyvsp[-1].expres).val;
			 }
#line 2849 "y.tab.c"
    break;


#line 2853 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1113 "proiect.y"

void yyerror(char *s)
{
	printf("\nEROARE la linia [%d] :: %s... \n\n", yylineno, s);
}

int main(int argc, char **argv)
{
	yyin = fopen(argv[1], "r");

	FILE *file1 = fopen("symbol_table.txt", "w");
	FILE *file2 = fopen("symbol_table_functions.txt", "w");

	yyparse();

	fclose(file1);
	fclose(file2);
}


