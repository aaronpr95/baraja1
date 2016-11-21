/* prototipos de las funciones de las pilas vectoriales */

int pila_vacia(int);
int pila_llena(int, int);
void apilar(int *cima,CARTA pila[], CARTA micarta, int n);
int desapilado(CARTA *micarta, int *cima, CARTA pila[]);
int valor_cima(CARTA *micarta, int cima, CARTA pila[]);