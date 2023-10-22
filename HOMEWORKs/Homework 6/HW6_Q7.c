#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

struct List
{
	int data;
	struct List* next;
};

List* create_sorted_linked_list(int n, int* arr) {
	//sorting array:
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[i] < arr[j])
			{
				int r = arr[i];
				arr[i] = arr[j];
				arr[j] = r;
			}
		}
	}
	//array is sorted; now we can create sorted linked list:
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