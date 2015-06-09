#include <iostream>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <stack>
#include <list>

#define IZQUIERDA 1
#define DERECHA 3
#define ARRIBA 2
#define ABAJO 4

using namespace std;

COORD coor={0,0}; //ESTO  ES PARA LAS COORDENADAS DEL PANEL DEL  JUEGO

void gotoxy(int x,int y)//X FILAS Y COLUNMAS, PARA LA POCICION DE LOS AVIONES
{
    coor.X=x;coor.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coor);
}

void naveBorrar(int x,int y)
{
    gotoxy(x,y++);cout<<"    ";
    gotoxy(x,y++);cout<<"     ";
    gotoxy(x,y++);cout<<"    ";
}

void nave(int x,int y)
{
        gotoxy(x,y++);cout<<"  "<<char(219)<<char(62);
        gotoxy(x,y++);cout<<char(219)<<char(219)<<char(219)<<char(219)<<char(62);
        gotoxy(x,y++);cout<<"  "<<char(219)<<char(62);
}

void naveEnemigo(int x,int y,string l)
{
        gotoxy(x,y++);cout<<" "<<char(60)<<char(219);
        gotoxy(x,y++);cout<<char(60)<<char(219)<<l<<char(219)<<char(219);
        gotoxy(x,y++);cout<<" "<<char(60)<<char(219);
}

void proyectil(int x,int y,int n)
{
    if(n%2==0)
    {
        gotoxy(x,y++);cout<<char(219)<<char(62);
        gotoxy(x,y++);cout<<char(219)<<char(62);
    }
   else
    {
        gotoxy(x,y++);cout<<char(219)<<char(62);
    }
}

void proyectilBorrar(int x,int y,int n)
{
    if(n%2==0)
    {
        gotoxy(x,y++);cout<<"  ";
        gotoxy(x,y++);cout<<"  ";
    }
    else
    {
        gotoxy(x,y++);cout<<"  ";
    }
}

void fin(int nivel)
{
        gotoxy(20,10);cout<<"Realizado por: Franklin";
        gotoxy(20,12);cout<<"Llego al nivel "<<nivel;
}

void mostrar(int x, int y, string l)//ESTO VA MOSTRANDO  LA PFRASE O  PALABRA  ESCRITA AUN  INICIO
{
        gotoxy(x,y);cout<<l;
}

void barra(int vidas,int nivel)//ESTO  MUESTRA  LA BARRA DE LOS  NIVELES DE VIDA Q SE  TIENE
{
        gotoxy(5,0);cout<<"Nivel: "<<nivel;
        gotoxy(20,0);cout<<"Vidas: "<<vidas;
        gotoxy(0,1);cout<<"-------------------------------------------------------------------------------";
        gotoxy(0,24);cout<<"-------------------------------------------------------------------------------";
}

void choque(int x,int y,int i)
{
    if(i%2==0)
    {
        gotoxy(x,y++);cout<<"  "<<char(118);
        gotoxy(x,y++);cout<<char(62)<<char(62)<<"*"<<char(60)<<char(60);
        gotoxy(x,y++);cout<<"  "<<char(94);
    }
    else
    {
        gotoxy(x,y++);cout<<"  ";
        gotoxy(x,y++);cout<<" *";
    }
}

struct proy{
    int x;
    int y;
};

int main()
{
   system("color 17"); // ESTO  ES PARA CLOLOCAR  COLOR AL JUEGO
    int xenemigo=0,yenemigo;
    int xjugador=10,yjugador=10;
    bool jugar=true;
    int direccion=DERECHA;
    bool teclaDirec=false;
    bool otroNivel=true;
    int vidas=5,nivel=1;
    string o,a;
    queue<proy> balas,balasAux;
    stack<string> oracion,oracion2,aux;
    list<string> navEne,lista,lista2;
    while(jugar)
    {
        if(otroNivel)
        {
            oracion=aux;
            oracion2=aux;
            balas=balasAux;
            int xl=40;
            while(!lista.empty())
            {
                mostrar(xl++,0," ");
                lista.pop_front();
            }
            gotoxy(0,0);cout<<"Escriba unas palabras..."<<endl;
            do
            {
                getline(cin,o);
            }while(o=="");
            system("cls");  //LIMPIAR LA PANTALLA
            for(int i=0;i<o.length();i++)
            {
                a=o[i];
                oracion.push(a);
                navEne.push_back(a);
            }
            otroNivel=false;
        }
        if(kbhit())// MIENTAS NO  SE  PRECIONE  ALGUNA TECLA
        {
            int tt;
            tt=getch(); //ESPERA  A QUE  SE  PRECIO  UNA TECLA Y TERMINA
            if (tt==32)
	        {
	            proy p;
	            p.x=xjugador+3;
	            p.y=yjugador+1;
	            balas.push(p);
	        }
        }
        if(kbhit())
        {
            int tt;
            tt=getch();
            if (GetAsyncKeyState(VK_UP))
	        {
	            direccion = IZQUIERDA;//ARRIBA
	            teclaDirec=true;
	        }
	        else if (GetAsyncKeyState(VK_DOWN))
	        {
	            direccion = DERECHA;//ABAJO
	            teclaDirec=true;
	        }
	        else if (GetAsyncKeyState(VK_LEFT))
	        {
	            direccion = ARRIBA;//IZQUIERDA
	            teclaDirec=true;
	        }
	        else if (GetAsyncKeyState(VK_RIGHT))
	        {
	            direccion = ABAJO;//DERECHA
	            teclaDirec=true;
	        }
	        if(teclaDirec)
            {
                switch (direccion)
                {
                    case ARRIBA:    xjugador--;
                                    if(xjugador<0)
                                        xjugador=0;
                                    break;
                    case ABAJO:     xjugador++;
                                    if(xjugador>20)
                                        xjugador=20;
                                    break;
                    case IZQUIERDA: yjugador--;
                                    if(yjugador<2)
                                        yjugador=2;
                                    break;
                    case DERECHA:   yjugador++;
                                    if(yjugador>21)
                                        yjugador=21;
                                    break;
                }
                teclaDirec=false;
            }
        }
        if(xenemigo==0)
        {
            xenemigo=74;
            yenemigo=rand()%20+2; //ESOT  ES  PARA Q  LAS NAVES ENEMIGAS SE  PUDEN  PODER  DE FORMMA
            //ALEATORIA  EN  EL  PANEL DEL JUEGO
        }
        while(!balas.empty() && balas.front().x>78)//ESTO  ES  PARA BORAR LAS BALAS  SOBRANTES
        {
            balas.pop();
        }
        nave(xjugador,yjugador);
        naveEnemigo(xenemigo,yenemigo,navEne.front());
        while(!balas.empty())
        {
            int x=balas.front().x;
            int y=balas.front().y;
            if((x==xenemigo+1 && y==yenemigo)||(x==xenemigo &&y==yenemigo+1)||(x==xenemigo+1 &&y==yenemigo+2)||
               (x==xenemigo+2 && y==yenemigo)||(x==xenemigo+1 &&y==yenemigo+1)||(x==xenemigo+2 &&y==yenemigo+2)||
               (x==xenemigo+3 && y==yenemigo)||(x==xenemigo+2 &&y==yenemigo+1)||(x==xenemigo+3 &&y==yenemigo+2))
            {
                naveBorrar(xenemigo--,yenemigo);
                xenemigo=1;
                a=navEne.front();
                oracion2.push(a);
                lista.push_back(a);
                navEne.pop_front();
            }
            else
            {
                proyectil(x,y,1);
                proy p;
                p.x=x+1;
                p.y=y;
                balasAux.push(p);
            }
            balas.pop();
        }
        if((xjugador+2==xenemigo && yjugador+2==yenemigo)||
           (xjugador+3==xenemigo && yjugador+2==yenemigo)||
           (xjugador+3==xenemigo && yjugador+1==yenemigo)||
           (xjugador+4==xenemigo && yjugador+1==yenemigo)||
           (xjugador+3==xenemigo && yjugador==yenemigo)||
           (xjugador+4==xenemigo && yjugador==yenemigo)||
           (xjugador+3==xenemigo && yjugador-1==yenemigo)||
           (xjugador+4==xenemigo && yjugador-1==yenemigo)||
           (xjugador+2==xenemigo && yjugador-2==yenemigo)||
           (xjugador+3==xenemigo && yjugador-2==yenemigo))
        {
            naveBorrar(xenemigo--,yenemigo);
            vidas--;
            xenemigo=1;
            for(int i=1;i<3;i++)
            {
                choque(xjugador,yjugador,i);
                Sleep(150);
                naveBorrar(xjugador,yjugador);
            }
            if(vidas<=0)
            {
                jugar=false;
            }
        }
        barra(vidas,nivel);
        if(oracion==oracion2)
        {
            otroNivel=true;
            nivel++;
            system("cls");
            fin(nivel);
            lista2=lista;
            int xm=35;
            mostrar(20,14,"La frase es: ");
            while(!lista2.empty())
            {
                mostrar(xm++,14,lista2.front());
                lista2.pop_front();
            }

            system("cls");
        }
        lista2=lista;
        int xl=40;
        while(!lista2.empty())
        {
            mostrar(xl++,0,lista2.front());
            lista2.pop_front();
        }
        Sleep(100/nivel+25); //ES  PARA  CONTROLAR  LA VELOCIDAD DE LAS NAVES
        naveBorrar(xjugador,yjugador);
        naveBorrar(xenemigo--,yenemigo);
        balas=balasAux;
        while(!balasAux.empty())
        {
            proyectilBorrar(balasAux.front().x-1,balasAux.front().y,1);
            balasAux.pop();
        }
    }
    system("cls");
    fin(nivel);
    lista2=lista;
    int xm=35;
    mostrar(20,14,"La frase es: ");
    while(!lista2.empty())
    {
        mostrar(xm++,14,lista2.front());
        lista2.pop_front();
    }
    return 0;
}
