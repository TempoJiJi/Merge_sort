#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __LIST{
    int index;
    struct __LIST *next;
}List;

int get_index(List *list, int n)
{
    int i;
    for(i=0;i<n;i++)
	list = list->next;
    return list->index;
}

void Merge(List **head, int low, int high){
    int combined[10000],i,j;
    int k = 0, mid = (low+high)/2;
    List *list;
    list = *head;
    for(i=low, j=mid+1; i<=mid || j<=high;){
	if(i>mid)
	    combined[k++] = get_index(list,j++);
	else if(j>high)	
	    combined[k++] = get_index(list,i++);
	else if(get_index(list,i) >= get_index(list,j))
	    combined[k++] = get_index(list,j++);
	else
	    combined[k++] = get_index(list,i++);
    }
    k=0;
    for(i=0; i<low; i++)
	list = (list->next);
    for(i=low; i<=high; i++){
	list->index = combined[k++];
	list = list->next;
    }
}

void Sort(List **list, int low, int high){
    if(high > low){
	Sort(list, low, (low+high)/2);
	Sort(list, ((low+high)/2)+1, high);
	Merge(list, low, high);
    }
}

void merge_sort(List **head)
{
    if (head == NULL || (*head==NULL))
	return;
    int n = 0;
    List *_head;
    _head = *head;
    while (_head && _head->next){
	n++;
	/*  Circular linked list  */
	if (_head->next == *head)
	    break;
	_head = _head->next;
    }   
    Sort(head, 0, n-1);
}

int main()
{
    int i;
    List *list,*head;  
    list = (List*)malloc(sizeof(List));
    head = list; 
    srand((unsigned)time(NULL));
    for(i=0; i<8; i++){
	list->next = (List*)malloc(sizeof(List));
	list->index = rand() / (i+1);
	list = list->next;
    }
    list = head;
    int n=0;
    while(list && list->next){
	list = list->next;
	n++;
    }
    list = head;
    Sort(&list, 0 , n-1);
    while(head && head->next){
	printf("%d\n",head->index);
	head = head->next;
    }
}
