#include <stdio.h>

// размеры поля
#define N 7
#define M 15

#define NO 255
#define YES 254
#define FINISH 0
#define START 253

// поле
char P[N][M]={
"##############",
"#            #",
"#  #     #   #",
"#* #     #  +#",
"#  #  #      #",
"#     #      #",
"##############"};

unsigned char R[N][M]; // рабочий массив
const int Nk=100; // max количество итераций


void fillR() // заполнение рабочего массива
{
	int i,j;
	for(i=0;i<N;i++)
		for(j=0;j<M;j++)
			if(P[i][j]=='#') // поле непроходимо
				R[i][j]=NO;
			else if(P[i][j]==' ') // поле проходимо
				R[i][j]=YES;
			else if(P[i][j]=='+') // цель
				R[i][j]=FINISH;
			else if(P[i][j]=='*') // старт
				R[i][j]=START;
}
void printP()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M-1;j++)	
			printf("%c",P[i][j]);
		putchar('\n');
	}
}
void printR()
{
	int i,j;
	for(i=0;i<N;i++)
	{
		for(j=0;j<M-1;j++)	
			printf("%03u ",R[i][j]);
		putchar('\n');
	}
}
int wave(int *starti,int *startj)
{
	int Ni=0;
	int i,j;
	do
	{
	  for(i=1;i<N-1;i++)
		for(j=1;j<M-1;j++)
	
			if(R[i][j]==Ni)
			{
				if(R[i+1][j]==START)
                {
                	*starti=i+1;
                	*startj=j;
                	return 1;
                }
				else if (R[i+1][j]==YES)
					R[i+1][j]=Ni+1;

				if(R[i-1][j]==START)
                {
                	*starti=i-1;
                	*startj=j;
                	return 1;
                }
				else if (R[i-1][j]==YES)
					R[i-1][j]=Ni+1;

				if(R[i][j+1]==START)
                {
                	*starti=i;
                	*startj=j+1;
                	return 1;
                }
				else if (R[i][j+1]==YES)
					R[i][j+1]=Ni+1;

				if(R[i][j-1]==START)
                {
                	*starti=i;
                	*startj=j-1;
                	return 1;
                }
				else if (R[i][j-1]==YES)
					R[i][j-1]=Ni+1;				
			}
	  Ni++;
    }
	while(Ni<=Nk);
	return 0;
}

int min(int a,int b, int c, int d)
{
	if(a<=b && a<=c && a<=d)
		return a;
	else if(b<=a && b<=c && b<=d)
		return b;
	else if(c<=a && c<=b && c<=d)
		return c;
	else if(d<=a && d<=b && d<=c)
		return d;

}

void path(int starti,int startj)
{
	int X=startj,Y=starti,X1=X,Y1=Y;
    int minval;

    while(1)
    {
       minval=min(R[Y+1][X],R[Y-1][X],R[Y][X+1],R[Y][X-1]);
       if(minval==R[Y+1][X])
       {
          Y1=Y+1;
          X1=X;
       }
       else if(minval==R[Y-1][X])
       {
       	  Y1=Y-1;
       	  X1=X;
       }
       else if(minval==R[Y][X-1])
       {
       	  Y1=Y;
       	  X1=X-1;
       }
       else if(minval==R[Y][X+1])
       {
       	  Y1=Y;
       	  X1=X+1;
       }     
       if(R[Y1][X1]==0)
         return;

       X=X1;
       Y=Y1; 
       P[Y][X]='.';
       printf("%d,%d\n",X,Y);
    } 
}

int main()
{
	int result;
	int X,Y,X1,Y1;
	fillR();
	printR();
    result=wave(&Y,&X);
    printf("%d,%d\n",X,Y);
    printR();
    path(Y,X);
    printP();
    
	return 0;
}
