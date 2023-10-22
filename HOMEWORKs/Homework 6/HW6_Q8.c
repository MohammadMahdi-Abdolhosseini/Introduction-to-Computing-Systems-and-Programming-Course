#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

struct List
{
	int data;
	struct List* next;
};

List* merge(List* list1, List* list2) {
	//linking 2 list:
	List* current = list1;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = list2;

	//getting length value:
	int length = 1;
	current = list1;
	while (current->next != NULL)
	{
		length++;
		current = current->next;
	}

	//sorting linked list;
	for (int i = 0; i < 2 * length; i++)
	{
		current = list1;
		while (current->next != NULL)
		{
			if (current->data > current->next->data)
			{
				int temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
			}
			current = current->next;
		}
	}
	return list1;
}

List* merge2(List* list1, List* list2) {
	List* result = NULL;
	if (list1 == NULL)
		return list2;
	else if (list2 == NULL)
		return list1;
	if (list1->data <= list2->data)
	{
		result = list1;
		result->next = merge(list1->next, list2);
	}
	else
	{
		result = list2;
		result->next = merge(list1, list2->next);
	}
	return result;
}