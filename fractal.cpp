#include "fractal.h"
#define BANDW true
char arr[ARRSIZE][ARRSIZE][3];
//sets the values of arr
void init_fractal (){
  //arr =  malloc(sizeof(char)*ARRSIZE*ARRSIZE*3+1);
}


//updates arr, and pixbuf.
void update(Glib::RefPtr< Gdk::Pixbuf > pixbuf, int rowstride, int nchannels){
  char r = (char)rand()%256;
  char g = (char)rand()%256;
  char b = (char)rand()%256;
  if (rand()%7 ==0){
    r=0;b=0;g=0;
  }
  if (BANDW){
    r=b;
    g=b;
  }
  int setx = rand()%ARRSIZE;
  int sety = rand()%ARRSIZE;
  arr[setx][sety][0]=r;
  arr[setx][sety][1]=g;
  arr[setx][sety][2]=b;
  //symmetry is perdy
  arr[sety][ARRSIZE-1-setx][0]=r;
  arr[sety][ARRSIZE-1-setx][1]=b;
  arr[sety][ARRSIZE-1-setx][2]=g;
  //
  arr[ARRSIZE-1-setx][ARRSIZE-1-sety][0]=r;
  arr[ARRSIZE-1-setx][ARRSIZE-1-sety][1]=g;
  arr[ARRSIZE-1-setx][ARRSIZE-1-sety][2]=b;
  //
  arr[ARRSIZE-1-sety][setx][0]=r;
  arr[ARRSIZE-1-sety][setx][1]=b;
  arr[ARRSIZE-1-sety][setx][2]=g;

  //oi fuck
  for (int x1 =0; x1<ARRSIZE; x1++){
    for (int x2 =0; x2<ARRSIZE; x2++){
      for (int x3=0; x3<ARRSIZE; x3++){
	for (int y1 =0; y1<ARRSIZE; y1++){
	  for (int y2 =0; y2<ARRSIZE; y2++){
	    for (int y3=0; y3<ARRSIZE; y3++){
	      int offset = (x1*ARRSIZE*ARRSIZE + x2*ARRSIZE + x3)*nchannels + (y1*ARRSIZE*ARRSIZE + y2*ARRSIZE + y3)*rowstride;
	      guchar * pixel = &pixbuf->get_pixels()[ offset ];
	      addv3(pixel, arr[x1][y1], arr[x2][y2], arr[x3][y3]);
	      
	    }   
	    }
	 }
      }
    }
  }
}

void addv3( guchar* result, char * a, char * b, char * c ){
  for (int i =0; i<3; i++){
    result[i]=(a[i]+b[i]+c[i])%256;
    
  }
  if (!BANDW){
  result[2]=result[2]*6/5;
  }
}


void destroy(){
  free(arr);
}




