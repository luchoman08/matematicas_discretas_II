#include <stdio.h>


void imprimir_x_y_matriz(int x, int y, int* mat, int nfil, int ncol)
{
	printf("Imprimir posicion [%d][%d]: \n", x,y);
	mat = (mat + y * (nfil));
	mat += (x);
	printf("%d", *mat);
}
void imprimir_matris_puntero(int* mat, int nfil, int ncol)
{
	printf("Imprimir matriz: \n");
	for(int i=0; i<nfil*ncol;i++)
	{
		if(i%nfil==0&&i!=0)printf("\n");
		printf("%d ", *mat+i);
	}
	printf("\n");
}
int main (int args, char** argv)
{
    
	int mat[3][3] ={ {1,2,3},{4,5,6},{7,8,9}};
	int* matapunter = &mat[0][0];
	imprimir_matris_puntero(matapunter,3,3);
	imprimir_x_y_matriz(2,1, matapunter, 3 ,3 );
	return 0;
	
}
