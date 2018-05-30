#include <stdlib.h>
#include "matmul.h"

#define A(i,j,wA) A[i * wA + j]
#define B(i,j,wB) B[i * wB + j]
#define C(i,j,wB) C[i * wB + j]

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
  double wT = 16;

   for (unsigned int i = 0; i < wB; i += wT) {
	   for (unsigned int j = 0; j < wB; j += wT) {
	      for (unsigned int k = 0; k < wB; k += wT) {
		      for (unsigned int x = i; x < i + wT; x++) {
		         for (unsigned int y = j; y < j + wT; y++) {
			         for (unsigned int z = k; z < k + wT; z++) {
			            C(x,y,wB) += (float)(A(x,z,wA) * B(y,z,wB));
			         }
		         }
		      }
	      }
	   }
   }
  /*for (unsigned int i = 0; i < hA; ++i) {
    for (unsigned int j = 0; j < wB; ++j) {
      double sum = 0;
      for (unsigned int k = 0; k < wA; ++k) {
        double a = A[i * wA + k];
        //double b = B[k * wB + j];
        double b = B[j * wB + k];
        sum += a * b;
      }
      C[i * wB + j] = (float)sum;
    }
  }*/
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
