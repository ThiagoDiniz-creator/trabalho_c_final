
int lineCounter(char *arquivo)
{
    char ch[58];
    FILE *file;
    int lines = 0;

    file = fopen(arquivo, "r");
    while ((fgets(ch, 58, file)) && ch[0] != EOF)
    {
        lines++;
    }

    fclose(file);
    return lines;
}

void getLine(char *arquivo, char *line, int lineNumber)
{
    char ch[57];
    FILE *file;

    file = fopen(arquivo, "r");
    for (int i = 0; (fgets(ch, sizeof(ch), file)) && ch[0] != EOF; i++)
    {
        if (lineNumber * 2 == i)
        {
            strcpy(line, ch);
            break;
        }
    }
    fclose(file);
}

int isValid(char *arquivo)
{
    FILE *file = fopen(arquivo, "r");
    int validation = 0;
    if (file == NULL)
    {
        validation = -1;
    }
    else
    {
        int linhas = lineCounter(arquivo);

        for (int i = 0; i < linhas; i++)
        {
            char ch[57];
            getLine(arquivo, ch, i);

            for (int j = 0; j < 57; j++)
            {
                if (j < 5)
                {
                    if (!isdigit(ch[j]))
                    {
                        return -2;
                    }
                }
                else if (j == 5)
                {
                    if (!ch[j] == ' ')
                    {
                        return -2;
                    }
                }
                else if (j > 5 && j < 56)
                {
                    if (!(ch[j] == 'a' || ch[j] == 'b' || ch[j] == 'c' || ch[j] == 'd' || ch[j] == 'e'))
                    {
                        return -2;
                    }
                }
            }
        }

        fclose(file);

        validation = 1;
    }
    return validation;
}

void setId(int *notas, char *linha)
{
    int n1;

    const char *a = &linha[0];
    sscanf(a, "%d", &n1);

    notas[0] = n1;
}

void setGabarito(char *respostas, char *linha)
{
    for (int i = 0; i < 51; i++)
    {
        respostas[i] = linha[i + 6];
    }
}

void orderPontuacao(int pontuacao[][2], size_t length)
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

void generateOutput(int pontuacao[][2], size_t length)
{
    char arquivo[] = "notasClassificadas.txt";
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

int calcularNota(char *gabaritoOficial, char *gabarito)
{
    int nota = 0;
    for (int i = 0; i < 50; i++)
    {
        if (gabaritoOficial[i] == gabarito[i])
        {
            nota++;
        }
    }
    return nota;
}

void setPontuacao(int *pontuacao, char *gabaritoOficial, char *gabarito)
{
    pontuacao[1] = calcularNota(gabaritoOficial, gabarito);
}

int arquivoMain()
{
    system("clear");
    char entrada[99], gabaritoOficial[51] = {'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b',
                                             'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c',
                                             'b', 'a', 'a', 'b', 'c', 'd', 'e', 'e', 'd', 'c', 'b', 'a', '\0'};
    int lines;
    printf("Digite o nome do arquivo (ele deve estar na mesma pasta que o sistema, e deve conter a extensão, como .txt): \n");
    scanf("%s", entrada);

    system("clear");
    if (isValid(entrada) == -1)
    {
        printf("O arquivo inserido não existe \n");
        return 0;
    }
    else if (isValid(entrada) == -2)
    {
        printf("O arquivo não segue o padrão necessário em uma (ou mais) linhas. Cada linha deve conter:\n");
        printf("Cinco primeiras posições(1-5): o registro do aluno, que são cinco valores númericos.\n");
        printf("Sexta posição(6): um espaço vazio (tecla BACKSPACE ou espaço).\n");
        printf("Sétima a quinquagésima sexta casa(7-56): As cinquenta respostas, sendo cada uma delas: a, b, c, d ou e.\n");
        printf("Após a digitação dos valores vá para próxima linha com o ENTER.\n");
        printf("Segue um exemplo com o padrão aceitado: \n");
        printf("12345 abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde\n");
        printf("10000 edcbaedcbaedcbaedcbaedcbaedcbaedcbaedcbaedcbaedcbe\n");
        printf("74125 abcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcdeabcde\n");
        return 0;
    }

    lines = lineCounter(entrada);

    char gabarito[lines][50];
    int pontuacao[lines][2];

    for (int i = 0; i < lines; i++)
    {
        char ch[57];
        getLine(entrada, ch, i);

        setGabarito(gabarito[i], ch);
        setId(pontuacao[i], ch);
        setPontuacao(pontuacao[i], gabaritoOficial, gabarito[i]);
    }
    orderPontuacao(pontuacao, lines);
    generateOutput(pontuacao, lines);

    printf("A classificação foi concluída com sucesso. Um arquivo chamada 'notasClassificadas.txt' contém a classificação exibida acima.\n");
}