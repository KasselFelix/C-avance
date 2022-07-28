#include <stdlib.h>
#include "arbre_freq.h"
#include "huffman.h"
#include <string.h>

int main(int argc, char **argv) {
    switch( argc ) {

        case 2:   compresser( argv[ 1 ]            ); break;
        case 3: decompresser( argv[ 1 ], argv[ 2 ] ); break;
        default: printf( "Il faut soit le nom du fichier à compresser, soit le nom du fichier à compresser et la destination.\n" );
    }
    return 0;
}
