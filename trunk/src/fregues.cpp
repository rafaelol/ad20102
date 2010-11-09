#include "fregues.h"

namespace TrabalhoAD {

Fregues::Fregues()
{
	m_id = 0;
	m_fila = 0;

	m_tempo_chegada_fila1 = 0.0;
	m_tempo_saida_fila1 = 0.0;
	m_tempo_chegada_fila2 = 0.0;
	m_tempo_saida_fila2 = 0.0;
	m_tempo_saida_sistema = 0.0;

	m_quantidade_fila1 = 0;
	m_quantidade_fila2 = 0;

	m_tipo_cliente_servido = 0;
}

Fregues::Fregues(int id, double tempo_chegada, int quantidade_fila1, int quantidade_fila2, int tipo_cliente_servido)
{
	m_id = id;
	m_fila = 1;

	m_tempo_chegada_fila1 = tempo_chegada;
	m_tempo_saida_fila1 = 0.0;
	m_tempo_chegada_fila2 = 0.0;
	m_tempo_saida_fila2 = 0.0;
	m_tempo_saida_sistema = 0.0;

	m_quantidade_fila1 = quantidade_fila1;
	m_quantidade_fila2 = quantidade_fila2;

	m_tipo_cliente_servido = tipo_cliente_servido;
}

void Fregues::saiu_fila1(double tempo)
{
	m_tempo_saida_fila1 = tempo;
}

void Fregues::terminou_servico1(double tempo)
{
	m_tempo_chegada_fila2 = tempo;
	m_fila = 2;
}

void Fregues::saiu_fila2(double tempo)
{
	m_tempo_saida_fila2 = tempo;
}

void Fregues::terminou_servico2(double tempo)
{
	m_tempo_saida_sistema = tempo;
}

double Fregues::tempo_espera1()
{
	return m_tempo_saida_fila1 - m_tempo_chegada_fila1;
}

double Fregues::tempo_servico1()
{
	return m_tempo_chegada_fila2 - m_tempo_saida_fila1;
}

double Fregues::tempo_espera2()
{
	return m_tempo_saida_fila2 - m_tempo_chegada_fila2;
}

double Fregues::tempo_servico2()
{
	return m_tempo_saida_sistema - m_tempo_saida_fila2;
}

double Fregues::tempo_total1()
{
	return tempo_espera1() + tempo_servico1();
}

double Fregues::tempo_total2()
{
	return tempo_espera2() + tempo_servico2();
}

int Fregues::quantidade_elementos_fila1()
{
	return m_quantidade_fila1;
}

int Fregues::quantidade_elementos_fila2()
{
	return m_quantidade_fila2;
}

int Fregues::quantidade_elementos_sistema1()
{
	return quantidade_elementos_fila1() + ((m_tipo_cliente_servido == 1) ? 1 : 0);
}

int Fregues::quantidade_elementos_sistema2()
{
	return quantidade_elementos_fila2() + ((m_tipo_cliente_servido == 2) ? 1 : 0);
}

int Fregues::tipo_cliente_servido()
{
	return m_tipo_cliente_servido;
}

int Fregues::fila_pertencente()
{
	return m_fila;
}

void Fregues::print()
{
	printf("*************************\n");

	printf("Dados do Fregues %d\n", m_id);
	printf("X1 = %f\n", tempo_servico1());
	printf("W1 = %f\n", tempo_espera1());
	printf("T1 = %f\n", tempo_total1());
	printf("Nq1 = %d\n", quantidade_elementos_fila1());
	printf("N1 = %d\n", quantidade_elementos_sistema1());

	printf("X2 = %f\n", tempo_servico2());
	printf("W2 = %f\n", tempo_espera2());
	printf("T2 = %f\n", tempo_total2());
	printf("Nq2 = %d\n", quantidade_elementos_fila2());
	printf("N2 = %d\n", quantidade_elementos_sistema2());

	printf("*************************\n\n");
}

}

