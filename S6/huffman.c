#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arbre_freq.h"
#include "huffman.h"

#define BUFFER_SIZE 256

int *distri_code(FILE *f) {
  int c;
  int i;
  int *tab = (int *) malloc(256 * sizeof(int));
  if (!tab)
    {
      fprintf(stderr,"Impossible d allouer le tableau de distribution\n");
      exit(1);
    }
  for(i=0;i<256;i++) tab[i]=0;
  while((c=fgetc(f))!=EOF) {
    tab[(unsigned char) c]++;
  } return tab;
}

PArbreBinaire creer_arbre_huffman(char lettre, unsigned int nb_occ) {
  PArbreBinaire pah = creer_arbre(1,dupliquer_lf, copier_lf, detruire_lf, afficher_lf, comparer_lf,
				  ecrire_lf, lire_lf);
  LettreFrequence lf={lettre, nb_occ};
  pah->racine=creer_noeud_binaire(pah,&lf); // la donnee sera copiee
  return pah;
}
PListe creer_liste_occ(int *occ) {
  PListe pl=(PListe)malloc(sizeof(Liste));
  pl->elements=NULL;
  pl->dupliquer=dupliquer_ah;
  pl->copier=copier_ah;
  pl->detruire=detruire_ah;
  pl->afficher=afficher_ah;
  pl->comparer=comparer_ah;
  pl->ecrire=ecrire_ah;
  pl->lire=lire_ah;

  int i;
  PArbreBinaire pah=creer_arbre_huffman(0,0);
  for (i=0;i<256;i++) {
    if (occ[i]>0) {
      LettreFrequence *plf=(LettreFrequence *)pah->racine->data;
      plf->lettre=i;
      plf->nb_occ=occ[i];
      printf( "avant\n" );
  afficher_liste( pl );
  printf( "arbre\n" );
  afficher_ah( pah );

      inserer_place(pl, pah);
      printf("après\n" );
  afficher_liste( pl );
    }
  }
  detruire_ab(pah);
  return pl;
}


PArbreBinaire fusion_arbres(PArbreBinaire pab1, PArbreBinaire pab2) {
  unsigned int nb_occ1=((LettreFrequence *)pab1->racine->data)->nb_occ;
  unsigned int nb_occ2=((LettreFrequence *)pab2->racine->data)->nb_occ;
  PArbreBinaire pab=creer_arbre_huffman(0,nb_occ1 + nb_occ2);
  pab->racine->gauche=pab1->racine;
  pab->racine->droit=pab2->racine;
  free(pab1);
  free(pab2);
  return pab;
  return NULL;
}

PArbreBinaire construire_arbre_codes(PListe plocc) {
  if (plocc->elements==NULL) {
    detruire_liste(plocc);
    return NULL;
  }
  while (plocc->elements->suivant!=NULL) {
      PElement p1=extraire_en_tete(plocc);
      PElement p2=extraire_en_tete(plocc);
      fflush( stdout );
      PArbreBinaire pab=fusion_arbres(p1->data, p2->data);
      inserer_place(plocc,pab);
      detruire_ab(pab);
      free(p1);
      free(p2);
  }
  PElement p=extraire_en_tete(plocc);
  PArbreBinaire pac=p->data;
  free(p);
  detruire_liste(plocc);
  return pac;
}


void map_ab_prefixe_chemin_rec(PNoeudBinaire pnb,
			       void (*fonction)(void *data, int fprof,
								   TypeChemin tc, TypeNoeudArbreBinaire tnab, void *oa),
			       int prof, TypeChemin tcn, void *optarg) {
  if (pnb) {
    TypeNoeudArbreBinaire ntnab=FEUILLE;
    if ((pnb->gauche) && (pnb->droit))
      ntnab=INTERNE;
    else if (pnb->gauche)
      ntnab=AFILSGAUCHE;
    else if (pnb->droit)
      ntnab=AFILSDROIT;
    fonction(pnb->data,prof, tcn, ntnab, optarg);
    map_ab_prefixe_chemin_rec(pnb->gauche,fonction, prof+1, FILSGAUCHE, optarg);
    map_ab_prefixe_chemin_rec(pnb->droit,fonction, prof+1, FILSDROIT, optarg);
  }
}
  
void map_ab_prefixe_chemin(PArbreBinaire pab,
			   void (*fonction)(void *data, int prof, TypeChemin tc, TypeNoeudArbreBinaire tnab, void *oa),
			   void *optarg) {
  map_ab_prefixe_chemin_rec(pab->racine,fonction, 0, RACINE, optarg);
}

void affiche_code(void *data, int prof, TypeChemin tc, TypeNoeudArbreBinaire tnab, void *oa) {
  char *code=(char *)oa;
  int l=prof;
  switch(tc) {
  case RACINE:
    // rien a faire...
    break;
  case FILSGAUCHE:
    code[l-1]='0';
    break;
  case FILSDROIT:
    code[l-1]='1';
    break;
  default:
    printf("Type de chemin inconnu !");
  }
  code[l]='\0';
  LettreFrequence *plf=(LettreFrequence *)data;
  if(tnab==FEUILLE) {
    printf("Caractere='%c' [%d], nb_occ=%d, code=%s\n",plf->lettre,
	   (unsigned char)plf->lettre, plf->nb_occ, code);
  }
}

void construire_tableau_code_fonction(void *data, int prof, TypeChemin tc,
				      TypeNoeudArbreBinaire tnab, void *oa) {
  TabCode *tcode=(TabCode *)oa;
  int l=prof;
  switch(tc) {
  case RACINE:
    // rien a faire...
    break;
  case FILSGAUCHE:
    tcode->code_courant[l-1]='0';
    break;
  case FILSDROIT:
    tcode->code_courant[l-1]='1';
    break;
  default:
    printf("Type de chemin inconnu !");
  }
  tcode->code_courant[l]='\0';
  LettreFrequence *plf=(LettreFrequence *)data;
  if(tnab==FEUILLE) {
    printf("Caractere='%c' [%d], nb_occ=%d, code=%s\n",plf->lettre,(unsigned char)plf->lettre,
	   plf->nb_occ, tcode->code_courant);
    tcode->code[(unsigned char)plf->lettre]=strdup(tcode->code_courant);
  }
}

char **construire_tableau_code(PArbreBinaire pah) {
  TabCode tc;
  tc.code_courant[0]='\0';
  int i;
  for (i=0;i<256;i++) {
    tc.code[i]=NULL;
  }
  map_ab_prefixe_chemin(pah,construire_tableau_code_fonction,&tc);
  char **code=(char **)malloc(256*sizeof(char *));
  for (i=0;i<256;i++) {
    code[i]=tc.code[i];
  }
  return code;
}

int ajouter_bits(char *code, char* buffer, int ptr) {
  // il faut ajouter les poids forts en premier...
  int i=0;
  int c,r,v;
  //printf("Code: %s\n",code);
  while(i<strlen(code)) {
    c=ptr/8;
    r=ptr%8;
    //printf("Adding bit: %c\n",code[i]);
    v=code[i]=='0'?0:1;
    if(v) {
      unsigned char n=1<<r;
      buffer[c]=buffer[c]|n;
    }
    else {
      unsigned char n=255-(1<<r);
      buffer[c]=buffer[c]&n;
    }
    ptr++;
    i++;
  }
  return ptr;
}

int compresser(const char *nom_fichier_in) {
  FILE *f=fopen(nom_fichier_in, "r");
  if (f==NULL) {
    printf("Impossible d'ouvrir le fichier %s\n",nom_fichier_in);
    return 0;
  }

  int *occ=distri_code(f);
  int i;
  int nb_occ=0;
  for (i=0;i<256;i++) {
    nb_occ+=occ[i];
  }
  PListe plocc=creer_liste_occ(occ);
  
  PArbreBinaire pah = construire_arbre_codes(plocc);
  
  char **code = construire_tableau_code(pah);

  int max_len=0;
  for (i=0;i<256;i++) {
    if ((code[i]!=NULL) && (strlen(code[i])>max_len))
      max_len=strlen(code[i]);
  }

  rewind(f);

  int outnamesize=strlen(nom_fichier_in)+3;
  char *nom_fichier_out=(char *)malloc(sizeof(char)*(outnamesize+1));
  printf( "%s", nom_fichier_out );
  sprintf(nom_fichier_out,"%s.hf",nom_fichier_in);
  FILE *fout=fopen(nom_fichier_out,"wb");

  ecrire_ah(pah,fout);
    
  fwrite(&nb_occ,sizeof(int),1,fout);
  
  int c;
  char buffer[BUFFER_SIZE];
  int nb_bits_limit=BUFFER_SIZE*8-max_len;
  int seuil=nb_bits_limit - (nb_bits_limit % 8);
  int nb_octets = seuil/8;
  int ptr=0;
  //int cptr=0;
  while((c=fgetc(f))!=EOF) {
    unsigned char cc=(unsigned char)c;
    ptr=ajouter_bits(code[cc],buffer, ptr);
    if (ptr>seuil) {

      fwrite(buffer, nb_octets, 1, fout);

      // On enleve les octets deja ecrits
      int omax=ptr/8+1;
      omax=omax>=BUFFER_SIZE?BUFFER_SIZE-1:omax;
      for (i=nb_octets; i<=omax; i++) {
	buffer[i-nb_octets]=buffer[i];
      }
      ptr-=seuil;
    }
  }

  // il faut ecrire les derniers bits...
  int ptra=ptr;
  ptra=ptra%8==0?ptra:ptra+(8-ptra%8);
  int nbo=ptra/8;

  fwrite(buffer,nbo,1,fout);
  
  fclose(fout);
  fclose(f);

  
  // Liberation de la memoire
  for (i=0;i<256;i++) {
    free(code[i]);
  }
  free(code);

  detruire_ab(pah);
  free(occ);
  free(nom_fichier_out);
  return 1;
}

int decompresser(const char *nom_fichier_in, const char *nom_fichier_out) {
    
    FILE * f = fopen( nom_fichier_in, "rb" );
    if ( f ) {

        PArbreBinaire ah = lire_ah( f );
        fclose( f );
        f = fopen( "sortie", "wb" );
        if ( f == NULL ) {
            printf( "Erreur à l'écriture du fichier.\n" );
            return 0;
        }
        // écrire fichier à partir de ah
        fclose( f );
        
    }
    printf( "Erreur à la lecture du fichier.\n" );
    return 1;
}
