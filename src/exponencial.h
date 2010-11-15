#ifndef EXPONENCIAL_H_
#define EXPONENCIAL_H_

#include <cstdlib>
#include <cmath>
#include <sys/time.h>

namespace TrabalhoAD
    {

    /**
     * A classe DistExponencial representa um gerador pseudo-aleatório
     * de tempos entre chegadas exponencialmente distribuídas.
     *
     * A semente que inicalizou a classe ficará sempre guardada. Desta forma,
     * será possível recupera-la e repetir os testes de forma precisa para verificar
     * o funcionamento do simulador.
     *
     * A geração é feita através da função inversa da PDF da distribuição
     * exponencial.
     *
     * \warning Esta classe não utiliza métodos tradicionais como srand() e rand()
     * para a geração de números pseudo-aleatórios e sim as funções
     * drand48_r() e srand48_r() pois, além delas retornarem um número pseudo-aleatório
     * uniformemente distribuído entre [0.0, 1.0), estas funções são re-entrantes, o que
     * evita problemas no caso do simulador, onde teremos mais de um classe deste tipo gerando
     * tempos de chegada concomitantemente. Estes métodos não estão presentes nativamente no
     * MingW, assim, para compilar o código em ambiente Windows, é necessário ferramentas como
     * o CygWin.
     */
    class DistExponencial
    {
    private:
    long int m_semente; /**< Guarda a semente inicial, importante para garantirmos a uniformidade dos testes */
    struct drand48_data m_estado_prng; /**< Guarda o estado do gerador de números pseudo-aleatórios */
    double m_taxa; /**< Taxa lambda */
    bool m_deterministico; /**< Indica se o gerador deve rodar em modo determinístico ou não. */

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
     * Retorna o tempo até a próxima chegada.
     */
    double proxima_chegada();
    
    /**
     * Ativa ou desativa o modo deterministico.
     */
    void determistico(bool ativado);    
    };

}

#endif //EXPONENCIAL_H_
