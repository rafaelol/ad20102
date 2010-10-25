#include "exponencial.h"
#include <cstdlib>
#include <ctime>

namespace Simulador
{

DistExponencial::DistExponencial(double taxa)
{
	m_taxa = taxa;

	m_semente = time(NULL);
	srand48_r(m_semente, &m_estado_prng);
	
}

DistExponencial::DistExponencial(double taxa, long int semente)
{
	m_taxa = taxa;

	m_semente = semente;
	srand48_r(m_semente, &m_estado_prng);
}

double inversa(double prob)
{
	return 0.0;
}

long int DistExponencial::semente() const
{
	return m_semente;	
}

double DistExponencial::proxima_chegada()
{
	double rnd;

	drand48_r(&m_estado_prng, &rnd);
	return inversa(rnd);
}


}
