//bibliotecas
#include <stdio.h>
#include <conio.h>

//macros para el menu
#define NUEVA      	1
#define ANTERIOR		2
#define RECORDS		3
#define AYUDA			4
#define SALIR			5

//macro para los fichero de textos
#define MAX				100

//condicion de error en las funciones
#define ERROR			-1
#define EXITO			1

//macros para el cuadro
#define FILA			26
#define COL          47

//tipo de estructura para el tablero
typedef struct
{
	char tablero[FILA][COL];
   char nombre[MAX];
   int puntos;
   int cont;

}CUADRO;

//declaracion de funciones
int menu(void);
int ayuda(void);

//definicion de ayuda(ayuda para el juego)
int ayuda(void)
{
	//declaracion de variables
	FILE *f;
   char linea[MAX];

   //abrimos el fichero como lectura
   if((f=fopen("ayuda.txt","r"))==NULL)
   {
   	perror("Error ayuda: fopen");
      return(ERROR);
   }

   //lectura por lineas en un fichero de texto
   while((fgets(linea,MAX,f)) != NULL)
   	printf("%s",linea);

   //cerramos el fichero
   if(fclose(f)==EOF)
   {
   	perror("Error ayuda: fclose");
      return(ERROR);
   }

	return(EXITO);

}

//definicion de la funcion menu
int menu(void)
{
	//declaracion de variables
   int opcion;

   //mostramos el menu
   textcolor(LIGHTMAGENTA);
   gotoxy(30,6);
   cprintf(" COMECOCOS ");
   textcolor(YELLOW);
   gotoxy(25,9);
   cprintf("%d.-NUEVA PARTIDA",NUEVA);
   gotoxy(25,11);
   cprintf("%d.-PARTIDA ANTERIOR",ANTERIOR);
   gotoxy(25,13);
   cprintf("%d.-RECORDS",RECORDS);
   gotoxy(25,15);
   cprintf("%d.-AYUDA",AYUDA);
   gotoxy(25,17);
   cprintf("%d.-SALIR",SALIR);

   //recogemos la opcion
	textcolor(LIGHTRED);
   gotoxy(40,19);
	cprintf("Elija una opcion: ");
   scanf("%d%*c",&opcion);
   fflush(stdin);

   return(opcion);
}

