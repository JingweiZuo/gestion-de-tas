#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char *tas_malloc(unsigned int taille)
{
  int courant = first_fit(int taille);
  assert(taille<=taillecourant);//taille<taille_bloc
  
  if (taille<=taille(courant))
  {
    if((taille(courant)-taille)>=0)
    {
      //decouper 2 blocs
      //taillecourant1=taille;
      //taillecourant2=taillecourant-taille;
      tas[courant]=taille(courant)-taille;
      //adr_bloc[courant+1]=adr_bloc[courant];
      //CP=courant;
      &tas[courant+1]=&adr_bloc[courant]+taille;//changer l'address de courant
      libre = adr_bloc(courant+taille);
      return adr_bloc[courant];//return l'address de la zone allouée
    }
  }
  return NULL;
}

int bloc_suivant(int i)　{
  return tas[i]+1;
}

char *adr_bloc(int i){
  return (char *)&tas[i+1]; //&tas[i＋1]
}

int taille_courant(int i){
  return tas[i]);
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
    cp=courant;
    courant =bloc_suivant(courant);
  }
  return FIN;
}



int tas_free(char *ptr)
{

}
