#include "FunctionOf_UT-KALA_Phase1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_allinfo_command()
{
	printf("\n # Enter command: ");
	char* command = (char*)malloc(sizeof(char));
	int i = 0;
	while (command[i - 1] != '\n')
	{
		command = (char*)realloc(command, (i + 1) * sizeof(char));
		command[i] = getchar();
		i++;
	}
	command[i - 1] = NULL;
	return command;
}

char* separate_the_only_command(char* allinfo_command) {
	char* only_command = (char*)malloc(sizeof(char));
	int i = 0;
	while (allinfo_command[i] != ' ')
	{
		only_command = (char*)realloc(only_command, (i + 1) * sizeof(char));
		only_command[i] = allinfo_command[i];
		i++;
	}
	only_command[i] = NULL;
	return only_command;
}

char* separate_the_specified_command(char* allinfo_command, int n) {
	char* specified_command = (char*)malloc(sizeof(char));
	int i = 0;
	while (allinfo_command[i + n] != ' ')
	{
		specified_command = (char*)realloc(specified_command, (i + 1) * sizeof(char));
		specified_command[i] = allinfo_command[i + n];
		i++;
	}
	specified_command[i] = NULL;
	return specified_command;
}

struct buyer* add_buyer(char* username, char* password) {
	struct buyer* newbuyer = (struct buyer*)malloc(sizeof(struct buyer));
	newbuyer->username = (char*)malloc(strlen(username) * sizeof(char));
	newbuyer->password = (char*)malloc(strlen(password) * sizeof(char));
	strcpy(newbuyer->username, username);
	strcpy(newbuyer->password, password);
	newbuyer->Account_Balance = 0;
	newbuyer->count_of_goods = 0;
	return newbuyer;
}

struct seller* add_seller(char* username, char* password) {
	struct seller* newseller = (struct seller*)malloc(sizeof(struct seller));
	newseller->username = (char*)malloc(strlen(username) * sizeof(char));
	newseller->password = (char*)malloc(strlen(password) * sizeof(char));
	strcpy(newseller->username, username);
	strcpy(newseller->password, password);
	newseller->Account_Balance = 0;
	newseller->count_of_goods = 0;
	return newseller;
}

void show_goods(struct seller** seller, int numofseller) {
	int goods_num = 0;
	for (int i = 0; i < numofseller; i++)
	{
		for (int j = 0; j < seller[i]->count_of_goods; j++)
		{
			if (seller[i]->count_of_goods != 0)
			{
				printf("\tGoods[%d]:\n\t\tName: %s\n", goods_num + 1, seller[i]->goods[j]->name);
				printf("\t\tPrice: %d\n", seller[i]->goods[j]->price);
				printf("\t\tCount: %d\n", seller[i]->goods[j]->count);
				printf("\t\tSeller: %s\n", seller[i]->username);
				goods_num++;
			}
		}
	}
	if (goods_num == 0)
	{
		printf("\tSorry..there is no product to sale.\n");
	}
}

int char_amount_check(char* text) {
	for (int i = 0; i < strlen(text); i++)
	{
		//بررسی هر حرف وارد شده برای تشخیص کاراکتر نبودن آن
		if (text[i] != '0' && text[i] != '1' && text[i] != '2' && text[i] != '3' && text[i] != '4' && text[i] != '5' && text[i] != '6' && text[i] != '7' && text[i] != '8' && text[i] != '9') {
			return 1;
		}
	}
	if (atoi(text) == 0)
	{
		return 1;
	}
	return 0;
}