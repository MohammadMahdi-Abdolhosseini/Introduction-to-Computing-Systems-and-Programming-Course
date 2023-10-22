#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct point
{
	int point_coordinates[1][2];
};

struct polygon
{
	int n;
	struct point **points;
};

struct point* new_Point(int x, int y) {
	struct point *R = (int*)malloc(sizeof(R));
	if (R == NULL)
	{
		printf("out of memory : Error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	R->point_coordinates[0][0] = x;
	R->point_coordinates[0][1] = y;
	return R;
}

struct polygon* new_polygon(int n, struct point **points) {
	struct polygon *PG = (int*)malloc(sizeof(PG));
	if (PG == NULL)
	{
		printf("out of memory : Error in memory allocation\n");
		exit(EXIT_FAILURE);
	}
	PG->n = n;
	PG->points = points;
	return PG;
}

int main()
{
	int n = 3;
	//printf("Enter value of n: ");
	//scanf_s("%d", &n);
	struct point **points;
	points = (int*)malloc(n * sizeof(points));
	for (int i = 0; i < n; i++)
	{
		points[i] = new_Point(i, i);
	}
	struct polygon *PG = new_polygon(n, points);
	printf("Polygon has %d sides.", n);
	printf("\nPoint Coordinates are: Pi(X,Y)");
	printf("\nPolygon Points Coordinats:");
	for (int i = 0; i < n; i++)
	{
		printf("\tP%d(%d,%d)\t", i + 1, PG->points[i]->point_coordinates[0][0], PG->points[i]->point_coordinates[0][1]);
	}
	return 0;
}