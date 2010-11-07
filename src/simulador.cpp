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



	return m_resultados;

}








}
