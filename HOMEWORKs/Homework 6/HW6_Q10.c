#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TNode TN;

struct TNode
{ 
	int data;
	struct TNode* left;
	struct TNode* right;
};

struct TNode* create_tnode_linked_list(int n, int* arr) {
	int mid = (n - 1) / 2;
	TN* tnode = (TN*)malloc(sizeof(TN));
	tnode->data = arr[mid];
	if (mid == 0)
	{
		tnode->right = NULL;
		tnode->left = NULL;
	}
	else
	{
		int *left_arr = (int*)malloc(mid * sizeof(int));
		int *right_arr = (int*)malloc(mid * sizeof(int));
		for (int i = 0; i < mid; i++)
		{
			left_arr[i] = arr[i];
			right_arr[i] = arr[mid + 1 + i];
		}
		tnode->left = (TN*)malloc(sizeof(TN));
		tnode->left = create_tnode_linked_list(mid, left_arr);
		tnode->right = (TN*)malloc(sizeof(TN));
		tnode->right = create_tnode_linked_list(mid, right_arr);
	}
	return tnode;
}

int main() {
	int A[] = { 8,10,12,15,16,20,25 };
	TN* M = create_tnode_linked_list(7, A);
}