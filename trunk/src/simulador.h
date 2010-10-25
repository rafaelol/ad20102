#ifndef SIMULADOR_H_
#define SIMULADOR_H_

#include<vector>
#include<queue>

#include "fregues.h"
#include "exponencial.h"
#include "eventos.h"

using namespace std;


namespace Simulador
{

/**
 * TipoFila indica qual o tipo da fila, FIFO/FCFS ou LIFO/LCFS
 */
enum TipoFila {FIFO, LIFO};

/**
 * TipoSimulação indical qual o tipo da simulação a ser executada,
 *  Batch (1 fase transiente + n rodadas) ou 
 *  Replicativo (n * (fase transiente + rodada)).
 */
enum TipoSimulacao {BATCH, REPLICATIVO};

/**
 * A classe Simulador é a responsável por executar a simulação propriamente,
 * coletar e armazenar os resultados de cada rodada e apresentar o resultado
 * da simulação.
 *
 */
class Simulador
{
private:
priority_queue<Evento, vector<Evento>, greater<Evento> > m_eventos;

queue<Fregues> m_fila1;
queue<Fregues> m_fila2;

TipoFila m_tipo_fila1;
TipoFila m_tipo_fila2;

public:




};










}

#endif //SIMULADOR_H_

