#include <stdio.h>
#include "utilitaires_tableaux.h"
#include "tris.h"
#include <stdlib.h>


int main(int argc, char **argv)
{
	int i;
	
	if(argc < 3){
		fprintf(stderr, "%s: Nombre d'arguments incorrect (%d)\n", argv[0], argc);
		fprintf(stderr, "USAGE: %s <fichier a trier> <fichier de sortie>\n", argv[0]);
		exit(1);
	}


	for(i=0;i<argc;i++)
		printf("Argument %d : %s\n", i, argv[i]);


	/*A compiler tel quel puis a modifier*/

	return (0);
}
