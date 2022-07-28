#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void echanger_elem_tab(int tab[], int i, int j)
	{
	int t = tab[i];
	tab[i] = tab[j];
	tab[j] = t;
	}

int tab_trie(int tab[], int n)
	{
	int i;
	for (i = 1; i < n; i++)
		if( tab[i] < tab[i-1])
			return 0;
	return 1;
	}

int *nouveau_tableau(int n) {
	int *tab=malloc(n*sizeof(int));
  return tab;
}

int * detruire_tableau(int *t) {
	free(t);
  return NULL;
}

#define LIGNE_MAX 9999

int compter_lignes(char *nomFichier){
	FILE *pFi;
	int nbL=0;
	char c;
	
	pFi=fopen(nomFichier, "r");
	if(pFi==NULL){
		fprintf(stderr, "compter_lignes:: Ne peut ouvrir %s\nEXITING\n", nomFichier);
		exit(1);
	}
	while((c=fgetc( pFi))!=EOF)
		if(c=='\n')
			nbL++;
	fclose(pFi);
	return nbL;
}

int *lire_tableau(char *nomFichier, int *p_nbVal){
	int i;
	*p_nbVal=compter_lignes(nomFichier);
	int *tab=nouveau_tableau(*p_nbVal);
	int *tmp=tab;
	FILE *pFi;
	pFi=fopen(nomFichier, "r");
	if(pFi==NULL){
		fprintf(stderr, "lire_tableau:: Ne peut ouvrir %s\nEXITING\n", nomFichier);
		exit(1);
	}
	

	for(i=0;i<*p_nbVal;i++){
		fscanf(pFi,"%d",&tab[i]);
	}
	fclose(pFi);
  return tmp;
}


void ecrire_tableau(char *nomFichier, int *tab, int n){
	int i;
	FILE *pFi;
	pFi=fopen(nomFichier, "w");
	if(pFi==NULL){
		fprintf(stderr, "ecrire_tableau:: Ne peut ouvrir %s\nEXITING\n", nomFichier);
		exit(1);
	}
	
	for(i=0;i<n;i++){
		fprintf(pFi,"%d\n",tab[i]);
	}
	fclose(pFi);	
	return ;
}

void afficher_tab(int tab[], int n){
	int i;
	for(i=0;i<n;i++){
		fprintf(stdout,"%d\n",tab[i]);
	}
}




