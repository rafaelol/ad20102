#ifndef EXPONENCIAL_H_
#define EXPONENCIAL_H_

#include <cstdlib>
#include <cmath>
#include <sys/time.h>

namespace TrabalhoAD
    {

    /**
     * A classe DistExponencial representa um gerador pseudo-aleatório
     * de tempos entre chegadas exponencialmente distribuídos.
     *
     * A semente que inicalizou a classe ficará sempre guardada, desta forma
     * será possível recupera-la e repetir os testes de forma precisa para verificar
     * o funcionamento do simulador.
     *
     * O método de geração é através da função inversa a PDF da distribuição
     * exponencial.
     *
     * \warning Esta classe não utiliza o método tradicional com srand() e rand()
     * para a geração de números pseudo-aleatórios, mas utiliza as funções
     * drand48_r() e srand48_r(), pois além delas retornarem um número pseudo-aleatório
     * uniformemente distribuído entre [0.0, 1.0), estas funções são re-entrantes o que
     * evita problemas no caso do simulador onde teremos mais de um classe deste tipo gerando
     * tempos de chegada.
     */
    class DistExponencial
    {
    private:
    long int m_semente; /**< Guarda a semente inicial, importante para podermos repetir os testes de forma garantida */
    struct drand48_data m_estado_prng; /**< Guarda o estado do gerador de números pseudo-aleatórios */
    double m_taxa; /**< Taxa lambda */

    /**
     * Reversa da função exponencial.
     *
     * \param prob Probabilidade [0.0, 1.0)
     */
    double inversa(double prob);

    public:
    /**
     * Construtor da classe DistExponencial.
     * Este construtor irá inicializar o gerador de números pseudo-aleatórios com o valor de gettimeofday().
     *
     * \param taxa Taxa lambda da distribuição exponencial.
     */
    DistExponencial(double taxa);

    /**
     * Construtor da classe DistExponencial.
     *
     * \param taxa Taxa lambda da distribuição exponencial.
     * \param semente Semente inicial do gerador.
     */
    DistExponencial(double taxa, long int semente);

    /**
     * Retorna a semente inicial do gerador acoplado a esta distribuição exponencial
     */
    long int semente() const;

    /**
     * Retorna o tempo até a próxima chegada
     */
    double proxima_chegada();
    };

}

#endif //EXPONENCIAL_H_
