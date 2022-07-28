#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "arbre_freq.h"
#include "huffman.h"

void *dupliquer_lf(const void *src) {
  
    if ( src ) {
        LettreFrequence * dst = malloc( sizeof( LettreFrequence ) );
        memcpy( dst, src, sizeof( LettreFrequence ) );
        return dst;
    } else return NULL;
}

void copier_lf(const void *src, void *dst) {

    if ( dst = malloc( sizeof( LettreFrequence ) ) )
        memcpy( dst, src, sizeof( LettreFrequence ) );
}

void detruire_lf(void *data) {
  
    if( data ) free( data );
}

void afficher_lf(const void *data) {

    ecrire_lf( data, stdout );
}

int comparer_lf(const void *a, const void *b) {

    if ( a && b ) {
        LettreFrequence lf_a = * ( ( LettreFrequence * ) a );
        LettreFrequence lf_b = * ( ( LettreFrequence * ) b );
        return lf_a.nb_occ - lf_b.nb_occ;
    }
    return 0;
}

int ecrire_lf(const void *data, FILE *f) {

    if ( data ) {

        LettreFrequence * lf = ( LettreFrequence * ) data;
        return fprintf( f, "%c %ud\n", lf -> lettre, lf -> nb_occ );
    }
    return 0;
}

void * lire_lf(FILE *f) {
    
    LettreFrequence * lf = malloc( sizeof( LettreFrequence ) );
    fscanf( f, "%c %ud\n", & ( lf -> lettre ), & ( lf -> nb_occ ) );
    return lf;
}

void *dupliquer_ah( const void *src ) {
  
    if ( src ) {

        PArbreBinaire copie = malloc( sizeof( ArbreBinaire ) );
        memcpy( copie, src, sizeof( ArbreBinaire ) ); // plus rapide à écrire
        copie -> racine = copier_ab( ( void * ) src, ( ( PArbreBinaire ) src ) -> racine );
        return copie;
    }
    return NULL;
}

PNoeudBinaire copier_ab(PArbreBinaire pab, PNoeudBinaire pnb) {
  
    if ( pnb ) {

        PNoeudBinaire copie = malloc( sizeof( NoeudBinaire ) );
        pab -> copier( pnb -> data, copie -> data );
        if ( pnb -> gauche )
            copie -> gauche = dupliquer_ah( pnb -> gauche );
        if ( pnb -> droit )
            copie -> droit = dupliquer_ah( pnb -> droit );
        return copie;
    }
    return NULL;
}

void copier_ah(const void *src, void *dst) {

    * ( ( PArbreBinaire ) dst ) = * ( ( PArbreBinaire ) dupliquer_ah( src ) );
}

void detruire_ah(void *data) {

    if ( data )
        detruire_ab( data );
}

void afficher_ah(const void *data) {
    afficher_ab_prefixe( ( void * ) data );
}

int comparer_ah(const void *a, const void *b) {
  /* a completer */
  return -1; // pour que cela compile
}

//void ecrire_noeud_huffman(void *data, int prof, TypeChemin tc, TypeN  /* a completer */ ) {

//}

void ecrire_ah_rec( PNoeudBinaire pnb, FILE * f ) {

    if ( pnb && pnb -> data ) {
        
        char lettre = ( ( LettreFrequence * ) pnb -> data ) -> lettre;
        fprintf( f, "%hhd", lettre );
        if ( ! lettre ) {
            
            ecrire_ah_rec( pnb -> gauche, f );
            ecrire_ah_rec( pnb -> droit,  f );
        }
    }
}

int ecrire_ah(const void *data, FILE *f) {

    if ( data && f ) {

        PArbreBinaire pab = ( PArbreBinaire ) data;
        if ( pab -> racine )
            ecrire_ah_rec( pab -> racine, f );
    }
    return 0;
}

PNoeudBinaire lire_ah_rec(FILE *f) {

    char lettre;
    fscanf( f, "%hhd", &lettre );
    PNoeudBinaire pnb = malloc( sizeof( NoeudBinaire ) );
    LettreFrequence * lf = malloc( sizeof( lf ) );
    pnb -> data = lf;
    lf -> lettre = lettre;

    if ( lettre ) {

        pnb -> gauche = NULL;
        pnb -> droit = NULL;

    } else {

        pnb -> gauche = lire_ah_rec( f );
        pnb -> droit = lire_ah_rec( f );
    }
    return pnb;
}

void * lire_ah(FILE *f) {
  
    PArbreBinaire ah = creer_arbre( 1, dupliquer_lf, copier_lf, detruire_lf, afficher_lf, comparer_lf, ecrire_lf, lire_lf );
    ah -> racine = lire_ah_rec( f );
    return ah;
}
