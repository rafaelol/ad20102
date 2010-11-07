#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include<vector>
#include<queue>

#include "fregues.h"
#include "exponencial.h"
#include "eventos.h"

using namespace std;


namespace Simulador
{

/**
 * TipoFila indica qual o tipo da fila, FIFO/FCFS ou LIFO/LCFS
 */
enum TipoFila {FIFO, LIFO};

/**
 * A struct AmostragemFila unifica os dados de uma determinada fila.
 */
typedef struct
{
	double X; /**< Soma dos tempos de serviço na fila. */
	double X_quad; /**< Soma dos quadrados dos tempos de serviço na fila. */
	double W; /**< Soma dos tempos de esperas na fila. */
	double W_quad; /**< Soma dos quadrados dos tempos de serviço na fila. */
	double T; /**< Soma dos tempos totais na fila + servidor. */
	double T_quad; /**< Soma dos quadrados dos tempos totais na fila + servidor */
	int Nq; /**< Soma da quantidade de pessoas na fila. */
	int Nq_quad; /**< Soma dos quadrados da quantidade de pessoas na fila. */
	int N; /**< Soma da quantidade de pessoas na fila + servidor. */
	int N_quad; /** Soma dos quadrados da quantidade de pessoas na fila + servidor. */

} AmostragemFila;

/**
 * A struct ResultadosConsolidados reuni os dados das duas filas do sistema 
 */
typedef struct
{
	int quantidade; /**< Quantidade de amostras realizadas */

	AmostragemFila fila1; /**< Dados da fila 1 */
	AmostragemFila fila2; /**< Dados da fila 2 */
} ResultadosConsolidados;


/**
 * A classe Simulador é a responsável por executar a simulação propriamente,
 * coletar e armazenar os resultados de cada rodada e apresentar o resultado
 * da simulação.
 *
 */
class Simulador
{
private:
priority_queue<Evento, vector<Evento>, greater<Evento> > m_eventos; /**< Heap com os eventos a serem processador. */

queue<Fregues> m_fila1; /**< Fila de espera 1. */
queue<Fregues> m_fila2; /**< Fila de espera 2. */

TipoFila m_tipo_fila1; /**< Forma de serviço da fila de espera 1. */
TipoFila m_tipo_fila2; /**< Forma de serviço da fila de espera 2. */

DistExponencial* m_chegada; /**< Gerador de tempos exponencialmente distribuidos para as chegadas ao sistema. */
DistExponencial* m_servico; /**< Gerador de tempos exponencialmente distribuidos para os tempos de servico. */

double m_tempo_atual; /**< Tempo de simulação. */

ResultadosConsolidados m_resultados; /**< Armazena os dados coletados por esta instância do simulador. */
public:

/**
 * Construtor da classe Simulador.
 *
 * \param fila1 Modo de serviço da Fila 1, FCFS ou LCFS.
 * \param fila2 Modo de serviço da Fila 2, FCFS ou LCFS.
 * \param taxa_chegada Taxa lambda de chegada de clientes ao sistema.
 * \param taxa_servico Taxa mi do tempo de serviço.
 *
 */
Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico);


/**
 * Construtor da classe Simulador.
 *
 * \param fila1 Modo de serviço da Fila 1, FCFS ou LCFS.
 * \param fila2 Modo de serviço da Fila 2, FCFS ou LCFS.
 * \param taxa_chegada Taxa lambda de chegada de clientes ao sistema.
 * \param taxa_servico Taxa mi do tempo de serviço.
 * \param semente_chegada Semente para alimentar o gerador das chegadas do sistema.
 * \param semente_servico Semente para alimentar o gerador dos tempos de serviço do sistema.
 *
 */
Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico, long int semente_chegada, long int semente_servico);

/**
 * Destrutor responsável por desalocar os recursos do simulador.
 */
~Simulador();

/**
 * Executa o simulador até que 'quantidade' de clientes tenham sido servidos completamente, mas não armazena os dados
 * estatísticos. Utilize para proceder com a fase transiente.
 */ 
void executa_sem_coleta(int quantidade);

/**
 * Executa o simulador até que 'quantidade' de clientes tenham sido servidos completamente, armazena e retorna os dados
 * estatísticos. Utilize para proceder com a fase normal de simulação.
 */ 
ResultadosConsolidados executa_com_coleta(int quantidade);

};










}

#endif //SIMULADOR_H_

