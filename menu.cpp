
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <winbgim.h>
#include <time.h>
 
#define N_MET 20
#define T 500
#define NUM 1
#define P_IZQ 2
#define P_DER 3
#define VAR 4
#define FUNCION 5
#define OPER_B 6

#define TALLA 10

//Estructuras para el manejo de los botones

typedef struct 
{
  char texto[100];
  int x1, y1, x2, y2;
}BOTON;

typedef struct
{
  int numBot;
  BOTON vectorB[10];
}A_BOTON;

// Estruturas para el manejo de una lista
typedef struct reg
{
   char info[100];
   struct reg *sig;
}*LISTA;

typedef struct 
{
   LISTA cabPila;
   LISTA cima;
}PILA;

// Estructuras para el generador de polinomios
typedef struct regNodo
{ 
   int exp;
   float coef; 
   struct regNodo *sigTer;
}*TERM;

typedef struct
{
  int nTerm;
  TERM vectPol[TALLA]; 
}SISTEMA_E;

typedef struct regNum
{
  int x1, y1;
  char num[20];
  struct regNum *sigNum;
}*NUME;

typedef struct
{ 
 int n;
 NUME vectorNum[50];
}TABLA;

typedef struct 
{
  char name[100];
}NAME_MET;

typedef struct regMenu
{
  int x1, y1, x2, y2;
  char name[100];
  struct regMenu *cabMet;
  struct regMenu *sig;
}*MENU;

void imprimeEncabezado(int x, char *exp, char *name , float raiz, int nIter );
void imprimeTabla( int , int, int , int );
void imprimeDatosTabla( TABLA t );
void interfaceDeSENL( TABLA t , int x, int y, int x2,int dX, int nCol, char *exp, char *nameMet, float raiz, int nIter);
int creaNodoNum( NUME *, char *, int, int );
int insNodoNum( NUME *, char *, int, int );
void iniTabla( TABLA * );
void imprimeTabla( TABLA );
void leer( char * men, char *cad );
void retraso(int ms);
int creaNodo( MENU *, char *, int, int, int, int );
int insNodo( MENU *, char *, int, int, int , int );
void creaMenu( MENU * );
void imprimeMenu( MENU , MENU *, int * );
void menu();
void dibujaRectangulo( MENU , int );
void dibujaNombre( MENU, int);
void dibujaMenuPrincipal( MENU );
void limpiaPantalla(int , int, int );
void dibujaLinea( int, int, int, int, int );
void insMenu( MENU *l, char *name );
void iniVectorMet( NAME_MET * );
void direccionaMetodo( NAME_MET *, MENU );
float iteracionSimple( char*, int, TABLA *, int * );
void lee_texto(int x,int y, char cadena[]);
int leerDatos( char *exp );
void iniPila( PILA * );
int creaNodoL( LISTA *, char * );
int push( PILA * , char * );
int pop( PILA *, char * );
void leerExp( char * );
int jerToken( char * );
void funcionToken( char *infija, char *token, int *i );
int tipoToken( char * );
void convPosfija( char *, char *);
void concatenaPosfija( char *, char *);
float evaluaPosfija( char *,float  );
int pilaVacia(PILA );
void verificaExpresion( char * );
int analiParent( int , int );
void analifun( char *, int *);
int checaOper( int nOpe, int nNum );
void imprimeFunciones();
float evaluaExp( char *, float );
int botonSel(char *, char *, int, int, int, int );
float biseccion( char *exp,TABLA *t, int, int * );
float regulaFalsi( char *exp,TABLA *t, int nIter, int * );
float secante( char *exp, TABLA *, int, int * );
void insRengTabla( TABLA *t, int *x, int *y, int *i, float X, float vX );
float  newtonRaphson( char *exp, TABLA *t, int nIter, int * );
float  newtonRaphsonMejorado( char *exp,TABLA *t, int nIter, int * );
float calculaPriDer( char *exp, float x);
float calculaSegDer( char *exp, float x);
void interfaceDeIteraccionSimple( char *exp, int nIter, TABLA *t );
void eliminaTablaDeDatos( TABLA *t );

// Prototipos para los metodos matriciales

void interfazDeMetodosMatriciales( int, char * );
int leerIncognitas( int );
float **crearMatriz(int, int);
void imprimePlantilla(int, int *coorX, int *coorY, int * );
void leerSistema( float **m , int x, int y, int nR, int nC);
void eliminacionGauss_GaussJordan( float **, int, int, int, int, int );
void intercambiaRenglon( float **, int, int, int, int, int);
void eliminaRenglon( float **, int, int , int , int, int, int );
void sustitucionInversa( float **, int );
void imprime(float **, int, int );
void imprimeRenglon( char *, int, int, int, int );
void eliminaMatriz( float **m, int nR );
void imprimeSolucion( float **m, int nR );

  //Funciones para el control de la estructura boton

void iniArrayBoton( A_BOTON *, int );
void insBoton( A_BOTON *,char *, int, int, int, int ); 
void imprimeBoton( A_BOTON );
int checaBoton( A_BOTON );

/* Prototipos de funcion para interpolacion numerica y ajuste de Datos */ 
   
     int leerNdatos();
     int leerTabla( float **, int , int, A_BOTON ); 
     void imprimeTablaFuncion( float **, int, int );
     void interfazDeInterpolacionYAjuste( int );
     int capturaDatos( float ***m, int *N, int );
     void imprimeResInterpolacion( float **m, int N, int, char *pol );
     void imprimeInterpolacion( float **m, int N, float Xn, int metodo, char *pol );
     void imprimeEncabezado( int met );
     void imprimePolinomio( char *pol );
   
  // Interpolacion Lineal 
     float interpolacionLineal(float **m, int nR, int nC, float Xn);
  
  // Polinomio de Lagrange
     void iniSistema( SISTEMA_E * );
     void insTermino( TERM *, float, int );
     int creaNodoTer( TERM *, float, int );
     void determinaPolinomio( SISTEMA_E s, char *cad );
     void polinomioDeLagrange(float **m, int  nR, int nC, char *pol);
     void generaPolinomio( TERM *cabPol, float *v, int nR );
     void concatenaTerminosPol( char *pol, float num, int i, int exp );
      
     float interpolacionDeLagrange(float **m, int  nR, int nC, float Xn);
     
   // float interpolacionDeLagrange(float **,int ,int , float );  
   // void polinomioDeLagrange(float **m, int  nR, int nC, char *pol);
   // void generaPolinomio( TERM *cabPol, float *v, int nR )
  
  // Diferencias Divididas
     void dameCoeficientes( float **t, int nR, int index );
     float interpolarDD( float **t, int N, float Xn );
     void damePolinomioDD( float **t, int N, char *pol );
  
  //Minimos cuadrados 
    void metodoDeMinimosCuadrados( float **m, float **t, int N, int nR, int nC, char *pol );
    void inicializa( float **m, int nR, int nC );
    void creaPolinomio( float **m, int nR, int nC, char *pol );



int Dx = 330;
int Dy = 150;
float tolerancia;
int incog;
int activacion;

int main()
{
    initwindow(1300,680); //open a 400x300 graphics window
    
    menu(); 
     
    getch();  
    closegraph();        //close graphics window
}

void menu()
{
  int coorX, coorY;
  int x,y, band, band2, band3, band4;
  MENU aux, aux2, sub, aux3, listaMenu = NULL;
  NAME_MET vectorName[ N_MET ];
   
  x = 360;
  y = 35;
  
  settextstyle( 4, 0, 4 );
 
  outtextxy( x, y, "ANALISIS NUMERICOS" );
  
  setcolor( YELLOW ); 
  rectangle( 5,5,1295, 100);
  rectangle( 5,105,1295, 665);
  
  iniVectorMet( vectorName );
  
  creaMenu( &listaMenu );
  
  do
  {
     coorX = mousex();
     coorY = mousey();
     
     if( ismouseclick( WM_LBUTTONDOWN) )
     {
        if( band)
         { // Este ciclo controla el menu pri
           do    
           { 
             imprimeMenu( aux -> sig, &sub, &band2 );
             
             if( band2 )
             { 
                dibujaLinea(YELLOW , 570,106, 570, 665 );
                
                do
                {  
                   imprimeMenu( sub -> cabMet, &aux3, &band3 );
                   
                   if( band3 /*&& aux3 -> cabMet*/ )
                   {
                      band3 = 0;
                      limpiaPantalla( 900, 400, YELLOW  );
                      
                      dibujaLinea(BLACK , 570,106, 570, 665 );
                      
                      direccionaMetodo( vectorName, aux3 );
                  
                          /*dibujaLinea(YELLOW , 865,106, 865, 665 );
                          imprimeMenu( aux3 -> cabMet, &aux3, &band4 );
                        
                           if( band4 )
                             printf("ir ametodo" );
                           else
                           {
                             limpiaPantalla( 900, 400  );
                             dibujaLinea(BLACK , 865,106, 865, 665 );
                           }
                            */  
                  }else
                      {
                         delay(500);
                         limpiaPantalla( 600, 400, YELLOW );
                         
                         dibujaLinea(BLACK , 570,106, 570, 665 );
                         
                         if( band3 )
                               direccionaMetodo( vectorName, aux3 );
                                
                                
                                puts( " Ir a metodo" );
                                band3 = 0;
                            }
                     
                   }while( band3 );     
                
                }//fin de Band2
                
            }while( band2 );
            
         limpiaPantalla( 300,300, YELLOW );
     
     }else
             limpiaPantalla( 300, 300, YELLOW);
        
         clearmouseclick(WM_LBUTTONDOWN );
     
     }else
      {
           aux = listaMenu;
           //Efecto en el boton de inicio
           if( coorX > aux -> x1 && coorX < aux -> x2 && coorY > aux -> y1 && coorY < aux -> y2 )
           {
                dibujaNombre( aux , GREEN );
                band = 1; 
            }else
               {    dibujaRectangulo( aux , LIGHTBLUE  );
                    dibujaNombre( aux , WHITE );
                    band = 0;
               }
        }
 
  }while(!kbhit());   

}

void iniVectorMet( NAME_MET *a )
{
   
   for( int i = 0; i < 12; i++ )
        strcpy( a[i].name, " " );
   
   strcpy( a[0].name, "Iteracion Simple " );
   strcpy( a[1].name, "Biseccion " );
   strcpy( a[2].name, "Regula Falsi " );
   strcpy( a[3].name, "Secante " );
   strcpy( a[4].name, "Newton Raphson " );
   strcpy( a[5].name, "Newton Raphson mejorado " );
   strcpy( a[6].name, "Eliminacio de Gauss " );
   strcpy( a[7].name, "Metodo de Gauss Jordan " );
   strcpy( a[8].name, "Metodo de Interpolacion Lineal " );
   strcpy( a[9].name, "Polinomio de interpolacion de Lagrange " );
   strcpy( a[10].name, "Metodo de Diferencias Divididas " );
   strcpy( a[11].name, "Minimos Cuadrados " );
   
}

void imprimeMenu( MENU l, MENU *sub, int *bandAux)
{
  MENU aux, aux2;
  int coorX, coorY, band = 1; 
  
  *bandAux = 0;
  
  clearmouseclick(WM_LBUTTONDOWN );
  
  if( l ) 
  { 
    do
    {
     coorX = mousex();
     coorY = mousey();
     
     if( ismouseclick( WM_LBUTTONDOWN) )
     {
        if( *bandAux)
                *sub = aux2;
        
        band = 0;
        clearmouseclick(WM_LBUTTONDOWN );
     
     }else
      {
          *bandAux = 0;
          
          for(aux = l; aux; aux = aux -> sig) 
            if( coorX > aux -> x1 && coorX < aux -> x2 && coorY > aux -> y1 && coorY < aux -> y2 )
            {
                 dibujaRectangulo( aux , BLACK );
                 dibujaNombre( aux , GREEN );
                 aux2 = aux;
                 *bandAux = 1;
            }else
               {    dibujaRectangulo( aux , LIGHTBLUE  );
                    dibujaNombre( aux , WHITE );
               }
       }
      
      // printf(" bandAux : %d\n", *bandAux );
    
     delay(1); 
  
    }while(band); 
 }else
   { 
     setcolor(WHITE );
     outtextxy(600,500, "Sin metodo" ); 
   }
}
/*
  Aqui se crea los submenus insertabdose en la lista */
void creaMenu( MENU *l )
{
  MENU aux, aux2;
  
  insMenu( l, "MenuPrincipal.txt" );   
  
  aux = (*l)-> sig;
  
  for( int i = 0; i<4; i++, aux = aux -> sig )
  {
    switch( i )
    {
      case 0:  insMenu(  &aux -> cabMet, "SolENL.txt" ); break;
      case 1:  insMenu(  &aux -> cabMet, "SolMat.txt" ); break;
      case 2:  insMenu(  &aux -> cabMet, "InterpolacionNum.txt" ); break;
      case 3:  insMenu(  &aux -> cabMet, "AjusteDeDatos.txt" ); break;
    }
  }    
}

void insMenu( MENU *l, char *name )
{
  FILE *ptrArch;
  char cad[400], cad2[300], cad3[200];
  int tam, x1, y1, x2, y2, num, i, cont;
  
  ptrArch = fopen( name, "r" );
  
  if( ptrArch == NULL )
      puts(" No se pudo abrir el archivo");
  else
  {
     while( !feof( ptrArch ) )
     {    
        fgets( cad, 200, ptrArch);
        
        cont = i = 0;
        cad3[0] = '\0';
        
        while( i < strlen( cad ) )
         {
            funcionToken( cad, cad2, &i);
            
            switch( tipoToken( cad2 ))
            {
              case 1: 
                      num = atoi( cad2 );
                      
                      switch( cont )
                      {
                        case 0: x1 = num;break;
                        case 1: y1 = num;break;
                        case 2: x2 = num;break;
                        case 3: y2 = num;break; }
                      
                      cont ++; break;
              case 5: 
                       strcat( cad3, cad2 );
                       
                       tam = strlen( cad3 );
                       cad3[tam] = 32;
                       cad3[tam + 1] = '\0';
           }
         }
       insNodo( l, cad3, x1, y1, x2, y2 );
      // printf(" %s %d %d %d %d \n", cad3 , x1 , y1, x2, y2 );
     }
       fclose( ptrArch );
  } 
}

int creaNodo( MENU *nodo, char *cad, int cX1, int cY1, int cX2, int cY2 )
{
  int res = 0;
  
  if( *nodo = (MENU)malloc( sizeof( struct regMenu ) ) )
  {
    strcpy( (*nodo) -> name, cad  );
    (*nodo) -> x1 = cX1;
    (*nodo) -> y1 = cY1;
    (*nodo) -> x2 = cX2;
    (*nodo) -> y2 = cY2;
    (*nodo) -> sig = NULL;
    (*nodo) -> cabMet = NULL;
    res = 1;
  } 
  
  return( res );  
}

int insNodo( MENU *l, char *cad, int cX1, int cY1, int cX2, int cY2 )
{
  MENU aux, nuevo;  
  int res = 0;
  
  if( creaNodo( &nuevo, cad, cX1, cY1, cX2, cY2 ) )
  {
    aux = *l;
    
    for(; aux && aux -> sig; aux = aux -> sig );
    
    if( !*l ) 
        *l = nuevo;
    else
       aux -> sig = nuevo;
    res = 1;
  
  } 
  
  return( res );  
}

void direccionaMetodo( NAME_MET *a, MENU met )
{
   TABLA t;
   float raiz, aux, xI, xD;
   int opc, opc2, i, tam, x, y, nIter;   
   char exp[50], cadAux[50], cadIter[10];
   
   limpiaPantalla( 400, 400 , YELLOW);
   
   for( i = 0; i < N_MET; i++)
      if( !strcmp( a[i].name, met -> name) )
                 break;
  printf( " %d ", i );
  
  if( i < 6 )               
  {
    do
    {
      iniTabla( &t );
      
      settextstyle( 8, 0, 1 );
      nIter = leerDatos( exp );
      
      switch( i )
      { 
       case 0:  x = 260; y = 240;
              strcpy( cadAux, exp );
  
              strcat( cadAux, "+x" ); 
              tam = strlen( cadAux );
              cadAux[tam] = '\0';
              
              raiz = iteracionSimple( cadAux, nIter, &t, &opc2 );
              
              if( opc2 == 1 )
               {
                     aux = raiz;
                     limpiaPantalla( 400, 400, YELLOW );
                     
                     settextstyle( 8, 0, 1 );
                     outtextxy( x + 12 , y + 10 , " i     Xo      f(Xo)    Error " );    
                     interfaceDeSENL( t,x,y, 450, 355, 3, exp, "Metodo de Iteraccion Simple",aux, t.n ); 
                }
               
               break; 
               
     case 1:  x = 50; y = 260;
              
              raiz = biseccion( exp, &t, nIter,&opc2  );
              
              if( opc2 == 1 )
              {
                limpiaPantalla( 400, 400, YELLOW );
              
                settextstyle( 8, 0, 1 );
                outtextxy( x + 12 , y + 10 , " i     Xi      f(Xi)      Xd      f(Xd)     Xn      f(Xn)   Error " );    
                interfaceDeSENL( t,x,y, 470, 760, 7, exp, "Metodo de Biseccion",raiz, t.n ); 
              }
              break;
              
     case 2:  x = 50; y = 260;
             
             raiz = regulaFalsi( exp,&t, nIter, &opc2 );
              
             if( opc2 == 1 )
             { 
              limpiaPantalla( 400, 400, YELLOW );
              settextstyle( 8, 0, 1 ); 
              outtextxy( x + 12 , y + 10 , " i     Xi      f(Xi)      Xd      f(Xd)     Xn      f(Xn)   Error " );    
              interfaceDeSENL( t,x,y, 460, 760, 7, exp, "Metodo de Regula Falsi",raiz, t.n );
             }
             break; 
     case 3: 
             x = 260; y = 240;
             
             raiz = secante( exp, &t, nIter, &opc2 );
             
             if( opc2 == 1 )
             {
               limpiaPantalla( 400, 400, YELLOW );
  
               settextstyle( 8, 0, 1 );
               outtextxy( x + 12 , y + 10 , " i     Xo      f(Xo)    Error " );    
               interfaceDeSENL( t,x,y, 450, 355, 3, exp, "Metodo de la Secante",raiz, t.n ); 
            }
            break; 
     
     case 4: x = 240; y = 240;
             raiz = newtonRaphson( exp, &t, nIter, &opc2 );
            
            if( opc2 == 1 )
            { 
             limpiaPantalla( 400, 400, YELLOW );
             
             settextstyle( 8, 0, 1 );
             outtextxy( x + 10 , y + 10 , " i     Xo      f(Xo)    Error    f'(Xo) " );    
             interfaceDeSENL( t,x,y, 450, 465, 4, exp, "Metodo de Newton-Raphson",raiz, t.n ); 
             }
             break; 
     case 5: 
             x = 240; y = 240;
             
             raiz = newtonRaphsonMejorado( exp, &t, nIter, &opc2 );
             
             
             if( opc2 == 1 )
             {
             
             limpiaPantalla( 400, 400, YELLOW );
             
             settextstyle( 8, 0, 1 );
             outtextxy( x + 10 , y + 10 , " i     Xo      f(Xo)    Error    f'(Xo)   f''(Xo)" );    
             interfaceDeSENL( t,x,y, 410, 560, 5, exp, "Metodo de Newton-Raphson Mejorado",raiz, t.n );
             }
             break;
     }
       if( opc2 == 1 )
       {
         opc = botonSel("NUEVA FUNCION "," IR A MENU ", 890, 610, 1020, 650); 
         
         if( opc == 2 )
             opc2 = 2;
   
      }else
         opc = 2; 
     
     eliminaTablaDeDatos( &t ); 
   }while( opc2 != 2 || opc != 2 );  
    delay( 400 ); 
 }else
    if( i > 7 && i < 12 )
       interfazDeInterpolacionYAjuste(i );
    else
       interfazDeMetodosMatriciales( i, a[i].name ); 
 
   limpiaPantalla( 400, 400, YELLOW );
} 

/************************************  Inicio de funciones para los metodo de interpolacion y ajuste de datos ***********************************/


int capturaDatos( float ***m, int *N , int metodo)
{
   int X, Y, opcBoton, nR;
   A_BOTON bot;
   
   Y = 500; X = 496;
   
   iniArrayBoton( &bot, 3);
   insBoton( &bot, "Continuar", X, Y, X + 128, Y + 40 ); 
   insBoton( &bot, "Cancelar", X + 168, Y, X + 168 + 128, Y + 40 ); 
   
   switch( metodo )
   {
      case 8: nR = 2; break;
      case 9: nR = 3; break;
      case 10: nR = 3; break;
      case 11: nR = 2; break;
   }
    
   *N = leerNdatos();
   
   *m = crearMatriz( *N, nR );
   
   opcBoton = leerTabla( (*m), *N, 2, bot );
   
   limpiaPantalla( 400, 400, YELLOW );
   
   return( opcBoton );
}  

int leerNdatos()
{
  int opc, N, dx, dy;
  char cad[20];
  
  dx = 240;
  dy = 100;
  
  settextstyle( 8, 0, 1 );
  setcolor(YELLOW );
  rectangle( 645 - dx,  350 - dy ,  645 + dx, 350 + dy );
  
  limpiaPantalla( 645,  350, YELLOW );
  
  setcolor( GREEN );
  outtextxy( 645 - dx + 35, 350- dy + 30 , "Introduzca el No de datos de la tabla" );
  
  setcolor( WHITE );
  outtextxy( 645 - dx + 100, 350- dy + 105 , "       N  =" );
  
  lee_texto( 645 - dx + 240, 350 - dy + 105, cad );
  
  limpiaPantalla( 645, 350, YELLOW );
  setcolor(BLACK);
  rectangle( 645 - dx,  350 - dy ,  645 + dx, 350 + dy );
  setcolor(WHITE );
  
  N = atoi( cad ); 
  
  return( N );
}

int leerTabla( float **m , int nR, int nC, A_BOTON bot )
{
  int opcBoton, X, dY, dX, x, y, x2, y2, Y, sX, sY, i, j;
  char cad[200];
  
  dY = 34; dX = 120; sX = 10; sY = 10; Y = 370;
  
  x =  620 - ((dX/2 + sX/2)*nR - dX/2); X = x;
  x2 = 620 + ((dX/2 + sX/2)*nR + dX/2 );
  y2 = 370 + (( dY/2 + sY/2)*nC + dY/2 );
  
  setlinestyle( 0, 0, 3 );
  
  setcolor(YELLOW);
  rectangle( x- 30 - dX/2 , 230 , x2 + 35 , y2 + 150); 
  limpiaPantalla( x- 30, y2, YELLOW );
  
  setcolor(WHITE );
  
  line( x - 40, 409, x2 + 5 , 409);
  line( x - 12, Y + 5 , x - 12, y2 + 15 );
  outtextxy( 645 - 167, 280, "Introduzca los datos de la tabla" );
  
  imprimeBoton( bot );
  
  rectangle( x-10 - dX/2 , Y-10, x2 + 15, y2 + 26);  
  outtextxy( x - 35, Y + 10, "X" );
  outtextxy( x - 35, y2 - 10, "Y" );
  
  setcolor( 2 );
  setlinestyle(0, 0, 0 );
  
  for( i = 0 ; i < nC; i++, Y += dY + sY, X = x) 
     for( j = 0; j < nR; j++, X += dX + sX )
          rectangle( X, Y , X + dX,  Y + dY );
  
  settextstyle( 8, 0, 1  );
  
  for( i = 0; i < nR; i++,  X += dX + sX )
     for(Y = 370, j = 0; j < nC; j++,Y += dY + sY )
       {
         lee_texto( X + 10, Y + 8, cad );
         m[i][j] = atof(cad);
       }
       
  setlinestyle( 0, 0, 3 );
  opcBoton = checaBoton( bot );
   
  setcolor(BLACK);
  setlinestyle(0, 0, 3 );
  rectangle( x- 30 - dX/2 , 230 , x2 + 35 , y2 + 150); 
  
  return( opcBoton );
}

void imprimeEncabezado( int met )
{
  int x;
  char cad[100];
  
  settextstyle( 10, 0, 3  );
  
  switch( met )
  {
    case 8: x = 430; strcpy( cad, "Método de interpolación líneal"); break;
    case 9: x = 380; strcpy( cad, "Polinomio de interpolación de Lagrange");break;
    case 10: x = 430; strcpy( cad, "Método de diferencias divididas"); break;
    case 11: x = 430; strcpy( cad, "Método de mínimos cuadrados");
  }
  
  outtextxy( x,130, cad );
  settextstyle( 8, 0, 1 );
  
}

void imprimeTablaFuncion( float **m, int nR, int nC )
{
  int i, j, x, y, X,dX, Y;
  char cad[10];
  
 // line( 655, 100, 655, 600 );
  
  dX = 170;
  X = 50; Y = 270;
  
  setcolor(GREEN);
  outtextxy( X+30, Y+10, " x     f(x) " );
  
  setcolor(WHITE );
  
  setlinestyle(0,0,3);
  line( X + dX/2 - 70 , Y + 40, X + dX/2 + 70 , Y + 40 );
  
  for( y = Y + 50, i = 0; i < nR; i++, y += 20 )
     for(x = X + 28, j = 0; j < nC; j++, x += 82 )
     {
       if( !j )
         sprintf(cad, "%.1f", m[i][j] ); 
       else
         sprintf(cad, "%.2f", m[i][j] ); 
       
       outtextxy( x, y, cad );
     }
  
  line( X + dX/2  , Y + 10, X + dX/2, y + 10 );
}

void imprimeInterpolacion( float **m, int N, float Xn, int metodo, char *pol)
{
  char cad[20];
  float Yn;
  
  switch( metodo )
  {
    case 8: Yn = interpolacionLineal( m, N, 2, Xn ); break;
    case 9: Yn = interpolacionDeLagrange( m, N, 3, Xn ); break;
    case 10: Yn = interpolarDD(m, N, Xn ); break;
    case 11: Yn = evaluaExp( pol, Xn );// Minimos cuadrados
  }
  
  sprintf( cad, "%.4f", Yn );
  outtextxy( 590-10, 400 -30, cad );
}

void imprimeResInterpolacion( float **m, int N, int metodo, char *pol)
{
  char cad[20];
  float Xn, Yn;
  
  setcolor( WHITE );
  outtextxy( 590 - 10, 400-50,"         " );
  outtextxy( 590-10, 400 -30,"           " );
  lee_texto( 590 - 10, 400-50, cad );
  Xn = atof( cad );
  
  imprimeInterpolacion( m, N, Xn, metodo, pol);
} 

void imprimePolinomio( char *pol )
{
  int i,j, x, y, cont = 0;
  char cad[100];
  
  cad[0] = '\0';
  
  x = 485; y = 370;
  
  limpiaPantalla( 590,400, GREEN );
  
  setcolor( YELLOW);
  outtextxy(  532, y-50, "Polinomio" );
  outtextxy( 405, y, "P(x) = " );
  
  puts( pol );
  
  setcolor(WHITE);
  
  for( j = i = 0; i < strlen( pol ); i++, j++ )
  {
    if( pol[i] != '+' && pol[i] != '-' )
        cad[j] = pol[i];
    else
       {
           if( pol[i+1] == 32 )
              cont++;
           
           cad[j] = pol[i];
       }
    
    if( cont == 2 )
    {
      cad[j] = '\0';
      outtextxy(x,y, cad );
      cad[0] = '\0';
      cont = -1;
      i--;
      j = -1;
      y += 20; 
    }
  
  //putchar( pol[i] );
   }
 
   cad[j] = '\0';
   printf( " %d ", strlen(cad) );
   outtextxy(x,y, cad );
}

void imprime( float **m, int nR, int nC )
{
  int i, j;
  
  puts("\n");
  
  for( i = 0; i < nR; i++)
   {
      for( j = 0; j < nC; j++)
         printf(" %.4f ", *(*(m+i)+j) );
      
      puts("\n");
  
   }
}

void interfazDeInterpolacionYAjuste( int metodo )
{
   A_BOTON bot;
   float **tabla, Xn, Yn, **matriz, **copiaTab;
   int N, X, Y, band, band2, band3, band4, band5, band8, band9, dX, dY, grado;
   char cad[20], pol[500];
   PILA poli;
   
   iniPila( &poli );
   
   band = band3 = band4 = 1;
   Y = 250; X = 400;
   
   dX = 200;
   dY = 100;
   
   iniArrayBoton( &bot, 5);
   
   insBoton( &bot, "Interpolación", X, Y, X + 177, Y + 40 ); 
   
   Y = 600; X = 900;
   
   insBoton( &bot, "Nueva tabla", X, Y, X + 150, Y + 40 ); 
   insBoton( &bot, "Ir a menú", X + 170, Y, X + 160 + 140, Y + 40 ); 
   
   Y = 250; X = 400;
   
   if( metodo != 8 ) //Si el metodo es diferente Interpolacion lineal
      insBoton( &bot, "Ajuste de datos", X + 188, Y, X + 188 + 195, Y + 40 ); 

  do
  {
     if( !capturaDatos( &tabla, &N, metodo ) )
     {
       setcolor(WHITE );
       imprimeEncabezado( metodo );
       
       setcolor(GREEN );
       rectangle( 590 - dX, 400 - dY, 590 + dX, 400 + dY );
       imprimeTablaFuncion( tabla, N, 2 );
       
       band2 = band5 = band4 = 1;
       band8 = 0;
       
       if( metodo == 10 )// Si el metodo Diferencias Divididas
       {
          copiaTab = crearMatriz(N, 3);
           
          for( int i = 0; i < N; i++ )
               for( int j = 0; j < 3; j++ )
                    copiaTab[i][j] = tabla[i][j];
  
          dameCoeficientes( copiaTab, N, 1 ); 
  
          for( int i = 0; i < N; i++)
                tabla[i][2] = copiaTab[i][2];
       }
       
       do
       { 
         imprimeBoton( bot );
         band9 = 1;
         
         switch( checaBoton( bot ) )
         {
           case 0: if( band3 ) // Hacer una interpolacion numerica
                   {
                      limpiaPantalla( 590, 400, GREEN );
                      setcolor( WHITE );
                      
                      if( metodo == 11 && !band8 )// si el metodo es minimos cuadrados
                            band9 = 0;
                      
                      if( band9 )
                      {
                          outtextxy( 590-80, 400- 50," Xn = " );
                          outtextxy( 590-80, 400-30," Yn = " );
                          lee_texto( 590 - 10, 400-50, cad );
                      
                          Xn = atof( cad );
                          
                          imprimeInterpolacion( tabla, N, Xn, metodo,pol);
                      
                          if( band4 )
                             insBoton( &bot, "Nueva interpolación", 590 - 120, Y + 190, 590+ 120, Y + 190+ 40 );
                      
                          band3  = band4 = 0; band5 = 1;
                      }else
                          {                        
                            int a, b,d;
                            
                            a = 610; b = 330; d = 20;
                                                        
                            outtextxy( a - 190, b,"Para este método lo primero que" );
                            outtextxy( a - 190, b + d,"se tiene que hacer es un ajuste" );
                            outtextxy( a - 190, b + d*2,"de datos, el polinomio generado");
                            outtextxy( a - 190, b +d*3,"se utilizará para hacer las" );
                            outtextxy( a - 190, b+d*4,"interpolaciones necesarias." );
                            outtextxy( a - 190, b+d*6,"Seleccione el botón de Ajuste." );
                            
                          }
                      }
                   
                   break;
                   
           case 1: if( !band3 && !band4 )// Creaccion de nueva tabla
                        bot.numBot--;
                    
                    band3 = band4 = 1; band2 = 0;
                    
                    eliminaMatriz( tabla, N);
                    
                    if( metodo == 10 )
                          eliminaMatriz( copiaTab, N); 
                    
                    break;
           
           case 2: retraso(100);limpiaPantalla( 590, 400, GREEN ); setlinestyle( 0,0,0);band2 = band = 0;break;
           
           case 3:  if( metodo == 8 )// Nueva interpolacion lineal
                       imprimeResInterpolacion( tabla, N, metodo, pol );
                    else
                       { // En caso en que los metodos se haga algun ajuste de datos
                          
                          band8 = 1;
                        
                           if( band5 ) 
                           {
                              limpiaPantalla( 590, 400, GREEN );
                              
                              switch( metodo )
                              {
                                case 9: polinomioDeLagrange( tabla, N, 3, pol); break;
                                case 10: damePolinomioDD( tabla, N, pol ); break;
                                case 11:/* Minimos cuadrados*/ 
                                         
                                          setcolor(WHITE);
                                          
                                          if( N == 2 )
                                          {
                                            outtextxy( 590-190, 390- 30,"El único polinomio para esta tabla" );
                                            outtextxy( 590 - 190, 390,"es una ecuación lineal presione una");
                                            outtextxy( 590 - 190, 420,"tecla para continuar." );
                                            grado = 1;
                                            getch();
                                          }else
                                              {        
                                                outtextxy( 590-120, 400- 50,"Grado del polinomio" );
                                                outtextxy( 590 - 70, 400," G = " );
                                                lee_texto( 580 , 400, cad );
                                          
                                                grado = atoi( cad );
                                               }
                                          
                                          matriz = crearMatriz( grado + 1, grado + 2 );
                                          inicializa( matriz, grado + 1, grado + 2 );
                                          
                                          metodoDeMinimosCuadrados( matriz, tabla, N, grado + 1, grado + 2, pol);
                                          
                                          eliminaMatriz( matriz, grado + 1); 
                                          
                                          break;
                              }
                              
                              puts(pol);
                              //outtextxy(400, 400, pol );
                              
                              imprimePolinomio( pol );
                              
                              if( !band4 && !band3 ) 
                                  bot.numBot--;
                              
                              band3 = band4 = 1; 
                              band5 = 0;
                           }
                       }
                    break;
                      
           case 4: imprimeResInterpolacion( tabla, N, metodo, pol );// Nueva interpolacion
        }
         
       }while(band2);
       
       limpiaPantalla( 590, 400, GREEN );
     
     }else
         {
           retraso(10);
           eliminaMatriz(  tabla, N);
           setlinestyle( 0,0,0); 
           band = 0;
         }
  }while(band);
}

/********************** Inicio de funciones para el metodo de minimos cuadrados ************************************************/

void metodoDeMinimosCuadrados( float **m, float **t, int N, int nR, int nC, char *pol )
{
  int i, j, k, z;
  
  for( i = 0; i < nR; i++ )
    for( j = 0, z = i; j < nC; j++, z++ )
       if( i == 0 && j == 0 )
            m[i][j] = N;
       else
          for( k = 0; k < N; k++ )
             if( j == nC - 1 )
                m[i][j] += t[k][1] * pow( t[k][0], i );
             else
                m[i][j] += pow( t[k][0], z);
  
  imprime( m, nR, nC);
  
  activacion = 0;
  eliminacionGauss_GaussJordan( m , 7, 0,0, nR, nC);
  
  imprime( m, nR,nC);
  
  creaPolinomio( m, nR, nC, pol );
}

void creaPolinomio( float **m, int nR, int nC, char *pol )
{
  pol[0] = '\0';
  
  for(int i = 0; i < nR; i++ )
     concatenaTerminosPol( pol, m[i][nC-1], i, i );// Se crea el polinomio
}

void inicializa( float **m, int nR, int nC )
{
  int i, j;
  
  for( i = 0; i < nR; i++ )
     for( j = 0; j < nC; j++ )
           *(*(m + i) + j ) = 0;
}


/*** Interpolacion Lineal ***/ 
float interpolacionLineal(float **m, int nR, int nC, float Xn)
{
  float Yi = -9999;
  int i, rS;
  
  for( i = 0, rS = i+1; i < nR-1; i++, rS++)
      if(  Xn >= m[i][0]&&  Xn <= m[rS][0] )
             break;
  
  if( i < nR-1 )
       Yi = m[i][1] + ( ((m[rS][1] - m[i][1])*( Xn - m[i][0] ))/(m[rS][0]- m[i][0])); 
  
  return( Yi );
}

/*********  Funciones para el polinomio de Lagrange *********/

void polinomioDeLagrange(float **m, int  nR, int nC, char *pol)
{
  SISTEMA_E sisPol;
  int i, j,z;
  float den,vector[nR-1];
  TERM aux;
  
  iniSistema( &sisPol );
  
  for( i = 0; i < nR; i++ )
  {
     den = 1;  
     
     for( j = 0; j < nR-1; j++ )
        if( j >= i )
        {
          vector[j] = m[j+1][0]*-1;
          den *=(m[i][0] - m[j+1][0]);
        }else
            {
              vector[j] = m[j][0]*-1;
              den *= (m[i][0] - m[j][0]);
            }
     
     generaPolinomio( &sisPol.vectPol[sisPol.nTerm], vector, nR -1 );
     sisPol.nTerm ++;  
     
     for(aux = sisPol.vectPol[i]; aux ; aux -> coef = (aux -> coef / den)*m[i][1], aux = aux -> sigTer );
   
   }
   
   //imprimeSistema( sisPol );
   determinaPolinomio( sisPol, pol );
  // puts( pol );
}

void determinaPolinomio( SISTEMA_E s, char *pol )
{
  TERM aux;
  int i ;
  float acum;
  
  pol[0] = '\0'; 
  
  for( i = 0; i < s.nTerm;  i++ )
  {
     acum = 0;
     
     for(int  j = 0; j < s.nTerm; j++ )
     {
         aux = s.vectPol[j];
         
         for( int k = 0; k <i; aux = aux -> sigTer, k++);
         
         acum += aux -> coef;
     }
     // Se crea el polinomio
     concatenaTerminosPol( pol, acum, i,  aux -> exp );
  }
}

void concatenaTerminosPol( char *pol, float num, int i, int exp )
{
  char cadAux[100];
  int band = 0;
  
  sprintf( cadAux, "%.3f", num );
  
  if( strcmp(cadAux, "0.000" ) &&  strcmp(cadAux, "-0.000" ) )
  {
     if( i && strlen(pol) > 0 )
     {
       num = atof(cadAux); 
          
          if( num < 0 )
           {  
              band = 1;
              num *= -1;
           }
           
          if( band )
            strcat( pol ," - " );
          else
            strcat( pol ," + " );
          
          sprintf( cadAux, "%.3f", num );
     }
      
       strcat(pol, cadAux );
      
      
       if( exp == 1 ) 
            strcat(pol, "*x");
       else
          if( exp > 1 )
          {
               strcat(pol, "*x^");
               sprintf(cadAux,"%d", exp );
               strcat(pol, cadAux );
          }
    }
}

void generaPolinomio( TERM *cabPol, float *v, int nR )
{
  int i;
  float var1, var2;
  TERM aux;
  
  insTermino( cabPol, 1, 2 );
  insTermino( cabPol, v[0] + v[1], 1);
  insTermino( cabPol, v[0]*v[1], 0 );
 
  for( i = 2; i < nR ; i++ )
  { 
     for(aux = *cabPol; aux; aux -> exp++, aux = aux -> sigTer );
     
     aux = *cabPol;
     
     var1 = aux -> coef;
     var2 = aux -> sigTer -> coef;
     aux = (*cabPol)->sigTer;
     
     while( aux )   
     {
        aux -> coef = var1 * v[i] + var2;
        var1 = var2;
     
        if(!aux -> sigTer )
        {
          insTermino( cabPol, v[i]*var1, 0 );
          aux = NULL;   
        }else     
            {
              aux = aux -> sigTer;
              var2 = aux -> coef;
            }
     }  
  }
}

void iniSistema( SISTEMA_E *s )
{
  int i;   
  
  for( i = 0; i < TALLA; i++ )
      s -> vectPol[i] = NULL;
  
  s -> nTerm = 0;
}

void insTermino( TERM *cabPol, float c, int e )
{
  TERM nuevo,aux;
  
  if( creaNodoTer( &nuevo, c, e ) )
  {
    for( aux = *cabPol; aux && aux -> sigTer; aux = aux -> sigTer );
     
    if( !*cabPol)
         *cabPol = nuevo;
     else
          aux -> sigTer = nuevo;   
  }
}

int creaNodoTer( TERM *nuevo, float c, int e )
{
   int res = 0;
   
  if( *nuevo = (TERM )malloc( sizeof( struct regNodo) ) )
  {
    (*nuevo) -> coef = c;
    (*nuevo) -> exp = e;
    (*nuevo) -> sigTer = NULL; 
     res = 1;
  }
   
  return( res );
}

float interpolacionDeLagrange(float **m, int  nR, int nC, float Xn)
{
  int i, j;
  float num,den,inter = 0;
  
  for( i = 0; i < nR; i++ )
  {
     num = den = 1;  
     
     for( j = 0; j < nR-1; j++ )
        if( j >= i )
        {
          num *=(Xn - m[j+1][0]);
          den *=(m[i][0] - m[j+1][0]);
        }else
            {
              num *= (Xn - m[j][0]);
              den *= (m[i][0] - m[j][0]);
            }
     
     m[i][nC-1] = num/den;
  }
  
  imprime( m, nR, nC );
  
  for( i = 0; i < nR; i++ )
     inter += ( m[i][1] * m[i][2] );   
  
  return(inter);
}


/********************************** Funciones para el manejo del metodo de Diferencias Divididas ************************************************/

void dameCoeficientes( float **t, int nR, int index )
{
  int i, j; 
  
  t[index-1][2] = t[0][1];
  
  if( index < nR )
  {
    for( j = index, i = 0; j < nR; j++, i++ )
      t[i][1] = ( t[i+1][1] - t[i][1] ) / ( t[j][0] - t[i][0] );  
    
    dameCoeficientes( t, nR, index+1 );
  }
}

float interpolarDD( float **t, int N, float Xn )
{
  float interp, term;
  int i,j;
  
  interp = t[0][2];
  
  for( i = 1; i < N; i++ )
  { 
    term = 1;
    
    for(j = 0; j < i; j++ )
        term *= (Xn -t[j][0]);
   
    interp += ( t[i][2] * term);
  }
  
  return( interp );
}

void damePolinomioDD( float **t, int N, char *pol )
{
  SISTEMA_E sisPol;
  int i, j,z;
  float vector[N], acum;
  TERM aux, aux2;
  
  pol[0] = '\0';
  iniSistema( &sisPol );
  
  if( t[0][2] != 0 )
      insTermino( &sisPol.vectPol[0], t[0][2], 0);
  
  sisPol.nTerm++;
  
  if( t[1][2] != 0 )
  {
     insTermino( &sisPol.vectPol[1], t[1][2], 1);
     insTermino( &sisPol.vectPol[1], t[1][2]*t[0][0]*-1, 0 );
  }
  
  sisPol.nTerm++;
  
  for( i = 2; i < N; i++, sisPol.nTerm++ )
    if( t[i][2] != 0 )
    {
       for( j = 0; j < i; j++ )
           vector[j] = t[j][0]*-1;
       
       generaPolinomio( &sisPol.vectPol[sisPol.nTerm], vector, i);
       
       aux = sisPol.vectPol[sisPol.nTerm];
       
        for(; aux ; aux -> coef *= t[i][2], aux = aux -> sigTer );// Multiplicar el coef por el polinomio generado
    }
  
  for(i = 0; i < N; i++)
  {
     acum = 0;
     
     for( j = i; j < N ; j++ )
     {
        aux = sisPol.vectPol[j];
        
        while( aux )
        {
            if( aux -> exp == i )
            {
               acum += aux -> coef;
               break;
            }
            aux = aux -> sigTer;
        }
     }
     
    concatenaTerminosPol( pol, acum, i, i );
   }
}

/****************************************** Inicion de la Funciones para los métodos Matriciales *******************************************/

void interfazDeMetodosMatriciales( int metodo, char *met )
{
  limpiaPantalla( 400, 400, YELLOW ); 
  
  activacion = 1;
  
  puts( met );
  int x,y, Y, nI, dX,band3,band2, band;
  float **m;
  A_BOTON bot;
  
  band = band2 = band3 = 1;
  dX = 140;
  iniArrayBoton( &bot, 3);
  
  insBoton( &bot, "N u e v o", 920, 600, 1048,640 ); 
  insBoton( &bot, "Ir a menu", 1100, 600, 1228, 640 ); 
 
  do
  { 
    if( band2 )
    {
      nI = leerIncognitas( metodo );
      m = crearMatriz(nI, nI + 1 );
    
      imprimePlantilla( nI, &x, &y, &Y );
      insBoton( &bot, "Solucionar", 645 - dX/2, Y + 30, 645+ dX/2+5,Y + 30 +40 ); 
    
      imprimeBoton( bot );
    
      leerSistema( m , x, y,nI, nI+1);
    }
    
    switch( checaBoton( bot ) )
    {
      case 0: bot.numBot--; band2 = band3 = 1;limpiaPantalla( 645, 350, YELLOW );  break;
      case 1: band = 0;break;
      case 2: if( band3 )
              {
                eliminacionGauss_GaussJordan( m, metodo, x,y,nI, nI+1 );
                imprimeSolucion( m, nI);
                eliminaMatriz( m, nI );
                band2 = 0;
                band3 = 0;
              }
    }
  
  }while( band );
}

float **crearMatriz(int nR, int nC )
{
   float **m;
   int i;
   
   m = (float ** )malloc( sizeof( float *) * nR );
   
   for( i = 0; i < nR; i++ )
      m[i] = (float *)malloc( sizeof( float ) * nC );
   
   return( m ); 
}

int leerIncognitas( int metodo )
{
  char cad[20];
  int opc, nI, dx, dy;
  
  dx = 240;
  dy = 100;    
   
  setcolor( WHITE );
  
  settextstyle( 4, 0, 1 );
  if( metodo == 6 )
      outtextxy( 485,130, " Eliminacion de Gauss" );
  else
      outtextxy( 460,130, " Metodo de Gauss - Jordan" );
  
  settextstyle( 8, 0, 1 );
  
  setcolor(YELLOW );
  rectangle( 645 - dx,  350 - dy ,  645 + dx, 350 + dy );
  limpiaPantalla( 645, 350, YELLOW );
  setcolor( GREEN );
  outtextxy( 645 - dx + 35, 350- dy + 30 , " Introduzca el numero de Incognitas " );
  setcolor( WHITE );
  outtextxy( 645 - dx + 100, 350- dy + 105 , "Incognitas = " );
  lee_texto( 645 - dx + 240, 350 - dy + 105, cad );
  
  limpiaPantalla( 645, 350, YELLOW );
  setcolor(BLACK);
  rectangle( 645 - dx,  350 - dy ,  645 + dx, 350 + dy );
  setcolor(WHITE );
  
  nI = atoi( cad ); 
  
  return( nI );
}

void iniArrayBoton( A_BOTON *vB, int nB)
{ 
   vB->numBot = 0;

   for( int i = 0; i < nB; i++)
   {
       strcpy( vB->vectorB[i].texto, " " );
       vB->vectorB[i].x1 = 0;
       vB->vectorB[i].y1 = 0;
       vB->vectorB[i].x2 = 0;
       vB->vectorB[i].y2 = 0;
   }
}

void insBoton(A_BOTON *vB, char *cad, int X1, int Y1, int X2, int Y2 )
{
    strcpy( vB->vectorB[vB->numBot].texto, cad);
    vB->vectorB[vB->numBot].x1 = X1;
    vB->vectorB[vB->numBot].y1 = Y1;
    vB->vectorB[vB->numBot].x2 = X2;
    vB->vectorB[vB->numBot].y2 = Y2;
    vB->numBot ++;
}

void imprimeBoton( A_BOTON vB )
{
  setcolor(WHITE);
  settextstyle( 8, 0 , 1 );
  for( int i = 0; i < vB.numBot; i++)
  {  
    rectangle(vB.vectorB[i].x1, vB.vectorB[i].y1, vB.vectorB[i].x2, vB.vectorB[i].y2 );
    outtextxy( vB.vectorB[i].x1+16, vB.vectorB[i].y1+10, vB.vectorB[i].texto ); 
  }
}

int checaBoton( A_BOTON vB )
{
  int i, opc, coorX, coorY, band = 0;
  
  do
  {
      coorX = mousex();
      coorY = mousey();
      
      // Se buscan las coordenadas del mouse en algunos de los botones
      for( i = 0; i < vB.numBot; i++ )
          if( coorX > vB.vectorB[i].x1 && coorX < vB.vectorB[i].x2 && coorY > vB.vectorB[i].y1 && coorY < vB.vectorB[i].y2 )
               break;
      
      if( ismouseclick( WM_LBUTTONDOWN) && i < vB.numBot )
      {
           opc = i;
           band = 1;
      }else
           if( i < vB.numBot )
           {
              setcolor( 4 );
              rectangle( vB.vectorB[i].x1,vB.vectorB[i].y1,vB.vectorB[i].x2,vB.vectorB[i].y2 ); 
           }else
                imprimeBoton( vB );
  
    clearmouseclick(WM_LBUTTONDOWN );
    
    delay(1);
     
  }while(!band ); 
  
  return( opc );
}

void eliminacionGauss_GaussJordan( float **m , int opc, int X, int Y, int nR, int nC )
{
  int i, j, x, z, k;
  float num;
  char cadAux[100];
   
  x = X;
  k = Y;
   
  for( i = 0; i < nR ; )
     if( *(*( m + i ) + i ) == 0 )
       intercambiaRenglon( m,i, X, Y, nR,nC);
      else
       {
         if( *(*( m + i ) + i ) != 1 )              
         {
           num = *(*( m + i ) + i );
           
           z = X;           
           
           for( j = i; j < nC; j++, z += 120)
           {
                *(*( m + i ) + j) /= num; 
                
               sprintf(cadAux, "%.2f", m[i][j]);
               imprimeRenglon( cadAux, z, Y, i, j);
              
          }
       }
       if( opc == 7 && i >= 1 )
                eliminaRenglon( m, 0, i, i, X, k-44, nC );
            
        eliminaRenglon( m, i + 1, nR, i, X, Y, nC); 
        i++;
        
        Y+=44, X+=120;
      }
  
  if( opc == 6 ) 
      sustitucionInversa( m, nR);
}

void intercambiaRenglon( float **m, int i, int x, int y, int nR, int nC )
{
  int j, indice, yAux = y;
  float numAux, mayor = -9999;
  char cad[40];
  
  for( j = i+1; j < nR; j++)
     if( *(*( m + j ) + i) != 1 )
     {
         if( *(*( m + j ) + i ) > mayor )
         {
             mayor = *(*( m + j ) + i ); 
             indice = j;
          }
     }else
         {
           indice = j;
           break;
         }
   for( int k = 0; k < indice; yAux += 44, k++ );
   
   for( j = i; j < nC; j++, x+=120 )
   {
     numAux =  *(*( m + i ) + j );
     *(*( m + i ) + j ) = *(*( m + indice ) + j );
      sprintf(cad, "%.2f", *(*( m + i ) + j ) );
     imprimeRenglon( cad, x, y, -1, 1 );
     
     *(*( m + indice ) + j ) = numAux;
      sprintf(cad, "%.2f", *(*( m + indice ) + j )  );
      imprimeRenglon( cad, x, yAux, -1, 1 );
  }
}

void eliminaRenglon( float **m, int z, int k , int i, int x, int y, int nC )
{
   int j;
   float num;
   char cadAux[40];
   int X = x;
   
   y+=44;
   
   for(;  z < k;  z++, y+=44, x= X )
      if( *(*( m + z ) + i ) != 0 )
      {
         num  = *(*( m + z ) + i ) * -1;
   
         for( j = i; j < nC; j++, x+=120 )
          {
              *(*( m + z ) + j ) = num * (*(*(m+i)+j) ) + *(*( m + z ) + j );
              
              sprintf(cadAux, "%.2f", m[z][j]);
              imprimeRenglon( cadAux, x, y, z, j );
          }
   }
}

void sustitucionInversa( float **m, int n )
{
  int i, j;
  
  for( i = n-2; i >= 0; i-- )
    for( j = n-1; j > i; j-- )
         m[i][n] -= m[i][j] * m[j][n];
  
  puts("\n\n\n" );       
  for( i = 0; i < n; i++)
       printf(" %f ", m[i][n] );
}

void imprimeRenglon(char *cad, int x, int y, int i , int j  )
{
   if( activacion )
   {
      setfillstyle(SOLID_FILL, BLACK );
      floodfill( x + 5, y + 5, GREEN );
   
      setcolor(WHITE);
   
      settextstyle( 8, 0, 1  );
     
      if( i == j && !strcmp( cad, "1.00" ) )
          setcolor( LIGHTBLUE);
   
      if( strlen(cad) == 4 )
        outtextxy( x + 35, y + 7, cad );
      else
         outtextxy( x + 20, y + 7, cad );
       
      retraso(500);
  }
}

void leerSistema( float **m , int x, int y, int nR, int nC)
{
   char cad[200];
   int i, j, X = x;
   float coef;
   
   settextstyle( 8, 0, 1  );
   
   for( i = 0; i < nR; i++, X = x, y+=44)
     for( j = 0; j < nC; j++, X+= 120 )
       {
         lee_texto( X + 45, y + 7, cad );
         coef = atof(cad);
        
         m[i][j] = coef;
       } 
}

void imprimePlantilla(int incog, int *coorX, int *coorY, int *cY)
{
  int X, dY, dX, x, y, x2, y2, Y, sX, sY, i, j;
  
  printf(" in: %d ", incog );
  
  dY = 34;
  dX = 110;
  sX = 10;
  sY = 10;
  
  x =  645 - ((dX/2 + sX/2)*incog + dX/2); X = x;
  y =  370 - (( dY/2 + sY/2)*incog + dY/2 ); Y = y;
  x2 = 645 + ((dX/2 + sX/2)*incog + dX/2);
  y2 = 327 + (( dY/2 + sY/2)*incog + dY/2 );
  
  setlinestyle( 0, 0, 3);
  rectangle( x-10, y-10, x2 + 10, y2+ 10 );  
  setcolor( BLACK );
  rectangle( x+15, y-10, x2 - 15, y2+ 10 );   
  setlinestyle( 0, 0, 1);
  
  setcolor( GREEN );
  
  for( i = 0 ; i < incog; i++, Y+= dY + sY, X = x) 
     for( j = 0; j < incog+1; j++, X += dX + sX )
            rectangle( X, Y , X + dX,  Y + dY );      

   *coorX = x;
   *coorY = y;
   *cY = Y;
}

void imprimeSolucion( float **m, int nR )
{
  int x, y;
  char cad[100];
  char cad2[10];
  
  x = 50; y = 608;
  
  settextstyle(10, 0, 1 );
  outtextxy( x - 10, y-30, " Soluciones: " );
  settextstyle(8, 0, 1 );
  
  for( int i = 0; i < nR; i++, x+= 130 )
  {
    cad[0] = '\0';
    sprintf( cad2, "%d", i+1 );
    strcat( cad,"x" );
    strcat( cad,cad2 );
    strcat( cad," = " );
    setcolor(2);
    outtextxy( x, y, cad ); 
     
    sprintf(cad2, "%.2f", m[i][nR] );
    setcolor(15);
    outtextxy( x + 50 , y, cad2 ); 
  }
  
  settextstyle( 10, 0, 1 );
}

void eliminaMatriz( float **m, int nR )
{
  for(int i = 0; i < nR; i++ )
     free( &m[i][0] );
  
  free( m );
}
   
/************************************************** Fin de los metodos Matriciale *******************************************************/

void eliminaTablaDeDatos( TABLA *t )
{
  NUME aux;
  int i;
  
  for( i = 0; i < t->n; i++ )
  {
     aux = t-> vectorNum[ i ];
     
     for(; aux; free( aux ), aux = aux -> sigNum );
  }
}

void interfaceDeSENL( TABLA t , int x, int y, int x2,int dX, int nCol, char *exp, char *nameMet, float raiz, int nIter)
{ 
   char cad[50];
   int  x1, y1;
  
   x1 = 870; 
   y1 = 570;
  
   rectangle( x1 - 5, y1 - 10, x1 + 380, y1 + 30 ); 
      
   settextstyle( 4, 0, 1 );
   setcolor(WHITE );
   outtextxy(x2, 130, nameMet );
   setcolor( WHITE );
   outtextxy( 40, 180, " f( x ) = " ); 
   setcolor( GREEN );
   outtextxy( 150, 180, exp );
  
   imprimeTabla( x, y, dX, nCol);
   imprimeDatosTabla( t );
   
   settextstyle( 8, 0, 1 );
   
   outtextxy( x1, y1, " Raiz = " ); 
   outtextxy( x1 + 170, y1, " Iteracciones = " );  
   
   setcolor( WHITE );
   
   sprintf( cad, "%.4f", raiz );
   outtextxy( x1 + 85, y1, cad ); 
   sprintf( cad, "%d", nIter );
   outtextxy( x1 + 345, y1, cad ); 
}

void imprimeTabla( int x, int y, int dX,int nL )
{
  int i, x1, y1;
  
  x1 = x + 50; y1 = y + 10;
  
  setlinestyle( SOLID_LINE,0, 1);
  
  rectangle( x, y, x + dX, 600 );
  limpiaPantalla( x + 50, y + 40, GREEN ); 
  
  line( x + 10, y + 40, x + dX -10, y + 40 );
  
  for( i = 0; i < nL; x1 += 102, i++ )
      line( x1, y1, x1, 590 ); 
}

void imprimeDatosTabla( TABLA t )
{
  NUME aux;
  
  settextstyle( 8, 0, 1 );
  setcolor(WHITE );
       
  for( int i = 0; i < t.n; i++ )
  {
      aux = t.vectorNum[i];
      
      while( aux )
      {
        outtextxy( aux -> x1, aux -> y1, aux -> num );
        aux = aux -> sigNum;
      }
  }
}

int leerDatos( char *exp )
{
   int x1, y1, nIter, tam;   
   char cad[10];
   
   setlinestyle( SOLID_LINE,0, 4);
   
   setcolor( BLUE  );
   rectangle( 650 - Dx, 385 - Dy, 650 + Dx, 385 + Dy  );
   limpiaPantalla(  650 , 385, BLUE ); 
   
   setcolor( WHITE  );
   outtextxy( 400, 130, " sen(x) cos(x) tan(x) log(x) ln(x) e(x) raiz(x) " );
   setcolor( GREEN );
   outtextxy(650 - Dx + 10, 385 - Dy + 60, " f(x) =  " ); 
   leer( " Introduzca una expresion Algebraica ", exp );

   tam = strlen( exp );
   printf("tamExp = %d", tam );
   
   verificaExpresion( exp );
   
   setcolor( GREEN );
   outtextxy(650 - 400 + 170, 385 - 150 + 60, "                                             " );
   outtextxy(650 - Dx + 10, 385 , " f(x) = " ); 
   setcolor( WHITE );
   outtextxy(650 - 400 + 170, 385 , exp );
   
   setcolor( GREEN );
   outtextxy(650 - Dx + 10, 385 - Dy + 60, " Iter = " ); 
   leer( " Introduzca el No. de  Iteraciones            ", cad);
   
   nIter = atoi( cad );
   
   setcolor( GREEN );
   outtextxy(650 - Dx + 10, 385 - Dy + 60, " Tol = " ); 
   leer( " Introduzca una Tolerancia            ", cad );
    
   tolerancia = atof(cad); 
  
   return( nIter );
}

void leer( char * men, char *cad )
{
  int Dx, Dy;
  
  Dx = 400; Dy = 150;  
  
  setcolor( WHITE );
  outtextxy(650 - 200, 385 - Dy + 20, men ); 
  lee_texto( 650 - Dx + 170, 385 - Dy + 60, cad );
}

float iteracionSimple( char *exp, int nIter, TABLA *t, int *opc )
{
  float  Xn, error, vI, gX;
  int  i, x, y;
  char cad[10];
  
  error = 100;
  
  delay(200 );
  
  setcolor(GREEN);
  outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xo = " ); 
  leer( " Introduzca un valor inicial              ", cad );
  
  *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 );
  
  if( *opc == 1 )
  {    
       Xn = atof( cad ); 
       i = 0; x = 280; y = 285;
       
       while( error > tolerancia && i < nIter )
       {  
          gX = evaluaExp( exp, Xn );
          
          sprintf( cad, "%d", i ); insNodoNum( &t -> vectorNum[t -> n], cad, x, y ); 
          x += 50;
          sprintf( cad, "%.4f", Xn ); insNodoNum( &t -> vectorNum[t -> n ], cad, x, y ); 
          x += 100;
          
          sprintf( cad, "%.4f", gX );insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); 
          x += 100;
          
          error = gX - Xn;
          
          if( error < 0 )
             error *= -1;
          
          sprintf( cad, "%.4f", error ); insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); 
          
          if( error > tolerancia )
              Xn = gX; 
          
          i++; y += 22; x = 280; t -> n++;
      }
    }
   
   return( Xn );
    
}
float biseccion( char *exp, TABLA *t, int nIter , int *opc)
{
 int  i, x,y, band;
 float Xi, Xd, Xn, vXn, vXi, vXd;
 char cad[10];
 
 band = i = 0;
 
 do
 {
   setcolor(GREEN);
   outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xi = " ); 
   leer( " Introduzca un valor para Xizq              ", cad );
   
   Xi = atof( cad );
   
   setcolor(GREEN);
   outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xd = " ); 
   leer( " Introduzca un valor para Xder              ", cad );
   
   Xd = atof( cad );
      
   if( evaluaExp( exp, Xi ) * evaluaExp( exp, Xd ) < 0 )
   {
    *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 ); 
    
    if( *opc == 1 )
    {
      x = 70; y = 315;   
      
      do
      {
        vXi = evaluaExp( exp, Xi );
        vXd = evaluaExp( exp, Xd );
        Xn = (Xi + Xd)/2;
        vXn = evaluaExp( exp, Xn );
        
        printf(" %d  %.4f  %.4f  %.4f  %.4f  %.4f  %.4f", i, Xi, vXi, Xd, vXd, Xn, vXn );
        
        sprintf( cad, "%d", i );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 50;
        
        sprintf( cad, "%.4f", Xi );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXi );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", Xd );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXd );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
         
        sprintf( cad, "%.4f", Xn );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXn );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        if( vXn < 0 && vXi < 0 )
           Xi = Xn;
         else
            if( vXn < 0 && vXi > 0 )
                Xd = Xn;
            else
               if(  vXn > 0 && vXi > 0 )
                   Xi = Xn;
               else
                   Xd = Xn;
       
       if( vXn < 0 )  
          vXn *= -1;
        
       sprintf( cad, "%.4f", vXn );
       insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
           
        printf(" %.4f\n", vXn );     
        
        i++; y += 22; x = 70; t -> n++;
      
      }while( vXn >= tolerancia && i < nIter );
      
      band = 1;
    }
   
   }else
    {    setcolor( WHITE );
         outtextxy(650 - 200, 385 + 50, " Valores no Permisibles, vuelva a intentar " );
         delay( 1400 );
         outtextxy(650 - 200, 385 + 50, "                                               " );
    }
 }while( !band );
 
 if( vXn <= tolerancia )
   {
           printf("\n Raiz = %.4f\n\n", Xn );  
           sprintf( cad, "%.4f", Xn ); 
           outtextxy( 900, 600, cad  );
             
   }
  return( Xn );
}

float regulaFalsi( char *exp,TABLA *t, int nIter, int *opc )
{
 int  i, x,y, band;
 float Xi, Xd, Xn, vXn, vXi, vXd;
 char cad[10];
 
 band = i = 0;
 
 do
 {
   setcolor(GREEN);
   outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xi = " ); 
   leer( " Introduzca un valor para Xizq              ", cad );
   
   Xi = atof( cad );
   
   setcolor(GREEN);
   outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xd = " ); 
   leer( " Introduzca un valor para Xder              ", cad );
   
   Xd = atof( cad );
      
   if( evaluaExp( exp, Xi ) * evaluaExp( exp, Xd ) < 0 )
   {
    *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 );
    
    if( *opc == 1 )
    {
      x = 70; y = 315;   
      
      do
      {
        vXi = evaluaExp( exp, Xi );
        vXd = evaluaExp( exp, Xd );
        Xn = (Xi * vXd - Xd * vXi )/( vXd - vXi );
        vXn = evaluaExp( exp, Xn );
        
        //printf(" %d  %.4f  %.4f  %.4f  %.4f  %.4f  %.4f", i, *vIzq, vXi, *vDer, vXd, Xn, vXn );
        
        sprintf( cad, "%d", i );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 50;
        
        sprintf( cad, "%.4f", Xi );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXi );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", Xd );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXd );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
         
        sprintf( cad, "%.4f", Xn );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        sprintf( cad, "%.4f", vXn );
        insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
        
        if( vXn < 0 && vXi < 0 )
           Xi = Xn;
         else
            if( vXn < 0 && vXi > 0 )
                Xd = Xn;
            else
               if(  vXn > 0 && vXi > 0 )
                   Xi = Xn;
               else
                   Xd = Xn;
       
       if( vXn < 0 )  
          vXn *= -1;
        
       sprintf( cad, "%.4f", vXn );
       insNodoNum( &t -> vectorNum[ t -> n ], cad, x, y ); x += 100;
           
        printf(" %.4f\n", vXn );     
        
        i++; y += 22; x = 70; t -> n++;
      
      }while( vXn >= tolerancia && i < nIter );
      
      band = 1;
    }
   
   }else
    {    setcolor( WHITE );
         outtextxy(650 - 200, 385 + 50, " Valores no Permisibles, vuelva a intentar " );
         delay( 1400 );
         outtextxy(650 - 200, 385 + 50, "                                               " );
    }
 }while( !band );
 
 if( vXn <= tolerancia )
   {
           printf("\n Raiz = %.4f\n\n", Xn );  
           sprintf( cad, "%.4f", Xn ); 
           outtextxy( 900, 600, cad  );
    }
  
  return( Xn );  
}

float secante( char *exp, TABLA *t, int nIter, int *opc)
{
  float Xn,vXn, x1, x2, vX1,vX2;
  int x,y,band,j,i = 0;
  char cad[10];
  
  band = 0; 
  
  do
  { 
    x = 280; y = 290;
    
    setcolor(GREEN);
    outtextxy(650 - Dx + 10, 385 - Dy + 60, "  X1 = " ); 
    leer( " Introduzca un valor para x1              ", cad );
  
    x1 = atof( cad );
  
    setcolor(GREEN);
    outtextxy(650 - Dx + 10, 385 - Dy + 60, "  X2 = " ); 
    leer( " Introduzca un valor para x2             ", cad );
   
    x2 = atof( cad );
    
    vX1 = evaluaExp( exp, x1 );
    vX2 = evaluaExp( exp, x2 );
    
    if(  (vX1 > 0 && vX2 >0 ) || (vX1 < 0 && vX2 < 0 ) )
    {
       *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 );
       
       if(*opc == 1  ) 
       {
          insRengTabla( t,  &x, &y, &i, x1, vX1 ); y += 22; x = 280;
          insRengTabla( t,  &x, &y, &i, x2, vX2 ); y += 22; x = 280;
          
          do
          {   
            Xn = x1 - ( vX1 * ( x1 - x2) ) / ( vX1 - vX2 );
            vXn = evaluaExp( exp, Xn );
            
            insRengTabla( t,  &x, &y, &i, Xn, vXn );
            
            if( vXn < 0 )
                vXn = vXn * -1;
                   
            x1 = x2; x2 = Xn; vX1 = evaluaExp( exp, x1 ); vX2 = evaluaExp( exp, x2 );
            
            y += 22; x = 280;
          
          }while( vXn >= tolerancia && i < nIter ); 
          
          band = 1;
       }
   }else
       {
         setcolor( WHITE );
         outtextxy(650 - 200, 385 + 50, " Valores no Permisibles, vuelva a intentar " );
         delay( 1400 );
         outtextxy(650 - 200, 385 + 50, "                                               " );
       }
  }while(!band);
  
  if( vXn <= tolerancia )
       printf("\n Raiz = %.4f\n\n", Xn );  
  
  return( Xn ); 
}

float newtonRaphson( char *exp, TABLA *t, int nIter, int *opc )
{
  float aux,Xo, Xn, vXn, Xi, dXn;
  int  x, y, h , i = 0;
  char cad[10];
  x = 260; y = 290;
  
  setcolor(GREEN);
  outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xo = " ); 
  leer( " Introduzca un valor inicial              ", cad );
  
  Xo = atof( cad );
  
  *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 );
 
  if( *opc == 1  )
    do
    {
       Xn = Xo;
       vXn = evaluaExp( exp, Xn );
       
       aux = vXn; 
       
       if( aux < 0) aux *= -1;
       
       if( aux > tolerancia )
       {
           dXn = calculaPriDer( exp, Xn ); 
           insRengTabla( t,  &x, &y, &i, Xn, vXn ); 
       
           sprintf(cad, "%.4f", dXn );
           insNodoNum( &t -> vectorNum[ t -> n-1 ], cad, x, y );
       
           Xo = Xn - vXn/dXn;
       }else
            insRengTabla( t,  &x, &y, &i, Xn, vXn ); 
        
       if( vXn < 0)
         vXn *= -1;
       
       y += 22; x = 260;
    
    }while( vXn >= tolerancia && i < nIter ); 
 
   if( vXn <= tolerancia )
       printf("\n Raiz = %.4f\n\n", Xn );  
   
   return( Xn );
}

float newtonRaphsonMejorado( char *exp, TABLA *t, int nIter, int *opc )
{
  float aux,Xo, Xn, vXn, Xi, dXn, ddXn;
  int  x, y, h , i = 0;
  char cad[10];
  x = 260; y = 290;
  
  setcolor(GREEN);
  outtextxy(650 - Dx + 10, 385 - Dy + 60, "  Xo = " ); 
  leer( " Introduzca un valor inicial              ", cad );
  
  Xn = atof( cad );
  
  *opc = botonSel("IR   A   S O L U C I O N "," IR A MENU", 450, 430, 600, 490 );
 
  if( *opc == 1  )
    do
    {
       vXn = evaluaExp( exp, Xn );
       
       aux = vXn; 
       
       if( aux < 0) aux *= -1;
       
       if( aux > tolerancia )
       {
           dXn = calculaPriDer( exp, Xn ); 
           ddXn = calculaSegDer( exp, Xn );
         
           insRengTabla( t,  &x, &y, &i, Xn, vXn ); 
           
           sprintf(cad, "%.4f", dXn );
           insNodoNum( &t -> vectorNum[ t -> n-1 ], cad, x, y ); x += 100; 
           
           sprintf(cad, "%.4f", ddXn );
           insNodoNum( &t -> vectorNum[ t -> n-1 ], cad, x, y );
           
            Xn = Xn - ( vXn/( dXn - vXn/(2*dXn)* ddXn ) );
       }else
            insRengTabla( t,  &x, &y, &i, Xn, vXn ); 
        
       if( vXn < 0)
         vXn *= -1;
       
       y += 22; x = 260;
    
    }while( vXn >= tolerancia && i < nIter ); 
 
   if( vXn <= tolerancia )
       printf("\n Raiz = %.4f\n\n", Xn );  
   
   return( Xn );
}

float calculaPriDer( char *exp, float x)
{
  return( (evaluaExp( exp, x + 0.01 ) - evaluaExp( exp, x - 0.01  ) )/0.02 );
}

float calculaSegDer( char *exp, float x)
{
  return( (evaluaExp( exp, x + 0.02 ) - 2 * evaluaExp( exp, x ) + evaluaExp( exp, x - 0.02 )) / 0.0004);
}

void insRengTabla( TABLA *t, int *x, int *y, int *i, float X, float vX )
{
   char cad[10];
   
   sprintf( cad, "%d", *i ); insNodoNum( &t -> vectorNum[t -> n], cad, *x, *y ); 
   *x = *x + 50;
   sprintf( cad, "%.4f", X ); insNodoNum( &t -> vectorNum[t -> n], cad, *x, *y ); 
   *x = *x + 100;
   sprintf( cad, "%.4f", vX ); insNodoNum( &t -> vectorNum[t -> n], cad, *x, *y ); 
   *x = *x + 100;
   
   if( vX < 0 )
       vX *= -1;
   
   sprintf( cad, "%.4f", vX ); insNodoNum( &t -> vectorNum[t -> n], cad, *x, *y );
   *x = *x + 100; 
   
   *i = *i + 1; t-> n++;
}

int creaNodoNum( NUME *l, char *cad, int x, int y )
{
  int res = 0;
  
  if( *l = (NUME) malloc (sizeof( struct regNum ) ) )
  {
     (*l) -> x1 = x;
     (*l) -> y1 = y;
     (*l) -> sigNum = NULL;
     strcpy( (*l) -> num , cad  );
     
     res = 1;
  }
  
  return( res );
  
}

int insNodoNum( NUME *l, char * cad, int x, int y)
{
  NUME aux, nuevo;  
  int res = 0;
  
  if( creaNodoNum( &nuevo, cad, x, y ) )
  {
    puts( nuevo -> num );  
    aux = *l;
    
    for(; aux && aux -> sigNum; aux = aux -> sigNum );
    
    if( !*l ) 
        *l = nuevo;
    else
       aux -> sigNum = nuevo;
    res = 1;
  
  }
  
  return( res );  
}

void iniTabla( TABLA *t )
{
   t -> n = 0;
   
   for( int i = 0; i < 50; i++ )
       t -> vectorNum[i] = NULL;
}

int botonSel( char *cad1, char *cad2, int x1, int y1, int x2, int y2 )
{ 
  setlinestyle( SOLID_LINE,0, 2);
  
  char cadena[50];
  int corX, corY, bandera = -1;
  int dX, band = 0;
  
  dX = 60;
  
  settextstyle( 11 , 0 , 1 );
  
  outtextxy( x1 + 10, y1 + 10, cad1 );
  outtextxy( x2 + dX + 26 , y1 + 10 , cad2 );
  
  do
  {
    corX = mousex();
    corY = mousey();
    
    if( corX > x1 && corX < x2 && corY > y1 && corY < y2 )
    {   
        setcolor( GREEN );
        setlinestyle( 0, 0, 6 );       
        rectangle( x1, y1 , x2, y2 );
    
         if( ismouseclick( WM_LBUTTONDOWN) )
             band = 1;
     }else
       {
          setcolor( BLACK );
          setlinestyle( 0, 0, 6 );       
          rectangle( x1, y1 , x2, y2 );
        
          setlinestyle( 0, 0, 2 );  
          setcolor( WHITE );       
          rectangle( x1, y1 , x2, y2 );
        
          if( corX > x2 + dX && corX < x2 + dX +( x2 - x1 ) && corY > y1 && corY < y2 )
          {   
               setcolor( GREEN );       
               setlinestyle( 0, 0, 6 ); 
               rectangle( x2 + dX, y1 , x2 + dX +( x2 - x1 ), y2 );  
               
               if( ismouseclick( WM_LBUTTONDOWN) )
                   band = 2;
          }else
              {  
                 setcolor( BLACK );
                 setlinestyle( 0, 0, 6 );  
                 rectangle( x2 + dX, y1 , x2 + dX +( x2 - x1 ), y2 );  
               
                 setcolor( WHITE );       
                 setlinestyle( 0, 0, 2 );
              rectangle( x2 + dX, y1 , x2 + dX +( x2 - x1 ), y2 );  
               }
           }
  
   clearmouseclick(WM_LBUTTONDOWN );
   delay(1);  
  
  }while ( band != 1 && band != 2 ); 
  
  setlinestyle( SOLID_LINE,0, 1);
  
  return( band );
}

void lee_texto(int x,int y, char cadena[])
{
 char tecla, var;     
 int contador=0;
 cadena[0]='\0';
 
 do{
      //Si no se presiona una tecla, se imprimira un guion definidamente
      do{  //párpadeo
			 setcolor(15);
			 outtextxy(x+textwidth(cadena),y,"_");
			 retraso(50);
			 setcolor(0);
			 outtextxy(x+textwidth(cadena),y,"_");
			 retraso(50);
			 setcolor(15);
      }while(!kbhit());
     
      tecla = getch();
     
      if(tecla==0)  // si es código extendido
         tecla=getch();
        if(tecla==8 && contador > 0)  // se presion¢ <backspace>
			{
				 setcolor(BLACK);
	 			 outtextxy(x,y,cadena);  // se borra en la pantalla
				 cadena[--contador]='\0';  //se borr¢ £ltimo caracter del arreglo
				 setcolor( WHITE );
				 outtextxy(x,y,cadena);
			}
		 else
			{  
              if(tecla!=13)
              {  
				 cadena[contador++]=tecla;
				 cadena[contador]='\0';
				 outtextxy(x,y,cadena);
              }
            }    
  }while(tecla!=13); 
}

void retraso(int ms)
{
  clock_t i,j;
 
  i=clock();
 
  do
  {
    j=clock();
  }while((j-i) < ms);  
}

void dibujaLinea(int aColor, int x1, int y1, int x2, int y2)
{
  setcolor( aColor );   
  line( x1, y1, x2, y2 );
}

void limpiaPantalla(int x, int y, int color)
{
  setfillstyle(1, BLACK );   
  floodfill( x,y, color );
}

void dibujaRectangulo( MENU aux, int color )
{
    setcolor( color );
    rectangle( aux -> x1, aux -> y1, aux -> x2 , aux -> y2 );
}

void dibujaNombre( MENU aux, int color )
{
    setcolor( color );
      settextstyle( 8, 0, 1 );
    outtextxy( aux -> x1+10, aux -> y1+15, aux -> name );
}

void funcionToken( char *infija, char *token, int *i )
{
   int j, k, band = 1;
   
   j = 0;
   
   while( *i < strlen( infija ) && band )
   {
    
    if( infija[ *i ] != 32 )
     { 
       token[j] = infija[ *i ];
       
       if( infija[*i] == '-')
       {       
          if( isdigit( infija[*i + 1 ] ) )
          {
             if( *i )
              for( k = *i - 1; k >= 0 && band; k-- )//Este ciclo es para checar si el operador (-) es uniario o binario 
                   if( infija[ k ] != 32 ) 
                   {
                       if( infija[k] == ')' || isdigit( infija[k] ) || infija[k] == 'x' )
                           band = 0;
                       
                       k = 0;       
                   }      
          }else
             band = 0;
       }else
        {
          if( isdigit( infija[*i] ) || infija[*i] == 46 || isalpha( infija[*i] ) )
          {
             if( !isdigit( infija[*i + 1]))
                if( !(infija[*i + 1] == 46) )
                     if( !isalpha( infija[*i + 1]))
                             band = 0;
         
          }else
                band = 0;
       }
       
       j++;
      
      }  
     
     *i = *i + 1;
   }
   
   token[ j ] =  '\0';  
}

int tipoToken( char *toker )
{
  int tipo = 0;
 
 if( toker[0] != '_' )
    if( isdigit(  *toker ) || ( toker[0] == '-' && strlen( toker ) > 1 ) || toker[0] == '.' )
        tipo = 1; 
    else
       if( !strcmp( toker, "(" ) )
          tipo = 2;
       else
         if( !strcmp( toker, ")" ) )
             tipo = 3;
         else
            if( !strcmp( toker, "x" ) )
                tipo = 4;
            else
                if( isalpha(toker[0]) )
                   tipo = 5;
                else
                   tipo = 6;
        
  return( tipo );
}

float evaluaExp( char *inFija, float Xo )
{
  char posFija[ T ];
  float  res;
  
  convPosfija( inFija, posFija );
  res = evaluaPosfija( posFija , Xo);
  
  return( res );
}

void verificaExpresion( char * infija )
{  
  int i, pI, pD, cont, resOpe, nNum , nOper, band2 ,band = 1;
  char token[10];
  
  setcolor( BLUE );
  line( 650 - 330, 355, 650 + 330, 355 );
         
  do
  {
    nNum = nOper = cont = pI = pD = i = 0;
    resOpe = band2 = 1;
    
    while( i < strlen( infija ) )
    {
      funcionToken( infija, token, &i );
      
      switch( tipoToken(token) )
      {
       case VAR :  nNum ++; break;      
       case P_IZQ: pI++; break;
       case P_DER: pD++; break;
       case FUNCION: analifun( token, &cont ); break;
       case NUM:    
                    nNum++;
                    
                    for( int k = 0; k < strlen( token ); k++ )
                    if( isalpha( *(token + k ) ) )
                    {
                        if( *(token + k) != 'x' )
                         {  
                            printf("\n El termino \"%s\" es invalido\n", token);
                            /*outtextxy(650 - 400 + 40, 385 + 50, " El termino " );
                            outtextxy(650 - 400 + 40, 385 + 70, token );
                            outtextxy(650 - 400 + 40, 385 + 50, "  " );    
                              */
                        }else
                          {
                             printf("\n El termino \"%s\" es incorrecto separe la x con el operador \" * \" \n", token);    
                          }
                        k = strlen(token) - 1;
                        band2 = 0; 
                    }
                    
                    break;
       case OPER_B: nOper++;
      }
    }
    
    resOpe = checaOper( nOper , nNum );
    
    if( analiParent( pI , pD ) && !cont && band2 && resOpe )
    {
       band = 0;
    }else
       {
         setcolor( GREEN );
         outtextxy(650 - 320, 385 , " f(x) = " ); 
         setcolor( RED );
         outtextxy(650 - 400 + 170, 385 , "                                             " );
         outtextxy(650 - 400 + 170, 385 , infija );
         
         //printf("\n\n Corrija la expresion.\n\n f(x) = " );
       
         setcolor( WHITE );
         outtextxy(650 - 200, 385 + 50, " Expresion invalida, Corrijala " );
         delay( 1400 );
         
         outtextxy(650 - 200 , 385 + 50, "                                           " );
         outtextxy(650 - 400 + 170, 385 - 150 + 60, "                                             " );
         lee_texto( 650 - 400 + 170, 385 - 150 + 60, infija ); 
         //fflush( stdin );
         //gets( infija );
       }
  
  }while(band);
  
  if( !band )
     limpiaPantalla( 650, 385, BLUE );
}

int checaOper( int nOpe, int nNum )
{
  int res = 1;
  
  if( nOpe == nNum ) 
  {
    printf("\n Sobran un operador.");
    res = 0;
  }else
     if( nNum - nOpe > 1 )
     {
       printf("\n Faltan operadores");
       res = 0;
     }
     if( nOpe - nNum > 1 )
     {
       printf("\n Faltan numeros");
       res = 0;
     }   
  
  return( res );
}

void analifun( char *token, int *cont )
{
  int bandAux = 1;   
  
  if( !strcmp( token, "sen" ) );
      else
         if( !strcmp( token, "cos" ) );
         else
            if( !strcmp( token, "tan" ) );
            else
               if( !strcmp( token, "ln" ) );
               else
                 if( !strcmp( token, "log" ) );
                 else
                   if( !strcmp( token, "raiz" ) );
                     else
                      if( !strcmp( token, "e" ) );
                       else
                          { bandAux = 0, *cont = *cont + 1; }
  if( !bandAux )              
      printf("\n La funcion \" %s \" es incorrecta", token );
}

int analiParent( int pI, int pD )
{
   int res = 1;
   
   if( pI < pD )
   {  
       printf("\n Faltan %d parentesis abierto", pD - pI );
       res = 0; 
   }else
         if( pI > pD ) 
         {    
              printf("\n Faltan %d parentesis cerrado", pI - pD );
              res = 0;
         } 
   
   return( res );
}

float evaluaPosfija( char *posFija, float incog )
{
  PILA pila;
  char term[100], cad[100];
  int i = 0;
  float res, x, y;
  
  res = 0;
  
  iniPila( &pila );
  
  while( i < strlen( posFija ) )
  {
    
    funcionToken( posFija, term, &i );
    
    switch( tipoToken( term ) )
    {
      case VAR:  sprintf(cad, "%f", incog );
                 push( &pila, cad ); break;
               
      case NUM: push( &pila, term ); break;
      case OPER_B: pop( &pila, cad );
                  
                   x = atof( cad );
                
                   pop( &pila, cad );
                
                   y = atof( cad );
               
                   switch( term[0] )
                   {
                    case '+': res = y + x; break;
                    case '-': res = y - x; break;
                    case '*': res = y * x; break;
                    case '/': res = y / x; break;
                    default: res = pow(y,x); 
                   }
               
                   sprintf( cad, "%f", res );
                   push( &pila, cad );
                   
                   break;
      
      case FUNCION: pop(&pila, cad );
                   // puts( cad );
                    
                    x = atof( cad );
                    
                    if( !strcmp( term, "sen" ) )
                       res = sin(x);
                    else
                      if( !strcmp( term, "cos" ) )
                        res = cos(x);
                      else
                         if( !strcmp( term, "tan" ) )
                             res = tan(x);
                         else
                             if( !strcmp( term, "ln" ) )
                                 res = log(x);
                             else
                               if( !strcmp( term, "log" ) )
                                  res = log10(x);
                               else
                                 if( !strcmp( term, "e" ) )
                                    res = exp(x);
                                 else
                                    if( !strcmp( term, "raiz" ) )
                                       res = sqrt(x);
                         
                    sprintf( cad, "%f", res );
                    push( &pila, cad );
                   
     } 
  }
  
  if( pop( &pila, cad ) )
      res = atof( cad );
  
  return( res );
}


void convPosfija( char *infija, char *posfija )
{
   PILA pila;
   int tam, band,i = 0;
   char exp[T],cad[T],token[10];
   
   strcpy( exp, infija );
   
   iniPila( &pila );
   push( &pila , "(" );
   
   tam = strlen( exp );
   
   exp[ tam ] = ')';
   exp[ tam + 1 ] = '\0';
   posfija[0] = '\0';
   
   while( pilaVacia( pila ) && i < strlen( exp ) )
   {
      band = 1;
          
      funcionToken( exp, token, &i );
     
      switch( tipoToken( token ) )
      {
        case VAR:      
        case NUM: concatenaPosfija( posfija, token ); break;
        
        case P_IZQ: push( &pila, token ); break;
        
        case FUNCION:     
        case OPER_B:
                    do
                     {
                       pop( &pila, cad );
                       
                       if( tipoToken( cad ) == OPER_B || tipoToken( cad ) == FUNCION )
                       {
                           if( jerToken( cad ) >= jerToken( token ) )
                               concatenaPosfija( posfija, cad );
                           else
                              band = 0;
        
                       }else
                            band = 0;
                     
                     }while( band && pilaVacia(pila) );
                     
                     if( !band )
                        push( &pila, cad );
                     
                     push( &pila, token );
                     
                     break;  
        case P_DER: 
                    do
                    {
                      pop( &pila, cad );
                      
                      if( strcmp( cad , "(" ) )
                         concatenaPosfija( posfija, cad );
                      else
                         band = 0;
                      
                    }while( band && pilaVacia( pila ) );
                 
                    break;
      }
   }
}

int pilaVacia( PILA p )
{
  int res = 0;
  
  if( p.cima )
     res = 1;
  
  return( res ); 
}

void concatenaPosfija( char *posfija, char *ter )
{
   int tam;
   
   strcat( posfija, ter );
   
   tam = strlen( posfija );
   
   posfija[ tam ] = 95;
   posfija[ tam + 1] = '\0';
}


int jerToken( char *token )
{
  int jer = 0;
  
  if( !isdigit( token[0] ) )  
     if( ( isalpha( token[0] ) &&  token[0] != 'x') || !strcmp( token, "^" ) )
         jer = 4;
     else
        if( !strcmp( token, "*" ) || !strcmp( token, "/" ) )
          jer = 3;
        else
           if( !strcmp( token, "+" ) || !strcmp( token, "-" ) )
              jer = 2;
  
  return( jer );   
}

void iniPila( PILA *p )
{
   p -> cabPila = NULL;
   p -> cima = NULL;
}

int creaNodoL( LISTA *l, char *cad )
{
  int res = 0;
  
  if( *l = (LISTA)malloc( sizeof(struct reg) ) )
  {
     strcpy( (*l) -> info, cad );
     (*l ) -> sig = NULL;
     res = 1;
  }
  
  return( res );
}


int push( PILA *p , char *token )
{
  LISTA nodo, aux;
  int res = 0;
 
  if( creaNodoL( &nodo, token ) )
  {
    if( p -> cabPila == NULL )
      {
         p -> cabPila = nodo;
         p -> cima = nodo; 
     }else 
        {
           p -> cima -> sig = nodo;
           p -> cima = nodo;
        }
     
     res = 1;    
  }

  return( res );  

}

int pop( PILA *p, char *ter )
{
   LISTA aux, ant;
   int res = 0;
   
   for( aux = p -> cabPila; aux && aux != p -> cima; ant = aux, aux = aux -> sig );
   
   if( aux )
   {
     if( aux == p -> cabPila)
          p -> cabPila = p -> cima = NULL;
     else
         p -> cima = ant;
     
     strcpy( ter, aux -> info ); 
     
     free( aux );   
     
     res = 1; 
   }
   
   return( res );
}

void leerExp( char *infija )
{
   printf("\n Escriba una expresion( infija ) algebraica : \n\n f(x) = " );
   gets( infija);
}
