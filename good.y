%{
   #include <stdio.h>
   #include <stdlib.h>    
   #include "function.h"
 
   int yylex();
  

   void yyerror(char*msg);
   int count = 0 ; 
   char tmp1[100];
   char tmp2[100];
   char operateur[100];
   int cond1 = 0 ;
   int cond2 = 0;
   
%}

%union {
char *str; 
int ent;
float real;  	
}


%token IF  
%token space 
%token jump 
%token tiret8  
%token DeuxPoints
%token Equal  
%token Apostrophe 
%token <str>variable
%token PrO 
%token PrF 
%token Int
%token Float
%token Char
%token <str>Entier
%token Real
%token Vargule
%token Character
%token Plus
%token Minus
%token PointExclamation
%token Sup
%token Inf
%token ELSE
%token ELIF
%token Div
%token Mul
%token OR
%token AND
%token Commenter
%token tab
%token ANDC
%token ORC



%start START

%%//automate

START : START_WITH_SPACES START | START_WITH_SPACES 

START_WITH_SPACES : SPACES CODE  jump { count=0 ; }JUMPS 

CODE :  AFFECTATION {AjouterTableEspace( "inst" ,count,0);  } | CONDITION_IF_OR_ELIF   | Commenter  | CONDITION_ELSE | DICLARATION {AjouterTableEspace( "inst" ,count,0);}

CONDITION_IF_OR_ELIF : IF_OR_ELIF CONDITION  SPACES      

CONDITION : SPACES PrO SPACES EXPRITION_LOGIQUE PrF  SPACES  DeuxPoints  
   
CONDITION_ELSE : ELSE {AjouterTableEspace( "else" ,count,0);}  SPACES DeuxPoints SPACES 

EXPRITION_LOGIQUE    : EXPRITION_LOGIQUE_B  EXPRITION { cond2=TriterInstruction(1); 
                       strcpy(operateur,OPERATEUR(operateur));                       
                       if(cond2==1){
                       strcpy(tmp2,quad[qc-1].op1); 
                       qc--;}else{
                        strcpy(tmp2,quad[qc-1].res);

                       }
                       cond1=0;
                       cond2=0;                         
                       remplire_quadr(operateur,tmp1 ,tmp2 ,""); afficher_qdr(); }
  
EXPRITION_LOGIQUE_B : EXPRITION_LOGIQUE_A OPERATEUR_COMPARAISON SPACES 

EXPRITION_LOGIQUE_A  : EXPRITION { cond1 =TriterInstruction(1);if(cond1==1){strcpy(tmp1,quad[qc-1].op1);
                                                                            qc--;}else{
                                                                            strcpy(tmp1,quad[qc-1].res);}  }  
       
AFFECTATION   : variable   SPACES Equal SPACES EXPRITION  {TriterInstruction(0); ajour_quad(qc-1, 3, $1) ;afficher_qdr();}  
 
EXPRITION:VALEUR_OR_VARIABLE SPACES OPIRATEUR SPACES EXPRITION|VALEUR_OR_VARIABLE SPACES|Pro_EXPRITION_PrF_B  PrF  { empiler(")");} | PrO_EXPRITION_PrF_OPIRATEUR_SPACES_EXPRITION_D  OPIRATEUR SPACES EXPRITION

PrO_EXPRITION_PrF_OPIRATEUR_SPACES_EXPRITION_D :  Pro_EXPRITION_PrF_B PrF  { empiler(")");}

Pro_EXPRITION_PrF_B : Pro_EXPRITION_PrF_A EXPRITION

Pro_EXPRITION_PrF_A : PrO   { empiler("(");}

IF_OR_ELIF : IF {AjouterTableEspace( "if" ,count,0); }   | ELIF {AjouterTableEspace( "elif" ,count,0);}
 
DICLARATION : TYPE DECLARER 

DECLARER : space SPACES variable SPACES INISI MOR_DECLARATION 
 
MOR_DECLARATION : Vargule SPACES variable SPACES INISI MOR_DECLARATION | 

INISI :  INI | 

INI : Equal SPACES VALEUR SPACES

//Les Type Exist
TYPE : Int 

VALEUR_OR_VARIABLE : VALEUR | variable {empiler($1);}
 
VALEUR : Entier {empiler($1);}

OPERATEUR_COMPARAISON : PointExclamation Equal {strcpy(operateur,"!=");} | 
Equal Equal {strcpy(operateur,"==");}   | Inf  {strcpy(operateur,"<");}  | 
Sup {strcpy(operateur,">");} | Sup Equal {strcpy(operateur,"<=");} | Inf Equal {strcpy(operateur,">=");} 

OPIRATEUR : Plus { empiler("+");} | Minus { empiler("-");} | Div { empiler("/");} | Mul { empiler("*");}

SPACES : space SPACES {count++;} |

JUMPS : jump JUMPS |


%%

void yyerror(char* s){

	printf ("Error %s\n",s);

}

int yywrap(){

    return 1;

}

int main(void){ return yyparse();}
