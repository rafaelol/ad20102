#include "eventos.h"

namespace Simulador {

Evento::Evento(ETipo tipo, double tempo)
{
	m_tipo = tipo;
	m_tempo = tempo;
}

ETipo Evento::tipo() const
{
	return m_tipo;
}

double Evento::tempo() const
{
	return m_tempo;
}

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
