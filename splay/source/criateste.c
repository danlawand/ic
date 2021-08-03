#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	FILE *pFile;
	int n_testes, chave, escolhe_operacao, inseridos;

    if (argc < 1) {
		printf("It needs the file's name.\n");
		exit(EXIT_FAILURE);
    }

	pFile = fopen(argv[1],"w");

	printf("Digite o número de testes\n");
	scanf("%d",&n_testes);

	int t[n_testes];
	inseridos = 0;

	for (int i = 0; i < n_testes; i++) {
		t[i] = -1;
	}

	srand(time(0));
	chave = 1 + (rand()%n_testes);
	
	t[inseridos] = chave;
	inseridos++;
	
	fprintf(pFile,"i %d %d\n", chave, chave);

	for (int i = 1; i < n_testes-1; i++) {
		escolhe_operacao = rand()%4;
		if (escolhe_operacao >= 2) {
			chave = 1+(rand()%n_testes);
			t[inseridos] = chave;
			inseridos++;
			fprintf(pFile,"i %d %d\n", chave, chave);
		} else if (escolhe_operacao == 1) {
			chave = t[(rand()%(inseridos))];
			fprintf(pFile,"r %d\n", chave);
		} else {
			chave = 1+(rand()%n_testes);
			fprintf(pFile,"g %d\n", chave);
		}
	}

	fclose(pFile);
}