#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <winbgim.h>
#define MAX_T   20           // Tamaño del tablerero 20 x 20
#define NUM_PD  99           // Cantidad de palabras disponibles
#define TAM_P   10           // Tamaño maximo que puede tener una palabra
#define NUM_PE  10           // Cantidad de palabras elegidas para el juego
#define NUM_POS 8            // Cantidad de posiciones para colocar las palabras
#define TAM_PANTALLAX 1016   // Tamaño de pantalla horizontal ML(1016) PC(1273)
#define TAM_PANTALLAY 543   // Tamaño de pantalla vertical    ML(543)  PC(959)

void inicializar_tablero(char tablero[MAX_T][MAX_T]){

    int f,c;

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            tablero[f][c]=' ';

        }
    }

}

void maquillar_tablero(char tablero[MAX_T][MAX_T]){

    int f,c;

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            if ((tablero[f][c]=='-') || (tablero[f][c]=='|') || (tablero[f][c]=='/') || (tablero[f][c]=='%'))
                tablero[f][c]=' ';

        }
    }


}

void copiar_tablero (char tablero[MAX_T][MAX_T], char tablero_resuelto[MAX_T][MAX_T]){

    int f,c;

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            tablero_resuelto[f][c]=tablero[f][c];

        }
    }


}


void imprimir_tablero(char tablero[MAX_T][MAX_T]){

    int f,c,i;
    char cadena[2]={'0','\0'};

    settextstyle(8,0,1);
    setcolor(15);

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            cadena[0]=tablero[f][c];

            outtextxy(c*24+504,f*24+29,cadena);

        }
    }


}

void inicializar_palabras_elegidas(int palabras_elegidas[NUM_PE]){

        int i=0;

        for (i=0;i<NUM_PE;i++)
            palabras_elegidas[i]=-1;
    }

void elegir_palabras(int palabras_elegidas[NUM_PE]){

    int i,x,n=0;
    bool repetida=false;

    while(n<NUM_PE){

        x=rand()%NUM_PD;
        for (i=0;i<=n;i++)
            if (palabras_elegidas[i]==x)
                repetida=true;

        if (!repetida){
            palabras_elegidas[n]=x;
            n++;
        }

        repetida=false;
    }


}

void imprimir_palabras(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int lineas_resueltas[NUM_PE][4]){

    int f=0,c=0;

    char cadena[10];

    settextstyle(8,0,1);
    setcolor(15);


    for(f=0;f<NUM_PE;f++){
        for(c=0;palabras[palabras_elegidas[f]][c];c++){
            cadena[c]=palabras[palabras_elegidas[f]][c];

        }
        cadena[c]='\0';

        outtextxy(20,f*30+100,cadena);
    }
}


int horizontal_normal (char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux;
    bool disponible=true, cruce=false;;
    int c=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);
    int f=rand()%MAX_T;

    aux=c;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c++;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c++;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }
    

    if (disponible){

        c=aux;

        if ((c>0) && (tablero[f][c-1]==' '))
            tablero[f][c-1]='-';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c++;
        }

        lineas_resueltas[n][2]=c-1;
        lineas_resueltas[n][3]=f;

        if ((c<MAX_T) && (tablero[f][c]==' '))
            tablero[f][c]='-';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int horizontal_inversa(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux;
    bool disponible=true, cruce=false;;
    int c=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));
    int f=rand()%MAX_T;

    aux=c;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c--;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c--;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }

    if (disponible){

        c=aux;

        if ((c<MAX_T-1) && (tablero[f][c+1]==' '))
            tablero[f][c+1]='-';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c--;
        }

        lineas_resueltas[n][2]=c+1;
        lineas_resueltas[n][3]=f;

        if ((c>=0) && (tablero[f][c]==' '))
            tablero[f][c]='-';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int vertical_normal(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux;
    bool disponible=true, cruce=false;;
    int c=rand()%MAX_T;
    int f=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);

    aux=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                f++;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                f++;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }


    if (disponible){

        f=aux;

        if ((f>0) && (tablero[f-1][c]==' '))
            tablero[f-1][c]='|';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            f++;
        }

        lineas_resueltas[n][2]=c;
        lineas_resueltas[n][3]=f-1;

        if ((f<MAX_T) && (tablero[f][c]==' '))
            tablero[f][c]='|';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int vertical_inversa(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux;
    bool disponible=true, cruce=false;;
    int c=rand()%MAX_T;
    int f=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));

    aux=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                f--;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                f--;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }


    if (disponible){

        f=aux;

        if ((f<MAX_T-1) && (tablero[f+1][c]==' '))
            tablero[f+1][c]='|';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            f--;
        }

        lineas_resueltas[n][2]=c;
        lineas_resueltas[n][3]=f+1;

        if ((f>=0) && (tablero[f][c]==' '))
            tablero[f][c]='|';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int diagonal_principal_normal(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux_c,aux_f;
    bool disponible=true, cruce=false;;
    int c=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);
    int f=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);

    aux_c=c;
    aux_f=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c++;
                f++;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c++;
                f++;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }


    if (disponible){

        c=aux_c;
        f=aux_f;

        if (((c>0) && (f>0)) && (tablero[f-1][c-1]==' '))
            tablero[f-1][c-1]='%';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c++;
            f++;
        }

        lineas_resueltas[n][2]=c-1;
        lineas_resueltas[n][3]=f-1;

        if (((c<MAX_T) && (f<MAX_T)) && (tablero[f][c]==' '))
            tablero[f][c]='%';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int diagonal_principal_inversa(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux_c,aux_f;
    bool disponible=true, cruce=false;;
    int c=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));
    int f=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));

    aux_c=c;
    aux_f=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c--;
                f--;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c--;
                f--;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }


    if (disponible){

        c=aux_c;
        f=aux_f;

        if (((c<MAX_T-1) && (f<MAX_T-1)) && (tablero[f+1][c+1]==' '))
            tablero[f+1][c+1]='%';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c--;
            f--;
        }

        lineas_resueltas[n][2]=c+1;
        lineas_resueltas[n][3]=f+1;

        if (((c>=0) && (f>=0)) && (tablero[f][c]==' '))
            tablero[f][c]='%';
    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int diagonal_secundaria_normal(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux_c,aux_f;
    bool disponible=true, cruce=false;;
    int c=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));
    int f=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);


    aux_c=c;
    aux_f=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c--;
                f++;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c--;
                f++;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }


    if (disponible){

        c=aux_c;
        f=aux_f;

        if (((c<MAX_T-1) && (f>0)) && (tablero[f-1][c+1]==' '))
            tablero[f-1][c+1]='/';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c--;
            f++;
        }

        lineas_resueltas[n][2]=c+1;
        lineas_resueltas[n][3]=f-1;

        if (((c>=0) && (f<MAX_T)) && (tablero[f][c]==' '))
            tablero[f][c]='/';

    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int diagonal_secundaria_inversa(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int i,aux_c,aux_f;
    bool disponible=true, cruce=false;;
    int c=rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1);
    int f=strlen(palabras[palabras_elegidas[n]])-1+(rand()%(MAX_T-strlen(palabras[palabras_elegidas[n]])+1));


    aux_c=c;
    aux_f=f;

    for (i=0;(palabras[palabras_elegidas[n]][i]) && (disponible);i++){

        if (tablero[f][c]==' '){
                disponible=true;
                c++;
                f--;
        }

        else{
            if (tablero[f][c]==palabras[palabras_elegidas[n]][i]){
                cruce=true;
                c++;
                f--;
            }
            else{
                disponible=false;
                cruce=false;
            }
        }
    }

    

    if (disponible){

        c=aux_c;
        f=aux_f;

        if (((c>0) && (f<MAX_T-1)) && (tablero[f+1][c-1]==' '))
            tablero[f+1][c-1]='/';

        lineas_resueltas[n][0]=c;
        lineas_resueltas[n][1]=f;

        for (i=0;palabras[palabras_elegidas[n]][i];i++){

            tablero[f][c]=palabras[palabras_elegidas[n]][i];
            c++;
            f--;
        }

        lineas_resueltas[n][2]=c-1;
        lineas_resueltas[n][3]=f+1;

        if (((c<MAX_T) && (f>=0)) && (tablero[f][c]==' '))
            tablero[f][c]='/';

    }

    if (cruce)
        return 1;
    if (disponible)
        return 0;
    else
        return -1;
}

int elegir_posicion(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], int n, char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int x=rand()%NUM_POS;
    int r;

	switch (x)
	{
		case 0: r=horizontal_normal(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 1: r=horizontal_inversa(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 2: r=vertical_normal(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 3: r=vertical_inversa(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 4: r=diagonal_principal_normal(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 5: r=diagonal_principal_inversa(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 6: r=diagonal_secundaria_normal(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;

		case 7: r=diagonal_secundaria_inversa(palabras,palabras_elegidas,n,tablero,lineas_resueltas);
		        break;
	}

    return r;
}

void poner_palabras(char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], char tablero[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int n,r,cruz;
    bool falta_palabra;

    do{

        cruz=0;

        falta_palabra=false;

        inicializar_tablero(tablero);

        inicializar_palabras_elegidas(palabras_elegidas);

        elegir_palabras(palabras_elegidas);

        for (n=0;n<NUM_PE;n++){

            r=elegir_posicion(palabras,palabras_elegidas,n,tablero,lineas_resueltas);

            if (r==-1)
                falta_palabra=true;

            if(r==1)
                cruz++;
        }

    }while((cruz<2) || (falta_palabra));

}

void preparar_tablero (char palabras[NUM_PD][TAM_P], int palabras_elegidas[NUM_PE], char tablero[MAX_T][MAX_T], char tablero_resuelto[MAX_T][MAX_T], int lineas_resueltas[NUM_PE][4]){

    int x,f,c;

    poner_palabras(palabras,palabras_elegidas,tablero,lineas_resueltas);

    maquillar_tablero(tablero);

    copiar_tablero(tablero,tablero_resuelto);

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            if(tablero[f][c]==' '){
                x=65+(rand()%26);
                tablero[f][c]=x;
            }
        }
    }
}

void pintaintxy(int x, int y, int num){

    char cad_int[10];

    itoa(num,cad_int,10);

    outtextxy(x,y,cad_int);

}

void pintaint(int num){

    char cad_int[10];

    itoa(num,cad_int,10);

    outtext(cad_int);

}

bool rango_mouse(bool &nueva_sopa){

    if(((mousex()>=500) && (mousex()<=975)) && (( mousey()>=30) && (mousey()<=505)))
        return true;
    if(((mousex()>=500) && (mousex()<=975)) && (( mousey()>=30) && (mousey()<=505)))
        return true;
    if(((mousex()>=328) && (mousex()<=457)) && (( mousey()>=477) && (mousey()<=509)))
        exit(1);
    if(((mousex()>=16) && (mousex()<=265)) && (( mousey()>=477) && (mousey()<=509))){
        nueva_sopa=true;
        return true;
    }
    return false;

}

void imprimir_posiciondelmouse(){

    if(ismouseclick(WM_LBUTTONDOWN)){
        pintaintxy(mousex()-228,mousey()-6,mousex());
        pintaintxy(mousex()-194,mousey()-6,mousey());
        putpixel(mousex(),mousey(),10);

        clearmouseclick(WM_LBUTTONDOWN);
    }


}

void imprimir_lineash(){

    setlinestyle(1,1,4);
    setcolor(15);

   // for(int i=0;i<=MAX_T;i++)
     //   line(497,28+(i*24),976,28+(i*24)); Imprimir todas las lineas horizontales

    line(497,28,976,28);
    line(497,508,976,508);

}

void imprimir_lineasv(){

    setlinestyle(1,1,4);
    setcolor(15);

    //for(int i=0;i<=MAX_T;i++)
      //  line(498+(i*24),27,498+(i*24),507); //Imprimir todas las lineas verticales

    line(498,27,498,507);
    line(978,27,978,507);

}

void limpiar_buffer(int lineas_buffer[4], char &tecla, bool &nueva_sopa){

    tecla='0';

    for(int i=0;i<4;i++)
        lineas_buffer[i]=-1;

    nueva_sopa=false;

}

bool buffer_lleno(int lineas_buffer[4]){

    for(int i=0;i<4;i++)
        if(lineas_buffer[i]==-1)
            return false;
    return true;


}

int num_cuadro(){

    int i;
    int rx=498;
    int ry=28;

    for(i=0;i<MAX_T*MAX_T;i++){
        if(((mousex()>=rx) && (mousex()<=rx+23)) && ( mousey()>=ry) && (mousey()<=ry+23)){
            return i;
        }
        rx=rx+24;
        if(rx>=(((MAX_T-1)*24)+521)){
            ry=ry+24;
            rx=498;
        }
    }
}

void guardar_fila_columna(int lineas_buffer[4]){


    int f,c,cont=0;

    for(f=0;f<MAX_T;f++){
        for(c=0;c<MAX_T;c++){

            if(cont==num_cuadro()){

                if(lineas_buffer[0]==-1){
                    lineas_buffer[0]=c;
                    lineas_buffer[1]=f;
                }
                else{
                    lineas_buffer[2]=c;
                    lineas_buffer[3]=f;
                }
            }
            cont++;

        }
    }
}

void imprimir_buffer(int lineas_buffer[0][4]){

    for(int i=0;i<4;i++)
        pintaintxy(mousex()-470+i*60,mousey()+50,lineas_buffer[0][i]);

}

void rayar(int lineas_buffer[4]){

    setcolor(2);

    setlinestyle(0,0,1);

    line(lineas_buffer[0]*24+509, lineas_buffer[1]*24+39, lineas_buffer[2]*24+509, lineas_buffer[3]*24+39);

}


bool encontrar_palabra(int lineas_resueltas[NUM_PE][4], int lineas_buffer[4]){

    for(int i=0;i<NUM_PE;i++){

        if(   (((lineas_resueltas[i][0]==lineas_buffer[0]) && (lineas_resueltas[i][1]==lineas_buffer[1])) && ((lineas_resueltas[i][2]==lineas_buffer[2]) && (lineas_resueltas[i][3]==lineas_buffer[3]))) || (((lineas_resueltas[i][2]==lineas_buffer[0]) && (lineas_resueltas[i][3]==lineas_buffer[1])) && ((lineas_resueltas[i][0]==lineas_buffer[2]) && (lineas_resueltas[i][1]==lineas_buffer[3])))){

            setcolor(10);

            settextstyle(0,0,1);

            outtextxy(7,i*30+105,"x");

            lineas_resueltas[i][0]=-1;
            lineas_resueltas[i][1]=-1;
            lineas_resueltas[i][2]=-1;
            lineas_resueltas[i][3]=-1;

            return true;
        }
    }
    return false;

}

void encerrar_letra(int lineas_buffer[4],int letra, int color){

    setcolor(color);

    setlinestyle(0,0,1);

    circle(lineas_buffer[letra*2]*24+509, lineas_buffer[letra*2+1]*24+39, 9);

}

void inicializar_tiempo(int &t,int tiempo[3]){

    t=0;

    for (int i=0;i<3;i++)
        tiempo[i]=0;

}


void calcular_tiempo(int tiempo[3],int &t){

    Sleep(100);
    t++;
    if(t==10){
        tiempo[2]++;
        t=0;
        outtextxy(242,420," ");
    }

    if(tiempo[2]==60){
        tiempo[1]++;
        tiempo[2]=0;
        outtextxy(165,420," ");

    }

    if(tiempo[1]==60){
        tiempo[0]++;
        tiempo[1]=0;
    }



}

void imprimir_contorno (){

    settextstyle(0,0,4);
    setcolor(10);
    outtextxy(20,20,"SOPA DE LETRAS");

    setlinestyle(0,0,1);
    settextstyle(8,0,1);
    setcolor(3);
    outtextxy(20,70,"PALABRAS:");
    line(20,89,116,89);

    outtextxy(20,420,"HORA:   MIN:   SEG:" );

    setcolor(2);
    rectangle(15,476,264,510);
    settextstyle(0,0,3);
    setbkcolor(3);
    setcolor(0);
    outtextxy(20,480,"NUEVA SOPA");

    setcolor(2);
    rectangle(328,476,456,510);
    setcolor(0);
    outtextxy(332,480,"SALIR");

}

void mostrar_tiempo(int tiempo[3]){

    setbkcolor(0);
    settextstyle(8,0,1);
    setcolor(10);
    for(int i=0;i<3;i++){
        pintaintxy(78*i+75,420,tiempo[i]);

    }



}

void menu(int &opcion_menu){

    char tecla;

    setcolor(9);
    setlinestyle(0,0,5);
    ellipse( 505, 85, 0, 360, 460, 76 );
    settextstyle(0,0,5);
    setcolor(10);
    outtextxy(105,50,"BIENVENIDOS AL JUEGO");
    outtextxy(215,84,"SOPA DE LETRAS");

    setcolor(2);
    setlinestyle(0,0,1);
    rectangle(106,286,234,320);
    settextstyle(0,0,3);
    setbkcolor(3);
    setcolor(0);
    outtextxy(110,290,"JUGAR");

    setcolor(2);
    rectangle(430,286,582,320);
    setcolor(0);
    outtextxy(434,290,"XJUGAR");
    setcolor(4);
    outtextxy(434,290,"*");

    setcolor(2);
    rectangle(778,286,906,320);
    setcolor(0);
    outtextxy(782,290,"SALIR");


    settextstyle(8,0,1);
    setbkcolor(0);
    setcolor(4);
    outtextxy(10,505,"*JUGAR: juegue con el tablero solo con las palabras escondidas");

    do{
        if(ismouseclick(WM_LBUTTONDOWN)){

            if(((mousex()>=106) && (mousex()<=235)) && ( mousey()>=287) && (mousey()<=319)){
                opcion_menu=1;

            }

            if(((mousex()>=430) && (mousex()<=583)) && ( mousey()>=287) && (mousey()<=319)){
                opcion_menu=2;

            }

            if(((mousex()>=778) && (mousex()<=907)) && ( mousey()>=287) && (mousey()<=319)){
                exit(1);

            }
        }
        clearmouseclick(WM_LBUTTONDOWN);

        if(kbhit()){
                    tecla=getch();
                    if(tecla==27)
                        exit(1);
                    opcion_menu=0;
        }
    }while(opcion_menu==0);

    cleardevice();
}

void cargando(){

settextstyle(0,0,4);
setbkcolor(0);

setcolor(15);
outtextxy(300,250,"Cargando");

Sleep(500);
setcolor(14);
outtextxy(556,250,".");

Sleep(500);
setcolor(1);
outtextxy(590,250,".");

Sleep(500);
setcolor(4);
outtextxy(624,250,".");

Sleep(500);
setcolor(4);
outtextxy(624,250,".");

Sleep(500);
cleardevice();

}

void felicitaciones(){

    settextstyle(0,0,4);
    setbkcolor(0);

    setcolor(4);
    outtextxy(137,134,"Felecidades");
    outtextxy(149,161,"Has ganado");
    setlinestyle(1,1,4);
    circle(310,305,80);
    circle(270,275,15);
    circle(350,275,15);
    ellipse(310,318,180,360,60,30);
    ellipse(310,318,180,360,60,50);
    delay(500);

    setcolor(1);
    outtextxy(137,134,"Felecidades");
    outtextxy(149,161,"Has ganado");
    setlinestyle(1,1,4);
    circle(310,305,80);
    circle(270,275,15);
    circle(350,275,15);
    ellipse(310,318,180,360,60,30);
    ellipse(310,318,180,360,60,50);
    delay(500);


}


main () {

    srand(time(NULL)); // Para que no se repita la secuencia de palabras

    char palabras[NUM_PD][TAM_P]={'A','L','C','A','R','A','V','A','N','\0', // Animales 0-32
                                  'A','N','A','C','O','N','D','A','\0',' ',
                                  'B','A','C','A','L','A','O','\0',' ',' ',
                                  'B','A','L','L','E','N','A','\0',' ',' ',
                                  'C','A','C','H','I','C','A','M','O','\0',
                                  'C','H','I','M','P','A','N','C','E','\0',
                                  'D','E','L','F','I','N','\0',' ',' ',' ',
                                  'E','L','E','F','A','N','T','E','\0',' ',
                                  'E','S','C','O','R','P','I','O','N','\0',
                                  'F','L','A','M','E','N','C','O','\0',' ',
                                  'G','A','R','R','A','P','A','T','A','\0',
                                  'G','U','A','C','A','M','A','Y','O','\0',
                                  'H','A','L','C','O','N','\0',' ',' ',' ',
                                  'H','O','R','M','I','G','A','\0',' ',' ',
                                  'I','G','U','A','N','A','\0',' ',' ',' ',
                                  'I','M','P','A','L','A','\0',' ',' ',' ',
                                  'J','A','G','U','A','R','\0',' ',' ',' ',
                                  'J','I','R','A','F','A','\0',' ',' ',' ',
                                  'L','A','G','A','R','T','I','J','A','\0',
                                  'L','E','O','P','A','R','D','O','\0',' ',
                                  'M','A','P','A','C','H','E','\0',' ',' ',
                                  'M','A','R','I','P','O','S','A','\0',' ',
                                  'N','O','V','I','L','L','O','\0',' ',' ',
                                  'O','R','A','N','G','U','T','A','N','\0',
                                  'P','E','L','I','C','A','N','O','\0',' ',
                                  'P','I','N','G','U','I','N','O','\0',' ',
                                  'R','E','N','A','C','U','A','J','O','\0',
                                  'S','E','R','P','I','E','N','T','E','\0',
                                  'T','A','R','A','N','T','U','L','A','\0',
                                  'T','I','B','U','R','O','N','\0',' ',' ',
                                  'V','E','N','A','D','O','\0',' ',' ',' ',
                                  'Z','A','M','U','R','O','\0',' ',' ',' ', 
                                  'Z','O','R','R','I','L','L','O','\0',' ', // Animales 0-32
                                  'A','L','E','M','A','N','I','A','\0',' ', // Paises 33-65
                                  'A','R','G','E','N','T','I','N','A','\0',
                                  'B','O','L','I','V','I','A','\0',' ',' ',
                                  'B','U','L','G','A','R','I','A','\0',' ',
                                  'C','A','M','E','R','U','N','\0',' ',' ',
                                  'C','O','L','O','M','B','I','A','\0',' ',
                                  'D','I','N','A','M','A','R','C','A','\0',
                                  'E','C','U','A','D','O','R','\0',' ',' ',
                                  'E','S','L','O','V','E','N','I','A','\0',
                                  'F','I','L','I','P','I','N','A','S','\0',
                                  'F','I','N','L','A','N','D','I','A','\0',
                                  'G','U','A','T','E','M','A','L','A','\0',
                                  'G','U','Y','A','N','A','\0',' ',' ',' ',
                                  'H','O','N','D','U','R','A','S','\0',' ',
                                  'H','U','N','G','R','I','A','\0',' ',' ',
                                  'I','N','D','O','N','E','S','I','A','\0',
                                  'I','R','L','A','N','D','A','\0',' ',' ',
                                  'J','A','M','A','I','C','A','\0',' ',' ',
                                  'J','O','R','D','A','N','I','A','\0',' ',
                                  'L','I','T','U','A','N','I','A','\0',' ',
                                  'M','A','C','E','D','O','N','I','A','\0',
                                  'M','A','R','R','U','E','C','O','S','\0',
                                  'N','I','C','A','R','A','G','U','A','\0',
                                  'N','I','G','E','R','I','A','\0',' ',' ',
                                  'N','O','R','U','E','G','A','\0',' ',' ',
                                  'P','A','R','A','G','U','A','Y','\0',' ',
                                  'P','O','R','T','U','G','A','L','\0',' ',
                                  'R','U','M','A','N','I','A','\0',' ',' ',
                                  'S','U','D','A','F','R','I','C','A','\0',
                                  'T','A','I','L','A','N','D','I','A','\0',
                                  'U','R','U','G','U','A','Y','\0',' ',' ',
                                  'V','E','N','E','Z','U','E','L','A','\0',
                                  'Z','A','M','B','I','A','\0',' ',' ',' ', // Paises 33-65 
                                  'A','D','I','D','A','S','\0',' ',' ',' ', // Empresas-Productos 66-98
                                  'A','M','A','Z','O','N','\0',' ',' ',' ',
                                  'A','N','D','R','O','I','D','\0',' ',' ',
                                  'B','A','N','E','S','C','O','\0',' ',' ',
                                  'C','H','E','V','R','O','L','E','T','\0',
                                  'C','O','L','G','A','T','E','\0',' ',' ',
                                  'D','I','R','E','C','T','V','\0',' ',' ',
                                  'D','I','S','N','E','Y','\0',' ',' ',' ',
                                  'D','O','R','I','T','O','S','\0',' ',' ',
                                  'D','U','R','A','C','E','L','L','\0',' ',
                                  'F','A','C','E','B','O','O','K','\0',' ',
                                  'F','E','R','R','A','R','I','\0',' ',' ',
                                  'G','A','T','O','R','A','D','E','\0',' ',
                                  'G','O','O','D','Y','E','A','R','\0',' ', 
                                  'G','O','O','G','L','E','\0',' ',' ',' ',
                                  'H','U','M','M','E','R','\0',' ',' ',' ',
                                  'M','I','C','R','O','S','O','F','T','\0',
                                  'M','O','T','O','R','O','L','A','\0',' ',
                                  'M','O','V','I','L','N','E','T','\0',' ',
                                  'M','O','V','I','S','T','A','R','\0',' ',
                                  'N','E','S','C','A','F','E','\0',' ',' ',
                                  'N','I','N','T','E','N','D','O','\0',' ',
                                  'P','E','T','R','O','B','R','A','S','\0',
                                  'P','I','R','E','L','L','I','\0',' ',' ',
                                  'S','A','M','S','U','N','G','\0',' ',' ',
                                  'S','I','R','A','G','O','N','\0',' ',' ',
                                  'T','E','L','E','F','O','N','O','\0',' ',
                                  'T','E','L','E','V','I','S','O','R','\0',
                                  'T','O','Y','O','T','A','\0',' ',' ',' ',
                                  'T','W','I','T','T','E','R','\0',' ',' ',
                                  'W','I','K','I','P','E','D','I','A','\0',
                                  'W','I','N','D','O','W','S','\0',' ',' ',
                                  'Z','A','P','A','T','O','\0',' ',' ',' '}; // Empresas-Productos 66-98


    char tablero[MAX_T][MAX_T];

    char tablero_resuelto[MAX_T][MAX_T];

    int lineas_resueltas[NUM_PE][4];

    int palabras_elegidas[NUM_PE];

    int lineas_buffer[4];

    int t,tiempo[3];

    char tecla;

    int palabras_encontradas;

    int opcion_menu;

    bool nueva_sopa;


    initwindow(TAM_PANTALLAX,TAM_PANTALLAY);

        opcion_menu=0;
        menu(opcion_menu);

        do{
            cargando();
            nueva_sopa=false;
            palabras_encontradas=0;
            preparar_tablero (palabras,palabras_elegidas,tablero,tablero_resuelto,lineas_resueltas);
            switch(opcion_menu){

                case 1: imprimir_tablero(tablero);
                        break;

                case 2: imprimir_tablero(tablero_resuelto);
                        break;

            }

            imprimir_palabras(palabras,palabras_elegidas,lineas_resueltas);
            imprimir_lineash();
            imprimir_lineasv();
            imprimir_contorno();

            limpiar_buffer(lineas_buffer,tecla,nueva_sopa);
            inicializar_tiempo(t,tiempo);

            do{
                calcular_tiempo(tiempo,t);
                mostrar_tiempo(tiempo);
                if(ismouseclick(WM_LBUTTONDOWN) && rango_mouse(nueva_sopa)){
                    if(nueva_sopa)
                        palabras_encontradas=11;
                    guardar_fila_columna(lineas_buffer);
                    encerrar_letra(lineas_buffer,0,3);
                    if(buffer_lleno(lineas_buffer)){
                        encerrar_letra(lineas_buffer,1,3);
                        encerrar_letra(lineas_buffer,0,0);
                        encerrar_letra(lineas_buffer,1,0);
                        if(encontrar_palabra(lineas_resueltas,lineas_buffer)){
                            rayar(lineas_buffer);
                            palabras_encontradas++;
                        }
                        limpiar_buffer(lineas_buffer,tecla,nueva_sopa);
                    }
                }
                clearmouseclick(WM_LBUTTONDOWN);
                if(kbhit()){
                    tecla=getch();
                    if(tecla==27)
                        exit(1);
                }

            }while(palabras_encontradas<10);

            do{
                if(palabras_encontradas==10)
                    felicitaciones();
                if(ismouseclick(WM_LBUTTONDOWN))
                    if(rango_mouse(nueva_sopa) && nueva_sopa);
                    else
                        clearmouseclick(WM_LBUTTONDOWN);
                if(kbhit()){
                    tecla=getch();
                    if(tecla==27)
                        exit(1);
                }
            }while(!nueva_sopa);

            cleardevice();
            clearmouseclick(WM_LBUTTONDOWN);

        }while(nueva_sopa);
    closegraph();
}

