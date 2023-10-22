#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List List;

struct List
{
	int data;
	struct List* next;
};

List* remove_repetition(List* list)
{
	List* current = list;
	List* node;
	while (current != NULL)
	{
		int current_num = current->data;
		node = current;
		while (node->next != NULL)
		{
			if (current_num == node->next->data)
			{
				List* delete_node;
				delete_node = node->next;
				node->next = node->next->next;
				free(delete_node);
				continue;
			}
			node = node->next;
		}
		current = current->next;
	}
	return list;
}