// cppbblib.c   version of 17-08-06   with error numbers

#include  <stdio.h>
#include <iostream>
#include  <string.h>
#include  <stdlib.h>


using namespace std;
typedef  int   COORD ;
typedef enum   SIDE  { Basura, Top, Right, Bottom, Left } SIDE ;

#define X 0
#define Y 1
#define   MAXSIZE  30 

void  ERROR( int m, char * s ) {  fprintf( stderr, "ERR %d %s\n", m ) ;  exit( 1 ) ;  }

#define RECEIVE_KILL			1, "More than one app"
#define INVALID_BOX_NUMBER		2, "Invalid box"
#define INVALID_DEFLECTOR_POSITION	3, "Invalid deflector"
#define INVALID_DEFLECTOR_SYMBOL	4, "Invalid symbol"
#define INVALID_BOX_SIZE		5, "Invalid size"
#define INVALID_INPUT_HOLE		6, "Invalid input hole"
#define ALARM				7, "ALARM"

char  box[MAXSIZE+2][MAXSIZE+2], boxi[MAXSIZE+2][MAXSIZE+2] ;  // only values: .,/,\,? 
COORD  Sb=100, S1 ;
long long   Count = 0 ;
char  Local ;
FILE * pin, * pout ;

char  ReceiveChar() {
char c ;

   c = getc( pin ) ;
   if(  c == '|'  ) ERROR( RECEIVE_KILL ) ;
   return c ;
   }


void  SendChar( char c ) {  fputc( c, pout ) ;  fflush( pout ) ;  }


void  Finalize( ) {
   if(  !Local  ) {  SendChar( 'F' ) ;
      		     fclose( pout ) ;
                     fclose( pin ) ;     }
   exit( 0 ) ;
   }

long long  HowManyThrows( ) {   return  Count ;  }

void  ResetBox( ) {
   if(  Local  )  memcpy( box, boxi, sizeof(box) ) ;
   else  SendChar( 'R' ) ;
   }

int  Initialize( int which ) {
   FILE *ar ;
   COORD i, j ;
   int k ;
   char c ;

   memset( boxi, sizeof(boxi), '.' ) ;

   if(  which < 0  ||  which > 15 )  ERROR( INVALID_BOX_NUMBER ) ;

   Local = !which ;
   if(  Local  ) {

//      ar = fopen( "blackbox.in", "r" ) ;
      ar = stdin;
	   fscanf( ar, "%d", &Sb ) ;
      if(  1 > Sb  ||  Sb > MAXSIZE  )   ERROR( INVALID_BOX_SIZE ) ;

      for(  i = 0  ;  i <= Sb+1  ;  i++  )
         for(  j = 0  ;  j <= Sb+1  ;  j++  )
            boxi[i][j] = '.' ;

      fscanf( ar, "%d", &k ) ;
      for(  ;  k >= 1  ;  k--  ) {
         fscanf( ar, "%d %d %c",  &j, &i, &c ) ;
         if(  i < 1  ||  i > Sb  ||  j < 1  ||  j > Sb  )   ERROR( INVALID_DEFLECTOR_POSITION ) ;
         if(  c != '/'  &&  c != '\\'  )   ERROR( INVALID_DEFLECTOR_SYMBOL ) ;
         boxi[i][j] = c ;
         }

      fclose( ar ) ;
      ResetBox( ) ;
      Count = 0 ;
      }
   else {
      pin = fopen( "/var/tmp/from_box", "r" ) ;
      pout = fopen( "/var/tmp/to_box", "w" ) ;

      SendChar( '{' ) ;
      c = ReceiveChar( ) ;
      if(  c != '}'  )   ERROR( ALARM ) ;

      SendChar( which + 32 ) ;
      c = ReceiveChar( ) ;
      Sb = c - 32 ;
      }
   S1 = Sb + 1 ;
   return Sb ;
   }


void  ToggleDeflectors( ) {
COORD   i, j ;
   if(  Local  ) {
      for(  i = 1  ;  i <= Sb   ;  i++  )
         for(  j = 1  ;  j <= Sb  ;  j++  )
                  if(  box[i][j] == '/'  )  box[i][j] = '\\' ;
            else  if(  box[i][j] == '\\'  )  box[i][j] = '/' ; 
      } 
   else   SendChar( 'I' ) ;
   }

long  throwBall( int hi, int si, int &ho, int &so ) {

int  av[2][5/*SIDE*/] = { { 27, 0, -1, 0, 1 }, { 84, -1, 0, 1, 0 } } ;

long   hits, i ;
COORD   p[2] ;
char   b, c ;

   if( si < 1   ||  si > 4  ||  hi < 1  ||  hi > Sb )   ERROR( INVALID_INPUT_HOLE ) ;

   if(  Local  ) {
      hits = 0 ;

      switch( si ) {
        case Top    : p[X] = hi      ; p[Y] = S1 ; break ;
        case Right  : p[Y] = S1 - hi ; p[X] = S1 ; break ;
        case Bottom : p[X] = hi      ; p[Y] = 0  ; break ;
        case Left   : p[Y] = S1 - hi ; p[X] = 0  ; break ;
         }

      do {  for(  b = X   ;  b <= Y  ;  b++  )  p[b] += av[b][si]  ;
            if(  box[S1-p[Y]][p[X]] != '.'  ) {
                hits++ ;
                si = ((si-1) ^ 1 ^ 2* ( box[S1-p[Y]][p[X]] == '\\' ) )+ 1 ;

   	   /*   coming from    Top     Right   Bottom  Left         1  2  3  4
	       	    /           Right   Top     Left    Bottom      2  1  4  3
	       	    \           Left    Bottom  Right   Top         4  3  2  1     */
                box[S1-p[Y]][p[X]] ^= '/' ^ '\\'  ;
                }
         }  while(  p[X]  &&  p[X] != S1  &&  p[Y]  &&  p[Y] != S1  ) ;

      switch(  si  ) {
        case Top:   case Bottom : ho = p[X] ;       break ;
        case Right: case Left :   ho = S1-p[Y] ;
        }
      so = ( (si-1) ^ 2 )+ 1 ;
      }
   else  {   SendChar( 'T' ) ;
             SendChar( si+64 )  ;
             SendChar( hi+32 )  ;
             so = ReceiveChar( ) - 64 ;
             ho = ReceiveChar( ) - 32 ;
             hits = 0 ;
             for(  i = 0  ;  i <= 3  ;  i++  ) {
                c = ReceiveChar() ;
                hits |= ( ( (long)( c - 32 ) ) << (6*i) ) ;
                }
          }
   Count++ ;
   return hits ;
   }


