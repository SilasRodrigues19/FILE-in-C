#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

/*
    Exercicio :  (Inserir, Alterar e Exibir)
    Desenvolva uma programa que permita inserção de registros e alteração dos registros conforme lay-out abaixo:
    Int ra
    Char nome[20]
    Float nota1
    Float nota2

    Silas Rodrigues Gouveia Júnior

*/

typedef struct aluno ALUNO;

struct aluno
{
    char nome[20];
    int ra;
    float n1, n2;
};

void flush_in();
void cadastrar();
void listar();
void editar();

FILE *arquivo;
ALUNO all;

int op;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    do
    {
        system("cls");

        printf("---------- Gerenciador de dados dos alunos ----------------\n");
        printf("\n [1] - Cadastrar");
        printf("\n [2] - Listar");
        printf("\n [3] - Editar");
        printf("\n [4] - Exluir\n");
        printf("\n [0] - Sair\n\n");


        printf("Digite uma opção: ");

        scanf("%d", &op);
        //flush_in();

        switch(op)
        {
            case 1:
                cadastrar();
            break;

            case 2:
                listar();
            break;

            case 3:
                editar();
            break;

            case 4:
                excluir();
            case 0:
            break;

            default:
                printf("\nOpção Inválida!\n");
                system("pause");
                getch();
            break;
        }

    } while(op!=0);
}


void flush_in()
{
    int ch;
    while ( ( ch = fgetc ( stdin ) ) != '\n' && ch != EOF) {}
}


void cadastrar()
{

    flush_in();

    char numstr[10];


	do
    {

        if ((arquivo = fopen("alunos_notas.txt", "a+b")) == NULL){
				printf("Não foi possível abrir o arquivo 'alunos_notas.txt'");
				exit(1);
        } else {


        arquivo = fopen("alunos_notas.txt","a+b");

        system("cls");

        printf("\n---------------Cadastrando dados do aluno--------------------\n");

        printf("Nome: ");
        gets(all.nome);

        printf("RA: ");
        gets(numstr);
        all.ra = atoi(numstr);

        printf("Digite a primeira nota do aluno: ");
        gets(numstr);
        all.n1 = atof(numstr);


        printf("Digite a segunda do aluno: ");
        gets(numstr);
        all.n2 = atof(numstr);

        float validarn1 = all.n1;
        float validarn2 = all.n2;

        if (validarn1 > 10 && validarn2 > 10) {
            printf("\n[ERRO] - As duas notas devem ser menores ou iguais a 10");
            cadastrar();
        } else if (validarn1 > 10) {
            printf("\n[ERRO] - A primeira nota deve ser menor ou igual a 10");
            cadastrar();
        } else if (validarn2 > 10) {
            printf("\n[ERRO] - A segunda nota deve ser menor ou igual a 10");
            cadastrar();
        }
        else  {


        fwrite(&all, sizeof(ALUNO),1,arquivo);
        fclose(arquivo);
        printf("Deseja realizar novo Cadastro (1 - Sim/2- Não)?");
        }
        }
    } while(getche()=='1');

}
void listar()
{
    system("cls");

    if ((arquivo = fopen("alunos_notas.txt", "r+b")) == NULL){
        printf("Arquivo 'alunos_notas.txt' está vazio");
        exit(1);
    } else {


    arquivo = fopen("alunos_notas.txt","rb");

    while(fread(&all,sizeof(ALUNO),1,arquivo)==1)
    {
        printf("\n---------------Listando dados do aluno--------------------\n");
        printf("Nome: %s\n",all.nome);
        printf("RA: %d\n",all.ra);
        printf("Primeira nota: %.2f\n",all.n1);
        printf("Segunda nota: %.2f\n",all.n2);
        printf("------------------------------------------------------------\n\n");
    }

    fclose(arquivo);
    getch();
    }
}

void editar()
{
    system("cls");

    int posicao = 0; // Inicio do Arquivo;
    int achou = 0;
    int AltRA[30];
    char AltNome[20];


    flush_in();
    printf("\n---------------Editando dados do aluno--------------------\n");

    if ((arquivo = fopen("alunos_notas.txt", "r+b")) == NULL){
        printf("Arquivo 'alunos_notas.txt' está vazio");
        exit(1);
    } else {

    printf("Digite o Nome: ");
    gets(AltNome);

    arquivo = fopen("alunos_notas.txt","r+b");

    system("cls");

    op = -1;

    while(fread(&all, sizeof(ALUNO), 1, arquivo)==1 && op!=0)
    {
        if(strcmp(AltNome,all.nome)==0)
        {
            printf("\n---------------Editando dados do aluno--------------------\n");
            printf("\n [1] - Nome: %s",all.nome);
            printf("\n [2] - RA: %d",all.ra);
            printf("\n [3] - Primeira nota: %2.f",all.n1);
            printf("\n [4] - Segunda nota: %2.f",all.n2);
            printf("\n [0] - Voltar");
            printf("\n----------------------------------------------------------\n\n");

            printf("\n\nEscolha uma opção: ");
            scanf("%d", &op);

            flush_in();

            switch(op)
            {
                case 1:

                    printf("\n-----------------Alterando nome do aluno-----------------\n");
                    printf("Digite o nome: ");
                    gets(all.nome);
                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&all,sizeof(ALUNO),1,arquivo) == sizeof(ALUNO);
                break;

                case 2:

                    printf("\n-----------------Alterando RA do aluno-----------------\n");
                    printf("Digite o novo RA: ");
                    char numstr[10];
                    gets(numstr);
                    all.ra = atoi(numstr);

                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&all,sizeof(ALUNO),1,arquivo) == sizeof(ALUNO);
                break;

                case 3:

                    printf("\n-----------------Alterando primeira nota do aluno-----------------\n");
                    printf("Digite a nota corrigida: ");
                    char numstr1[10];
                    gets(numstr1);
                    all.n1 = atof(numstr1);
                    float validarn1alt = all.n1;

                    if (validarn1alt > 10) {
                        printf("\n[ALTERAÇÃO FALHOU] - A nota deve ser menor ou igual a 10\n");
                        printf("Retornando para o inicio\n");
                        system("pause");
                        main();
                    }

                    else{

                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&all,sizeof(ALUNO),1,arquivo) == sizeof(ALUNO);
                    break;

                    }

                case 4:

                    printf("\n-----------------Alterando segunda nota do aluno-----------------\n");
                    printf("Digite a nota corrigida: ");
                    char numstr2[10];
                    gets(numstr2);
                    all.n2 = atof(numstr2);
                    float validarn2alt = all.n2;

                    if (validarn2alt > 10) {
                        printf("\n[ALTERAÇÃO FALHOU] - A nota deve ser menor ou igual a 10\n");
                        printf("Retornando para o inicio\n");
                        system("pause");
                        main();

                    } else {

                    fseek(arquivo, posicao, SEEK_SET);
                    achou= fwrite(&all,sizeof(ALUNO),1,arquivo) == sizeof(ALUNO);
                    break;

                    }

                case 0:
                break;

                default:

                    printf("\nOpção Inválida!\n");
                    system("pause");
                    getch();
                break;
            }

        }
        posicao = posicao + sizeof(ALUNO);

        fseek(arquivo, posicao, SEEK_SET);
    }

    op = -1;

    fclose(arquivo);
}
}

void excluir ()
{
            char op;


            printf("Deseja excluir todos os dados?\n[S] - Sim, desejo apagar tudo.\n[N] - Não, quero retornar ao menu.\n");
            scanf("%s",&op);
            if (op == 's' || op == 'S'){

                if((arquivo = fopen("alunos_notas.txt", "r+b")) == NULL){
                    printf("Não existem dados a serem apagados nesse arquivo!\n");

                } else {
                    printf("Todos excluidos com êxito!\n");
                    FILE * arquivo;
                    arquivo = fopen("alunos_notas.txt","w");

                }

            } else if (op == 'n' || op == 'N') {
                system("cls");
                printf("Retornando ao menu...\n");
            } else {
                printf("Opção inválida\nFechando programa...");
                fclose(arquivo);
                exit(1);
            }
            getch();
}
