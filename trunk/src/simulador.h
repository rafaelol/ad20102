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
     * TipoFila indica qual o tipo da fila: Indefinido, FIFO/FCFS ou LIFO/LCFS
     */
    enum TipoFila {NAODEFINIDA, FIFO, LIFO};

    /**
     * A struct AmostragemFila unifica os dados de uma determinada fila.
     */
    typedef struct
    {
        double X; /**< Soma dos tempos de serviço na fila. */
        double X_quad; /**< Soma dos quadrados dos tempos de serviço na fila. */
        double W; /**< Soma dos tempos de espera na fila. */
        double W_quad; /**< Soma dos quadrados dos tempos de serviço na fila. */
        double T; /**< Soma dos tempos totais na fila + servidor. */
        double T_quad; /**< Soma dos quadrados dos tempos totais na fila + servidor */
        long long int Nq; /**< Soma da quantidade de fregueses na fila. */
        long long int Nq_quad; /**< Soma dos quadrados da quantidade de fregueses na fila. */
        long long int N; /**< Soma da quantidade de fregueses na fila + servidor. */
        long long int N_quad; /** Soma dos quadrados da quantidade de fregueses na fila + servidor. */

    } AmostragemFila;

    /**
     * A struct ResultadosConsolidados reune os dados das duas filas do sistema.
     */
    typedef struct
    {
        int quantidade; /**< Quantidade de amostras realizadas */

        AmostragemFila fila1; /**< Dados da fila 1 */
        AmostragemFila fila2; /**< Dados da fila 2 */
    } ResultadosConsolidados;


    /**
     * A classe Simulador é a responsável por executar a simulação propriamente dita,
     * coletar e armazenar os resultados de cada rodada e apresentar o resultado
     * da simulação.
     *
     */
    class Simulador
    {
    private:
    priority_queue<Evento, vector<Evento>, greater<Evento> > m_eventos; /**< Heap com os eventos a serem processados. */

    deque<Fregues> m_fila1; /**< Fila de espera 1. */
    deque<Fregues> m_fila2; /**< Fila de espera 2. */

    TipoFila m_tipo_fila1; /**< Forma de serviço da fila de espera 1 (FCFS/LCFS). */
    TipoFila m_tipo_fila2; /**< Forma de serviço da fila de espera 2 (FCFS/LCFS). */

    DistExponencial* m_chegada; /**< Gerador de tempos exponencialmente distribuidos para as chegadas ao sistema. */
    DistExponencial* m_servico; /**< Gerador de tempos exponencialmente distribuidos para os tempos de servico. */

    double m_tempo_atual; /**< Tempo de simulação. */
    int m_prox_id; /**< Id do próximo freguês. */

    Fregues m_fregues_em_servico; /**< Freguês atualmente em serviço. */
    bool m_servidor_ocupado; /**< Indica se existe alguem em processamento no servidor. */

    ResultadosConsolidados m_resultados; /**< Armazena os dados coletados por esta instância do simulador. */
    bool m_verbose; /**< Indica se o Simulador deve imprimir informações sobre sua execução (modo verborrágico). Padrão: FALSO. */

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
     * \param taxa_chegada Taxa lambda de chegada de fregueses ao sistema.
     * \param taxa_servico Taxa mi do tempo de serviço do servidor.
     *
     */
    Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico);


    /**
     * Construtor da classe Simulador.
     *
     * \param fila1 Modo de serviço da Fila 1, FCFS ou LCFS.
     * \param fila2 Modo de serviço da Fila 2, FCFS ou LCFS.
     * \param taxa_chegada Taxa lambda de chegada de fregueses ao sistema.
     * \param taxa_servico Taxa mi do tempo de serviço do servidor.
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
     * Executa o simulador até que 'quantidade' de fregueses tenham sido servidos completamente.
     * Os dados estatísticos dos fregueses atendidos podem ser coletados e armazenados ou não
     * (como por exemplo para ignorar os dados gerados na frase transiente).
     *
     * \param quantidade Número de fregueses que devem ser servidos completamente.
     * \param coleta Realiza a coleta de dados estatísticos ou não.
     */
    ResultadosConsolidados executa(int quantidade, bool coleta);

    /**
     * Zera todos os dados estatísticos coletados até o momento.
     */
    void limpa_dados_coletados();

    /**
     * Volta o simulador para seu estado inicial, removendo todos os fregueses e os dados coletados,
     * mas mantem o estado dos PRNGs.
     */
    void reinicia_simulador();

    /**
     * Ativa ou desativa o modo verborrágico do Simulador.
     */
    void define_verbose(bool ativado);

    /**
     * Retorna a semente geradora de tempo de serviço.
     */
    long int semente_gerador_tempo_servico(void);

    /**
     * Retorna a semente geradora de tempo de chegadas.
     */
    long int semente_gerador_chegadas(void);

    };


}

#endif //SIMULADOR_H_

