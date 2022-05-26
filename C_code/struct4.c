#include <stdio.h>
#include <stdlib.h>

typedef struct array_list list;

struct array_list
{
	int data;
	struct array_list *link;
};

void print_list_struct (list target)
{
	printf("target.data = %d\n", target.data);
	printf("target.link = %d\n", target.link);

	if (target.link != NULL)
	{
		printf("target.link->data = %d\n", target.link->data);
	}
}

void set_both_link (list *target1, list *target2)
{
	target1->link = target2;
	target2->link = target1;
}

int main(void)
{
	int cnt = 0;

	struct array_list test1 = { 3, NULL };

	list test2 = { 7, NULL };

	set_both_link(&test1, &test2);

	print_list_struct(test1);
	print_list_struct(test2);

	while (test1.link && cnt++ < 10)
	{
		printf("data = %d\n", test1.link->data);
		test1.link = test1.link->link;
	}

	return 0;
}
