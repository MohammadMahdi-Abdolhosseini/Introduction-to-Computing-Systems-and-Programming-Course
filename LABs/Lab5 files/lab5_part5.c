#include <stdio.h>
#define matrix_size 3
#define zero 0
#define one 1
#define two 2

void calc_transposed_matrix(double matrix[matrix_size][matrix_size],
		double transposed_matrix[matrix_size][matrix_size]);

void mult_const_to_matrix(const double c, double matrix[matrix_size][matrix_size]);{
	for(int i = zero; i < matrix_size; i++){
		for(int j = zero; j < matrix_size; j++){
			matrix[i][j] *= one/c;
		}
	}
}

void print_matrix(double matrix[matrix_size][matrix_size]){
	for (int i = zero; i < matrix_size; i++){
		for (int j = zero; j < matrix_size; j++){
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}

double determinant(double matrix[matrix_size][matrix_size]){
	double determinant = matrix[zero][zero] * ((matrix[one][one] * matrix[two][two]) - (matrix[two][one]*matrix[one][two])) -matrix[zero][one] * (matrix[one][zero]
   * matrix[two][two] - matrix[two][zero] * matrix[one][two]) + matrix[zero][two] * (matrix[one][zero] * matrix[two][one] - matrix[two][zero] * matrix[one][one]);
	return determinant;
}

int inverse_of_matrix(double matrix[matrix_size][matrix_size], double inversed_matrix[matrix_size][matrix_size]){
	double determinant_of_matrix = determinant(matrix), ZERO = 0;
	if(determinant_of_matrix == ZERO)
		return zero;
    calc_transposed_matrix(matrix, inversed_matrix);
    mult_const_to_matrix(determinant_of_matrix, inversed_matrix);
    return one;
}

int main(){
	double a[matrix_size][matrix_size] = { {9, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	double a_inverse[matrix_size][matrix_size];
	if(inverse_of_matrix(a, a_inverse))
		print_matrix(a_inverse);
	else
		printf("Undefined determinant\n");
	return zero;
}