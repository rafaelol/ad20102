#ifndef FREGUES_H_
#define FREGUES_H_

#include <cstdio>

namespace TrabalhoAD
{

    /** \brief A classe Fregues representa um freguês que chegou durante a simulação.
     *
     *  Um objeto do tipo freguês armazena dados obtidos durante a simulação, como por exemplo
     *  o tempo de espera em cada um das filas, a duração do serviço para ele e a quantidade
     *  de outros fregueses em cada fila no momento de sua chegada no sistema. Estes dados serão
     *  utilizados no final da simulação para a obtenção dos valores médios e variâncias do sistema simulado.
     *
     *
     */
    class Fregues
    {
        private:
        int m_id; /**< Identificador único do freguês no sistema */
        int m_rodada; /**< Em qual rodada o freguês está. */

        int m_fila; /**< Em qual fila o freguês está */

        double m_tempo_chegada_fila1; /**< Tempo em que o freguês chegou no sistema e entrou na fila 1. */
        double m_tempo_saida_fila1; /**< Tempo em que o freguês saiu da fila 1 para seu primeiro serviço. */
        double m_tempo_chegada_fila2; /**< Tempo em que o freguês saiu do primeiro serviço e foi para a fila 2. */
        double m_tempo_saida_fila2; /**< Tempo em que o freguês saiu da fila 2 para seu segundo serviço. */
        double m_tempo_saida_sistema; /**< Tempo em que o freguês saiu do segundo serviço e saiu do sistema. */

        int m_quantidade_fila1; /**< Quantidade de fregueses na fila 1 no momento de chegada deste freguês. */
        int m_quantidade_fila2; /**< Quantidade de fregueses na fila 2 no momento de chegada deste freguês. */
        int m_tipo_cliente_servido; /**< Se no momento da chegada o freguês servido era da fila 1, 2 ou se não havia nenhum freguês em atendimento no servidor. */
        public:

        /**
         * Construtor padrão para a classe Fregues; iniciliza todos os valores com 0.
         */
        Fregues();

        /**
         * Construtor da classe Fregues.
         *
         * \param id Um identificador único do freguês no sistema.
         * \param tempo_chegada O tempo (a partir de 0.0) em que o freguês chegou no sistema.
         * \param quantidade_fila1 Quantidade de outros fregueses na fila de espera 1 no momento que o freguês chega ao sistema.
         * \param quantidade_fila2 Quantidade de outros fregueses na fila de espera 2 no momento que o freguês chega ao sistema.
         * \param tipo_cliente_servido Se no momento da chegada o freguês servido era da fila 1, 2 ou se não havia freguês em atendimento no servidor.
         * \param n_rodada Indica a rodada que o freguês pertence.
         */
        Fregues(int id, double tempo_chegada, int quantidade_fila1, int quantidade_fila2, int tipo_cliente_servido, int n_rodada);

        /**
         * Registra o tempo em que o freguês saiu da fila de espera 1 para o seu primeiro serviço.
         *
         * \param tempo Tempo em que o freguês saiu da fila de espera 1.
         */
        void saiu_fila1(double tempo);

        /**
         * Registra o tempo em que o freguês terminou seu primeiro serviço e foi encaminhado para a fila de espera 2.
         *
         * \param tempo Tempo em que o freguês terminou seu primeiro serviço.
         */
        void terminou_servico1(double tempo);

        /**
         * Registra o tempo em que o freguês saiu da fila de espera 2 para o seu segundo serviço.
         *
         * \param tempo Tempo em que o freguês saiu da fila de espera 2.
         */
        void saiu_fila2(double tempo);

        /**
         * Registra o tempo em que o freguês terminou seu segundo serviço e saiu do sistema.
         *
         * \param tempo Tempo em que o freguês terminou seu segundo serviço.
         */
        void terminou_servico2(double tempo);

        /**
         * A quantidade de tempo que o freguês aguardou na fila de espera 1.
         */
        double tempo_espera1();

        /**
         * A quantidade de tempo que o freguês aguardou na fila de espera 2.
         */
        double tempo_espera2();

        /**
         * A duração do primeiro serviço do freguês.
         */
        double tempo_servico1();

        /**
         * A duração do segundo serviço do freguês.
         */
        double tempo_servico2();

        /**
         * A quantidade total de tempo gasto pelo freguês na primeira fila (espera + serviço).
         */
        double tempo_total1();

        /**
         * A quantidade total de tempo gasto pelo freguês na segunda fila (espera + serviço).
         */
        double tempo_total2();

        /**
         * A quantidade de outros fregueses na fila 1 no momento da chegada deste freguês ao sistema.
         */
        int quantidade_elementos_fila1();

        /**
         * A quantidade de outros fregueses na fila 2 no momento da chegada deste freguês ao sistema.
         */
        int quantidade_elementos_fila2();

        /**
         * A quantidade de outros fregueses no sistema 2 (fila + servidor) no momento da chegada deste freguês ao sistema.
         */
        int quantidade_elementos_sistema1();

        /**
         * A quantidade de outros fregueses no sistema 2 (fila + servidor) no momento da chegada deste freguês ao sistema.
         */
        int quantidade_elementos_sistema2();

        /**
         * Se no momento da chegada o freguês servido era da fila 1, 2 ou se não havie nenhum freguês em atendimento no servidor.
         */
        int tipo_cliente_servido();

        /**
         * Se o freguês no momento está no processo da fila 1 ou fila 2.
         */
        int fila_pertencente();

        /**
         * Qual a rodada o freguês pertence.
         */
        int rodada_pertencente();

        /**
         * Imprime as informações do freguês.
         */
        void print();

    };


}

#endif //FREGUES_H_

