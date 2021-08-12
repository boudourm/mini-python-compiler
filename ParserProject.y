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

START : START_WITH_SPACES START | START_WITH_SPACES 

START_WITH_SPACES : SPACES CODE  jump JUMPS 

CODE : DICLARATION | AFFECTATION  | CONDITION_IF   | Commenter 

CONDITION_IF : IF CONDITION  jump JUMPS START CONDITION_ELIF_OR_ELSE   

CONDITION_ELIF_OR_ELSE : ELIF CONDITION jump JUMPS START CONDITION_ELIF_OR_ELSE    | CONDITION_ELSE    

//Condition_if  Exemple :if( a = b) :
CONDITION: SPACES   PrO SPACES EXPRITION_LOGIQUE PrF  SPACES  DeuxPoints  
 
//condition_else:
CONDITION_ELSE : ELSE SPACES DeuxPoints SPACES 

EXPRITION_LOGIQUE : EXPRITION OPERATEUR_COMPARAISON SPACES EXPRITION 

// Instruction Exemple : a =5+a-7
AFFECTATION : variable SPACES Equal SPACES EXPRITION    
 
// Exprition Exemple : 7+a-5+2
EXPRITION :  VALEUR_OR_VARIABLE SPACES OPIRATEUR SPACES EXPRITION    | VALEUR_OR_VARIABLE  SPACES | PrO EXPRITION PrF  | PrO EXPRITION PrF OPIRATEUR SPACES EXPRITION  
  
// une Valeur comme 5 , 5.5  ou bien un variable comme A ...
VALEUR_OR_VARIABLE : VALEUR | variable
 
//DICLARATION DES VARIABLE 
DICLARATION : TYPE DECLARER 

DECLARER : space SPACES variable SPACES INISI MOR_DECLARATION 

// S a dir plusieur declaration dans la meme ligne Exemple : int x, y ,z=5 ... 
MOR_DECLARATION : Vargule SPACES variable SPACES INISI MOR_DECLARATION | 

// variable est inisialiser ou non dans la declaration Exemple : int x =5
INISI :  INI | 

// inisialisation
INI : Equal SPACES VALEUR SPACES

// Les Valeur
VALEUR : Entier |Real  |Character

//Les Type Exist
TYPE : Int | Float | Char

OPERATEUR_COMPARAISON : PointExclamation Equal | Equal Equal | Inf | Sup | Sup Equal | Inf Equal 

// Les opirateur + - * /
OPIRATEUR : Plus |Minus |Div |Mul

// Les Espace et les Jumps
SPACES : space SPACES |

JUMPS : jump JUMPS |

%%

void yyerror(char* s){

	printf ("Error %s\n",s);

}

int yywrap(){

    return 1;

}

int main(void){ return yyparse();}
