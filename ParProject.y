%{

   #include <stdio.h>

   #include <stdlib.h>

   void yyerror(char*);

%}

%union {}

%token IF space jump tiret8  DeuxPoints
 Equal  Apostrophe variable PrO PrF 
 Int Float Char Entier  Real Vargule
 Character Plus Minus PointExclamation
 Sup Inf ELSE ELIF  Div Mul
 OR AND Commenter tab ANDC ORC

%start START

%%//automate

START : SPACES  CODE   

CODE : CONDITION_IF  |  AFFECTATION jump | Commenter jump

CONDITION_IF : IF CONDITION    

CODES :   CODE   CODES | CODE 
   
//Condition_if  Exemple :if( a = b) :
CONDITION : SPACES   PrO SPACES EXPRITION_LOGIQUE PrF  SPACES  DeuxPoints jump WITH_ELSE

WITH_ELSE :   CODES  CONDITION_ELSE    
 
//condition_else:
CONDITION_ELSE : ELSE SPACES DeuxPoints SPACES jump  

EXPRITION_LOGIQUE : EXPRITION OPERATEUR_COMPARAISON SPACES EXPRITION 

// Exprition Exemple : 7+a-5+2
EXPRITION :  VALEUR_OR_VARIABLE SPACES OPIRATEUR SPACES EXPRITION    | VALEUR_OR_VARIABLE  SPACES | PrO EXPRITION PrF  | PrO EXPRITION PrF OPIRATEUR SPACES EXPRITION  
  





























// Instruction Exemple : a =5+a-7
AFFECTATION : variable SPACES Equal SPACES EXPRITION  





VALEUR_OR_VARIABLE : VALEUR | variable

// Les Valeur
VALEUR : Entier | Real  | Character

//AND_OR_OR : AND | OR | ANDC | ORC

OPERATEUR_COMPARAISON : PointExclamation Equal | Equal Equal | Inf | Sup | Sup Equal | Inf Equal 

// Les opirateur + - * /
OPIRATEUR : Plus |Minus |Div |Mul

// Les Espace et les Jumps
SPACES : space SPACES |

//JUMPS : jump JUMPS |

%%

void yyerror(char* s){

	printf ("Error %s\n",s);

}

int yywrap(){

    return 1;

}

int main(void){ return yyparse();}
