%{
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



%}

%token BOOL START CONST END IF THEN ELSE ENDIF WHILE DO ENDWHILE FOR STARTFOR ENDFOR CLASS AND OR
%token EQ ASSIGN NOT NE LT LE GT GE PLUS MINUS MULTIP DIVIDE
%token TIP ID INTEGER CHAR FLOAT STRING NR_INT
%token PRINT SPECIAL_PRINT TXT1 TXT2 NUME_CLASA

%start compilator

%left ';'
%left OR AND
%left PLUS MINUS
%left MULTIP DIVIDE
%left '('  ')'

%union
{
    int num;
    float fl;
    char* str;
	_Bool bl;
	struct expp
	{
		float val;
		char* exp;
	}expres;
}

%type <num> INTEGER
%type <fl> FLOAT 
%type <str> TIP ID CHAR STRING BOOL NR_INT clasa NUME_CLASA param_list_dec param_dec parametrii elemente elemente_int param_list_call param_call call_list TXT1 TXT2
%type <expres> expresie operand
%%

compilator : program {printf("\nProgramul este corect sintactic! \n\n"); Print();}
           ;

program : global main
        | main
        ;      

global : clase functii declaratii {get_symbol_table("global");}
       | functii declaratii {get_symbol_table("global");}
       | clase functii {get_symbol_table("global");}
       | clase declaratii {get_symbol_table("global");}
       | clase {get_symbol_table("global");}
       | functii {get_symbol_table("global");}
       | declaratii {get_symbol_table("global");}
	   | declaratii functii clase {get_symbol_table("global");}
	   | declaratii functii {get_symbol_table("global");}
	   | declaratii clase {get_symbol_table("global");}
	   | functii clase declaratii {get_symbol_table("global");}
	   | functii declaratii clase {get_symbol_table("global");}
	   | clase declaratii functii {get_symbol_table("global");}
	   | functii clase {get_symbol_table("global");}
	   | declaratii clase functii {get_symbol_table("global");}
       ;

clase : clasa
      | clase clasa
      ;

clasa : CLASS ID '{' declaratii '}' ';' {save_class_name($2);  $$ = malloc(256); strcpy($$,"in clasa "); strcat($$, $2); get_symbol_table($$);}
      ;     

functii : functie
	    | functii functie
        ;

functie : TIP ID param_list_dec '@' blocuri '@' { char tmp[256]; sprintf(tmp, "in functie %d", nr_funct+1); get_symbol_table(tmp); declaratieFunctie($1,$2);}
        ;

param_list_dec : '(' ')' { $$=malloc(200); $$[0]=0;}
               | '(' parametrii ')' { $$ = $2;}
               ;

parametrii : param_dec
	       | parametrii ',' param_dec

param_dec : TIP ID {save_parameters($1, $2);}
          ;

param_list_call : '(' '@' ')' { $$=malloc(200); $$[0]=0; }
			    | '(' call_list ')' {$$ = $2;}

call_list : param_call
		  | call_list ',' param_call

param_call :  '@' ID {save_call_param($2);}
		   ;

declaratii : declaratie
           | declaratii declaratie
           ;

declaratie : TIP ID ';' { declaratie_neinit($1,$2,0); }
		   | TIP ID ASSIGN operand
		   | NUME_CLASA ID ';' {check_class_name($1);}
           | TIP ID ASSIGN INTEGER ';' {declaratie_int($1,$2,$4,0);}
           | TIP ID ASSIGN FLOAT ';' {declaratie_float($1,$2,$4,0);}
           | TIP ID ASSIGN STRING ';' {declaratie_string($1,$2,$4,0);}
           | TIP ID ASSIGN CHAR ';' {declaratie_char($1,$2,$4,0);}
		   | TIP ID ASSIGN BOOL ';' {declaratie_bool($1,$2,$4,0);}
           | TIP ID ASSIGN ID ';' {declaratie_id($1,$2,$4,0);}
           | CONST TIP ID ';' {declaratie_neinit($2,$3,1);}
           | CONST TIP ID ASSIGN INTEGER ';' {declaratie_int($2,$3,$5,1);}
           | CONST TIP ID ASSIGN FLOAT ';' {declaratie_float($2,$3,$5,1);}
           | CONST TIP ID ASSIGN ID ';' {declaratie_id($2,$3,$5,1);}
           | ID param_list_call ';' {apelareFunctie($1); nrCall++;}
           | array ';'
		   | TIP ID param_list_dec '@' blocuri '@' { declaratieFunctie($1,$2);}
           ; 

array : TIP ID '[' INTEGER ']' {declaratieArray_neinit($1,$2,$4,0);}
      | TIP ID '[' INTEGER ']' '[' INTEGER ']' {declaratieArray_neinit($1,$2,$4,$7);}
      | TIP ID '[' INTEGER ']' ASSIGN '{' elemente_int '}' {declaratieArray_init($1,$2,$4,0,$8);}
      | TIP ID '[' INTEGER ']' '[' INTEGER ']' ASSIGN '{' elemente_int '}' {declaratieArray_init($1,$2,$4,$7,$11);}
      ;

elemente_int : NR_INT {$$ = $1;}
             | elemente_int ',' NR_INT {$$ = $1; strcat($$,",");strcat($$,$3);}
             ;   

main : START '{' blocuri '}' END {get_symbol_table("local");}
     ;

blocuri : bloc
        | blocuri bloc
        ;

bloc : FOR '(' INTEGER '&' INTEGER '&' INTEGER ')' STARTFOR '{' blocuri '}' ENDFOR {}
     | IF '(' conditii ')' THEN '{' operatii '}' ENDIF
     | IF '(' conditii ')' THEN '{' operatii '}' ELSE '{' operatii '}' ENDIF
     | WHILE '(' conditii ')' DO '{' blocuri '}' ENDWHILE
     | operatii
     | declaratie
	 | SPECIAL_PRINT '(' TXT1 expresie TXT2 ',' expresie ')' ';' {
		 	verificareExpresiiPrint($4.exp, $7.exp, $7.val);
		 } 
     ;

conditii : operand
         | BOOL
         | NOT operand
         | operand EQ operand 
         | operand LE operand 
         | operand GE operand
         | operand LT operand 
         | operand GT operand
         | operand NE operand
         | conditii AND conditii
         | conditii OR conditii
         ;

operand : ID {$$.val=get_var_value($1); $$.exp = strdup($1);}
        | ID '[' INTEGER ']' {$$.val=get_array_value($1,$3,0); char tmp[256]; sprintf(tmp, "%s[%d]", $1, $3); $$.exp = strdup(tmp);}
        | ID '[' INTEGER ']' '[' INTEGER ']' {$$.val=get_array_value($1,$3,$6); char tmp[256]; sprintf(tmp, "%s[%d][%d]", $1, $3, $6); $$.exp = strdup(tmp);}
        | INTEGER {$$.val = $1; char tmp[100]; sprintf(tmp, "%d", $1); $$.exp = strdup(tmp);}
        | FLOAT {$$.val = $1; char tmp[100]; sprintf(tmp, "%f", $1); $$.exp = strdup(tmp);}
        ;

operatii : asignare_expresie ';'
         | operatii ';' asignare_expresie ';'
         ;

asignare_expresie : ID ASSIGN expresie {/*int exp = evalAST($3);*/ exprAssignment($1,$3.val); }
                  ;

expresie : operand
         | expresie PLUS expresie {
			 	$$.exp=malloc(200); sprintf($$.exp, "%s + %s", $1.exp, $3.exp); 
			 	$$.val = $1.val + $3.val; type_validation($$.val,$$.val);
			 }
         | expresie MINUS expresie {
			 $$.exp=malloc(200); sprintf($$.exp, "%s - %s", $1.exp, $3.exp); 
			 $$.val = $1.val - $3.val; type_validation($$.val,$$.val);
			 }
         | expresie MULTIP expresie {
			 $$.exp=malloc(200); sprintf($$.exp, "%s * %s", $1.exp, $3.exp); 
			 $$.val = $1.val * $3.val; type_validation($$.val,$$.val);
			 }
         | expresie DIVIDE expresie {
			 $$.exp=malloc(200); sprintf($$.exp, "%s / %s", $1.exp, $3.exp); 
			 $$.val = $1.val / $3.val; type_validation($$.val,$$.val);
			 }
		 | '(' expresie ')' {
			 $$.exp=malloc(200); sprintf($$.exp, "(%s)", $2.exp); 
			 $$.val = $2.val;
			 }
         ;

%%
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


