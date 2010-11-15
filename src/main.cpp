#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include <vector>
#include "simulador.h"

using namespace std;
using namespace TrabalhoAD;

#define INTCONF095  1.96

bool verbose = false;
bool modo_benchmark = false;
int verb;
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
  * No final da execução do simulador, retorna os parâmetros que foram usados para a simulação, para o caso de fazer a mesma simulação futuramente.
  */
void imprime_parametros_execucao(void);

/**
 * Imprime os dados estatisticos coletados em uma rodada de uma simulação.
 */
void imprimeresultado_rodada(ResultadosConsolidados result, int rodada);

/**
  * Faz a chamada para todos os cálculos de intervalo de confiança.
  */
void intervalos_confianca(vector<ResultadosConsolidados> &dados);

/**
  * Executa o benchmark para fazer a otimização da fase transiente.
  */
void roda_benchmark(void);

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
 * "--benchmark": Neste modo o simulador executará um benchmark para os valores do tamanho da fase transiente. Este modo irá interromper a execução do simulador após retornar os dados.
 * Forma 2:
 * Ao executar o simulador, a primeira coisa que é feita é verificar se os parâmetros foram passados. Se algum não foi passado, ele pedirá que se passe antes de começar a simulação.
 *
 * Também temos a opção de escolher como parâmetro do programa os parâmetros --ajuda, ou --sobre.
 * O parâmetro ajuda dá uma explicação resumida sobre os parâmetros que podem ser escolhidos.
 * O parâmetro sobre passa informações básicas sobre o grupo, integrantes e página do grupo.
 */
int main(int argc, char *argv[])
{
    int opcao;

    printf("Bem Vindo ao Cmulador, um simulador de filas.\n");
    printf("Para informacoes sobre como funciona a fila a ser simulada, leia nossa documentacao.\n");
    printf("Para ajuda nos parâmetros do programa, execute com o parametro --ajuda, ou -a.\n\n");

    while(1)
    {

        static struct option long_options[] =
        {
        {"benchmark",                   no_argument,            0, 'b'},
        {"ajuda",                       no_argument,            0, 'a'},
        {"sobre",                       no_argument,            0, 's'},
        {"verbose",                     required_argument,      0, 'v'},
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

        opcao = getopt_long (argc, argv, "basv:m:n:r:t:1:2:l:u:c:x:", long_options, &option_index);

        //printf("OPCAO = %c -- %d\n", opcao, opcao);

        if (opcao == -1) break;

        switch(opcao)
        {
        case 'v':
            verb = atoi(optarg);
            if (verb == 0)
            {
                verbose = false;
            }
            else if(verb == 1)
            {
                verbose = false;
            }
            else if(verb == 2)
            {
                verbose = true;
            }
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
	    printf("\"--benchmark\"(-b): Neste modo o simulador executara um benchmark para diversos valores de tamanho para a fase transiente.\n");
            printf("\"--verbose\"(-v): Execucao do programa em modo verborragico.\n");
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
            printf("Objetivo do desenvolvimento:\n");
            printf("Trabalho final da disciplina Avaliacao e Desempenho, do curso de Ciencia da Computacao da UFRJ.\nDisciplina cursada em 2010.2\n");
            printf("Pagina do projeto: http://code.google.com/p/ad20102/\n");
            printf("********************************\n\n");
            exit(0);
        case 'b':
            modo_benchmark = true;
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

    if ((modo != 1) && (modo != 2) && modo_benchmark == false)
    {
        printf("Escolha o tipo de simulacao deseja fazer:\n");
        printf("1 - Batch\n");
        printf("2 - Replicativo\n");
        printf("Escolha o numero: ");
        scanf("%d",&modo);
    }
    else if(modo_benchmark == false)
    {
        printf("Você ja escolheu o modo de simulacao: ");
        if (modo == 1) printf("Batch\n");
        else printf("Replicativo\n");
    }
    else
    {
	printf("Simulador irá rodar no modo de benchmark para a fase transiente.\n");
    }


    if(modo_benchmark == false)
    {
	if (n_rodadas <= -1)
	{
	    printf("Escolha a quantidade de rodadas: ");
	    scanf("%d",&n_rodadas);
	}
	else if (n_rodadas < 10)
	{
	    do
	    {
		printf("Voce determinou um valor menor que 10 para quantidade de rodadas, valor onde t-student nao e assintotico.\n");
		printf("Escolha a quantidade de rodadas: ");
		scanf("%d",&n_rodadas);
	    } while (n_rodadas < 10);
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
    }

    if (fila1 == NAODEFINIDA)
    {
        int op;

        do
        {
            printf("Escolha o tipo de serviço para a fila 1:\n");
            printf("1 - FCFS\n");
            printf("2 - LCFS\n");
            printf("Escolha o numero: ");
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
            printf("Escolha o numero: ");
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

    do
    {
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

        if (tx_lambda / tx_mi >= 1.0)
        {
            printf("As taxas escolhidas implicam em um ro maior que um. Isso faz as filas crescerem infinitamente.\n");
            printf("Escolha novos valores para tx_lambda e tx_mi.\n");
            tx_lambda = -1;
            tx_mi = -1;
        }
    } while(tx_lambda / tx_mi >= 1.0);

    if(modo_benchmark == true)
    {
	//Modo Benchmark da fase transiente.
	roda_benchmark();
    }
    else if (modo == 1)
    {
        //Modo Batch
        modobatch();
    }
    else if (modo == 2)
    {
        // Modo Replicativo
        modoreplicativo();
    }

    return 0;
}

void modobatch(void)
{
    vector<ResultadosConsolidados> dados; // vetor com os resultados consolidados de todas as rodadas
    Simulador *sim;
    ResultadosConsolidados result;

    if (seed_gerador_chegadas == -1 || seed_gerador_tempo_servico == -1)
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi);

        //sementes sendo passadas para a variável para poder retornar a chamada do programa.
        seed_gerador_tempo_servico = sim->semente_gerador_tempo_servico();
        seed_gerador_chegadas = sim->semente_gerador_chegadas();
    }
    else
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
    }

    sim->define_verbose(verbose);

    //Executando fase transiente

    if (verb == 2) printf("[INICIO] Executando fase transiente\n");

    sim->executa(t_transiente, false);

    if (verb == 2) printf("[FIM] Termino fase transiente\n");

    //Executando as rodadas
    for (int i = 0; i < n_rodadas; i++)
    {
        if (verb == 2) printf("[INICIO] Executando rodada %d\n", i);

        //Executando a rodada i
        result = sim->executa(t_rodada, true);

        if (verb == 2) printf("[FIM] Termino da rodada %d\n\n", i);

        // Armazena em um vetor os resultados
        dados.push_back(result);
        if (verb > 0)
        {
            imprimeresultado_rodada(result, i);
        }
        sim->limpa_dados_coletados();
    }

    intervalos_confianca(dados);

    imprime_parametros_execucao();

    delete sim;
}

void modoreplicativo(void)
{
    vector<ResultadosConsolidados> dados; // vetor com os resultados consolidados de todas as rodadas
    Simulador *sim;
    ResultadosConsolidados result;

    if (seed_gerador_chegadas == -1 || seed_gerador_tempo_servico == -1)
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi);

        //sementes sendo passadas para a variável para poder retornar a chamada do programa.
        seed_gerador_tempo_servico = sim->semente_gerador_tempo_servico();
        seed_gerador_chegadas = sim->semente_gerador_chegadas();
    }
    else
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
    }

    sim->define_verbose(verbose);

    for (int i = 0; i < n_rodadas; i++)
    {

        //Executando fase transiente

        if (verb == 2) printf("[INICIO] Executando fase transiente\n");

        sim->executa(t_transiente, false);

        if (verb == 2) printf("[FIM] Termino fase transiente\n");

        if (verb == 2) printf("[INICIO] Executando rodada %d\n", i);

        //Executando a rodada
        result = sim->executa(t_rodada, true);

        if (verb == 2) printf("[FIM] Termino da rodada %d\n\n", i);

        // Armazena em um vetor os resultados
        dados.push_back(result);

        if (verb > 0)
        {
            imprimeresultado_rodada(result, i);
        }

        sim->reinicia_simulador();
    }

    intervalos_confianca(dados);

    imprime_parametros_execucao();

    delete sim;
}

void imprime_parametros_execucao(void)
{
    printf("Voce pode executar novamente esta simulacao com os seguintes parametros:\n");
    printf("cmulator ");
    
    if(modo_benchmark == false)
    {
	printf("-m ");
    
	if (modo == 1)
	{
	    printf("batch ");
	}
	else
	{
	    printf("replicativo ");
	}
	
	
	printf("-n %d -r %d -t %d ", n_rodadas, t_rodada, t_transiente);
    }
    
    
    printf("-1 ");
    if (fila1 == FIFO)
    {
        printf("FCFS ");
    }
    else
    {
        printf("LCFS ");
    }
    printf("-2 ");
    if (fila2 == FIFO)
    {
        printf("FCFS ");
    }
    else
    {
        printf("LCFS ");
    }
    
    printf("-l %lf -u %lf -c %ld -x %ld\n", tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
}

void imprimeresultado_rodada(ResultadosConsolidados result, int rodada)
{
    double n = result.quantidade;

    printf("Imprimindo resultado da rodada %d\n", rodada);
    printf("Fila1 -> E[X]: %lf | E[X^2]: %lf\n",result.fila1.X / n , result.fila1.X_quad / n);
    printf("Fila1 -> E[W]: %lf | E[W^2]: %lf\n",result.fila1.W / n, result.fila1.W_quad / n);
    printf("Fila1 -> E[T]: %lf | E[T^2]: %lf\n",result.fila1.T / n, result.fila1.T_quad / n);
    printf("Fila1 -> E[Nq]: %lf | E[Nq^2]: %lf\n",result.fila1.Nq / n, result.fila1.Nq_quad / n);
    printf("Fila1 -> E[N]: %lf | E[N^2]: %lf\n",result.fila1.N / n, result.fila1.N_quad / n);
    printf("Fila2 -> E[X]: %lf | E[X^2]: %lf\n",result.fila2.X / n, result.fila2.X_quad / n);
    printf("Fila2 -> E[W]: %lf | E[W^2]: %lf\n",result.fila2.W / n, result.fila2.W_quad / n);
    printf("Fila2 -> E[T]: %lf | E[T^2]: %lf\n",result.fila2.T / n, result.fila2.T_quad / n);
    printf("Fila2 -> E[Nq]: %lf | E[Nq^2]: %lf\n",result.fila2.Nq / n, result.fila2.Nq_quad / n);
    printf("Fila2 -> E[N]: %lf | E[N^2]: %lf\n\n",result.fila2.N / n, result.fila2.N_quad / n);
}

void intervalos_confianca(vector<ResultadosConsolidados> &dados)
{
    double estimador_media, estimador_var, intervalo;

    printf("***********************************\n");
    printf("Intervalos de Confiança:\n");
    printf("Inicio (Media) Fim [Tamanho] [Em relacao a media]\n");
    printf("***********************************\n\n");

    printf("***Fila 1***\n");

    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila1.X / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila1.X / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila1.X / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[X] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);


    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila1.W / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila1.W / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila1.W / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[W] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += ((double)dados[i].fila1.W_quad / dados[i].quantidade) -
                           (((double)dados[i].fila1.W / dados[i].quantidade) * ((double)dados[i].fila1.W / dados[i].quantidade));
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        double temp = ((double)dados[i].fila1.W_quad / dados[i].quantidade) -
                      (((double)dados[i].fila1.W / dados[i].quantidade) * ((double)dados[i].fila1.W / dados[i].quantidade));
	estimador_var += (temp - estimador_media) *
			 (temp - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("V(W) = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila1.T / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila1.T / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila1.T / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[T] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila1.Nq / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila1.Nq / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila1.Nq / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[Nq] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila1.N / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila1.N / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila1.N / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[N] = %lf %lf [%lf] [%lf%%]\n\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    printf("***Fila 2***\n");

    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila2.X / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila2.X / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila2.X / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[X] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila2.W / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila2.W / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila2.W / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[W] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);


    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += ((double)dados[i].fila2.W_quad / dados[i].quantidade) -
                           (((double)dados[i].fila2.W / dados[i].quantidade) * ((double)dados[i].fila2.W / dados[i].quantidade));
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        double temp = ((double)dados[i].fila2.W_quad / dados[i].quantidade) -
                      (((double)dados[i].fila2.W / dados[i].quantidade) * ((double)dados[i].fila2.W / dados[i].quantidade));
	estimador_var += (temp - estimador_media) *
			 (temp - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("V(W) = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);


    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila2.T / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila2.T / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila2.T / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[T] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila2.Nq / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila2.Nq / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila2.Nq / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[Nq] = %lf (%lf) %lf [%lf] [%lf%%]\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);



    estimador_media = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_media += (double)dados[i].fila2.N / dados[i].quantidade;
    }
    estimador_media /= (double)dados.size();

    estimador_var = 0.0;
    for(unsigned int i = 0; i < dados.size(); i++)
    {
        estimador_var += (((double)dados[i].fila2.N / dados[i].quantidade) - estimador_media) *
                         (((double)dados[i].fila2.N / dados[i].quantidade) - estimador_media);
    }
    estimador_var /= (double)(dados.size() - 1);

    intervalo = INTCONF095 * (sqrt(estimador_var) / sqrt(dados.size()));

    printf("E[N] = %lf %lf [%lf] [%lf%%]\n\n", (estimador_media - intervalo < 0) ? 0 : estimador_media - intervalo, estimador_media + intervalo, 2.0 * intervalo, (200.0 * intervalo) / estimador_media);

}

void roda_benchmark(void)
{
    vector<ResultadosConsolidados> dados; // vetor com os resultados consolidados de todas as rodadas
    Simulador *sim;
    ResultadosConsolidados result;

    modo = -1;
    n_rodadas = -1;
    t_rodada = -1;
    t_transiente = 0;

    if (seed_gerador_chegadas == -1 || seed_gerador_tempo_servico == -1)
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi);

        //sementes sendo passadas para a variável para poder retornar a chamada do programa.
        seed_gerador_tempo_servico = sim->semente_gerador_tempo_servico();
        seed_gerador_chegadas = sim->semente_gerador_chegadas();
    }
    else
    {
        sim = new Simulador(fila1, fila2, tx_lambda, tx_mi, seed_gerador_chegadas, seed_gerador_tempo_servico);
    }

    sim->define_verbose(verbose);

    if (verb == 2) printf("[INICIO] Executando fase transiente\n");

    sim->executa(0, false);

    if (verb == 2) printf("[FIM] Termino fase transiente\n");

    for (n_rodadas = 1; n_rodadas <= 1000; n_rodadas++)
    {
        for (t_rodada = 1; t_rodada <= 1000; t_rodada++)
        {
            if (verb == 2) printf("[INICIO] Executando rodada %d com t_rodada %d\n", n_rodadas, t_rodada);

            //Executando a rodada i
            result = sim->executa(t_rodada, true);

            if (verb == 2) printf("[FIM] Termino da rodada %d com t_rodada %d\n\n", n_rodadas, t_rodada);

            // Armazena em um vetor os resultados
            dados.push_back(result);

            sim->limpa_dados_coletados();

            intervalos_confianca(dados);

            imprime_parametros_execucao();
        }


    }

    delete sim;


}
