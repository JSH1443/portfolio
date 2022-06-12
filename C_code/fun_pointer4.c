#include <stdio.h>


// int (*)[2] <<< 리턴 타입
// mat_add     <<< 함수 이름
// int (*p)[2] <<< 파라미터
// int (* mat_add2(int (*src)[2]))[2];

int (* mat_add(int (*src)[2]))[2]
{
	int i, j;



	static int res[2][2] = {
		{ 1, 1 }, { 1, 1 }
	};

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			res[i][j] += src[i][j];
		}
	}

	return res;
}

int main (void)
{
	int i, j;
	int src_mat[2][2] = {
		{ 1, 3 }, { 2, 4 }
	};

	int (*dst)[2] = mat_add(src_mat);

	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			printf("res[%d][%d] = %d\n", i, j, dst[i][j]);
		}
	}

	return 0;
}
