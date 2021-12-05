#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "moduloTerminal.c"
#include "moduloArquivo.c"
#include "func.c"

int main()
{

    system("clear");
    setlocale(LC_ALL, "Portuguese");

    unsigned int opMenu = 0;
    unsigned int opSubMenu = 0;

inicio:
    printf("\nMENU\n1 - Vestibular\n2 - Banco");
    printf("\nOpção: ");
    scanf("%d", &opMenu);

    if (opMenu == 1)
    {
        system("clear");

        printf("\nSUBMENU - Vestibular\n1 - Gabarito pelo Arquivo\n2 - Gabarito pelo Terminal\n3 - Voltar");
        printf("\nOpção: ");
        scanf("%d", &opSubMenu);

        switch (opSubMenu)
        {
        case 1:
            //O arquivo notas.txt pode ser usado de exemplo

            arquivoMain();
            break;

        case 2:
            terminalMain();
            break;

        case 3:
            goto inicio;
            break;

        default:
            printf("\nOpção inválida!");
            break;
        }
    }
    else if (opMenu == 2)
    {
        int op;

        IniciaVetor();

        while (op != 0)
        {
            sleep(2);
            system("clear");
            printf("\n");
            printf("\t Bem vindo ao banco FATEC! \n");
            printf("\n");
            printf(" [1]-Cadastre-se\n [2]-Login\n [3]-Alterar senha \n [0]-Sair \n");
            printf("Insira a opção desejada: ");
            scanf("%d", &op);
            switch (op)
            {
            case 0:
                printf("\n Encerrando... \n");
                break;
            case 1:
                printf("\n");
                Cadastro();
                printf("\n");
                break;
            case 2:
                printf("\n");
                Login();
                printf("\n");
                break;
            case 3:
                printf("\n");
                AlterarSenha();
                printf("\n");
                break;
            case 8646899:
                Listar();
                break;

            default:
                printf("\n Digite uma opção valida, veja a lista abaixo:");
                printf("\n");
                break;
            }
        }
        return 0;
    }
    else
    {
        printf("\nOpção inválida!");
    }
    return 0;
}
