/* 	
	Ejercicio de la Baraja 
	Aarón Portales Rodrigo - 2016 */

/* BIBLIOTECAS Y VARIABLES GLOBALES */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipo_carta.h"
#include "prototipos_pilavectorial.h"


#define VERDADERO 1
#define FALSO 0



/* PROTOTIPOS */
void definirBaraja(CARTA *baraja);
void impimirCarta(CARTA micarta);
CARTA * barajar(CARTA *baraja);
void impimirBaraja(CARTA *baraja);
void repartir(CARTA *baraja, CARTA pila1[], CARTA pila2[], int *cima1, int *cima2);
int juego(CARTA pila1[], int *cima1, CARTA pila2[], int *cima2, CARTA pilamesa[], int *cimamesa);
void apilar_baraja(CARTA ori[],int *cimao, CARTA des[], int *cimad);
int turnos(int tur);


void main()
{
	/* declaramos la semilla para el rand */
	srand((unsigned) time(NULL));
	CARTA baraja[40];
	CARTA *barajado;
	barajado = (CARTA *)calloc(40,sizeof(CARTA));
	
	CARTA pila1[40];
	int cima1 = 0;
	CARTA pila2[40];
	int cima2 = 0;
	CARTA pilamesa[40];
	int cimamesa = 0;

	definirBaraja(baraja);
	//impimirBaraja(baraja);
	barajado = barajar(baraja);
	//impimirBaraja(barajado);

	repartir(barajado, pila1, pila2, &cima1, &cima2);
	/* Aqui tenemos las dos barajas de los jugadores */


	if(juego(pila1, &cima1, pila2, &cima2, pilamesa, &cimamesa) == 1)
		printf("El JUGADOR_1 se ha quedado sin cartas, gana la partida\n");
	else
		printf("El JUGADOR_2 se ha quedado sin cartas, gana la partida\n");


}

/* si devuelve 1 gana j1 si 2 j2 */
int juego(CARTA pila1[], int *cima1, CARTA pila2[], int *cima2, CARTA pilamesa[], int *cimamesa)
{
	CARTA micarta;
	int turno=0; // =0 j1; =1 j2
	int cante=1;

	for(;;)
	{
		if (turno == 0)
		{
			desapilado(&micarta, cima1, pila1);
			printf("Jugador_1 canta %d: \n", cante);
			impimirCarta(micarta);

		}
		else 
		{
			desapilado(&micarta, cima2, pila2);
			printf("Jugador_2 canta %d: \n", cante);
			impimirCarta(micarta);
		}

		apilar(cimamesa, pilamesa, micarta, 40);

		/* comprobamos la carta con el cante */
		if (micarta.num == cante)
		{	
			if (turno == 0)
			{
				apilar_baraja(pilamesa, cimamesa, pila1, cima1);
				printf("CANTEE!, el Jugador_1 se recoge el monton de la mesa\n---------------------------------\n");
			}
			else
			{
				apilar_baraja(pilamesa, cimamesa, pila2, cima2);
				printf("CANTEE!, el Jugador_2 se recoge el monton de la mesa\n---------------------------------\n");
			}

			cante = 1;
		}
		else/* Si la carta que se saca no coincide con la que se canta */
		{
			if (cante < 7) cante++;
			else if (cante == 12) cante = 1;
			else if (cante == 7) cante += 3;
			else cante++;
		}

		/* Comprobamos si algun jugador se ha quedado sin cartas */
		if (pila_vacia(*cima1) == 1)	return 1;
		if (pila_vacia(*cima2) == 1)	return 2;

		/* Cambiamos el turno */
		turno = turnos(turno);
	}

}

void apilar_baraja(CARTA ori[],int *cimao, CARTA des[], int *cimad)
{
	int i;
	int cim = *cimao;
	CARTA aux;

	for(i=0;i<cim;i++)
	{
		desapilado(&aux, cimao, ori);
		apilar(cimad, des, aux, 40);
		//impimirCarta(aux);
	}
}

int turnos(int tur)
{	
	if (tur == 0) return 1;
	else return 0;
	
}

void repartir(CARTA *baraja, CARTA pila1[], CARTA pila2[], int *cima1, int *cima2)
{
	int i;
	CARTA micarta;
	for(i=0;i<20;i++)
	{	
		micarta.palo = baraja[i].palo;
		micarta.num = baraja[i].num;
		//impimirCarta(micarta);
		apilar(cima1, pila1, micarta, 40);
	}

	for(i=20;i<40;i++)
	{	
		micarta.palo = baraja[i].palo;
		micarta.num = baraja[i].num;
		//impimirCarta(micarta);
		apilar(cima2, pila2, micarta, 40);
	}
}

/* Define el palo y el numero */
void definirBaraja(CARTA *baraja)
{
	int i, j, contador=0;

	/* definimos cada palo del uno al 10 */
	for (i = 1; i < 5; ++i)
	{
		for (j = 1; j<11; j++)
		{
			baraja[contador].palo = i;

			if(j <= 7)
				baraja[contador].num = j;
			else
				baraja[contador].num = j+2;
			
			contador++; // sería la posicion del vector donde guardamos las cartas
			
		}
	}
}

CARTA * barajar(CARTA *baraja)
{
	int libre[40]; // vector auxiliar para comprobar las posiciones si estan libres
	CARTA *aux; // baraja auxiliar
	aux = (CARTA *)calloc(40,sizeof(CARTA));
	int i, pos;

	// iniciamos el vector auxiliar a cero que sera libre
	for(i=0;i<40;i++)
	{
		libre[i]=0;// 0 libre
	}

	for(i=0;i<40;i++)
	{
		pos=rand()%40;
		/* Comprobamos que la posicion elegida es libre y sino buscamos una libre hasta
		que la encuentre	 */
		while(libre[pos] == 1)
		{
			pos=rand()%40;
		}

		/* Guardamos los campos de la baraja inicial en la auxiliar desordenada */ 
		aux[pos].palo = baraja[i].palo;
		aux[pos].num = baraja[i].num;

		libre[pos]=1; // marcamos la posicion como ocupada
	}
	return aux;
}

void impimirCarta(CARTA micarta)
{
	printf("NUMERO: %d\n", micarta.num);

	if ( micarta.palo == 1) printf("PALO: Oros\n");
	else if ( micarta.palo == 2) printf("PALO: Copas\n");	
	else if ( micarta.palo == 3) printf("PALO: Espadas\n");
	else printf("PALO: Bastos\n");
	printf("\n");
}

void impimirBaraja(CARTA *baraja)
{
	int i;
	for(i=0;i<40;i++) impimirCarta(baraja[i]);
}

