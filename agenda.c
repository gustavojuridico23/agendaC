// por Gustavo Valle

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // para a função sleep()
#include <locale.h> // para caracteres especiais
#define MAX 100

// Para realizar o exercício da agenda, utilizei alguns conceitos de alocação dinâmica 
// que achei no canal "De aluno para aluno" e no site cprogressivo.net
// https://www.cprogressivo.net/2013/10/A-funcao-realloc-realocando-memoria-dinamicamente-e-a-calloc.html
// como o programa foi feito em ambiente Linux, segue link de compilador online com base no linux
// https://repl.it/languages/c

struct Contato {
    char nome[MAX];
    char endereco[MAX];
    int telefone;
    int repetido; // variável auxiliar para verificação, se o contato já está cadastrado
};

// ------------------------------------------------ DECLARAÇÃO DAS FUNÇÕES --------------------------------------------------------

void cadastrar(struct Contato *agenda, int final);
void mostrar(struct Contato *agenda, int final);
void consultar(struct Contato *agenda, int final);
void remover(struct Contato *agenda, int final);
void alterar(struct Contato *agenda, int final);

// ----------------------------------------------- FUNÇÃO MAIN ----------------------------------------------------------------------
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    int op, *posicao;
    int cap = 10, final = -1;
    struct Contato *agenda;

    agenda = (struct Contato *) calloc(cap, sizeof(struct Contato));

    do {
        system("clear");
//      printf("final: %d\n", final);
        printf("1 - Inserir contato\n2 - Mostrar contatos\n3 - Consultar contato\n4 - Alterar contato\n5 - Excluir contato\n9 - Sair\n\nDigite sua opção: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                cadastrar(agenda, final);
                if(agenda->repetido == 0) //se o contato não exstir
                    final++;    // incrementa o final
                else
                    agenda->repetido = 0; // se existir, não incrementa e a variável auxiliar 'repetido' zera novamente
            break;
            
            case 2:
                mostrar(agenda, final);
                break;
            case 3:
                consultar(agenda, final);
                break;
            case 4:
                alterar(agenda, final);
                break;
            case 5:
                remover(agenda, final);
                if(agenda->repetido == 1)
                    final--;
                    else
                        agenda->repetido == 0;
                break;
        }

    } while (op != 9);

    return 0;
}

// ------------------------------------------------ FUNÇÕES ------------------------------------------------------------------

// MOSTRAR A LISTA DE CONTATOS

void mostrar(struct Contato *agenda, int final){
    setlocale(LC_ALL, "Portuguese");
    system("clear");

    if(final == -1){
        printf("Lista de contatos vazia!!!\n\n\n");
    } else {
        for(int i = 0; i <= final; i++){
            printf("Contato %d\nNome: %s\nTelefone: %d\nEndereço: %s\n\n", i+1, agenda[i].nome, agenda[i].telefone, agenda[i].endereco);
        }
    }

    sleep(2);
}

// CADASTRAR UM NOVO CONTATO

void cadastrar(struct Contato *agenda, int final) {
    setlocale(LC_ALL, "Portuguese");
    int i, j, comparacao, meio;
    char str[MAX], endereco[MAX];
    int fone;
    if (final == -1){ // primeiro e segundo elementos, onde não há meio
        system("clear");
        printf("Preencha os dados para cadastro\n\n");
        printf("Nome: ");
        scanf(" %[^\n]", agenda[final+1].nome);
        printf("Telefone: ");
        scanf("%d", &agenda[final+1].telefone);
        printf("Endereço: ");
        scanf(" %[^\n]", endereco);
        strcpy(agenda[final+1].endereco, endereco);
    } else {
        system("clear");
        printf("Preencha os dados para cadastro\n\n");
        printf("Nome: ");
        scanf(" %[^\n]", str);
        printf("Telefone: ");
        scanf("%d", &fone);
        printf("Endereço: ");
        scanf(" %[^\n]", endereco);
        
        for(i = 0; i <= final; i++){    // a iteração percorre todos os nomes para localizar onde irá inserir
            comparacao = strcmp(agenda[i].nome, str);
            if(comparacao > 0){ // utilizei a comparação para saber se o valor digitado é antes do valor percorrido
                for(j = final+1; j >= i; j--) { // arrasta os elementos para a direita
                    strcpy(agenda[j].nome, agenda[j-1].nome);
                    agenda[j].telefone = agenda[j-1].telefone;
                    strcpy(agenda[j].endereco, agenda[j-1].endereco);
                }
                for(j = 0; str[j] != '\0'; j++){
                    agenda[i].nome[j] = str[j];
                }
                agenda[i].telefone = fone;
                strcpy(agenda[i].endereco, endereco);
                agenda[i].nome[j] = '\0';
                return; // se a comparação for maior que zero, ele irá retornar, caso contrário entrará na repetição novamente
            } else if (strcmp(agenda[final].nome, str) < 0) { // se o contato a ser inserido for depois de todos
                for(j = 0; str[j] != '\0'; j++){
                    agenda[final+1].nome[j] = str[j];
                    agenda[final+1].telefone = fone;
                    strcpy(agenda[final+1].endereco, endereco);
                }
            } else if(comparacao == 0){
                printf("Contato já cadastrado!\nPor favor, escolha outro nome para o novo contato...\n\n\n");
                sleep(2);
                agenda->repetido = 1; // se o contato já existir, não irá incrementar no valor 'final'
                return;
            }
            
        }
    }

}

// CONSULTAR UM CONTATO ESPECÍFICO

void consultar(struct Contato *agenda, int final){
    setlocale(LC_ALL, "Portuguese");
    char busca[MAX];
    int comparacao, flag = 0;


    system("clear");
    printf("Preencha os dados para consulta\n\n");
    printf("Nome: ");
    scanf(" %[^\n]", busca);

    for(int i = 0; i <= final; i++){ //percorre todos os contatos
        comparacao = strcmp(agenda[i].nome, busca); // compara o valor buscado com o contato que o For está percorrendo
        if(comparacao == 0){
            system("clear");
            printf("Buscando...\n"); // implementação de UX
            sleep(2);
            system("clear");
            printf("Busca concluída!\n\nNome: %s\nTelefone: %d\nEndereço: %s\n", agenda[i].nome, agenda[i].telefone, agenda[i].endereco);
            sleep(5);
            flag++;
        }
    }
    if(flag == 0){
        system("clear");
        printf("Buscando...\n"); // implementação de UX
        sleep(2);
        system("clear");
        printf("Contato não encontrado...\nPor favor, verifique o nome e tente novamente!\n");
        sleep(3);
        return;
    }

}

// REMOVER CONTATO

void remover(struct Contato *agenda, int final) {
    setlocale(LC_ALL, "Portuguese");
    int i, comparacao, index = -1;
    char exclusao[MAX];

    system("clear");
    if(final == -1){
        printf("Lista de contatos vazia!!!\n\n\n");
    } else {
        for(int i = 0; i <= final; i++){ // mostra os contatos cadastrados
            printf("Contato %d\nNome: %s\nTelefone: %d\nEndereço: %s\n\n", i+1, agenda[i].nome, agenda[i].telefone, agenda[i].endereco);
        }
    }
    printf("Digite o número do contato a ser excluído: ");
    scanf(" %[^\n]", exclusao);

    for(i = 0; i <= final; i++){
        comparacao = strcmp(agenda[i].nome, exclusao); // compara o nome digitado com cada nome da lista de contato
        if(comparacao == 0){
            index = i;  // pega o index do nome desejado
            for(i = index; i <= final; i++) { // arrasta todos os elementos a partir do index, para a esquerda
                strcpy(agenda[i].nome, agenda[i+1].nome);
                agenda[i].telefone = agenda[i+1].telefone;
                strcpy(agenda[i].endereco, agenda[i+1].endereco);
            }
        }
    }

    if(index > -1) { 
        printf("Contato excluído com sucesso!\n");
        sleep(2);
        agenda->repetido = 1;
    } else{
        printf("Não foi possível localizar o nome digitado\nVerifique e tente novamente!\n");
        sleep(2);
    }
}

// ALTERAR CONTATO

void alterar(struct Contato *agenda, int final){
    setlocale(LC_ALL, "Portuguese");
    int i, comparacao, novo_phone, opcao, flag = 0;
    char alterar[MAX], novo_nome[MAX], novo_endereco[MAX];

    system("clear");
    for(int i = 0; i <= final; i++){ //Mostrar os contatos cadastrados
            printf("Contato %d\nNome: %s\nTelefone: %d\nEndereço: %s\n\n", i+1, agenda[i].nome, agenda[i].telefone, agenda[i].endereco);
        }
    printf("Digite o nome do contato a ser alterado: ");
    scanf(" %[^\n]", alterar);

    for(i = 0; i <= final; i++){
        comparacao = strcmp(agenda[i].nome, alterar);
        if(comparacao == 0){ // se a comparação for igual a zero, significa que o nome digitado foi encontrado
            system("clear");
            printf("O que deseja alterar?\n\n1 - Nome\n2 - Número\n3 - Endereço\n\nOpção: ");
            scanf("%d", &opcao);
            if(opcao == 1){ // altera o nome
                printf("Novo nome: ");
                scanf(" %[^\n]", novo_nome);
                strcpy(agenda[i].nome, novo_nome);
                flag++;
            } else if(opcao == 2){ //   altera o telefone
                printf("Novo telefone: ");
                scanf("%d", &novo_phone);
                agenda[i].telefone = novo_phone;
                flag++;
            } else if(opcao == 3){
                printf("Novo endereço: ");
                scanf(" %[^\n]", novo_endereco);
                strcpy(agenda[i].endereco, novo_endereco);
                flag++;
            }
            printf("Contato alterado com sucesso!\n");
            sleep(2);
            return;
        }
    }
    if(flag == 0){
        printf("Contato não encontrado... Por favor, verifique o nome e tente novamente.\n");
        sleep(2);
    }
}