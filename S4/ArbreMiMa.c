#include <stdlib.h>
#include <stdio.h>
#include "ArbreMiMa.h"
#include "ListePos.h"

int changerCouleur( int couleurQuiJoue ) {
	if ( couleurQuiJoue == NOIR ) return BLANC;
	else                          return  NOIR;
}

int EvaluerPlateau_0(int plateau[H][H])
	{
	int res = 0;

	for ( int i; i < H; i++ )
	for ( int j; j < H; j++ )
	if ( plateau[ i ][ j ] == NOIR ) res += 1;
	else if ( plateau[ i ][ j ] == BLANC ) res -= 1;
	return res;
	}

int EvaluerPlateau_1( int plateau[ H ][ H ] ) {

	int res = 0;

	int poids[ H ][ H ] = {
        {  8, -4,  2,  2,  2,  2, -4,  8 },
		{ -4, -8, -2, -2, -2, -2, -8, -4 },
	    {  2, -2,  1,  1,  1,  1, -2,  2 },
		{  2, -2,  1,  1,  1,  1, -2,  2 },
		{  2, -2,  1,  1,  1,  1, -2,  2 },
		{  2, -2,  1,  1,  1,  1, -2,  2 },
		{ -4, -8, -2, -2, -2, -2, -8, -4 },
		{  8, -4,  2,  2,  2,  2, -4,  8 }
	};

	for ( int i; i < H; i++ )
	for ( int j; j < H; j++ )
	if ( plateau[ i ][ j ] == NOIR ) res += poids[ i ][ j ];
	else if ( plateau[ i ][ j ] == BLANC ) res -= poids[ i ][ j ];

	return res;
}

NdMiMa_t *Construire_arbre(int plateau[H][H], int prof, int couleurQuiJoue)
	{
		if ( prof == 0 ) return NULL;

		NdMiMa_t * noeud = malloc( sizeof( NdMiMa_t ) );
		noeud -> Couleur = couleurQuiJoue;
		noeud -> liste_pos = Trouver_liste_pos_jouables( plateau, couleurQuiJoue );

		if ( noeud -> liste_pos == NULL ) //Pas de position jouable 
			noeud -> JoueurBloque = Construire_arbre( plateau, prof - 1, changerCouleur( couleurQuiJoue ) );

		else {
			noeud -> JoueurBloque = NULL;

			for ( PosJouable_t * nouveauTour = noeud -> liste_pos; nouveauTour; nouveauTour = nouveauTour -> suiv ) {
				int nouveauPlateau[ H ][ H ];
				Copier_plateau( nouveauPlateau, plateau );
				Jouer_pion( nouveauPlateau, nouveauTour -> i, nouveauTour -> j, changerCouleur( couleurQuiJoue ) );
				nouveauTour -> Nd = Construire_arbre( nouveauPlateau, prof - 1, changerCouleur( couleurQuiJoue ) );
			}
		}

		return noeud;

	}

int MinMax(NdMiMa_t *arbre, int plateau[H][H], int (*EvaluerPlateau)(int plateau[H][H])) {
	
	if ( ! arbre || arbre -> JoueurBloque || arbre -> liste_pos == NULL ) return EvaluerPlateau( plateau );

	int minMax;
	int initialisationDuMinMax = 1;

	for ( PosJouable_t * nouveauTour = arbre -> liste_pos; nouveauTour; nouveauTour = nouveauTour -> suiv ) {
			int nouveauPlateau[ H ][ H ];
			Copier_plateau( nouveauPlateau, plateau );
			Jouer_pion( nouveauPlateau, nouveauTour -> i, nouveauTour -> j, arbre -> Couleur );
			int nouveauMinmax = MinMax( nouveauTour -> Nd, nouveauPlateau, EvaluerPlateau );
			if ( arbre -> Couleur == NOIR && ( initialisationDuMinMax || minMax < nouveauMinmax ) )
				minMax = nouveauMinmax;
			if ( arbre -> Couleur == BLANC && ( initialisationDuMinMax || minMax > nouveauMinmax ) )
				minMax = nouveauMinmax;
			initialisationDuMinMax = 0;
	}
	return minMax;
}

int MeilleurPos(NdMiMa_t *arbre, int plateau[H][H], int (*EvaluerPlateau)(int plateau[H][H]),int *pi, int *pj) {

	if ( ! arbre || arbre -> JoueurBloque || arbre -> liste_pos == NULL ) return 0;

	int minMax;
	int initialisationDuMinMax = 1;

	for ( PosJouable_t * nouveauTour = arbre -> liste_pos; nouveauTour; nouveauTour = nouveauTour -> suiv ) {
			int nouveauPlateau[ H ][ H ];
			Copier_plateau( nouveauPlateau, plateau );
			Jouer_pion( nouveauPlateau, nouveauTour -> i, nouveauTour -> j, arbre -> Couleur );
			int nouveauMinmax = MinMax( nouveauTour -> Nd, nouveauPlateau, EvaluerPlateau );
			if ( arbre -> Couleur == NOIR && ( initialisationDuMinMax || minMax < nouveauMinmax ) ) {
				minMax = nouveauMinmax;
				* pi = nouveauTour -> i;
				* pj = nouveauTour -> j;
			}
			if ( arbre -> Couleur == BLANC && ( initialisationDuMinMax || minMax > nouveauMinmax ) ) {
				minMax = nouveauMinmax;
				* pi = nouveauTour -> i;
				* pj = nouveauTour -> j;
			}
			initialisationDuMinMax = 0;
	}
	return 0;
}

NdMiMa_t *Detruire_arbre(NdMiMa_t *arbre)
	{
	if (arbre)
		{
		Detruire_liste(arbre->liste_pos);
		free(arbre);
		}
	return NULL;
	}
