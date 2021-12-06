void exibirResultado(int length, int pontuacao[][2])
{
    for (int i = 0; i < length; i++)
    {
        printf("\nMatricula: %d, Acertos: %d\n", pontuacao[i][0], pontuacao[i][1]);
    }
}

void calcularNotaTerminal(int length, char gabarito[][10], char gabaritoOficial[51], int pontuacao[][2])
{
    int nota = 0;

    for (int i = 0; i < length; i++)
    {
        unsigned int nota = 0;
        for (int j = 0; j < 50; j++)
        {
            if (gabarito[i][j] == gabaritoOficial[j])
            {
                nota = nota + 1;
                pontuacao[i][1] = nota;
            }
        }
    }
}

void inserirGabaritoTerminal(int length, int pontuacao[][2], char gabarito[][10])
{
    for (int k = 0; k < length; k++)
    {
        system("clear");

        printf("\nDigite o número de matrícula do candidato: ");
        scanf("%d", &pontuacao[k][0]);
        __fpurge(stdin);

        if (!(pontuacao[k][0] > 9999 && pontuacao[k][0] < 100000))
        {
            printf("A matrícula deve conter 5 dígitos, e não podem existir zeros no ínicio do número.");
            k--;
        }
        else
        {

            for (int j = 0; j < 50; j++)
            {
                printf("%d:", j + 1);
                gabarito[k][j] = tolower(getchar());
                __fpurge(stdin);

                if (!(gabarito[k][j] == 'a' || gabarito[k][j] == 'b' || gabarito[k][j] == 'c' || gabarito[k][j] == 'd' || gabarito[k][j] == 'e'))
                {
                    printf("O valor digitado precisa ser uma letra válida (a, b, c, d, e) \n");
                    j--;
                }
            }
            system("clear");
        }
    }
}

void inserirResultadoTxt(int pontuacao[][2], int length)
{
    char arquivo[] = "notasClassificadasTerminal.txt";
    FILE *file;
    file = fopen(arquivo, "w");

    printf("---- Notas dos alunos em ordem descendente ----\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d %d \n", pontuacao[i][0], pontuacao[i][1]);
        fprintf(file, "%d %d \n", pontuacao[i][0], pontuacao[i][1]);
    }
    printf("---- Fim das notas ----\n");

    fclose(file);
}

void ordenandoClassificacao(int pontuacao[][2], size_t length)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length - 1; j++)
        {
            if (pontuacao[i][1] > pontuacao[j][1])
            {
                int tempNota = pontuacao[j][1], tempId = pontuacao[j][0];
                pontuacao[j][1] = pontuacao[i][1];
                pontuacao[i][1] = tempNota;
                pontuacao[j][0] = pontuacao[i][0];
                pontuacao[i][0] = tempId;
            }
        }
    }
}

void terminalMain()
{

    char gabaritoOficial[51] = {'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', '\0'};
    int length = 0, success = 0;
    char term;
    system("clear");

    while (success != 1)
    {
        printf("\nQuantas provas gostaria de registrar: ");
        if (scanf("%d%c", &length, &term) != 2 || term != '\n')
        {
            system("clear");

            printf("O número de provas deve ser um valor númerico");
            __fpurge(stdin);
        }
        else
        {
            if (length > 0)
            {

                success = 1;
                char gabarito[length][10];
                int pontuacao[length][2];

                inserirGabaritoTerminal(length, pontuacao, gabarito);
                calcularNotaTerminal(length, gabarito, gabaritoOficial, pontuacao);
                ordenandoClassificacao(pontuacao, length);
                inserirResultadoTxt(pontuacao, length);

                printf("A classificação foi concluída com sucesso. Um arquivo chamada 'notasClassificadas.txt' contém a classificação exibida acima.\n");
            }
            else
            {
                system("clear");

                printf("O valor deve ser maior do que 0");
            }
        }
    }
}