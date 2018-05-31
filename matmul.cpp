#include <stdlib.h>
#include "matmul.h"

#define A(i,j,wA) A[i * wA + j]
#define B(i,j,wB) B[i * wB + j]
#define C(i,j,wB) C[i * wB + j]
#define TILE 16

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* matrix B is currently layed out and accessed in column-major. */
void matmul(float* C, const float* A, const float* B, unsigned int hA,
    unsigned int wA, unsigned int wB)
{
   for (unsigned int i = 0; i < wB; i += TILE) {
	   for (unsigned int j = 0; j < wB; j += TILE) {
	      for (unsigned int k = 0; k < wB; k += TILE) {
		      for (unsigned int x = i; x < i + TILE; x++) {
		         for (unsigned int y = j; y < j + TILE; y++) {
               float sum = 0;
			         for (unsigned int z = k; z < k + TILE; z++) {
                  float a = A(x,z,hA);
                  float b = B(y,z,hA);
                  sum += a * b;
			         }
               C(x,y,wB) += sum;
		         }
		      }
	      }
	   }
   }
}

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  /* This function which is currently called
   * for Matrix B such that a column-major ordering is
   * performed. */
  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
    //M.elements[i] = (rand() / (float)RAND_MAX);
    M.elements[(((int)(i / M.pitch)) + (M.pitch * i)) % (M.height * M.width)] = (rand() / (float)RAND_MAX);
  }
  return M;
}
