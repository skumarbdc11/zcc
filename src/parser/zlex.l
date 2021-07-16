D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "zstruct.h"
#include "zparser.h"
#include "zutils.h"
#include "zpreproc.h"

extern int g_scope_level;
extern long g_stack_size;
extern FILELIST_t g_filelist[MAX_INCLUDES];
extern int inc_level;
extern void yyerror(char* s);

int g_column = 1;
int g_line = 1;

void count();
void comment();
int check_type();
%}

%%
"/*"			{ comment(); }

(#include).*\n		{ 
						g_filelist[inc_level].linecount = ++g_line; 
						inc_level++;
						update_stack(yytext); 
						g_line = 1;
						g_filelist[inc_level].linecount = 0; 
					}
(#define).*\n		{ g_filelist[inc_level].linecount = ++g_line; }
(#endinclude)\n		{ 
						inc_level--; 
						g_line = g_filelist[inc_level].linecount; 
					}

"auto"			{ count(); return(AUTO); }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count(); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ count(); return(EXTERN); }
"float"			{ count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"int"			{ count(); return(INT); }
"long"			{ count(); return(LONG); }
"register"		{ count(); return(REGISTER); }
"return"		{ count(); return(RETURN); }
"short"			{ count(); return(SHORT); }
"signed"		{ count(); return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ count(); return(UNSIGNED); }
"void"			{ count(); return(VOID); }
"volatile"		{ count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }

{L}({L}|{D})*	{ 
					count();
					yylval.token.token = IDENTIFIER;
					yylval.token.data = (char*)strdup(yytext);
					return(check_type()); 
				}

0[xX]{H}+{IS}?	{ 
					unsigned char sign=0;

					count();
					yylval.pdata = new_data(INT_t,get_intval(HEX, yytext, &sign));
					if(sign)
						DATA_SIGNED(yylval.pdata) = 1;
					else
						DATA_SIGNED(yylval.pdata) = 0;
					return(HEX_CONSTANT); 
				}
0{D}+{IS}?		{
					unsigned char sign=0;

					count();
					yylval.pdata = new_data(INT_t,get_intval(OCT, yytext, &sign));
					if(sign)
						DATA_SIGNED(yylval.pdata) = 1;
					else
						DATA_SIGNED(yylval.pdata) = 0;
					return(OCT_CONSTANT); 
				}
{D}+{IS}?		{
					unsigned char sign=0;

					count();
					yylval.pdata = new_data(INT_t,get_intval(DEC, yytext, &sign));
					if(sign)
						DATA_SIGNED(yylval.pdata) = 1;
					else
						DATA_SIGNED(yylval.pdata) = 0;
					return(DEC_CONSTANT); 
				}

'(\\.|[^\\'])+'	{ 
					unsigned char sign=0;
					int val=0;

					count();
					if(yytext[1]=='\\')
					{
					  switch(yytext[2])
					  {
					  case 'n':
						val = '\n';
						break;
					  case '0':
					    val = '\0';
					    break;
					  case 't':
					    val = '\t';
					    break;
					  case 'b':
					    val = '\b';
					    break;
					  case 'r':
					    val = '\r';
					    break;
					  default:
					    yyerror("Invalid character constant");
					  }
					  yylval.pdata = new_data(INT_t,val);
					}
					else
					   yylval.pdata = new_data(INT_t,get_intval(CHR, yytext, &sign));
					DATA_SIGNED(yylval.pdata) = 0;
					return(DEC_CONSTANT); 
				}

\"(\\.|[^\\"])*\"	{
					char *str;
					 
					count();
					str = (char*)strdup(yytext+1);
					str[strlen(str)-1] = '\0';
					yylval.pdata = new_data(STRING_t, str);
					return(STRING_LITERAL); 
				}

{D}+{E}{FS}?	|
{D}*"."{D}+({E})?{FS}?	|
{D}+"."{D}*({E})?{FS}?	{
					unsigned char sign=0;

					count();
					yylval.pdata = new_data(FLOAT,get_fltval(yytext));
					return(FLT_CONSTANT); 
				}



"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ 
					count(); 
					if(!g_scope_level)
						g_stack_size = 0;
					g_scope_level++; 
					return('{'); 
				}
("}"|"%>")		{ 
					count(); 
					g_scope_level--;
					return('}'); 
				}
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return(ASSIGN_OP); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
"?"			{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* ignore bad characters */ }

%%

yywrap()
{
	return(1);
}


void comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}
}


void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			g_column = 0, g_filelist[inc_level].linecount = ++g_line;
		else if (yytext[i] == '\t')
			g_column += 8 - (g_column % 8);
		else
			g_column++;
}


int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/

	return(IDENTIFIER);
}
