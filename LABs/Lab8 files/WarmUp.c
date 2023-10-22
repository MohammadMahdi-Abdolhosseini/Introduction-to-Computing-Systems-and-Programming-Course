/*Q1
let us say we have a struct of node* and we will give the head to 
function bellow,  For Linked List 1->2->3->4->5,
what would be the output of code bellow? */

void traverse(struct Node *head)
{
   while (head->next != NULL)
   {
       printf("%d  ", head->data);
       head = head->next;
   }
}

//easily prints: 1 2 3 4 

//------------------------------------------------------------------------

/*Q2
let us say we have a struct of node* and we will give the head to 
function bellow,  For Linked List 1->2->3->4->5,
 what would be the output of code bellow? */

void func(struct node* head)
{
  if(head == NULL)
    return;
  func(head->next);
  printf("%d  ", head->data);
}

/*func() prints the given Linked List in reverse manner.
 For Linked List 1->2->3->4->5, fun1() prints 5 4 3 2 1. */

//------------------------------------------------------------------------

/*Q3
What is the output of following function for start pointing... 
to first node of following linked list? 1->2->3->4->5->6*/

void func(struct node* start)
{
  if(start == NULL)
    return;
  printf("%d  ", start->data); 
  
  if(start->next != NULL )
    func(start->next->next);
  printf("%d  ", start->data);
}

/*1 3 5 5 3 1
func() prints alternate nodes of the given Linked List,
first from head to end, and then from end to head.
If Linked List has even number of nodes, then skips the last node.*/


//------------------------------------------------------------------------

/*Q4*
The following C function takes a single-linked list of integers as a parameter
and rearranges the elements of the list. The function is called with the list containing
 the integers 1, 2, 3, 4, 5, 6, 7 in the given order. 
 What will be the contents of the list after the function completes execution?*/

struct node 
{
  int value;
  struct node *next;
};
void rearrange(struct node *list)
{
  struct node *p, * q;
  int temp;
  if ((!list) || !list->next) 
      return;
  p = list;
  q = list->next;
  while(q) 
  {
     temp = p->value;
     p->value = q->value;
     q->value = temp;
     p = q->next;
     q = p?p->next:0;
  }
}

//output: 2 1 4 3 6 5 7
/*The function rearrange() exchanges data of every node with its next node.
It starts exchanging data from the first node itself.*/