#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 1
//SAque e Deposito
typedef struct
{
    char nome[45];
    long int cpf;
    int senha;
    long double saldo;
} Usuario;
Usuario func[MAX];

void IniciaVetor()
{
    for (int i = 0; i < MAX; i++)
    {
        strcpy(func[i].nome, "NULL");
        func[i].cpf;
        func[i].senha;
        func[i].saldo;
    }
    
}


int ValidacaoCpf(long int cpf)
{
    if (cpf < 9999999999 || cpf > 99999999999 || cpf < 0)
        {
            do
            {
                printf("\n Cpf não é valido, digite um Cpf valido: \n");
                printf("\n Cpf: ");
                scanf("%ld", &cpf );
            } while (cpf < 9999999999 || cpf > 99999999999 || cpf < 0);
        }
}

int ValidacaoSenha(int senha)
{
    if(senha < 999 || senha > 9999 || senha < 0)
    {
        do
        {
            printf("\n Senha não é valida: ");
            printf("\n Digite uma senha de quatro digitos: ");
            scanf("%d", &senha);
        } while (senha < 999 || senha > 9999 || senha < 0);
    }
}

double ValidacaoSaldo (double long saldo)
{   
    if(saldo < 0)
    {
        do
        {
            printf("\n Deposito invalido. ");
            printf("\n Deposite deve ser de um valor positivo: ");
            scanf("%Lf", &saldo);
        } while (saldo < 0);
    }
}


void Cadastro()
{  
    printf("Erro, nao foi possivel abrir o arquivo\n");
        char nome[45];
        long int cpf;
        int senha, OpContin;
        long double  saldo;
        for (int i = 0; i < MAX; i++)
        {   
            printf(" \n [1]-Continuar [2]-Cancelar: ");
            printf("\n Digite uma das opções:");

            scanf("%d",&OpContin);
            switch (OpContin)
            {
            case 1:
                printf("\n");
                printf("\t Vocẽ selecionou a opção de cadastro. \n \t Preencha os campos abaixo de forma correta: \n");
                // O comando abaixo limpa o buffer, ou seja, não pega o que foi digitado anteriormente.
                printf("\n Nome:");
                getchar();
                fgets(func[i].nome, sizeof(nome),stdin);
                printf(" Cpf: ");
                scanf("%ld", &cpf);
                ValidacaoCpf(cpf);
                func[i].cpf = cpf;
                printf(" Digite uma senha de quatro digitos: ");
                scanf("%d", &senha);
                ValidacaoSenha(senha);
                func[i].senha = senha;
                printf(" Deposito inicial: ");
                scanf("%Lf", &saldo);
                ValidacaoSaldo(saldo);
                func[i].saldo = saldo;
                printf("\n");
                printf(" Por favor anote sua senha. \n Em poucos segundos o terminal será limpo e irá voltar a tela incial.");
                printf("\n");
                printf("\n");
                sleep(4);
                system("clear");
            break;
            case 2:
                break;
            default:
                printf("\n Opção digitada não existente encerrando processo.");
            break;
            }


    }
}

double FuncSaque(long int cpf, int senha, long double saldo)
{
    long double Valor;

    printf("\n Digite o valor do saque: ");
    scanf("%Lf", &Valor);
    if(Valor > 0 && Valor < saldo){
    
        for (int i = 0; i < MAX; i++)
        {
            if(cpf == func[i].cpf  && senha == func[i].senha)
            {   
                printf("\n Confirme sua senha: ");
                scanf("%d", &senha);
                if(senha == func[i].senha)
                {
                    func[i].saldo = func[i].saldo - Valor;
                }
                else
                {
                    printf("Deposito negado.");
                }
            }
        }
    } 
    else
    {
        printf("O valor do saque não pode ser negativo nem nulo.");
    }   
}

double FunDeposito(long int cpf, int senha){
    
    long double Valor;

    printf("\n Digite o valor do deposito: ");
    scanf("%Lf", &Valor);
    if(Valor > 0){
        for (int i = 0; i < MAX; i++)
        {
            if(cpf == func[i].cpf  && senha == func[i].senha)
            {  
                printf("\n Confirme sua senha: ");
                scanf("%d", &senha);
                if (senha == func[i].senha)
                {
                    func[i].saldo = func[i].saldo + Valor;
                }
                else
                {
                    printf("Deposito negado.");
                }
            }
        }
    }
    else
    {
        printf("O deposito não pode ser negativo nem nulo ou maior que o saldo atual.");
    }      
    
}

void Listar ()
{ 
    int limpa;  
    printf("\n");
    printf("\n");
    printf("Listar Usuários: \n");    
    for (int i = 0; i < MAX; i++)
    {
        printf("\t Nome: %s", func[i].nome);
        printf("\t Cpf: %ld\n",func[i].cpf);
        //printf("\t Senha: %d \n", func[i].senha);
        //printf("\t Saldo: %Lf \n", func[i].saldo);
        printf("\n");
        printf("\n");
    }
    getchar();
    printf("Presione o enter para limpar a tela. ");
    getchar();
    system("clear");
    
    
}

int ExibirDados(long int cpf, int senha)
{   
    long double AuxSaldo ;
    int op = 1;
    long double saldo;
    for (int i = 0; i < MAX; i++)
    {
        if(cpf == func[i].cpf  && senha == func[i].senha)
        {   
            while (op != 0)
            {
                printf("\n");
                printf("\n  Nome: %s  Cpf: %ld", func[i].nome, func[i].cpf);
                printf("\t Saldo disponivel: %.2Lf \n", func[i].saldo);
                printf("\n");

                printf(" \n [1]-Saque \n [2]-Deposito \n [0]-Sair \n Digite o numero da operação desejada:");
                scanf("%d", &op);
                
                switch (op)
                {
                case 0:
                    printf("\n Encerrando sessão...\n");
                    sleep(2);
                    system("clear");
                    break;
                case 1:
                    printf("\n  Nome: %s  Cpf: %ld", func[i].nome, func[i].cpf);
                    printf("\t Saldo disponivel: %.2Lf \n", func[i].saldo);
                    FuncSaque(cpf, senha, saldo);
                    system("clear");
                    break;
                case 2:
                    printf("\n  Nome: %s  Cpf: %ld", func[i].nome, func[i].cpf);
                    printf("\t Saldo disponivel: %.2Lf \n", func[i].saldo);
                    saldo = func[i].saldo;
                    FunDeposito(cpf, senha);
                    system("clear");
                    break;
                default:
                    printf("\n Digite uma opção valida! \n");
                    break;
                }
            }
             
        }
    }
}

int Login()
{
    int senha, OpContin;
    long int cpf, posicao;


    printf(" \n [1]-Continuar [2]-Cancelar: ");
    printf("\n Digite uma das opções:");
    scanf("%d",&OpContin);
    switch (OpContin)
    {
    case 1:
         
        printf("\n");
        printf(" Digite seu Cpf:");
        scanf("%ld", &cpf);
        ValidacaoCpf(cpf);
        printf(" Digite sua senha:");
        scanf("%d", &senha);
        ValidacaoSenha(senha);
        for (int i = 0; i < MAX; i++)
        {
            if(cpf == func[i].cpf  && senha == func[i].senha)
            {   
                
                ExibirDados(cpf, senha);          
            }
            else
            {
                printf("\n \tNegado! \n Verfique se seu cpf e senha estão corretos, e tente novamente. \n\n");
                sleep(3);
                system("clear");
            }
        }
        break;
        case 2:
        break;
    default:
        printf("\n Opção digitada não existente encerrando processo.");
        break;
    }

}

void AlterarSenha()
{
    char nome[45];
    long int cpf;
    int senha, ConfirmaSenha, OpContin;

    printf(" \n [1]-Continuar [2]-Cancelar: ");
    printf("\n Digite uma das opções:");

    scanf("%d",&OpContin);
    switch (OpContin)
    {
        case 1:
        printf("\n");
        printf("Digite o seu nome:");
        getchar();
        fgets(nome, sizeof(nome),stdin);
        printf("%s", nome);
        printf("Digite seu Cpf:");
        scanf("%ld", &cpf);
        ValidacaoCpf(cpf);


        for (int i = 0; i < MAX; i++)
        {
            if(func[i].cpf == cpf)
            {
                printf("\n Preencha os campos para confirmar a nova senha:"); 
                printf("\n Digite a nova senha:");
                scanf("%d",&senha);
                printf("\n Confirme a senha:");
                scanf("%d",&ConfirmaSenha);
                if (senha == ConfirmaSenha)
                {
                    func[i].senha = senha;
                }
                else
                {
                    do
                    {
                        printf("\n Preencha os campos para confirmar a nova senha:"); 
                        printf("\n Digite a nova senha:");
                        scanf("%d",&senha);
                        printf("\n Confirme a senha:");
                        scanf("%d",&ConfirmaSenha);
                        if (senha == ConfirmaSenha)
                        {
                            func[i].senha = senha;
                        }
                    } while (senha != ConfirmaSenha);  
                }
                
            }
            else
            {
                printf("\n Seus dados estão incoerentes, \n voltando ao menu inicial"); 
            }
        }
        break;
        case 2:
        break;
    }
}
