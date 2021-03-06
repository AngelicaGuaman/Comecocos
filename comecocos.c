//bibliotecas
#include <stdio.h>
#include <conio.h>
//#include <dos.h>     //para el sleep
#include "funciones.h"
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

//macros para el menu
#define NUEVA      	1
#define ANTERIOR		2
#define RECORDS		3
#define AYUDA			4
#define SALIR			5

//macros para el cuadro
#define FILA			26
#define COL          47
#define MOVER			3

#define MAX_PUNTOS	800

//macro para los fichero de textos
#define MAX				100

//Macros para el movimiento del fantasma
#define MAX_FAN	4

//macros para el movimiento del pacman
#define ARRIBA			'W'
#define ABAJO			'S'
#define IZQUIERDA		'A'
#define DERECHA		'D'
#define SALIR1			'Q'
#define SI           'Y'
#define NO				'N'

//estado del tablero
#define OCUPADA		'0'
#define LIBRE			'.'
#define VACIA			'1'
#define PACMAN			'P'
#define COMIDO			' '
#define FANTASMA		'F'
#define DIAMANTES		'D'

#define PUNTOS			100

//condicion de error en las funciones
#define ERROR			-1
#define EXITO			1

//declaracion de funciones
void mostrarTableroInicial(CUADRO *cuadro, int x, int y, int a, int b);
void mostrarTablero(CUADRO cuadro,int x,int y,int a, int b);
void iniciarTablero(CUADRO *cuadro);
int nueva(CUADRO cuadro);
int anterior(CUADRO cuadro);
int mover(CUADRO * cuadro,int *i, int* j,int *cont);
int mover_fantasmas(CUADRO *cuadro,int *a , int *b);
int jugar(CUADRO * cuadro, int*x, int *y, int * cont,int *a, int *b);
int records(CUADRO * cuadro, int puntaje);
int lectura_records(void);

//tipo de estructura para la posicion para el fantasma


//funcion principal
void main()
{
   int opcion;
   CUADRO cuadro;
   int cont; //contador para el puntaje
   int x,y; //posicion del pacman
   int a,b;//posicion del fantasma

   do
   {
   	clrscr();
      opcion=menu();

      randomize();

      switch(opcion)
      {
      	case NUEVA:
         	clrscr();
            x=17;
            y=23;
            a=15;
            b=21;
            cont=1;
				mostrarTableroInicial(&cuadro,x,y,a,b);
            gotoxy(49,4);
   			cprintf("Pulse Q para salir");

            if(jugar(&cuadro,&x,&y,&cont,&a,&b)==ERROR)
            	printf("Error al jugar la partida");

            break;

         case ANTERIOR:
         	clrscr();
            gotoxy(49,4);
   			cprintf("Pulse Q para salir");
            if(anterior(cuadro)== ERROR)
            	printf("No hay partida guardada");
            else
            {
            	if(jugar(&cuadro,&x,&y,&cont,&a,&b)==ERROR)
            		printf("Error al jugar la partida");
            }

            break;

         case RECORDS:
         	clrscr();
            if(lectura_records()== ERROR)
            	printf("No existe el fichero");

         	break;

         case AYUDA:
         	clrscr();
            if(ayuda()!= EXITO)
            	perror("Error main: AYUDA");

         	break;

      	case SALIR:
         	textcolor(LIGHTRED);
            gotoxy(30,28);
            cprintf("FinalizaciOn correcta del programa...");

            break;

         default:
         	textcolor(LIGHTRED);
         	gotoxy(30,26);                                          
            cprintf("OpciOn incorrecta...");

            break;
      }
      getch();
   }while(opcion != SALIR);

}

//movimiento de los fantasmas
int mover_fantasmas(CUADRO *cuadro,int *a, int *b)
{
   int aleatorio;


   aleatorio=random(MAX_FAN);

   switch(aleatorio)
   {
   	case 0: //arriba   *j=*j-1;
         if((cuadro->tablero[*a-1][*b]!= OCUPADA))
	        	*a=*a-1;
         else if((cuadro->tablero[*a+1][*b]!= OCUPADA))
         {
         	aleatorio=1;
         }
         else if ((cuadro->tablero[*a][*b-1]!= OCUPADA))
         	aleatorio=2;
         else if((cuadro->tablero[*a][*b+1]!= OCUPADA))
              aleatorio=3;
         break;

     case 1:
      	if((cuadro->tablero[*a+1][*b]!= OCUPADA))
	        	*a=*a+1;

      	break;

     case 2:
      	if((cuadro->tablero[*a][*b-1]!= OCUPADA))
	        	*b=*b-1;


         break;
     case 3:
      	if((cuadro->tablero[*a][*b+1]!= OCUPADA))
	        	*b=*b+1;
         else
         {
         	randomize();
   			aleatorio=random(MOVER);
         }

         break;
      }


	return(EXITO);
}


int jugar(CUADRO * cuadro, int*x, int *y, int *cont,int *a, int *b)
{
	int res,record;
   int fan;

	do
   {
   	res=mover(&(*cuadro),&(*x),&(*y),&(*cont));

      fan=mover_fantasmas(&(*cuadro),&(*a),&(*b));

      if(fan==EXITO)
      	mover_fantasmas(&(*cuadro),&(*a),&(*b));

      mostrarTablero(*cuadro,*x,*y,*a,*b);

      gotoxy(49,2);
      cprintf("%d X %d",*cont,PUNTOS);

   }while(res==EXITO);

   /*
   do
   	{
   		for(i=0;i<=3;i++)
   			fan=(mover_fantasmas(&cuadro,&fantasma,i));

   	}while (fan==EXITO);
      */


   //cuadro.cont=cont;
   record=(*cont*PUNTOS);

   if((record > MAX_PUNTOS))
   {
   	records(&(*cuadro),record);
   }


   return(EXITO);
}

void mostrarTablero(CUADRO cuadro,int x, int y,int a, int b)
{
	int i,j;

   //comprobacion si esta ocupada o libre
   for(i=1;i<=FILA;i++)
   	for(j=1;j<=COL;j++)
      {
   		if(cuadro.tablero[i-1][j-1] == LIBRE)
   		{
         	textcolor(YELLOW);
         	gotoxy(j,i);
            cprintf("%c",LIBRE);
   		}
         else if(cuadro.tablero[i-1][j-1] == OCUPADA)
         {
         	textcolor(LIGHTBLUE);
         	gotoxy(j,i);
		      cprintf("%c",219);
		   }
         else if(cuadro.tablero[i-1][j-1] == VACIA)
         {
         	gotoxy(j,i);
            cprintf(" ");
         }
         else if(cuadro.tablero[i-1][j-1] == COMIDO)
         {
         	gotoxy(j,i);
            cprintf("%c",COMIDO);
         }
         else if(cuadro.tablero[i-1][j-1] == DIAMANTES)
         {
         	textcolor(LIGHTMAGENTA);
         	gotoxy(j,i);
            cprintf("%c",248);
         }


      }


   //posicion de los fantasma
   textcolor(GREEN);
   gotoxy(b+1,a+1);
   cprintf("%c",1);

   //posicion del pacman
	textcolor(LIGHTRED);
  	gotoxy(y+1,x+1);
  	cprintf("%c",2);


}

int mover(CUADRO * cuadro,int* i, int* j,int *cont)
{
   char letra = (char)toupper(getch());
   char opcion;


   switch(letra)
   {
   	case ARRIBA:
      	if((cuadro->tablero[*i-1][*j]==LIBRE) || (cuadro->tablero[*i-1][*j]==COMIDO)|| (cuadro->tablero[*i-1][*j]== DIAMANTES))
         {
				if(cuadro->tablero [*i][*j]==LIBRE)
            		(*cont)++;
         	cuadro->tablero [*i][*j]=COMIDO;
      		*i=*i-1;
         }
      	break;

      case ABAJO:
      	if((cuadro->tablero[*i+1][*j]==LIBRE) || (cuadro->tablero[*i+1][*j]==COMIDO)|| (cuadro->tablero[*i+1][*j]== DIAMANTES))
         {
				if(cuadro->tablero [*i][*j]==LIBRE)
            		(*cont)++;
         	cuadro->tablero [*i][*j]=COMIDO;
      		*i=*i+1;
         }
         break;

      case IZQUIERDA:
      	if((cuadro->tablero[*i][*j-1]==LIBRE) || (cuadro->tablero[*i][*j-1]==COMIDO)|| (cuadro->tablero[*i][*j-1]== DIAMANTES))
         {
				if(cuadro->tablero [*i][*j]==LIBRE)
            		(*cont)++;
         	cuadro->tablero [*i][*j]=COMIDO;
      		*j=*j-1;
         }
         break;

      case DERECHA:
      	if((cuadro->tablero[*i][*j+1]==LIBRE)|| (cuadro->tablero[*i][*j+1]==COMIDO)|| (cuadro->tablero[*i][*j+1]== DIAMANTES))
         {
				if(cuadro->tablero [*i][*j]==LIBRE)
            		(*cont)++;
         	cuadro->tablero [*i][*j]=COMIDO;
      		*j=*j+1;
         }

         break;
      case SALIR1:
      	clrscr();
      	gotoxy(48,4);
         cprintf("Desea guardar la partida(Y/N): ");
         scanf("%c%*c",&opcion);
         opcion=(char)toupper(opcion);

         switch(opcion)
         {
         	case SI:
            	if(nueva(*cuadro)!= EXITO)
            		perror("Error mover: NUEVA");
               else
               	printf("Error al escribir en el fichero");

               gotoxy(48,5);
               cprintf("Partida guardada");
      			return(ERROR);
            case NO:
               gotoxy(48,6);
            	cprintf("No guardas los cambios");
            	return(ERROR);
            default:
            	gotoxy(48,7);
            	cprintf("Opcion incorrecta");

         }

         return(ERROR);
   }

   return EXITO;
}

int anterior(CUADRO cuadro)
{
	//declaracion de variables
	FILE *f;
   int i,j;

   //abrimos el fichero como lectura
   if((f=fopen("comecocos.dat","r"))==NULL)
   {
   	perror("Error anterior: fopen");
      return(ERROR);
   }

   //hacemos una lectura por bloques recorriendo los indices
   //del array para q muestre los diferentes estados del tablero
   while(fread(&cuadro, sizeof(CUADRO),1,f)==1)
   {
      for(i=1;i<=FILA;i++)
      	for(j=1;j<=COL;j++)
         {
         	if(cuadro.tablero[i-1][j-1]==OCUPADA)
            {
            	textcolor(LIGHTBLUE);
            	gotoxy(j,i);
            	cprintf("%c",219);
            }
            else if(cuadro.tablero[i-1][j-1] == LIBRE)
            {
            	textcolor(YELLOW);
            	gotoxy(j,i);
            	cprintf("%c",LIBRE);
            }
            else if(cuadro.tablero[i-1][j-1] == COMIDO)
            {
            	gotoxy(j,i);
            	cprintf("%c",COMIDO);
            }
            else if(cuadro.tablero[i-1][j-1] == VACIA)
            {
            	gotoxy(j,i);
            	cprintf(" ");
            }
            else if(cuadro.tablero[i-1][j-1] == DIAMANTES)
            {
            	textcolor(LIGHTMAGENTA);
            	gotoxy(j,i);
            	cprintf("%c",248);
            }
         }
   }

   //cerramos el fichero
   if(fclose(f)==EOF)
   {
   	perror("Error anterior: fclose");
      return(ERROR);
   }

	return(EXITO);

}

//mostramos el tablero Inicial
void mostrarTableroInicial(CUADRO  *cuadro, int x, int y,int a , int b)
{
	int i,j;  //i FILA y j COL

   clrscr();

   iniciarTablero(&(*cuadro));//iniciamos el tablero

   textcolor(LIGHTBLUE);

	//primera linea
  	for(i=1,j=1;j<=COL;j++)
   {
   	gotoxy(j,i);
     	cuadro->tablero[i-1][j-1]=OCUPADA;
     	cprintf("%c",220); //abajo
   }

   //linea izquierda del cuadro
   for(i=2,j=1;i<=FILA;i++)
   {
   	gotoxy(j,i);
     	cuadro->tablero[i-1][j-1]=OCUPADA;
     	cprintf("%c",219); //arriba
   }

   //linea derecha del cuadro
   for(j=COL,i=2;i<=FILA;i++)
   {
   	gotoxy(j,i);//primero se pone columna fila
   	cprintf("%c",219);//arriba
      cuadro->tablero[i-1][j-1]=OCUPADA;
   }

   //ultima linea
   for(i=FILA,j=2;j<COL;j++)
   {
   	gotoxy(j,i);
     	cuadro->tablero[i-1][j-1]=OCUPADA;
     	cprintf("%c",220); //abajo
   }

   //barras interiores
   for(i=3;i<=4;i++)
   	for(j=3;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=4;i++)
   	for(j=8;j<=12;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=5;i++)
   	for(j=14;j<=18;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=2;i<=5;i++)
   	for(j=23;j<=25;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=5;i++)
   	for(j=20;j<=21;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=5;i++)
   	for(j=27;j<=28;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=5;i++)
   	for(j=30;j<=34;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=4;i++)
   	for(j=36;j<=40;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=3;i<=4;i++)
   	for(j=42;j<=45;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=3;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=8;j<=12;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=14;j<=15;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=7;i<=14;i++)
   	for(j=17;j<=18;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=11;i++)
   	for(j=2;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   //declaramos las " "
   for(i=12;i<=13;i++)
   	for(j=2;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=VACIA;
         cprintf(" ");
      }

   for(i=14;i<=16;i++)
   	for(j=2;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=18;i<=19;i++)
   	for(j=3;j<=9;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=21;i<=24;i++)
   	for(j=3;j<=6;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=14;i<=17;i++)
   	for(j=8;j<=9;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=12;i++)
   	for(j=8;j<=9;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=8;j<=12;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=8;i<=10;i++)
   	for(j=11;j<=12;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=15;i++)
   	for(j=14;j<=15;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=12;i<=13;i++)
   	for(j=11;j<=13;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=7;i<=8;i++)
   	for(j=20;j<=28;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=10;i<=11;i++)
   	for(j=19;j<=21;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=7;i<=14;i++)
   	for(j=30;j<=31;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=10;i<=11;i++)
   	for(j=27;j<=29;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=15;i<=20;i++)
   	for(j=11;j<=12;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=33;j<=34;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=10;i++)
   	for(j=36;j<=37;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=38;j<=40;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=6;i<=7;i++)
   	for(j=42;j<=45;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=15;i++)
   	for(j=33;j<=34;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=11;i++)
   	for(j=42;j<=46;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=14;i<=16;i++)
   	for(j=42;j<=46;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=22;i<=26;i++)
   	for(j=23;j<=25;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=12;i<=13;i++)
   	for(j=35;j<=37;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=12;i++)
   	for(j=39;j<=40;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=15;i<=20;i++)
   	for(j=36;j<=37;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=14;i<=19;i++)
   	for(j=39;j<=40;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=17;i<=18;i++)
   	for(j=33;j<=35;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=18;i<=19;i++)
   	for(j=41;j<=45;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=17;i<=18;i++)
   	for(j=13;j<=15;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=21;i<=24;i++)
   	for(j=8;j<=9;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=22;i<=24;i++)
   	for(j=11;j<=15;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=20;i<=21;i++)
   	for(j=14;j<=15;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=17;i<=20;i++)
   	for(j=17;j<=18;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=22;i<=24;i++)
   	for(j=17;j<=21;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=19;i<=20;i++)
   	for(j=20;j<=28;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	for(i=17;i<=20;i++)
   	for(j=30;j<=31;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=22;i<=24;i++)
   	for(j=27;j<=31;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=22;i<=24;i++)
   	for(j=33;j<=37;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=20;i<=21;i++)
   	for(j=33;j<=34;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=21;i<=24;i++)
   	for(j=39;j<=40;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=21;i<=24;i++)
   	for(j=42;j<=45;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

   for(i=9;i<=10;i++)
   	for(j=23;j<=25;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=OCUPADA;
         cprintf("%c",219);
      }

	//declaramos las " "
   for(i=12;i<=13;i++)
   	for(j=42;j<=46;j++)
      {
      	gotoxy(j,i);
         cuadro->tablero[i-1][j-1]=VACIA;
         cprintf(" ");
      }

   for(i=15,j=20;i<=17;i++)
   {
		gotoxy(j,i);
      cuadro->tablero[i-1][j-1]=OCUPADA;
      cprintf("%c",219);
   }

   for(i=15,j=28;i<=17;i++)
   {
		gotoxy(j,i);
      cuadro->tablero[i-1][j-1]=OCUPADA;
      cprintf("%c",219);
   }

   for(i=14,j=27;j<=28;j++)
   {
		gotoxy(j,i);
      cuadro->tablero[i-1][j-1]=OCUPADA;
      cprintf("%c",219);
   }

   for(i=17,j=21;j<=27;j++)
   {
		gotoxy(j,i);
      cuadro->tablero[i-1][j-1]=OCUPADA;
      cprintf("%c",219);
   }

   for(i=14,j=20;j<=21;j++)
   {
		gotoxy(j,i);
      cuadro->tablero[i-1][j-1]=OCUPADA;
      cprintf("%c",219);
   }

   //posicion de los fantasmas
   /*for(j=0;j<=3;j++)
   {
   	fantasma[j].x = 16;
      fantasma[j].y = j+22;
      cuadro->tablero [(fantasma[j].x)-1][(fantasma[j].y)-1] =FANTASMA;
      gotoxy((fantasma[j].y),(fantasma[j].x));
      textcolor(GREEN);
      cprintf("%c",1);
   } */


   textcolor(GREEN);
   gotoxy(b+1,a+1);
   cuadro->tablero[a][b]=FANTASMA;
   cprintf("%c",1);

   //posicion de los diamantes
   textcolor(LIGHTMAGENTA);
   gotoxy(2,2);
   cuadro->tablero[2-1][2-1]= DIAMANTES;
   cprintf("%c",248);

   textcolor(LIGHTMAGENTA);
   gotoxy(46,2);
   cuadro->tablero[2-1][46-1]= DIAMANTES;
   cprintf("%c",248);

   textcolor(LIGHTMAGENTA);
   gotoxy(2,25);
   cuadro->tablero[25-1][2-1]= DIAMANTES;
   cprintf("%c",248);

   textcolor(LIGHTMAGENTA);
   gotoxy(46,25);
   cuadro->tablero[25-1][46-1]= DIAMANTES;
   cprintf("%c",248);

	for(i=14;i<=16;i++)
   	for(j=21;j<=27;j++)
      {
      	if((cuadro->tablero[i-1][j-1]!=OCUPADA) && (cuadro->tablero[i-1][j-1]!=FANTASMA))
         {
         	gotoxy(j,i);
            cuadro->tablero[i-1][j-1]=VACIA;
            cprintf(" ");
         }
      }

   //bucle para se pueda mover el pacman por COMIDO
   for(i=10;i<=17;i++)
   	for(j=17;j<=31;j++)
      {
      	if((cuadro->tablero[i-1][j-1]!=OCUPADA)&& (cuadro->tablero[i-1][j-1]!=VACIA) && (cuadro->tablero[i-1][j-1]!=FANTASMA))
         {
         	gotoxy(j,i);
            cuadro->tablero[i-1][j-1]=COMIDO;
            cprintf(" ");
         }
      }

   //posicion del pacman
	textcolor(LIGHTRED);
  	gotoxy(y+1,x+1);
  	cuadro->tablero[x][y]=PACMAN;
  	cprintf("%c",2);

  //comprobacion si esta ocupada o libre
   for(i=1;i<=FILA;i++)
   	for(j=1;j<=COL;j++)
      {
   		if(cuadro->tablero[i-1][j-1] == LIBRE)
   		{
         	textcolor(YELLOW);
         	gotoxy(j,i);
         	cprintf("%c",LIBRE);
   		}
      }

}

//iniciamos el tablero como LIBRE
void iniciarTablero(CUADRO * cuadro)
{
	int i,j;

   for(i=1;i<=FILA;i++)
   	for(j=1;j<=COL;j++)
    		cuadro->tablero[i-1][j-1]=LIBRE;
}


int lectura_records(void)
{

	//declaracion de variables
	FILE *f;
   CUADRO cuadro;

   //abrimos el fichero como lectura
   if((f=fopen("records.txt","r"))==NULL)
   {
   	perror("Error nueva: fopen");
      return(ERROR);
   }

   printf("\n\n\t\t   RECORDS\n");
   printf("\n\tNombre\t\t\t");
   printf("Puntaje\n");
   while(fscanf(f,"%s%d",cuadro.nombre,&cuadro.puntos)!=EOF)
   {
   	printf("\t%s\t\t",cuadro.nombre);
   	printf("\t%d\n",cuadro.puntos);
   }

   //cerramos el fichero
   if(fclose(f)==EOF)
   {
   	perror("Error nueva: fclose");
      return(ERROR);
   }

	return(EXITO);

}

int records(CUADRO  * cuadro, int puntaje)
{

	//declaracion de variables
	FILE *f;

   //abrimos el fichero como escritura
   if((f=fopen("records.txt","a"))==NULL)
   {
   	perror("Error nueva: fopen");
      return(ERROR);
   }

   gotoxy(49,10);
   cprintf("Ingrese el nombre(5 caract): ");
   gets(cuadro->nombre);
   fprintf(f,"%s\t",cuadro->nombre);
   gotoxy(49,11);
   cuadro->puntos=puntaje;
   cprintf("Su puntaje es %d\n",cuadro->puntos);
   fprintf(f,"%d\n",cuadro->puntos);

   //cerramos el fichero
   if(fclose(f)==EOF)
   {
   	perror("Error nueva: fclose");
      return(ERROR);
   }

	return(EXITO);

}

//definicion de nueva (nueva partida)
int nueva(CUADRO cuadro)
{
	//declaracion de variables
	FILE *f;

   //abrimos el fichero como escritura
   if((f=fopen("comecocos.dat","w"))==NULL)
   {
   	perror("Error nueva: fopen");
      return(ERROR);
   }

   //escribimos por bloques, porque va a tener diferentes estados el
   //tablero
   if((fwrite(&cuadro,sizeof(CUADRO),1,f)) != 1)
   {
   	perror("Error fwrite: nueva");
      fclose(f);
      return(ERROR);
   }

   //cerramos el fichero
   if(fclose(f)==EOF)
   {
   	perror("Error nueva: fclose");
      return(ERROR);
   }

	return(EXITO);
}


