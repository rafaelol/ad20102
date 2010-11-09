#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include "simulador.h"

using namespace std;
using namespace TrabalhoAD;

int modo = -1;
int n_rodadas = -1;
int t_rodada = -1;
int t_transiente = -1;
TipoFila fila1 = NAODEFINIDA;
TipoFila fila2 = NAODEFINIDA;
double tx_lambda = -1;
double tx_mi = -1;
long int seed_gerador_chegadas = -1;
long int seed_gerador_tempo_servico = -1;

/**
 * A funcao modobatch inicia o simulador através do modo batch.
 */
void modobatch(void);

/**
 * A funcao modobatch inicia o simulador através do modo replicativo.
 */
void modoreplicativo(void);

/**
 * Imprime os dados estatisticos coletados em uma rodada de uma simulação.
 */
void imprimeresultado_rodada(ResultadosConsolidados result, int rodada);

/**
 * A classe main define a forma que o simulador será executado. Existem duas formas de determinar como será executado.
 * Forma 1:
 * O dado é passado através de parâmetros ao executar o programa. Os parâmetros são:
 * "--modo": ao selecionar esse parâmetro, escolhemos o modo de execução das simulações, que pode ser tanto Batch como Replicativo.
 * "--n_rodadas": ao selecionar esse parâmetro, escolhemos a quantidade de rodadas que serão executadas
 * "--t_rodada": ao selecionar esse parâmetro, escolhemos o tamanho que as rodadas possuem.
 * "--t_transiente": ao selecionar esse parâmetro, escolhemos o tamanho da fase transiente.
 * "--fila1": Escolhe a disciplina de atendimento da Fila 1(FCFS ou LCFS)
 * "--fila2": Escolhe a disciplina de atendimento da Fila 2(FCFS ou LCFS)
 * "--tx_lambda": Escolhe o valor da taxa lambda, de chegada os clientes
 * "--tx_mi": Escolhe o valor da taxa mi, de atendimento do servidor.
 * "--seed_gerador_chegadas":
 * "--seed_gerador_tempo_servico":
 * Forma 2:
 * Ao executar o simulador, a primeira coisa que é feita é verificar se os parâmetros foram passados. Se algum não foi passado, ele pedirá que se passe antes de começar a simulação.
 *
 */
int main(int argc, char *argv[])
{
    bool verbose = false;
    int opcao;

    printf("Bem Vindo ao Cmulador, um simulador de filas.\n");
    printf("Para informacoes sobre como funciona a fila a ser simulada, leia nossa documentacao.\n");
    printf("Para ajuda nos parâmetros do programa, execute com o parametro --ajuda, ou -a.\n\n");

    while(1)
    {

        static struct option long_options[] =
        {
        {"ajuda",                       no_argument,            0, 'a'},
        {"sobre",                       no_argument,            0, 's'},
        {"verbose",                     no_argument,            0, 'v'},
        {"modo",                        required_argument,      0, 'm'},
        {"n_rodadas",                   required_argument,      0, 'n'},
        {"t_rodada",                    required_argument,      0, 'r'},
        {"t_transiente",                required_argument,      0, 't'},
        {"fila1",                       required_argument,      0, '1'},
        {"fila2",                       required_argument,      0, '2'},
        {"tx_lambda",                   required_argument,      0, 'l'},
        {"tx_mi",                       required_argument,      0, 'u'},
        {"seed_gerador_chegadas",       optional_argument,      0, 'c'},
        {"seed_gerador_tempo_servicos", optional_argument,      0, 'x'},
        {0, 0, 0, 0}
        };

        int option_index = 0;

        opcao = getopt_long (argc, argv, "v::a::s::m:n:r:t:1:2:l:u:c:x:", long_options, &option_index);

        //printf("OPCAO = %c -- %d\n", opcao, opcao);

        if (opcao == -1) break;

        switch(opcao)
        {
        case 'v':
            verbose = true;
            break;
        case 'a':
            printf("********************************\n");
            printf("Bem vindo a ajuda do Cmulator\n");
            printf("Instrucoes para execucao do programa:\n");
            printf("Os parametros da simulacao sao passados no prompt, ao executar o programa. Os parametros sao:\n");
            printf("\"--modo\"(-m): Escolha do modo de execucao das simulacoes. Opcoes: \"Batch\" ou  \"Replicativo\".\n");
            printf("\"--n_rodadas\"(-n): Escolha da quantidade de rodadas que serao executadas.\n");
            printf("\"--t_rodada\"(-r): Escolha do tamanho da rodada.\n");
            printf("\"--t_transiente\"(-t): Escolha do tamanho da fase transiente.\n");
            printf("\"--fila1\"(-1): Escolha da disciplina de servico da fila 1. Opcoes: \"FCFS\" ou \"LCFS\"\n");
            printf("\"--fila2\"(-2): Escolha da disciplina de servico da Fila 2. Opcoes: \"FCFS\" ou \"LCFS\"\n");
            printf("\"--tx_lambda\"(-l): Escolha do valor da taxa lambda, de chegada dos clientes.\n");
            printf("\"--tx_mi\"(-u): Escolha o valor da taxa mi, de atendimento do servidor.\n");
            printf("\"--seed_gerador_chegadas\"(-c): Semente utilizada para inicializar o gerador de chegadas.\n");
            printf("\"--seed_gerador_tempo_servico\"(-x): Semente utilizada para inicializar o tempo de servico.\n");
            printf("\"--sobre\"(-s): Sobre o projeto.\n");
            printf("Ao ser executado, o programa verifica os parâmetros usados, e perguntara iterativamente os parametros obrigatorios que faltam.\n");
            printf("Os seeds geradores somente sao passados atraves de parametros. Eles nao serao perguntados, pois sao opcionais.\n");
            printf("********************************\n\n");
            exit(0);
        case 's':
            printf("********************************\n");
            printf("Sobre o Cmulator:\n");
            printf("Equipe de Desenvolvimento:\n");
            printf("-- Bruno Buss\n");
            printf("-- Felipe Pedrosa\n");
            printf("-- Rafael Lopes\n");
            printf("-- Yanko Gitahy\n");
            printf("Pagina do projeto: http://code.google.com/p/ad20102/\n");
            printf("********************************\n\n");
            break;
        case 'm':
            if (strcasecmp("Batch", optarg) == 0)
            {
                modo = 1;
            }
            if (strcasecmp("Replicativo", optarg) == 0)
            {
                modo = 2;
            }
            break;
        case 'n':
            n_rodadas = atoi(optarg);
            break;
        case 'r':
            t_rodada = atoi(optarg);
            break;
        case 't':
            t_transiente = atoi(optarg);
            break;
        case '1':
            if ((strcasecmp("FCFS", optarg) == 0) || (strcasecmp("FIFO", optarg) == 0))
            {
                fila1 = FIFO;
            }
            if ((strcasecmp("LCFS", optarg) == 0) || (strcasecmp("LIFO", optarg) == 0))
            {
                fila1 = LIFO;
            }
            break;
        case '2':
            if ((strcasecmp("FCFS", optarg) == 0) || (strcasecmp("FIFO", optarg) == 0))
            {
                fila2 = FIFO;
            }
            if ((strcasecmp("LCFS", optarg) == 0) || (strcasecmp("LIFO", optarg) == 0))
            {
                fila2 = LIFO;
            }
            break;
        case 'l':
            tx_lambda = atof(optarg);
            break;
        case 'u':
            tx_mi = atof(optarg);
            break;
        case 'c':
            seed_gerador_chegadas = atoi(optarg);
            break;
        case 'x':
            seed_gerador_tempo_servico = atoi(optarg);
            break;
        }
    }

    //printf("DEBUG: \nmodo = %d \nn_rodada = %d \nt_rodada = %d \nt_transiente = %d\n", modo, n_rodadas, t_rodada, t_transiente);
    //printf("fila1 = %d\nfila2 = %d\ntx_lambda = %d\ntx_mi = %d\n", fila1, fila2, tx_lambda, tx_mi);
    //printf("seed__gerador_chegadas = %ld\nseed_gerador_tempo_servico = %ld\n", seed_gerador_chegadas, seed_gerador_tempo_servico);

    if ((modo != 1) && (modo != 2))
    {
        printf("Escolha o tipo de simulacao deseja fazer:\n");
        printf("1 - Batch\n");
        printf("2 - Replicativo\n");
        printf("Escolha o numero:");
        scanf("%d",&modo);
    }
    else
    {
        printf("Você ja escolheu o modo de simulacao: ");
        if (modo == 1) printf("Batch\n");
        else printf("Replicativo\n");
    }

    if (n_rodadas <= -1)
    {
        printf("Escolha a quantidade de rodadas:");
        scanf("%d",&n_rodadas);
    }
    else
    {
        printf("Você ja escolheu a quantidade de rodadas: %d\n", n_rodadas);
    }

    if (t_rodada <= -1)
    {
        printf("Escolha o tamanho de cada rodada: ");
        scanf("%d",&t_rodada);
    }
    else
    {
        printf("Você ja escolheu o tamanho de cada rodada: %d\n", t_rodada);
    }

    if (t_transiente <= -1)
    {
        printf("Escolha o tamanho da fase transiente: ");
        scanf("%d",&t_transiente);
    }
    else
    {
        printf("Você ja escolheu o tamanho da fase transiente: %d\n", t_transiente);
    }

    if (fila1 == NAODEFINIDA)
    {
        int op;

        do
        {
            printf("Escolha o tipo de serviço para a fila 1:\n");
            printf("1 - FCFS\n");
            printf("2 - LCFS\n");
            printf("Escolha o numero:");
            scanf("%d",&op);
            if (op == 1) fila1 = FIFO;
            else if (op == 2) fila1 = LIFO;
            else printf("Opcao invalida.\n");
        } while(fila1 == NAODEFINIDA);
    }
    else
    {
        printf("Você ja escolheu o tipo da fila 1: ");
        if (fila1 == FIFO) printf("FCFS\n");
        else printf("LCFS\n");
    }

    if (fila2 == NAODEFINIDA)
    {
        int op;

        do
        {
            printf("Escolha o tipo de serviço para a fila 2:\n");
            printf("1 - FCFS\n");
            printf("2 - LCFS\n");
            printf("Escolha o numero:");
            scanf("%d",&op);
            if (op == 1) fila2 = FIFO;
            else if (op == 2) fila2 = LIFO;
            else printf("Opcao invalida.\n");
        } while(fila2 == NAODEFINIDA);
    }
    else
    {
        printf("Você ja escolheu o tipo da fila 2: ");
        if (fila1 == FIFO) printf("FCFS\n");
        else printf("LCFS\n");
    }

    if (tx_lambda < 0.0)
    {
        printf("Escolha o valor da taxa lambda: ");
        scanf("%lf",&tx_lambda);
    }
    else
    {
        printf("Você ja escolheu o valor da taxa lambda: %f\n", tx_lambda);
    }

    if (tx_mi < 0.0)
    {
        printf("Escolha o valor da taxa mi: ");
        scanf("%lf",&tx_mi);
    }
    else
    {
        printf("Você ja escolheu o valor da taxa mi: %f\n", tx_mi);
    }

    if (modo == 1)
    {
        //Modo Batch
        modobatch();
    }
    if (modo == 2)
    {
        // Modo Replicativo
        modoreplicativo();
    }
    //começar a simulação

    return 0;
}

void modobatch(void)
{
    Simulador *sim;
    ResultadosConsolidados result;

    if (seed_gerador_chegadas == -1 || seed_gerador_tempo_servico == -1)
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi);
    }
    else
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
    }

    //Executando fase transiente

    sim->executa(t_transiente, false);

    //Executando as rodadas
    for (int i = 0; i < n_rodadas; i++)
    {
        result = sim->executa(t_rodada, true);
        imprimeresultado_rodada(result, i);
        sim->limpa_dados_coletados();
    }


    delete sim;
}

void modoreplicativo(void)
{
    Simulador *sim;
    ResultadosConsolidados result;

    for (int i = 0; i < n_rodadas; i++)
    {
        if (seed_gerador_chegadas == -1 || seed_gerador_tempo_servico == -1)
        {
            sim = new Simulador(fila1, fila2, tx_lambda, tx_mi);
        }
        else
        {
            printf("nao deveria passar aqui. Ops!\n");
            sim = new Simulador(fila1, fila2, tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
        }

        //Executando fase transiente

        sim->executa(t_transiente, false);

        //Executando a rodada
        result = sim->executa(t_rodada, true);
        imprimeresultado_rodada(result, i);

        delete sim;
    }
}

void imprimeresultado_rodada(ResultadosConsolidados result, int rodada)
{
    printf("Imprimindo resultado da rodada %d\n", rodada);
    printf("Fila1 -> X: %lf | X^2: %lf\n",result.fila1.X, result.fila1.X_quad);
    printf("Fila1 -> W: %lf | W^2: %lf\n",result.fila1.W, result.fila1.W_quad);
    printf("Fila1 -> T: %lf | T^2: %lf\n",result.fila1.T, result.fila1.T_quad);
    printf("Fila1 -> Nq: %d | Nq^2: %d\n",result.fila1.Nq, result.fila1.Nq_quad);
    printf("Fila1 -> N: %d | N^2: %d\n\n",result.fila1.N, result.fila1.N_quad);
    printf("Fila2 -> X: %lf | X^2: %lf\n",result.fila2.X, result.fila2.X_quad);
    printf("Fila2 -> W: %lf | W^2: %lf\n",result.fila2.W, result.fila2.W_quad);
    printf("Fila2 -> T: %lf | T^2: %lf\n",result.fila2.T, result.fila2.T_quad);
    printf("Fila2 -> Nq: %d | Nq^2: %d\n",result.fila2.Nq, result.fila2.Nq_quad);
    printf("Fila2 -> N: %d | N^2: %d\n\n",result.fila2.N, result.fila2.N_quad);
}
