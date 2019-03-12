#include <stdio.h>
#include <stdlib.h>
typedef struct josefu
{
	int data;
	struct josefu *next;
} josefu_list;
josefu_list *josefu_init(int num);
josefu_list *josefu_begin(josefu_list *list, int rule);
josefu_list *josefu_node(int num);
int josefu_free(josefu_list *list);
int main(void)
{
	josefu_list *list;
	int num, rule;
	puts("Please input number and rules: ");
	scanf("%d%d", &num, &rule);
	list = josefu_init(num);
	list = josefu_begin(list, rule);
	josefu_free(list);
	return 0;
}
josefu_list *josefu_init(int num)
{
	int i;
	josefu_list *new;
	josefu_list *list = josefu_node(1);
	for(i = num; i > 1; i--) {
		new = josefu_node(i);
		new->next = list->next;
		list->next = new;
	}
	return list;
}

int josefu_show(josefu_list *list)
{
	josefu_list *p = list;
	if(list == NULL)
		return 0;
	do {
		printf("%5d",p->data);
		p = p->next;
	} while(list != p);
	putchar('\n');
}
int josefu_free(josefu_list *list)
{
	free(list);
	return 0;
}

josefu_list *josefu_node(int num)
{
	josefu_list *p = NULL;
	p = (josefu_list *)malloc(sizeof(josefu_list));
	p->data = num;
	p->next = p;
	return p;
}
josefu_list *josefu_begin(josefu_list *list, int rule)
{
	int counter;
	josefu_list *tmp = NULL;
	for(counter = 1; list->next != list; counter++) {
		if(counter == rule - 1) {
			tmp = list->next;
			list->next = tmp->next;
			free(tmp);
			counter = 0;
			josefu_show(list);
		}
		list = list->next;
	}
	return list;
}
