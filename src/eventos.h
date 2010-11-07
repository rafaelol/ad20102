#ifndef EVENTOS_H_
#define EVENTOS_H_

namespace Simulador {

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

/**
 * Implementa o operador < para comparação entre dois eventos.
 * Um evento ev1 é menor que outro evento ev2 se o tempo em que
 * ev1 ocorrerá for menor do que o tempo em que ev2 ocorrerá.
 */
bool operator < (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() < ev2.tempo()) return true;
        else return false;
}

/**
 * Implementa o operador <= para comparação entre dois eventos.
 * Um evento ev1 é menor ou igual que outro evento ev2 se o tempo em que
 * ev1 ocorrerá for menor ou igual do que o tempo em que ev2 ocorrerá.
 */
bool operator <= (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() <= ev2.tempo()) return true;
        else return false;
}
/**
 * Implementa o operador > para comparação entre dois eventos.
 * Um evento ev1 é maior que outro evento ev2 se o tempo em que
 * ev1 ocorrerá for maior do que o tempo em que ev2 ocorrerá.
 */
bool operator > (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() > ev2.tempo()) return true;
        else return false;
}

/**
 * Implementa o operador >= para comparação entre dois eventos.
 * Um evento ev1 é maior ou igual que outro evento ev2 se o tempo em que
 * ev1 ocorrerá for maior ou igual do que o tempo em que ev2 ocorrerá.
 */
bool operator >= (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() >= ev2.tempo()) return true;
        else return false;
}

/**
 * Implementa o operador == para comparação entre dois eventos.
 * Um evento ev1 é igual a outro evento ev2 se o tempo em que
 * ev1 ocorrerá for igual ao tempo em que ev2 ocorrerá.
 */
bool operator == (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() == ev2.tempo()) return true;
        else return false;
}

/**
 * Implementa o operador != para comparação entre dois eventos.
 * Um evento ev1 é diferente a outro evento ev2 se o tempo em que
 * ev1 ocorrerá for diferente ao tempo em que ev2 ocorrerá.
 */
bool operator != (const Evento& ev1, const Evento& ev2)
{
        if(ev1.tempo() != ev2.tempo()) return true;
        else return false;
}




}

#endif //EVENTOS_H_
