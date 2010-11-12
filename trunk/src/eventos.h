#ifndef EVENTOS_H_
#define EVENTOS_H_

namespace TrabalhoAD
{

    /**
     * ETipo define os tipos de eventos que podem ocorrer no sistema.
     *
     * proxima_chegada_no_sistema:
     * Um novo fregues chegou ao sistema.
     *
     * termino_servico:
     * O serviço a um fregues terminou.
     */
    enum ETipo {proxima_chegada_no_sistema, termino_servico};

    /**
     *  A classe Evento representa um evento ocorrido em nosso sistema.
     *
     *  A classe descreve o tipo de evento e o tempo em que o evento ocorrerá.
     */
    class Evento
    {
    private:
    ETipo m_tipo; /**< Indica qual o tipo do evento */
    double m_tempo; /**< Indica o tempo no qual o evento ocorrerá */

    public:

    /**
     * Construtor da classe Evento
     *
     * \param tipo Determina o tipo do evento.
     * \param tempo O tempo em que o evento ocorrerá.
     */
    Evento(ETipo tipo, double tempo);

    /**
     * Retorna o tipo do evento.
     */
    ETipo tipo() const;

    /**
     * Retorna o tempo em que o evento ocorrerá.
     */
    double tempo() const;
    };


}

#endif //EVENTOS_H_
