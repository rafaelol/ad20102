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

}
