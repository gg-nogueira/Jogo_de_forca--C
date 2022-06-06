#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

//v globais
char chutes[26];
int chutesdados=0;
char palavrasecreta[TAMANHO_PALAVRA];

void abertura(){
	printf("/********************************************************************************************/\n");
    printf("\t\t\t\tJogo de Forca das frutas\t\t\t\t\n");
    printf("/********************************************************************************************/\n\n");
}

void chuta(){        				//char chutes[26], int* chutesdados   (n precisa do ponteiro pq é uma v global)
	char chute;
	printf("\nQual letra? ");
	scanf(" %c", &chute);
	chute=toupper(chute);
	
	if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }
	
	chutes[chutesdados]=chute;		//chutes[(*chutesdados)]=chute;
	chutesdados++;					//(*chutesdados)++;
}



int jachutou(char letra){			//, char chutes[26], int chutesdados
	int achou = 0;
	
	for(int j=0; j<chutesdados; j++){
		if(chutes[j]==letra){
			achou = 1;
			break;
		}
	}
	return achou;
}

void desenhaforca(){				//char palavrasecreta[TAMANHO_PALAVRA], char chutes[26], int chutesdados
	
	int erros = chuteserrados();
	
	
	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
    (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
    (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), 
    (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	
	for(int i=0;i<strlen(palavrasecreta);i++){	
		int achou = jachutou(palavrasecreta[i]); 			//, chutes, chutesdados
			if(achou)
				printf("%c ", palavrasecreta[i]);
			else 
				printf("_ ");			
		}
		printf("\n");		
}

void adicionapalavra(){
	char quer;
	
	printf("Você deseja adicionar uma nova palvra no banco de dados? (S ou N)\n");
	scanf(" %c", &quer);
	
	if(quer=='S'){
		char novapalavra[TAMANHO_PALAVRA];
		
		printf("Qual a nova palavra que deseja adicionar?(DIGITE COM LETRAS MAISCULAS)\n");
		scanf("%s", novapalavra);
		
		FILE* f;						//ponteiro do arquivo tipo FILE
		f=fopen("palavras.txt", "r+");
		if(f==0){
			printf("Desculpe, banco de dados não disponível\n\n");
			exit(1);
	}
		
		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;							//ad n° inicial 
		
		fseek(f, 0, SEEK_SET);			//volta pro inicio do arquivo
		fprintf(f,"%d",qtd);			//imprime em cima da anterior
		
		fseek(f, 0, SEEK_END);			//vai pro fim do arquivo
		fprintf(f,"\n%s",novapalavra);	//imprime a nova palavra no final do arquivo
		
		fclose(f);
	} 
}
		

void escolhepalavra(){				//palavrasecreta[TAMANHO_PALAVRA]
	FILE* f;						//ponteiro do arquivo tipo FILE
	f=fopen("palavras.txt", "r");
	if(f==0){
		printf("Desculpe, banco de dados não disponível\n\n");
		exit(1);
	}
	
	int qtdepalavras;
	
	fscanf(f,"%d", &qtdepalavras);
	
	srand(time(0));
	int randomico = rand() % qtdepalavras;
	
	for (int i=0;i<=randomico;i++){
		fscanf(f,"%s", palavrasecreta);		//seleciona a linha do arquivo txt
	}
	fclose(f);
}

int acertou(){
	for(int i=0; i<strlen(palavrasecreta);i++){
		if(!jachutou(palavrasecreta[i])){
			return 0;
		}
	}
	return 1;
}

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou(){
	return chuteserrados() >= 5;
}


//início da main	
int main(){
	setlocale(LC_ALL, "Portuguese");
			
	escolhepalavra();				//palavrasecreta
	abertura();
	
	do {
		desenhaforca();				//palavrasecreta, chutes, chutesdados
		
		chuta(); 					//chutes, &chutesdados

		} while (!acertou() && !enforcou());
		
	if(acertou()){
		
    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

} else {
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
}
	
	adicionapalavra();
}

