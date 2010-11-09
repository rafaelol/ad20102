#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include<vector>
#include<queue>
#include<deque>

#include "fregues.h"
#include "exponencial.h"
#include "eventos.h"

using namespace std;


namespace TrabalhoAD
{

/**
 * TipoFila indica qual o tipo da fila, FIFO/FCFS ou LIFO/LCFS
 */
enum TipoFila {NAODEFINIDA, FIFO, LIFO};

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

deque<Fregues> m_fila1; /**< Fila de espera 1. */
deque<Fregues> m_fila2; /**< Fila de espera 2. */

TipoFila m_tipo_fila1; /**< Forma de serviço da fila de espera 1. */
TipoFila m_tipo_fila2; /**< Forma de serviço da fila de espera 2. */

DistExponencial* m_chegada; /**< Gerador de tempos exponencialmente distribuidos para as chegadas ao sistema. */
DistExponencial* m_servico; /**< Gerador de tempos exponencialmente distribuidos para os tempos de servico. */

double m_tempo_atual; /**< Tempo de simulação. */
int m_prox_id; /**< Id do próximo cliente. */

Fregues m_fregues_em_servico; /**< Fregues atualmente em serviço. */
bool m_servidor_ocupado; /**< Indica se existe alguem em processamento no servidor. */

ResultadosConsolidados m_resultados; /**< Armazena os dados coletados por esta instância do simulador. */
bool m_verbose; /**< Indica se o Simulador deve imprimir informações sobre sua execução. O padrão é falso. */

/**
 * Função interna para inicializar as variáveis internas do simulador.
 */
void setup();

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
 * Executa o simulador até que 'quantidade' de clientes tenham sido servidos completamente.
 * Os dados estatísticos dos clientes atendidos podem ser coletados e armazenados ou não (como por exemplo para a frase transiente).
 *
 * \param quantidade Número de clientes que devem ser servidos completamente.
 * \param coleta Realiza a coleta de dados estatísticos ou não.
 */ 
ResultadosConsolidados executa(int quantidade, bool coleta);

/**
 * Zera todos os dados estatísticos coletados até o momento.
 */
void limpa_dados_coletados();

/**
 * Ativa ou desativa o modo verbose (verborrágico) do Simulador.
 */
void define_verbose(bool ativado);
};




}

#endif //SIMULADOR_H_

