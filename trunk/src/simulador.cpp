#include "simulador.h"

namespace TrabalhoAD
{
    //Operadores necessários para a comparação dos eventos
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



    Simulador::Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico, bool verbose)
    {
        m_tipo_fila1 = fila1;
        m_tipo_fila2 = fila2;

        m_chegada = new DistExponencial(taxa_chegada);
        m_servico = new DistExponencial(taxa_servico);

        m_verbose = verbose;

        setup();
    }


    Simulador::Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico, bool verbose, long int semente_chegada, long int semente_servico)
    {
        m_tipo_fila1 = fila1;
        m_tipo_fila2 = fila2;

        m_chegada = new DistExponencial(taxa_chegada, semente_chegada);
        m_servico = new DistExponencial(taxa_servico, semente_servico);

        m_verbose = verbose;

        setup();
    }

    Simulador::~Simulador()
    {
        delete m_chegada;
        delete m_servico;
    }


    void Simulador::setup()
    {
        while(!m_eventos.empty()) m_eventos.pop();

        m_fila1.clear();
        m_fila2.clear();

        m_tempo_atual = 0.0;

        //Evento inicial do simulador.
        m_eventos.push(Evento(proxima_chegada_no_sistema, m_chegada->proxima_chegada() ) );

        m_prox_id = 0;

        m_servidor_ocupado = false;

        limpa_dados_coletados();
    }

    void Simulador::limpa_dados_coletados()
    {
        m_resultados.quantidade = 0;

        m_resultados.fila1.X = 0.0;
        m_resultados.fila1.X_quad = 0.0;
        m_resultados.fila1.W = 0.0;
        m_resultados.fila1.W_quad = 0.0;
        m_resultados.fila1.T = 0.0;
        m_resultados.fila1.T_quad = 0.0;
        m_resultados.fila1.Nq = 0;
        m_resultados.fila1.Nq_quad = 0;
        m_resultados.fila1.N = 0;
        m_resultados.fila1.N_quad = 0;

        m_resultados.fila2.X = 0.0;
        m_resultados.fila2.X_quad = 0.0;
        m_resultados.fila2.W = 0.0;
        m_resultados.fila2.W_quad = 0.0;
        m_resultados.fila2.T = 0.0;
        m_resultados.fila2.T_quad = 0.0;
        m_resultados.fila2.Nq = 0;
        m_resultados.fila2.Nq_quad = 0;
        m_resultados.fila2.N = 0;
        m_resultados.fila2.N_quad = 0;
    }

    void Simulador::reinicia_simulador()
    {
        setup();
    }

    ResultadosConsolidados Simulador::executa(int quantidade, bool coleta)
    {
        int clientes_servidos = 0;

        //Loop principal do simulador...
        while(clientes_servidos < quantidade)
        {

            //Pega o 1o evento da lista de eventos
            Evento ev = m_eventos.top();
            m_eventos.pop();

            m_tempo_atual = ev.tempo();

            if(ev.tipo() == proxima_chegada_no_sistema) //Chegou um novo cliente ao sistema.
            {
                //Cria um novo Fregues e adiciona na fila 1
                Fregues novoFregues = Fregues(m_prox_id++, m_tempo_atual, m_fila1.size(), m_fila2.size(),
                                 (m_servidor_ocupado == false) ? 0 : m_fregues_em_servico.fila_pertencente());

                if(m_tipo_fila1 == FIFO)
                {
                    m_fila1.push_back(novoFregues);
                }
                else if(m_tipo_fila1 == LIFO)
                {
                    m_fila1.push_front(novoFregues);
                }

                //Programa a próxima chegada
                m_eventos.push(Evento(proxima_chegada_no_sistema, m_tempo_atual + m_chegada->proxima_chegada() ) );
            }
            else if(ev.tipo() == termino_servico) //O cliente em serviço terminou.
            {
                if(m_fregues_em_servico.fila_pertencente() == 1) //Se o fregues veio da Fila1, envia ele para a fila 2.
                {
                    m_fregues_em_servico.terminou_servico1(m_tempo_atual);

                    if(m_tipo_fila2 == FIFO)
                    {
                        m_fila2.push_back(m_fregues_em_servico);
                    }
                    else if(m_tipo_fila2 == LIFO)
                    {
                        m_fila2.push_front(m_fregues_em_servico);
                    }

                }
                else if(m_fregues_em_servico.fila_pertencente() == 2) //Se o fregues veio da Fila2, coleta todos os dados e remove do sistema.
                {
                    m_fregues_em_servico.terminou_servico2(m_tempo_atual);

                    if(coleta) //Devemos coletar os dados do cliente antes de remove-lo do sistema.
                    {
                        m_resultados.quantidade++;

                        //Dados da fila 1
                        m_resultados.fila1.X += m_fregues_em_servico.tempo_servico1();
                        m_resultados.fila1.X_quad += m_fregues_em_servico.tempo_servico1() * m_fregues_em_servico.tempo_servico1();

                        m_resultados.fila1.W += m_fregues_em_servico.tempo_espera1();
                        m_resultados.fila1.W_quad += m_fregues_em_servico.tempo_espera1() * m_fregues_em_servico.tempo_espera1();

                        m_resultados.fila1.T += m_fregues_em_servico.tempo_total1();
                        m_resultados.fila1.T_quad += m_fregues_em_servico.tempo_total1() * m_fregues_em_servico.tempo_total1();

                        m_resultados.fila1.Nq += m_fregues_em_servico.quantidade_elementos_fila1();
                        m_resultados.fila1.Nq_quad += m_fregues_em_servico.quantidade_elementos_fila1() *
                                        m_fregues_em_servico.quantidade_elementos_fila1();

                        m_resultados.fila1.N += m_fregues_em_servico.quantidade_elementos_sistema1();
                        m_resultados.fila1.N_quad += m_fregues_em_servico.quantidade_elementos_sistema1() *
                                        m_fregues_em_servico.quantidade_elementos_sistema1();


                        //Dados da fila 2
                        m_resultados.fila2.X += m_fregues_em_servico.tempo_servico2();
                        m_resultados.fila2.X_quad += m_fregues_em_servico.tempo_servico2() * m_fregues_em_servico.tempo_servico2();

                        m_resultados.fila2.W += m_fregues_em_servico.tempo_espera2();
                        m_resultados.fila2.W_quad += m_fregues_em_servico.tempo_espera2() * m_fregues_em_servico.tempo_espera2();

                        m_resultados.fila2.T += m_fregues_em_servico.tempo_total2();
                        m_resultados.fila2.T_quad += m_fregues_em_servico.tempo_total2() * m_fregues_em_servico.tempo_total2();

                        m_resultados.fila2.Nq += m_fregues_em_servico.quantidade_elementos_fila2();
                        m_resultados.fila2.Nq_quad += m_fregues_em_servico.quantidade_elementos_fila2() *
                                        m_fregues_em_servico.quantidade_elementos_fila2();

                        m_resultados.fila2.N += m_fregues_em_servico.quantidade_elementos_sistema2();
                        m_resultados.fila2.N_quad += m_fregues_em_servico.quantidade_elementos_sistema2() *
                                        m_fregues_em_servico.quantidade_elementos_sistema2();
                    }

                    clientes_servidos++;
                }

                m_servidor_ocupado = false;
            }

            //Se o servidor estiver vazio, verifica se tem algum cliente para ser atendido.
            if(m_servidor_ocupado == false)
            {
                if(!m_fila1.empty()) //Se tiver alguem na fila 1, de maior prioridade para ser atendido.
                {
                    //Move da fila 1 para o servidor.
                    m_fregues_em_servico = m_fila1.front();
                    m_fila1.pop_front();

                    m_fregues_em_servico.saiu_fila1(m_tempo_atual);
                    m_servidor_ocupado = true;

                    //Agenda o evento de conclusão do servico
                    m_eventos.push(Evento(termino_servico, m_tempo_atual + m_servico->proxima_chegada() ) );
                }
                else if(!m_fila2.empty()) //Se a fila 1 estiver vazia, verificamos a fila 2...
                {
                    //Move da fila 2 para o servidor.
                    m_fregues_em_servico = m_fila2.front();
                    m_fila2.pop_front();

                    m_fregues_em_servico.saiu_fila2(m_tempo_atual);
                    m_servidor_ocupado = true;

                    //Agenda o evento de conclusão do servico
                    m_eventos.push(Evento(termino_servico, m_tempo_atual + m_servico->proxima_chegada() ) );
                }
            }


        }

        return m_resultados;
    }

    void Simulador::define_verbose(bool ativado)
    {
        m_verbose = ativado;
    }

    long int Simulador::semente_gerador_tempo_servico(void)
    {
        return m_servico->semente();
    }

    long int Simulador::semente_gerador_chegadas(void)
    {
        return m_chegada->semente();

    }

}
