#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

/**
 * A classe main define a forma que o simulador será executado. Existem duas formas de determinar como será executado.
 * Forma 1:
 * O dado é passado através de parâmetros ao executar o programa. Os parâmetros são:
 * "--modo": ao selecionar esse parâmetro, escolhemos o modo de execução das simulações, que pode ser tanto Batch como Replicativo.
 * "--n_rodadas": ao selecionar esse parâmetro, escolhemos a quantidade de rodadas que serão executadas
 * "--t_rodada": ao selecionar esse parâmetro, escolhemos o tamanho que as rodadas possuem.
 * "--t_transiente": ao selecionar esse parâmetro, escolhemos o tamanho da fase transiente.
 * Forma 2:
 * Ao executar o simulador, a primeira coisa que é feita é verificar se os parâmetros foram passados. Se algum não foi passado, ele pedirá que se passe antes de começar a simulação.
 *
 */
int main(int argc, char *argv[])
{
    int qnt_argumentos = argc;

    int modo = -1;
    int n_rodadas = -1;
    int t_rodada = -1;
    int t_transiente = -1;

    for (int i = 1; i < qnt_argumentos; i = i + 2)
    {
        if (strcmp(argv[i], "--modo") == 0)
        {
            if ((strcmp("Batch", argv[i + 1]) == 0) || (strcmp("batch", argv[i + 1]) == 0))
            {
                modo = 1;
            }
            if ((strcmp("Replicativo", argv[i + 1]) == 0) || (strcmp("replicativo", argv[i + 1]) == 0))
            {
                modo = 2;
            }
        }
        else if (strcmp(argv[i], "--n_rodadas") == 0)
        {
            n_rodadas = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--t_rodada") == 0)
        {
            t_rodada = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "--t_transiente") == 0)
        {
            t_transiente = atoi(argv[i + 1]);
        }
        /* Se necessario, incluir mais abaixo
        else if (strcmp(argv[i], "--") == 0)
        {

        }
        */
    }

    //printf("DEBUG: \nmodo = %d \nn_rodada = %d \nt_rodada = %d \nt_transiente = %d\n", modo, n_rodadas, t_rodada, t_transiente);

    printf("Bem Vindo ao Cmulador, um simulador de filas.\nPara informações sobre como funciona a fila a ser simulada, leia nossa documentação.\n\n");

    if ((modo != 1) && (modo != 2))
    {
        printf("Escolha o tipo de simulação deseja fazer:\n");
        printf("1 - Batch\n");
        printf("2 - Replicativo\n");
        printf("Escolha o número:");
        scanf("%d",&modo);
    }
    else
    {
        printf("Você já escolheu o modo de simulação: ");
        if (modo == 1) printf("Batch\n");
        else printf("Replicativo\n");
    }

    if (n_rodadas == -1)
    {
        printf("Escolha a quantidade de rodadas:");
        scanf("%d",&n_rodadas);
    }
    else
    {
        printf("Você já escolheu a quantidade de rodadas: %d\n", n_rodadas);
    }

    if (t_rodada == -1)
    {
        printf("Escolha o tamanho de cada rodada: ");
        scanf("%d",&t_rodada);
    }
    else
    {
        printf("Você já escolheu o tamanho de cada rodada: %d\n", t_rodada);
    }

    if (t_transiente == -1)
    {
        printf("Escolha o tamanho da fase transiente: ");
        scanf("%d",&t_transiente);
    }
    else
    {
        printf("Você já escolheu o tamanho da fase transiente: %d\n", t_transiente);
    }

    //começar a simulação

    return 0;
}
