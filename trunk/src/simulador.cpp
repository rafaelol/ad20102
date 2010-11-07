#include "simulador.h"

namespace Simulador
{

Simulador::Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico)
{
	m_tipo_fila1 = fila1;
	m_tipo_fila2 = fila2;

	m_chegada = new DistExponencial(taxa_chegada);
	m_servico = new DistExponencial(taxa_servico);

	m_tempo_atual = 0.0;

	//Evento inicial do simulador.
	m_eventos.push(Evento(proxima_chegada_no_sistema, m_chegada->proxima_chegada() ) );
	
	m_prox_id = 0;

	m_fregues_em_servico = NULL;

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

	m_resultados.quantidade = 0;
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


Simulador::Simulador(TipoFila fila1, TipoFila fila2, double taxa_chegada, double taxa_servico, long int semente_chegada, long int semente_servico)
{
	m_tipo_fila1 = fila1;
	m_tipo_fila2 = fila2;

	m_chegada = new DistExponencial(taxa_chegada, semente_chegada);
	m_servico = new DistExponencial(taxa_servico, semente_servico);


	m_tempo_atual = 0.0;

	//Evento inicial do simulador.
	m_eventos.push(Evento(proxima_chegada_no_sistema, m_chegada->proxima_chegada() ) );

	m_prox_id = 0;

	m_fregues_em_servico = NULL;

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

	m_resultados.quantidade = 0;
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

Simulador::~Simulador()
{
	delete m_chegada;
	delete m_servico;
}


ResultadosConsolidados Simulador::executa_com_coleta(int quantidade)
{
	int clientes_servidos = 0;
	Fregues *f;

	//Loop principal do simulador...
	while(clientes_servidos < quantidade)
	{
		
		//Pega o 1o evento da lista de eventos
		Evento ev = m_eventos.top();
		m_eventos.pop();

		m_tempo_atual = ev.tempo();

		if(ev.tipo() == proxima_chegada_no_sistema) //Chegou um novo cliente ao sistema.
		{
			//Cria um novo fregues referente a chegada.
			f = new Fregues(m_prox_id++, m_tempo_atual, m_fila1.size(), m_fila2.size(),
					(m_fregues_em_servico == NULL) ? 0 : m_fregues_em_servico->fila_pertencente());

			//Adiciona o fregues na fila 1

			//Programa a próxima chegada
			m_eventos.push(Evento(proxima_chegada_no_sistema, m_tempo_atual + m_chegada->proxima_chegada() ) );
		}
		else if(ev.tipo() == termino_servico) //O cliente em serviço terminou.
		{
			f = m_fregues_em_servico;

			//Se o fregues veio da Fila1, envia ele para a fila 2.

			//Se o fregues veio da Fila2, coleta todos os dados e remove do sistema.

			m_fregues_em_servico = f = NULL;
		}

		//Se o servidor estiver vazio, verifica se tem algum cliente para ser atendido.
		if(m_fregues_em_servico == NULL)
		{
			if(!m_fila1.empty()) //Se tiver alguem na fila 1, de maior prioridade para ser atendido.
			{
				//Move da fila 1 para o servidor.

				//Agenda o evento de conclusão do servico
				m_eventos.push(Evento(termino_servico, m_tempo_atual + m_servico->proxima_chegada() ) );
			}
			else if(!m_fila2.empty()) //Se a fila 1 estiver vazia, verificamos a fila 2...
			{
				//Move da fila 2 para o servidor.
				
				//Agenda o evento de conclusão do servico
				m_eventos.push(Evento(termino_servico, m_tempo_atual + m_servico->proxima_chegada() ) );
			}
		}


	}




	return m_resultados;

}








}
