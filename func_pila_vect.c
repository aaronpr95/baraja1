/* Funciones de una pila vectorial */

#include <stdio.h>
#include "tipo_carta.h"
#include "prototipos_pilavectorial.h"

#define tam 100


int pila_vacia(int cima)
{
	if(cima==0)
	{
		return 1;//pila vacia
	}
	else
	{
		return 0;//pila no vacia
	}
}

int pila_llena(int cima,int n)//en n hay que pasarle tam
{
	if(cima == n)
	{
		return 1;//pila llena
	}else{
		return 0;//pila no llena
	}
}

void apilar(int *cima,CARTA pila[], CARTA micarta, int n)//en n hay que pasarle tam
{
	if(pila_llena(*cima,n)==1)
	{
		printf("\nPila llena, no se puede apilar\n");
	}else{
		/*
		pila[*cima]=elemento;//posible error
		//he apilado el dato en la posicion cima, pila(*cima), *cima
		*cima=*cima+1; */

		pila[*cima].palo = micarta.palo;
		pila[*cima].num = micarta.num;

		*cima=*cima+1;

	}
}

int desapilado(CARTA *micarta, int *cima, CARTA pila[])
{
	if(pila_vacia(*cima)==0)
	{
		micarta->palo = pila[*cima-1].palo;
		micarta->num = pila[*cima-1].num;
		//(*micarta).palo = pila[*cima].palo;
		//(*micarta).num = pila[*cima].num;
		*cima=*cima - 1;
		
		return 1;	
	}else{
		printf("\nPila vacia, no se puede desapilar\n");
		return 0;
	}
}

int valor_cima(CARTA *micarta, int cima, CARTA pila[])
{
	if(pila_vacia(cima)==0)
	{

		micarta->palo = pila[cima-1].palo;
		micarta->num = pila[cima-1].num;
		//*elemento=pila[cima];
		return 1;
	}else{
		printf("\npila vacia\n");
		return 0;
	}
}