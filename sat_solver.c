#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definição dos maximos (mexer se o pc tankar)
#define MAX_LIT 100
#define MAX_CLAU 100

//definir termos
#define SAT 1
#define UNSAT 0
#define UNDEFINED 2

//struct de uma clausula (sozinha)
typedef struct {
    int literais[MAX_LIT]; //literais da clausula (parcelas com ou do problema)
    int tamanho; //tamanho da clausula
} Clausula;

//estrutura do conjunto de clausulas (todas juntas formam a CNF - forma normal conjuntiva)
//em outras palavras, o conjunto de todos os problemas
typedef struct {
    Clausula clausulas[MAX_CLAU]; //conjunto das clausulas do problema
    int num_clausulas; //numero de clausulas que formam o problema completo (dado no scanneamento)
    int num_literais; //numero de literais que formam o problema (dado no scanneamento)
} CNF;

//estrutura da árvore
typedef struct {
    int variavel; //variável que é cuidada nesse nó da ávore
    int valor; //valor atribuido 1 (verdadeiro) ou -1 (falso)
    int atribuicoes[MAX_LIT]; //vai preenchendo com o passar da árvore, se por algum acaso der contradição, faz o que chamamos de BACKTRACKING
    struct Arvr* esquerda; //ponteiro pro prox nó da árvore
    struct Arvr* direita; //ponteiro pro prox nó da árvore
} Arvr;


void ler_arquivo_cnf(const char* nome_arquivo, CNF* problema){

    //primeiro passo - abrir o arquivo
    FILE* arquivo = fopen(nome_arquivo, "r");
    if(!arquivo){
        printf("erro na abertura do arquivo cnf");
        exit(1);
    }

    char linha[256];//
    int idx_clausula = 0;

    //segundo passo - ler o arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {//enquanto houver linhas no arquivo, o while se mantem

        if (linha[0] == 'c') 
            continue; //pula os comentários (linhas que começam com c)

        if (linha[0] == 'p') {
            sscanf(linha, "p cnf %d %d", &problema->num_literais, &problema->num_clausulas); //le o cabeçalho do problema
            //sscanf é uma função que lê a string e não uma entrada do usuário, como o scanf
            //Ex: p cnf 3 4 -> 3 literais e 4 clausulas
            continue; //pula pra próxima linha depois de ler o cabeçalho
        }

        Clausula c = {0}; //cria uma cláusula nova e zera tudo dentro dela

        char *token = strtok(linha, " "); //começa a separa o linha em tokens (separando os literais)
        while (token != NULL) {
            int literal = atoi(token); //converte o token para literal (int)

            if (literal == 0)
                break; //se for 0 para a esse while

            c.literais[c.tamanho++] = literal; //adiciona o literal na cláusula e aumenta o tamanho dela
            token = strtok(NULL, " "); //vai para o próximo literal
        }

        problema->clausulas[idx_clausula++] = c; //guarda uma clausula nova na estrutura do CNF
    }

    fclose(arquivo);
}



int main(){
    CNF problema; //cria a estrutura do problema
    ler_arquivo_cnf("problema.cnf", &problema); //lê o arquivo cnf e preenche a estrutura do problema

    return 0; //retorna 0 (sucesso)
}