#include <stdio.h>
#include "affiche_tas.h"
#include <ctype.h>



#include <assert.h>
#include <stdlib.h>
#include <string.h>

void afficher_tas(){
  printf ("libre = %d\n", libre);
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 16; j++) { 
      printf("%4d", j + 16*i);
    }
    printf("\n");
    for (j = 0; j < 16; j++) { 
      printf("%4d", tas[j + 16*i]);
    }
    printf("\n");
    for (j = 0; j < 16; j++) { 
      if (isalnum(tas[j + 16*i])) {
	printf("%4c", tas[j + 16*i]);
      } else {
	printf("    ");
      }
    }
    printf("\n\n");
  }
  printf("---------------------------------------------------------------\n\n");
}

void tas_init(){
  libre = 0;
  tas[0] = TAILTAS;
  tas[1] = FIN;
  // debug
  for (int i = 2; i < TAILTAS+1; i++) {
    tas[i] = 'z';
  }
}

int bloc_suivant(int i){
  return tas[i]+i+1;
}//*****important

char *adr_bloc(int i){
  return (char *)&tas[i+1]; //&tas[i＋1]
}

int taille_courant(int i){
  return tas[i];
}

int first_fit(int taille){
  int courant=libre; // au début ,libre=0
  int cp = -1;
  assert(taille>=0);
  assert(taille<=TAILTAS);
  while(courant!=FIN)
  {
    assert(courant>=0 &&courant<=TAILTAS);
    assert(courant>=cp);
    if(taille_courant(courant)>=taille)
      return courant;
    cp=courant;  //courant précédent
    courant =bloc_suivant(courant);//***important
  }
  return FIN;
}

char *tas_malloc(unsigned int taille)
{
  int courant = first_fit(taille);
  assert(taille<=taille_courant(courant));//taille<taille_bloc
  
  if (taille<=taille_courant(courant))
  {
    if((taille_courant(courant)-taille)>=1)
    {
      //decouper 2 blocs
      //taillecourant1=taille;
      //taillecourant2=taille_courant-taille;
      tas[courant]=taille;
      tas[courant+taille]=taille_courant(courant)-taille;
      libre = courant+taille+1;

      return adr_bloc(courant);//return l'address de la zone allouée
    }
  }
  return NULL;
}

void tas_free(char *ptr)
{
  int courant=0;
  
  for (int i=0 ; i < 128 ; i++)
  {
    if ((char *)&tas[i+1] == ptr)
    {
      courant = i;
      //printf("%d\n",courant);
      break;
    }    
  }
  

  for (int i=1 ; i<=tas[courant] ; i++)
  {
    tas[courant+i]=' ';
  }
  tas[courant+1] = libre ; 
  libre = courant;
}

int main(){
  tas_init();
  char *p1, *p2, *p3, *p4;
  p1 = (char *) tas_malloc(10);
  p2 = (char *) tas_malloc(9);
  p3 = (char *) tas_malloc(5);

  strcpy(p1,"tp 1");
  strcpy(p2,"tp 2");
  strcpy(p3,"tp 3");
  printf(" %s\n %s\n %s\n ",p1,p2,p3);
  afficher_tas();

  tas_free(p2);
  printf(" %s\n %s\n ",p1,p3);
  afficher_tas();

  p4 = (char *) tas_malloc(8);
  strcpy(p4,"systeme");
  printf(" %s\n %s\n %s\n ",p1,p4,p3);
  afficher_tas();
}

