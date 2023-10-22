#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions_Of_UTKALA_Pro.h"

//get_allinfo_command: get all informatin of entered command;
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

//separate_the_specified_command: return a specified word in command;
char* separate_the_specified_command(char* allinfo_command, int n) {
	char* specified_command = (char*)malloc(sizeof(char));
	int i = 0;
	while ((allinfo_command[i + n] != ' ') && (allinfo_command[i + n] != '\n') && (allinfo_command[i + n] != NULL))
	{
		specified_command = (char*)realloc(specified_command, (i + 1) * sizeof(char));
		specified_command[i] = allinfo_command[i + n];
		i++;
	}
	specified_command[i] = NULL;
	return specified_command;
}

//check_repeat_buyer: check out that the buyer-account we want to signup, didn't signup before;
int check_repeat_buyer(struct buyer* buyer, char* username) {
	struct buyer* current = buyer->next;
	while (current != NULL)
	{
		if (!strcmp(current->username, username))
			return 1;
		current = current->next;
	}
	return 0;
}

//check_repeat_seller: check out that the seller-account we want to signup, didn't signup before;
int check_repeat_seller(struct seller* seller, char* username) {
	struct seller* current = seller->next;
	while (current != NULL)
	{
		if (!strcmp(current->username, username))
			return 1;
		current = current->next;
	}
	return 0;
}

//last_buyer: it will return last node of buyer struct before NULL;
struct buyer* last_buyer(struct buyer* buyer) {
	struct buyer* current = buyer;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = (struct buyer*)malloc(sizeof(struct buyer));
	return current;
}

//add_buyer: adding a buyer account at the end of the buyer linked list;
void add_buyer(struct buyer* buyer, char* username, char* password) {
	if (!check_repeat_buyer(buyer, username)) {
		struct buyer* lastbuyer = last_buyer(buyer);
		lastbuyer->next->username = (char*)malloc(strlen(username) * sizeof(char));
		lastbuyer->next->password = (char*)malloc(strlen(password) * sizeof(char));
		strcpy(lastbuyer->next->username, username);
		strcpy(lastbuyer->next->password, password);
		lastbuyer->next->Account_Balance = 0;
		lastbuyer->next->goods = (struct shopping_goods*)malloc(sizeof(struct shopping_goods));
		lastbuyer->next->goods->next = NULL;
		lastbuyer->next->next = NULL;
		printf("\tyou're signed up. now, please login.\n");
	}
	else
		printf("\tError: there is a buyer-account with the same username;\n\tif it's yours please login.\n");
}

//last_seller: it will return last node of seller struct before NULL;
struct seller* last_seller(struct seller* seller) {
	struct seller* current = seller;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = (struct seller*)malloc(sizeof(struct seller));
	return current;
}

//add_seller: adding a seller account at the end of the seller linked list;
void add_seller(struct seller* seller, char* username, char* password) {
	if (!check_repeat_seller(seller, username)) {
		struct seller* lastseller = last_seller(seller);
		lastseller->next->username = (char*)malloc(strlen(username) * sizeof(char));
		lastseller->next->password = (char*)malloc(strlen(password) * sizeof(char));
		strcpy(lastseller->next->username, username);
		strcpy(lastseller->next->password, password);
		lastseller->next->Account_Balance = 0;
		lastseller->next->next = NULL;
		printf("\tyou're signed up. now, please login.\n");
	}
	else
		printf("\tError: there is a seller-account with the same username;\n\tif it's yours please login.\n");
}

//login_check_buyer: check buyer user info for login;
struct buyer* login_check_buyer(struct buyer* buyer, char* username, char* password) {
	struct buyer* current = buyer->next;
	while (current != NULL)
	{
		if (!strcmp(current->username, username)) {
			if (!strcmp(current->password, password)) {
				printf("\tlogin was successful.\n");
				printf("\tHi %s.\n", current->username);
				return current;
			}
			else
				printf("\tError: the password is incorrect.\n");
		}
		current = current->next;
	}
	printf("\tSorry..the login wasn't successful.\n\tif you aren't signed up, please sign up first.\n");
	return NULL;
}

//login_check_seller: check seller user info for login;
struct seller* login_check_seller(struct seller* seller, char* username, char* password) {
	struct seller* current = seller->next;
	while (current != NULL)
	{
		if (!strcmp(current->username, username)) {
			if (!strcmp(current->password, password)) {
				printf("\tlogin was successful.\n");
				printf("\tHi %s.\n", current->username);
				return current;
			}
			else
				printf("\tError: the password is incorrect.\n");
		}
		current = current->next;
	}
	printf("\tSorry..the login wasn't successful.\n\tif you aren't signed up, please sign up first.\n");
	return NULL;
}

//view_shopping_goods: print shopping goods in view command for buyers;
void view_shopping_goods(struct buyer* current_buyer) {
	int i = 0;
	struct shopping_goods* current_goods = current_buyer->goods->next;
	while (current_goods != NULL)
	{
		printf("\tBuy[%d]:\n\t\tName: %s\n", i + 1, current_goods->name);
		printf("\t\tPrice: %d\n", current_goods->price);
		printf("\t\tCount: %d\n", current_goods->count);
		printf("\t\tName of seller: %s\n", current_goods->sellerman);
		current_goods = current_goods->next;
		i++;
	}
	if (i == 0)
		printf("\tBuys: No purchase.\n");
}

//sorting_goods: sort by name of goods;
void sorting_goods(struct goods* goods) {
	int i = 0;
	while (i == 0)
	{
		i = 1;
		struct goods* current_goods = goods;
		if ((current_goods->next != NULL))
		{
			while ((current_goods->next->next != NULL))
			{
				if (strcmp(current_goods->next->name, current_goods->next->next->name) == 1)
				{
					struct goods* temp1 = current_goods->next;
					struct goods* temp2 = current_goods->next->next;
					struct goods* temp3 = current_goods->next->next->next;
					current_goods->next = temp2;
					temp1->next = temp3;
					temp2->next = temp1;
					i = 0;
				}
				else
					current_goods = current_goods->next;
			}
		}
	}
}

//view_goods: print goods in view command for sellers;
void view_goods(struct goods* goods, struct seller* current_seller) {
	int i = 0;
	sorting_goods(goods);
	struct goods* current_goods = goods->next;
	while (current_goods != NULL)
	{
		if (!strcmp(current_goods->seller->username, current_seller->username))
		{
			printf("\tGoods[%d]:\n\t\tName: %s\n", i + 1, current_goods->name);
			printf("\t\tPrice: %d\n", current_goods->price);
			printf("\t\tCount: %d\n", current_goods->count);
			i++;
		}
		current_goods = current_goods->next;
	}
	if (i == 0)
		printf("\tGoods: No Goods.\n");
}

//show_goods: print all goods in the system;
void show_goods(struct goods* goods) {
	sorting_goods(goods);
	struct goods* current_goods = goods->next;
	int i = 0;
	while (current_goods != NULL)
	{
		printf("\tGoods[%d]:\n\t\tName: %s\n", i + 1, current_goods->name);
		printf("\t\tPrice: %d\n", current_goods->price);
		printf("\t\tCount: %d\n", current_goods->count);
		printf("\t\tSeller: %s\n", current_goods->seller->username);
		if (current_goods->count_rate != 0)
			printf("\t\tRate: %.2f\n", current_goods->rate);
		else
			printf("\t\tRate: NaN\n");
		current_goods = current_goods->next;
		i++;
	}
	if (i == 0)
		printf("\tSorry..there is no product to sale.\n");
}

//char_amount_check: check the value if included character or was zero return 1; 
int char_amount_check(char* text) {
	for (int i = 0; i < strlen(text); i++)
		if (text[i] != '0' && text[i] != '1' && text[i] != '2' && text[i] != '3' && text[i] != '4' && text[i] != '5' && text[i] != '6' && text[i] != '7' && text[i] != '8' && text[i] != '9')
			return 1;
	if (atoi(text) == 0)
		return 1;
	return 0;
}

//check_repeat_goods: check out that the goods we want to add, didn't add before;
//return 0 if it wasn't repetitive; return 1 if it was repetitive and was for someone else; return 2 if it was for himself;
int check_repeat_goods(struct goods* goods, char* name_of_goods, struct seller* current_seller) {
	struct goods* current_goods = goods->next;
	while (current_goods != NULL)
	{
		if (!strcmp(current_goods->name, name_of_goods))
		{
			if (!strcmp(current_goods->seller->username, current_seller->username))
				return 2;
			else
				return 1;
		}
		current_goods = current_goods->next;
	}
	return 0;
}

//adding_goods: add a goods to goods-struct and link to its seller;
//stats 0 means the goods wasn't repetitive; stats 2 means it was for himself;
int adding_goods(struct goods* goods, struct seller* current_seller, char* name_of_goods, int price_of_goods, int count_of_goods, int stats) {
	struct goods* current_goods = goods;
	if (stats == 0)
	{
		while (current_goods->next != NULL)
			current_goods = current_goods->next;
		current_goods->next = (struct goods*)malloc(sizeof(struct goods));
		current_goods->next->name = (char*)malloc(strlen(name_of_goods) * sizeof(char));
		strcpy(current_goods->next->name, name_of_goods);
		current_goods->next->price = price_of_goods;
		current_goods->next->count = count_of_goods;
		current_goods->next->seller = (struct seller*)malloc(sizeof(struct seller));
		current_goods->next->seller = current_seller;
		current_goods->next->next = NULL;
		current_goods->next->rate = 0;
		current_goods->next->count_rate = 0;
		current_goods->next->sum_rate = 0;
		printf("\tyour product is added.\n");
		return 0;
	}
	if (stats == 2)
	{
		while (current_goods != NULL)
		{
			if (!strcmp(current_goods->next->name, name_of_goods))
			{
				current_goods->next->count += count_of_goods;
				printf("\tyour product is added.\n");
				return 0;
			}
			current_goods = current_goods->next;
		}
	}
	return 0;
}

//finding_goods: find a specified goods and return that; this function used in buy command;
//if didn't find anything or there was error, return NULL;
struct goods* finding_goods(struct goods* goods, char* name_of_goods, int count_of_goods, char* seller_username) {
	struct goods* current_goods = goods->next;
	while (current_goods != NULL)
	{
		if (!strcmp(current_goods->name, name_of_goods))
		{
			if (current_goods->count >= count_of_goods)
			{
				if (!strcmp(current_goods->seller->username, seller_username))
				{
					if ((current_goods->rate < 2) && (current_goods->count_rate >= 5))
					{
						printf("\tError: unfortunately, the product has been disabled because of low rate.\n");
						return NULL;
					}
					else
						return current_goods;
				}
				else
				{
					printf("\tError: seller username is incorrect\n");
					return NULL;
				}
			}
			else
			{
				printf("\tError: the inventory of the goods isn't enough.\n");
				return NULL;
			}
		}
		current_goods = current_goods->next;
	}
	printf("\tError: name of product is incorrect.\n");
	return NULL;
}

//last_purchase: return last node in shopping_goods for current_buyer; that's mean return NULL node and malloc that;
struct shopping_goods* last_purchase(struct buyer* current_buyer) {
	struct shopping_goods* current_shopping_goods = current_buyer->goods;
	while (current_shopping_goods->next != NULL)
		current_shopping_goods = current_shopping_goods->next;
	current_shopping_goods->next = (struct shopping_goods*)malloc(sizeof(struct shopping_goods));
	current_shopping_goods->next->next = NULL;
	return current_shopping_goods->next;
}

//remove_goods: free a specified goods node that we want to delete it;
void remove_goods(struct goods* goods, char* name_of_goods) {
	int i = 0;
	struct goods* current_goods = goods;
	while (current_goods->next != NULL)
	{
		if (!strcmp(current_goods->next->name, name_of_goods))
		{
			struct goods* temp = current_goods->next;
			if (temp->next == NULL)
			{
				current_goods->next = NULL;
				free(temp);
				i = 1;
			}
			else
			{
				current_goods->next = current_goods->next->next;
				free(temp);
				i = 1;
			}
		}
		if (current_goods->next != NULL)
			current_goods = current_goods->next;
	}
	if (i == 0)
		printf("\tError: name of product is incorrect.\n");
	else
		printf("\tRemoving was succesful.\n");
}

//change_goods_price: finding a specified goods node and change price;
int change_goods_price(struct goods* goods, struct seller* current_seller, char* name_of_goods, int new_price) {
	struct goods* current_goods = goods;
	while (current_goods->next != NULL)
	{
		if (!strcmp(current_goods->next->name, name_of_goods))
		{
			if (!strcmp(current_goods->next->seller->username, current_seller->username))
			{
				current_goods->next->price = new_price;
				printf("\tPrice changing was succesful.\n");
				return 1;
			}
			else
			{
				printf("\tError: this goods is for another seller.");
				return 0;
			}
		}
		current_goods = current_goods->next;
	}
	printf("\tError: name of product is incorrect.\n");
}

//rate_goods: you can rate goods only once per purchase; after rating ratibility = 0;
int rate_goods(struct goods* goods, struct buyer* current_buyer, char* name_of_goods, char* seller_username, char* rate) {
	struct shopping_goods* current_shopping_goods = current_buyer->goods;
	int i = 0;
	while (current_shopping_goods->next != NULL)
	{
		if (!strcmp(current_shopping_goods->next->name, name_of_goods))
		{
			if (!strcmp(current_shopping_goods->next->sellerman, seller_username))
			{
				i = 1;
				if (current_shopping_goods->next->ratibility == 1)
				{
					if (!char_amount_check(rate) && (atoi(rate) <= 5))
					{
						struct goods* current_goods = goods;
						while (current_goods->next != NULL)
						{
							i = 2;
							current_shopping_goods->next->ratibility = 0;
							if (!strcmp(current_goods->next->name, name_of_goods))
							{
								current_goods->next->sum_rate += atoi(rate);
								current_goods->next->count_rate += 1;
								current_goods->next->rate = (current_goods->next->sum_rate / current_goods->next->count_rate);
								printf("\tThe rating was succesful.\n");
								return 1;
							}
							current_goods = current_goods->next;
						}
					}
					else
					{
						printf("\tError: rate value must be integer and between 1,2,..,5.\n");
						return NULL;
					}
				}
			}
		}
		current_shopping_goods = current_shopping_goods->next;
	}
	if (i == 0)
		printf("\tError: name of product is incorrect.\n");
	if (i == 1)
		printf("\tError: you already rated for this goods.\n");
	if (i == 2)
		printf("\tError: the goods has been deleted.\n");
}

//search_command: if match found print result;
void search_command(struct goods* goods, char* name, char* seller_username, int max_price, int min_price) {
	sorting_goods(goods);
	struct goods* current_goods = goods->next;
	int i = 0;
	printf("\tSearch Result:\n");
	while (current_goods != NULL)
	{
		int match1, match2, match3, match4;
		match1 = match2 = match3 = match4 = 0;
		if (name == NULL)
			match1 = 1;
		else if (!strcmp(current_goods->name, name))
			match1 = 1;
		if (seller_username == NULL)
			match2 = 1;
		else if (!strcmp(current_goods->seller, seller_username))
			match2 = 1;
		if (max_price == -1)
			match3 = 1;
		else if (max_price >= current_goods->price)
			match3 = 1;
		if (min_price == -1)
			match4 = 1;
		else if (min_price <= current_goods->price)
			match4 = 1;
		if ((match1 == 1) && (match2 == 1) && (match3 == 1) && (match4 == 1))
		{
			printf("\t\tGoods[%d]:\n\t\t\tName: %s\n", i + 1, current_goods->name);
			printf("\t\t\tPrice: %d\n", current_goods->price);
			printf("\t\t\tCount: %d\n", current_goods->count);
			printf("\t\t\tSeller: %s\n", current_goods->seller->username);
			if (current_goods->count_rate != 0)
				printf("\t\t\tRate: %.2f\n", current_goods->rate);
			else
				printf("\t\t\tRate: NaN\n");
			i++;
		}
		current_goods = current_goods->next;
	}
	if (i == 0)
		printf("\t\tNot results found!\n");
}

//save_buyer_in_file: save format: username:password:Account_Balance:|goods_name(1):goods_price(1):goods_count(1):goods_sellerman(1):goods_ratibility(1):|goods_name(2): ...
void save_buyer_in_file(struct buyer* buyer) {
	FILE* fbuyer = fopen("buyer_file.txt", "w");
	if (fbuyer == NULL) {
		printf("\tError: unable to create buyer_file.\n");
		EXIT_FAILURE;
	}
	struct buyer* current_buyer = buyer->next;
	while (current_buyer != NULL)
	{
		fprintf(fbuyer, " %s:%s:%d:", current_buyer->username, current_buyer->password, current_buyer->Account_Balance);
		struct shopping_goods* current_goods = current_buyer->goods->next;
		while (current_goods != NULL)
		{
			fprintf(fbuyer, "|%s:%d:%d:%s:%d:", current_goods->name, current_goods->price, current_goods->count, current_goods->sellerman, current_goods->ratibility);
			current_goods = current_goods->next;
		}
		fputc('\n', fbuyer);
		current_buyer = current_buyer->next;
	}
	fclose(fbuyer);
}

//save_seller_in_file: save format: username:password:Account_Balance:
void save_seller_in_file(struct seller* seller) {
	FILE* fseller = fopen("seller_file.txt", "w");
	if (fseller == NULL) {
		printf("\tError: unable to create seller_file.\n");
		EXIT_FAILURE;
	}
	struct seller* current_seller = seller->next;
	while (current_seller != NULL)
	{
		fprintf(fseller, " %s:%s:%d:", current_seller->username, current_seller->password, current_seller->Account_Balance);
		fputc('\n', fseller);
		current_seller = current_seller->next;
	}
	fclose(fseller);
}

//save_buyer_in_file: save format: goods_name(1):goods_price(1):goods_count(1):goods_seller_username(1):goods_rate(1)*100:goods_count_rate(1):goods_sum_rate(1):
void save_goods_in_file(struct goods* goods) {
	FILE* fgoods = fopen("goods_file.txt", "w");
	if (fgoods == NULL) {
		printf("\tError: unable to create goods_file.\n");
		EXIT_FAILURE;
	}
	struct goods* current_goods = goods->next;
	while (current_goods != NULL)
	{
		fprintf(fgoods, " %s:%d:%d:%s:%.0f:%d:%.0f:\n", current_goods->name, current_goods->price, current_goods->count, current_goods->seller->username, current_goods->rate * 100, current_goods->count_rate, current_goods->sum_rate);
		current_goods = current_goods->next;
	}
	fclose(fgoods);
}

//read_word_from_file: get a string from file until ':';
char* read_word_from_file(FILE* fptr) {
	char* word = (char*)malloc(sizeof(char));
	int i = 0;
	while (word[i - 1] != ':')
	{
		word = (char*)realloc(word, (i + 1) * sizeof(char));
		word[i] = fgetc(fptr);
		i++;
	}
	word[i - 1] = NULL;
	return word;
}

//load_buyer_from_file: load and create buyers
void load_buyer_from_file(struct buyer* buyer) {
	FILE* fbuyer = fopen("buyer_file.txt", "r");
	if (fbuyer == NULL)
		fbuyer = fopen("buyer_file.txt", "w+");
	struct buyer* current_buyer = buyer;
	while ((fgetc(fbuyer) != EOF))
	{
		char* username = read_word_from_file(fbuyer);
		char* password = read_word_from_file(fbuyer);
		int Account_Balance = atoi(read_word_from_file(fbuyer));
		current_buyer->next = (struct buyer*)malloc(sizeof(struct buyer));
		current_buyer->next->username = (char*)malloc(strlen(username) * sizeof(char));
		current_buyer->next->password = (char*)malloc(strlen(password) * sizeof(char));
		strcpy(current_buyer->next->username, username);
		strcpy(current_buyer->next->password, password);
		current_buyer->next->Account_Balance = Account_Balance;
		current_buyer->next->goods = (struct shopping_goods*)malloc(sizeof(struct shopping_goods));
		current_buyer->next->goods->next = NULL;
		current_buyer->next->next = NULL;
		struct shopping_goods* current_goods = current_buyer->next->goods;
		char ch = fgetc(fbuyer);
		while (ch == '|')
		{
			current_goods->next = (struct shopping_goods*)malloc(sizeof(struct shopping_goods));
			current_goods->next->next = NULL;
			char* name = read_word_from_file(fbuyer);
			current_goods->next->name = (char*)malloc(strlen(name) * sizeof(char));
			strcpy(current_goods->next->name, name);
			current_goods->next->price = atoi(read_word_from_file(fbuyer));
			current_goods->next->count = atoi(read_word_from_file(fbuyer));
			char* sellerman = read_word_from_file(fbuyer);
			current_goods->next->sellerman = (char*)malloc(strlen(sellerman) * sizeof(char));
			strcpy(current_goods->next->sellerman, sellerman);
			current_goods->next->ratibility = atoi(read_word_from_file(fbuyer));
			current_goods = current_goods->next;
			ch = fgetc(fbuyer);
		}
		current_buyer = current_buyer->next;
	}
	fclose(fbuyer);
}

//load_seller_from_file: load and create sellers
void load_seller_from_file(struct seller* seller) {
	FILE* fseller = fopen("seller_file.txt", "r");
	if (fseller == NULL)
		fseller = fopen("seller_file.txt", "w+");
	struct seller* current_seller = seller;
	while ((fgetc(fseller) != EOF))
	{
		char* username = read_word_from_file(fseller);
		char* password = read_word_from_file(fseller);
		int Account_Balance = atoi(read_word_from_file(fseller));
		current_seller->next = (struct seller*)malloc(sizeof(struct seller));
		current_seller->next->username = (char*)malloc(strlen(username) * sizeof(char));
		current_seller->next->password = (char*)malloc(strlen(password) * sizeof(char));
		strcpy(current_seller->next->username, username);
		strcpy(current_seller->next->password, password);
		current_seller->next->Account_Balance = Account_Balance;
		current_seller->next->next = NULL;
		char ch = fgetc(fseller);
		current_seller = current_seller->next;
	}
	fclose(fseller);
}

//load_goods_from_file: load and create goods
void load_goods_from_file(struct goods* goods, struct seller* seller) {
	FILE* fgoods = fopen("goods_file.txt", "r");
	if (fgoods == NULL)
		fgoods = fopen("goods_file.txt", "w+");
	struct goods* current_goods = goods;
	while ((fgetc(fgoods) != EOF))
	{
		char* name = read_word_from_file(fgoods);
		int price = atoi(read_word_from_file(fgoods));
		int count = atoi(read_word_from_file(fgoods));
		current_goods->next = (struct goods*)malloc(sizeof(struct goods));
		current_goods->next->name = (char*)malloc(strlen(name) * sizeof(char));
		strcpy(current_goods->next->name, name);
		current_goods->next->price = price;
		current_goods->next->count = count;
		char* seller_username = read_word_from_file(fgoods);
		struct seller* current_seller = seller->next;
		while (current_seller != NULL)
		{
			if (!strcmp(current_seller->username, seller_username)) {
				current_goods->next->seller = current_seller;
				current_goods->next->rate = atof(read_word_from_file(fgoods)) / 100;
				current_goods->next->count_rate = atoi(read_word_from_file(fgoods));
				current_goods->next->sum_rate = atoi(read_word_from_file(fgoods));
				current_goods->next->next = NULL;
				char ch = fgetc(fgoods);
			}
			current_seller = current_seller->next;
		}
		current_goods = current_goods->next;
	}
	fclose(fgoods);
}