#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

struct List
{
	int data;
	struct List* next;
};

List* create_linked_list(int n, int* arr) {
	List* list = (List*)malloc(sizeof(List));
	List* current = list;
	for (int i = 0; i < n; i++)
	{
		current->data = arr[i];
		current->next = (List*)malloc(sizeof(List));
		if (i + 1 == n)
		{
			current->next = NULL;
		}
		else
		{
			current = current->next;
		}
	}
	return list;
}