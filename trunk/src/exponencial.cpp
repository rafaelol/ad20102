#include "exponencial.h"

using namespace std;


namespace TrabalhoAD
{

    DistExponencial::DistExponencial(double taxa)
    {
        struct timeval tempo;

        m_taxa = taxa;
        m_deterministico = false;
        
        gettimeofday(&tempo, NULL);

        m_semente = tempo.tv_usec;
        srand48_r(m_semente, &m_estado_prng);
    }

    DistExponencial::DistExponencial(double taxa, long int semente)
    {
        m_taxa = taxa;
        m_deterministico = false;
        
        m_semente = semente;
        srand48_r(m_semente, &m_estado_prng);
    }

    double DistExponencial::inversa(double prob)
    {
        // Probabilidade entre 0 e 1.
        return (-1) * (log(1 - prob) / m_taxa);
    }

    long int DistExponencial::semente() const
    {
        return m_semente;
    }

    double DistExponencial::proxima_chegada()
    {
        double rnd;

        if(m_deterministico == true) return (1.0/m_taxa);
        
        drand48_r(&m_estado_prng, &rnd);
        return inversa(rnd);
    }

    void DistExponencial::determistico(bool ativado)
    {
        m_deterministico = ativado;
    }


}
