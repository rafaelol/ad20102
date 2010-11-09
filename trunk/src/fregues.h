#ifndef FREGUES_H_
#define FREGUES_H_

namespace Simulador
{

/** \brief A classe Fregues representa um fregues que chegou durante a simulação. 
 *
 *  A classe Fregues representa um fregues que chegou durante a simulação.
 *  Um objeto do tipo cliente armazena dados obtidos durante a simulação, como por exemplo
 *  o tempo de espera em cada um das filas, a duração do serviço para ele e a quantidade
 *  de pessoas em cada fila no momento de sua chegada no sistema. Estes dados serão utilizados
 *  no final da simulação para a obtenção dos valores médios e variâncias do sistema simulado.
 *
 *
 *  \todo Adicionar função de debug para a classe Fregues, de forma a imprimir todos os dados
 *        relevantes no ostream passado.
 */
class Fregues
{
private:
int m_id; /**< Identificador único do fregues no sistema */

int m_fila; /**< Em qual fila o fregues está */

double m_tempo_chegada_fila1; /**< Tempo em que o fregues chegou no sistema e entrou na fila 1. */
double m_tempo_saida_fila1; /**< Tempo em que o fregues saiu da fila 1 para seu primeiro serviço. */
double m_tempo_chegada_fila2; /**< Tempo em que o fregues saiu do primeiro serviço e foi para a fila 2. */
double m_tempo_saida_fila2; /**< Tempo em que o fregues saiu da fila 2 para seu segundo serviço. */
double m_tempo_saida_sistema; /**< Tempo em que o fregues saiu do segundo serviço e saiu do sistema. */

int m_quantidade_fila1; /**< Quantidade de fregueses na fila 1, no momento de chegada deste fregues. */
int m_quantidade_fila2; /**< Quantidade de fregueses na fila 2, no momento de chegada deste fregues. */
int m_tipo_cliente_servido; /**< Se no momento da chegada, o cliente servido era da fila 1, 2 ou se não tinha nenhum cliente em atendimento pelo servidor. */
public:

/**
 * Construtor da classe Fregues.
 *
 * \param id Um identificador único do fregues no sistema.
 * \param tempo_chegada O tempo (a partir de 0.0) que o fregues chegou no sistema.
 * \param quantidade_fila1 Quantidade e pessoas na fila de espera 1 no momento que o fregues chega ao sistema.
 * \param quantidade_fila2 Quantidade e pessoas na fila de espera 2 no momento que o fregues chega ao sistema.
 * \param tipo_cliente_servido Se no momento da chegada, o cliente servido era da fila 1, 2 ou se não tinha nenhum cliente em atendimento pelo servidor. 
 */
Fregues(int id, double tempo_chegada, int quantidade_fila1, int quantidade_fila2, int tipo_cliente_servido);

/**
 * Registra o tempo em que o fregues saiu da fila de espera 1 para o seu primeiro serviço.
 *
 * \param tempo Tempo em que o fregues saiu da fila de espera 1.
 */
void saiu_fila1(double tempo);

/**
 * Registra o tempo em que o fregues terminou seu primeiro serviço e foi encaminhado para a fila de espera 2.
 *
 * \param tempo Tempo em que o fregues terminou seu primeiro serviço.
 */
void terminou_servico1(double tempo);

/**
 * Registra o tempo em que o fregues saiu da fila de espera 2 para o seu segundo serviço.
 *
 * \param tempo Tempo em que o fregues saiu da fila de espera 2.
 */
void saiu_fila2(double tempo);

/**
 * Registra o tempo em que o fregues terminou seu segundo serviço e saiu do sistema.
 *
 * \param tempo Tempo em que o fregues terminou seu segundo serviço.
 */
void terminou_servico2(double tempo);

/**
 * A quantidade de tempo que o fregues ficou esperando na fila de espera 1.
 */
double tempo_espera1();

/**
 * A quantidade de tempo que o fregues ficou esperando na fila de espera 2.
 */
double tempo_espera2();

/**
 * A quantidade de tempo do primeiro serviço ao fregues.
 */
double tempo_servico1();

/**
 * A quantidade de tempo do segundo serviço ao fregues.
 */
double tempo_servico2();

/**
 * A quantidade total de tempo na primeira fila (espera + serviço).
 */
double tempo_total1();

/**
 * A quantidade total de tempo na segunda fila (espera + serviço).
 */
double tempo_total2();

/**
 * A quantidade de pessoas na fila 1 no momento da chegada deste fregues ao sistema.
 */
int quantidade_elementos_fila1();

/**
 * A quantidade de pessoas na fila 2 no momento da chegada deste fregues ao sistema.
 */
int quantidade_elementos_fila2();

/**
 * Se no momento da chegada, o cliente servido era da fila 1, 2 ou se não tinha nenhum cliente em atendimento pelo servidor.
 */
int tipo_cliente_servido();

/**
 * Se o cliente no momento esta no processo da fila 1 ou fila 2.
 */
int fila_pertencente();

};


}

#endif //FREGUES_H_

