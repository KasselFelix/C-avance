#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utilitaires_tableaux.h"
#include "tris.h"


int main()
{
	int nbVal=1;
	int *tab=lire_tableau("100_valeurs.txt", &nbVal);
	int *tab2=nouveau_tableau(nbVal);
	ecrire_tableau("10_valeurs.txt",tab,nbVal);
	afficher_tab(tab,nbVal);
	printf("========================\n");
	afficher_tab(tab2,nbVal);
	
	
	free(tab);
  return 0;

}
