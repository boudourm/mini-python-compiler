
typedef struct Pile Pile;
struct Pile{
			  char nom[50];
			  Pile *svt;

           };

Pile *pile;
Pile *pile2;

int nombre = 1 ;

void empiler( char nom[])
{
    Pile *tmp = malloc(sizeof(*tmp));
    strcpy(tmp->nom,nom);
    tmp->svt = pile;
    pile = tmp;
}


char* depiler()
{
	char nom[50];
    Pile *tmp = pile;
    if (pile != NULL)
    {
       strcpy(nom,tmp->nom);
        pile = tmp->svt;
        free(tmp);
    }
    return strdup(nom);
}

void empiler2( char nom[])
{
    Pile *tmp = malloc(sizeof(*tmp));
    strcpy(tmp->nom,nom);
    tmp->svt = pile2;
    pile2= tmp;
}

char* depiler2()
{
	char nom[50];
    Pile *tmp = pile2;
    if (pile2 != NULL)
    {
       strcpy(nom,tmp->nom);
        pile2 = tmp->svt;
        free(tmp);
    }
    return strdup(nom);
}


typedef struct ESPACE ESPACE;
struct ESPACE{
			  
               char nom[50];
			   int count ;
               int fin ;
               int instruction ;
               int eliff ;
               int elsee ;

        };


ESPACE TableEspace[1000];

int SizeTableSpace = 0;


typedef struct QDR QDR;
struct QDR{
			  
               char oper[100];
			   char op1[100];
			   char op2[100];
			   char res[100]; 
        };


QDR quad[1000];

int qc = 0;






void ajour_quad(int num_quad, int colon_quad, char val [])
{	
if (colon_quad==0) strcpy(quad[num_quad].oper , val);
else if (colon_quad==1) strcpy(quad[num_quad].op1 , val);
else if (colon_quad==2) strcpy(quad[num_quad].op2 ,val);
else if (colon_quad==3) strcpy(quad[num_quad].res , val);
}









typedef struct INSTRUCTION INSTRUCTION;
struct INSTRUCTION{
			  
               char valeur[100]; 
        };


INSTRUCTION instruction[1000];

int SizeInstruction = 0;


void remplireInstruction(char valeur[])
{ 
   strcpy(instruction[SizeInstruction].valeur , valeur); 
   
   SizeInstruction ++ ;
   
}

void  remplire_quadr(char oper[] ,char op1[], char op2[] , char res[])
{
  
	
strcpy(quad[qc].oper , oper);
strcpy(quad[qc].op1 , op1);
strcpy(quad[qc].op2 , op2);
strcpy(quad[qc].res , res);

 
qc++;
}

char * OPERATEUR(char opr[100]){
	     if(strcmp(opr,"<")==0) { return "BNL" ;}
	     if(strcmp(opr,">")==0) { return "BNG" ; }
	     if(strcmp(opr,"==")==0){ return "BNE";}
	     if(strcmp(opr,"<=")==0){ return  "BG" ;}
	     if(strcmp(opr,">=")==0){ return  "BL" ;}
	     if(strcmp(opr,"!=")==0){ return "BE" ;}
    return "";
}


void decaler(i)
{  int count =2 ;
   int pos ;
   while(count !=0){
    pos = i ;
      while(pos<SizeInstruction-1){
        instruction[pos] = instruction[pos+1];
        pos++;
      }
      SizeInstruction = SizeInstruction-1;
      count--;
   }

}
char* getSauv(int nombre){
	char sauv[10];
	char num_sauv[10];

	strcpy(sauv,"t");
	sprintf(num_sauv,"%d",nombre);
	
	return strcat(sauv,num_sauv); ;
}





 char* resulta()
{   
           
  char val [10]; 
  int i= 1;
  char t[10];  
     
 if(SizeInstruction==1){

      remplire_quadr("=",instruction[0].valeur,"","");
 
      SizeInstruction = 0 ;
  }









   while(i<SizeInstruction)
   { 

   	  if(power(instruction[i].valeur)==2) 
     {  strcpy(t,getSauv(nombre));
     	nombre++;
        remplire_quadr(instruction[i].valeur,instruction[i-1].valeur,instruction[i+1].valeur ,t); 
        strcpy(instruction[i-1].valeur,t);       
        decaler(i);
      
        i=i-2;
       }
  

    i=i+2;
   }
 

 i= 1;
  
   
   
   while(i<SizeInstruction)
   { 

   	  if(power(instruction[i].valeur)==1) 
     {  strcpy(t,getSauv(nombre));
     	nombre++;
        remplire_quadr(instruction[i].valeur,instruction[i-1].valeur,instruction[i+1].valeur ,t); 
        strcpy(instruction[i-1].valeur,t);       
        decaler(i);
       
        i=i-2;
       }
  

    i=i+2;
   }
 
       SizeInstruction = 0;
       
       char sauv[10];
	   char num_sauv[10];

	  nombre--;
	return  getSauv(nombre) ;
}


void afficher_qdr()
{
printf("********************* Les Quadruplets ***********************\n");
int i ;
for(i=0;i<qc;i++)
{
printf("\n %d - ( %s , %s , %s , %s)",i,quad[i].oper,quad[i].op1,quad[i].op2,quad[i].res);
printf("\n---------------------------------------------------\n");
}}















int power(char nom[])
{
 if(strcmp(nom ,"+")==0) return 1 ;
 if(strcmp(nom ,"-")==0) return 1 ;
 if(strcmp(nom ,"/")==0) return 2 ;
 if(strcmp(nom ,"*")==0) return 2 ;
  return 0;
}


int TriterInstruction(int Condition)
{ int PrO =0;
  int PrF =0 ;
  int exist =0 ; 
  char valeur[100];
  char valeur2[100];
  char OneValeurAndCondition =0; 
    strcpy(valeur,depiler());  
     if(pile==NULL && Condition==1) 
      { 
        OneValeurAndCondition=1;
       
       }
   
   empiler(valeur);

  while(pile!=NULL){
      
      strcpy(valeur,depiler());  
      empiler2(valeur);
       
    if(strcmp(")", valeur)==0){
       exist =1;
       
      while(pile!=NULL && strcmp(valeur,"(")!=0){      
           
           strcpy(valeur,depiler());
           if(strcmp(valeur,"(")!=0)
          { empiler2(valeur); }         
      }
         if(strcmp(valeur,"(")==0){
               

        strcpy(valeur2,depiler2());
          
        while(pile2 !=NULL && exist==1)
        {  
           if(strcmp(valeur2,")")!=0)
           { remplireInstruction(valeur2); 
          	strcpy(valeur2,depiler2());                         
           }else{
           	exist =0 ;
           }

        }

         
//IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIILLLLLLLLLLLLLLLLLLLLLLLLLLL YYYYYYYYYYYYYYYYYYYYYYYYYA UN PROBLEM CAR RESULTA NO  return pas t +"nombre"             
             empiler2(resulta()); 
              nombre++;    
              
           while(pile2!=NULL)
           { strcpy(valeur2,depiler2()); 
             empiler(valeur2);
           }       
   
        }
     }     
   

   }



 



while(pile2!=NULL){
  
  strcpy(valeur,depiler2());
  remplireInstruction(valeur);       
}
  
resulta();
 nombre++;


return OneValeurAndCondition ;
   
}
















void fini(int count , char nom[]){
  int i= 0;
    
   while(i<SizeTableSpace)
   {    
   	      if(TableEspace[i].count >=count ){
   	   	    TableEspace[i].fin =1 ;
          if(strcmp("elif", nom)==0 ){
                   int y = TableEspace[i].count -count ;
                   if(y ==0 ){
                   TableEspace[i].eliff++;     
                }}
            


             if(strcmp("else", nom)==0 ){
                  
                  int y = TableEspace[i].count -count ;
                  
                   if(y ==0 ){
                   TableEspace[i].elsee++;     
                }}
          
       }
      
       i++;
   }	

}
int ExistElifOrIf(int count)
{ int i =0 ;
	while(i<SizeTableSpace )
    {     
    	 if(strcmp("if", TableEspace[i].nom)==0 || strcmp("elif", TableEspace[i].nom)==0 ){
           
            if (TableEspace[i].count==count &&  TableEspace[i].elsee==1)
            {
            	       
            TableEspace[i].elsee=2;
    
    	 	return 1 ;
    	     }
    	     
             if (TableEspace[i].count==count &&  TableEspace[i].elsee==0 && TableEspace[i].eliff==1 )
            {
            	       
            TableEspace[i].eliff=2;
    
    	 	return 2 ;
    	     }
    	}
    	 	i++;
    }		
    return 0 ;

} 

  
 


int VerifierElse(char nom[]){
  
    if(strcmp("else", nom)==0)
     { return 1 ;
     }
       return 0 ;
}

int AjouterTableEspace( char nom[] ,int count,int fin)
{ 
	 fini(count,nom);
 if(SizeTableSpace==0  &&  count!=0){
      printf("\nError syntaxique Vous ne devriez pas ecrire d espace quand vous commencez \n");
 }else{
   if(AllInstructionBefor()==1 && count != TableEspace[SizeTableSpace-1].count ){
      printf("\nError syntaxique il faut aligner le code  \n");  
   }else{
     if(DebutIfOrElifOrElse(count)==0){
         printf("\nError syntaxique  l instruction %s est vide  \n",TableEspace[SizeTableSpace-1].nom);    
      }else{
        if(InIfOrElifOrElse(count)==0 && count!=0){

          printf("\nError syntaxique il faut aligner le code \n"); 	
        }else{
        	  
              if(  VerifierElse(nom)==1 && ExistElifOrIf(count)!=1){
                   printf("\nError syntaxique else sans if ou bien elif \n");

              }else{

                 if(VerifierElif(nom)==1 && ExistElifOrIf(count)!=2){
                   printf("\nError syntaxique elif sans if ou bien elif \n");

                 }

              }
        }



      } 
   } 

 } 


 strcpy(TableEspace[SizeTableSpace].nom ,nom);
 TableEspace[SizeTableSpace].count = count;
 TableEspace[SizeTableSpace].fin = 0;
 TableEspace[SizeTableSpace].instruction = 0;
  TableEspace[SizeTableSpace].eliff=0;
   TableEspace[SizeTableSpace].elsee=0;
 SizeTableSpace ++ ;
}    


/*void  AfficherTableEspace()
{   int i = 0 ;
	while(i<SizeTableSpace)
	{ 
		 printf("\n  nom %s   count %d     fin%d   instruction%d", TableEspace[i].nom ,TableEspace[i].count,
		 	TableEspace[i].fin , TableEspace[i].instruction);
         i++;
	}	
}*/


int VerifierElif(char nom[] )
 { 
     if(strcmp("elif", nom)==0)
     { return 1 ;
     }
       return 0 ;
 } 

int AllInstructionBefor(){
 int i = 0 ;
   while(i<SizeTableSpace)
   { 
      if(strcmp("inst", TableEspace[i].nom)!=0){
         return 0 ; 
      }
         i++;  
   }
         return 1;
}

int DebutIfOrElifOrElse(int count){
   int i = 0 ;
   while(i<SizeTableSpace)
   { 
     if(strcmp("if", TableEspace[i].nom)==0 || strcmp("elif", TableEspace[i].nom)==0 || 
     	strcmp("else", TableEspace[i].nom)==0){
         if(i==(SizeTableSpace-1)){
         if( count <= TableEspace[SizeTableSpace - 1].count){
            
         	return 0;}  
           else{
           	   
          	     TableEspace[SizeTableSpace - 1].instruction = count ;
               }
             }                                                
           }
             i++;  
       }

             return 1; 
  }



int InIfOrElifOrElse(int count){
 int i = 0 ;
    while(i<SizeTableSpace)
    {  
     if(strcmp("if", TableEspace[i].nom)==0 || strcmp("elif", TableEspace[i].nom)==0 || 
     	strcmp("else", TableEspace[i].nom)==0){
        
         	if(count ==TableEspace[i].instruction && TableEspace[i].fin==0){
               
              
              return 1 ;  
       }
     

 }
     	i++;
    


}


return 0;


}






















