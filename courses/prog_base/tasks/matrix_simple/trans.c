#include <stdlib.h>
void fillRand(int mat[4][4])
{
	int i, n;
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)
		{
			mat[i][n] = 1000 - rand() % 2000;
		}
}
void matCopy(int src[4][4], int dest[4][4])
{
	int i, n;
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)
		{
			dest[i][n] = src[i][n];
		}
}
void rotateCW90(int mat[4][4])		
{
	int i, n, k;
	int tempMat[4][4] = { 0 };
	matCopy(mat, tempMat);
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)
		{
			mat[n][3 - i] = tempMat[i][n];
		}
}
void rotateCW270(int mat[4][4])
{
	int i;
	for (i = 0; i < 3;i++)
		rotateCW90(mat);
}
void transposeMain(int mat[4][4])		
{
	int i, n;
	int tempMat[4][4];
	matCopy(mat, tempMat);
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)
			mat[n][i] = tempMat[i][n];
}
void flipV(int mat[4][4])
{
	int i, n;
	int tempMat[4][4];
	matCopy(mat, tempMat);
	for (i = 0; i < 4; i++)
		for (n = 0; n < 4; n++)
			mat[3-n][i] = tempMat[n][i];
}
