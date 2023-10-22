#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct point
{
	int point_coordinates[1][2];
};

struct line
{
	int start_end_point_coordinates[2][2];
};

struct point* new_Point(int x, int y) {
	struct point *R = (int*)malloc(sizeof(R));
	if (R == NULL)
	{
		printf("out of memory : Error in memory allocation for struct point *R\n");
		exit(EXIT_FAILURE);
	}
	R->point_coordinates[0][0] = x;
	R->point_coordinates[0][1] = y;
	return R;
}

struct line* new_line(struct point *start, struct point *end) {
	struct line *d = (int*)malloc(sizeof(d));
	if (d == NULL)
	{
		printf("out of memory : Error in memory allocation for struct line *d\n");
		exit(EXIT_FAILURE);
	}
	d->start_end_point_coordinates[0][0] = start->point_coordinates[0][0];
	d->start_end_point_coordinates[0][1] = start->point_coordinates[0][1];
	d->start_end_point_coordinates[1][0] = end->point_coordinates[0][0];
	d->start_end_point_coordinates[1][1] = end->point_coordinates[0][1];
	return d;
}


float distance(struct point* x0, struct line* l0)
{
	struct point* P = x0;
	float Alfa = P->point_coordinates[0][0];
	float Beta = P->point_coordinates[0][1];

	struct line* d = l0;
	//start-point coordinates is : ( A , B )
	float A = d->start_end_point_coordinates[0][0];
	float B = d->start_end_point_coordinates[0][1];

	//end-point coordinates is : ( C , D )
	float C = d->start_end_point_coordinates[1][0];
	float D = d->start_end_point_coordinates[1][1];

	//calculate the slope of line : m
	float m = (B - D) / (A - C);

	//calculate the distance of point:( Alfa , Beta ) from line:[ (- m) * x + y + (m * A - B) = 0 ]
	float distance = (-m * Alfa + Beta + m * A - B) / (sqrtf(m * m + 1));
	if (distance < 0)
	{
		distance *= -1;
	}
	return distance;
}

int main() {
	int Alfa = 1;
	int Beta = 2;
	//start-point coordinates is : ( A , B )
	int A = -1;
	int B = -2;
	//end-point coordinates is : ( C , D )
	int C = 3;
	int D = 1;
	printf("Enter coordinates of point like this: X Y : ");
	scanf_s("%d %d", &Alfa, &Beta);
	printf("Enter coordinates of start-point of line like this: X Y : ");
	scanf_s("%d %d", &A, &B);
	printf("Enter coordinates of end-point of line like this: X Y : ");
	scanf_s("%d %d", &C, &D);
	//struct point *A1 = new_Point(A, B);
	//struct point *B1 = new_Point(C, D);
	printf("distance = %f", distance(new_Point(Alfa, Beta), new_line(new_Point(A, B), new_Point(C, D))));
}