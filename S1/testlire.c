#include <stdio.h>

/*void lecture_fichier(char* nom_fichier){
	FILE *f=fopen("text.txt")
}*/

typedef struct _contact {
char nom[30];
char prenom[30];
} contact;


int main(void){
	char *nom="text.txt";
	
	contact c1={"Tyrell", "Eldon\n" };
	
	FILE *f=fopen(nom,"wb");
	fwrite(&c1,sizeof(contact),1,f);
	fclose(f);
	
	f=fopen(nom,"rb");
	fread(&c1,sizeof(contact),1,f);
	fclose(f);
	
	//char tab[60];
	f=fopen(nom,"w");
	
	
	while (fgets(c,60,f)){
		
		printf("%c\n",t);
	}
	fclose(f);
	return 0;
}
