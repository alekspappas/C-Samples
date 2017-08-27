#include "utilities.hpp"

int SimpleTranspose (double *a,
		                 int size,
		                 int ldim)
{
	/*Confirm input pointer and size parameters are valid*/
	if (a == NULL or ldim < size)
	{
		return 1;
	}

	/*Transpose matrix */
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			double temp = a[(i*ldim) + j];
			a[(i*ldim) + j] = a[(j*ldim) + i];
			a[(j*ldim) + i] = temp;
		}
	}
	
	return 0;
}

void SwitchBlocks (double *a,
		               double *b,
		               int ldim,
		               int blocksize)
{
	for (int i = 0; i < blocksize; i++)
	{
		for (int j = 0; j < blocksize; j++)
		{
			double temp = a[(i*ldim) + j];
			a[(i*ldim) + j] = b[(i*ldim) + j];
			b[(i*ldim) + j] = temp;
		}
	}
}

int OptimizedTranspose (double *a,
		                    int size,
			                  int ldim,
			                  int blocksize)
{
	/*Loop through sublocks*/
	for (int i = 0; i < size/blocksize; i++)
	{
		for (int j = 0; j < size/blocksize; j++)
		{
			if ( j == i)
			{
				/*Tranpose block*/
				double * new_pt_a = a + i*(ldim) *(i*blocksize) + j*(blocksize);
				SimpleTranspose(new_pt_a, blocksize, ldim);
				
			}
			
			if ( j > i)
			{
				double * new_pt_a = a + i*(ldim) *(i*blocksize) + j*(blocksize);
				SimpleTranspose(new_pt_a, blocksize, ldim);
					
				/*Transpose second block*/
				double * new_pt_b = a + j*(ldim*blocksize) + i*(blocksize);
				SimpleTranspose(new_pt_b, blocksize, ldim);
				
				/*Switch blocks*/
				SwitchBlocks(new_pt_a, new_pt_b, ldim, blocksize);
			}
		}
	}
	return 0;
}	
