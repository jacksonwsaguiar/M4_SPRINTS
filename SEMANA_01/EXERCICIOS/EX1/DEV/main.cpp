#include <iostream>
#include <string>

// 1. Implemente a função 'converteSensor' que receberá 3 argumentos: uma medida, um valor mínimo e um valor máximo. A função retornará o valor percentual da medida (0 a 100) em função do intervalo entre os valores mínimo e máximo.
float converteSensor(int measure, int min, int max)
{
	int sub = (max - min);
	float division = (float)measure / (float)sub;

	return division;
}

// 2. Implemente a função 'leituraSensor' que não receberá argumentos. Esta função tem por
// objetivo simular a leitura de sensores (neste caso, sensores de distância).
// A função solicita e retorna um valor inteiro, entre o intervalo de mínimo e máximo (ver item 1),
// digitado pelo usuário (via teclado).
int leituraSensor()
{
	int value;
	while (value < 0 || value > 830)
	{
		printf("Digite um valor entre 0 e 830\n");
		scanf("%d", &value);
	}

	return value;
}

// 3. Implemente a função 'armazenaVetor' que receberá 4 argumentos: o ponteiro do vetor que receberá a medida, o tamanho do vetor, a posição atual para armazenamento e a medida para ser armazenada no vetor. A função deve armazenar a medida no vetor, segundo posição indicada (posição atual) e retornar a próxima posição para armazenamento futuro.
int armazenaValor(int *vetor, int length, int position, int value)
{

	if (position < length)
	{
		vetor[position] = value;
		return position++;
	}
	return 0;
}

// 4. Implemente a função 'direcaoMenorCaminho' que receberá 2 argumentos: (1) o ponteiro para um vetor e (2) o ponteiro
// para uma variável. Esta função deve avaliar 4 valores do vetor, a partir do ponteiro (1) recebido. Os 4 valores representam
// as distâncias nos sentidos: Direta, Esquerda, Frente e Trás (esses valores foram inseridos com a função 'leituraSensor',
// convertidos com a função 'converteSensor' e armazenados no vetor com a função 'armazenaVetor'). Esta função retorna o sentido
// de maior distância, e com base no ponteiro (2) para a variável, nela armazena o valor da maior distância.
char *direcaoMenorCaminho(int *vetor, int *maiorDistancia)
{

	int pos;
	for (int i = 0; i < 4; i++)
	{
		if (&vetor[i] > maiorDistancia)
		{
			*maiorDistancia = vetor[i];
			pos = i;
		}
	}

	if (pos == 0)
	{

		return (char*)"Direita";
	}
	else if (pos == 1)
	{
		return (char*)"Esquerda";
	}
	else if (pos == 2)
	{
		return (char*) "Frente";
	}
	else
	{
		return (char*)"Trás";
	}
}

// 5. Implemente a função 'leComando' que não receberá argumentos. Esta função pergunta ao usuário se ele deseja continuar o mapeamento. A função retorna o inteiro 1 (um) se a resposta for SIM ou 0 (zero) se a resposta for NÃO
bool leComando()
{

	char response;

	printf("Deseja continuar o mapeamento? S (sim) ou N (nao)?\n");
	scanf(" %c", &response);

	return response == 'S' ? true : false;
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um robô
// e através de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada seja
// enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas
int dirige(int *v, int maxv)
{
	int maxVetor = maxv;
	int *vetorMov = v;
	int posAtualVetor = 0;
	bool dirigindo = true;
	while (dirigindo)
	{
		int medida = leituraSensor(); /// .. Chame a função de de leitura da medida para a "Direita"
		medida = converteSensor(medida, 0, 830);
		posAtualVetor = armazenaValor(vetorMov, maxv, posAtualVetor, medida); // Chame a função para armazenar a medida no vetor

		dirigindo = leComando();
	}
	return posAtualVetor;
}

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o movimento
// do robô e no final percorrer o vetor e mostrar o movimento a cada direção baseado
// na maior distância a cada movimento
void percorre(int *v, int tamPercorrido)
{
	int *vetorMov = v;
	int maiorDir = 0;

	for (int i = 0; i < tamPercorrido; i += 4)
	{
		char *direcao = direcaoMenorCaminho(&(vetorMov[i]), &maiorDir);
		printf("Movimentando para %s distancia = %i\n", direcao, maiorDir);
	}
}

int main(int argc, char **argv)
{
	int maxVetor = 100;
	int vetorMov[maxVetor * 4];
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov, maxVetor);
	percorre(vetorMov, posAtualVet);

	return 0;
}