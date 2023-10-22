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