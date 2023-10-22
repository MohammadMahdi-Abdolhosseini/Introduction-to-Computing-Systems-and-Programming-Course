//CA_phase2: UT-KALA pro
//Designed by Mohammad Mahdi Abdolhosseini
//spring and summer 2020

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions_Of_UTKALA_Pro.h"

int main() {
	//intro:
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t\t\tWellcome to UT-KALA Pro\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

	//create B-Head:
	struct buyer* buyer = (struct buyer*)malloc(sizeof(struct buyer));
	buyer->next = NULL;
	load_buyer_from_file(buyer);
	//count of all buyers:
	int numofbuyer = 0;
	//create S-Head:
	struct seller* seller = (struct seller*)malloc(sizeof(struct seller));
	seller->next = NULL;
	load_seller_from_file(seller);
	//count of all sellers:
	int numofseller = 0;
	//create G-Head:
	struct goods* goods = (struct goods*)malloc(sizeof(struct goods));
	goods->next = NULL;
	load_goods_from_file(goods, seller);

	while (1)
	{
		//if sys_user was 1 it means there is a user in system that logined;
		int sys_user = 0;
		//current_buyer is used for logined buyer users;
		struct buyer *current_buyer = buyer;
		//current_seller is used for logined seller users;
		struct seller *current_seller = seller;
		char role;
		//Get command:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		char* text = get_allinfo_command();									//text = All info command
		char* text1 = separate_the_specified_command(text, 0);				//text1 = 1st word
		int n = strlen(text1) + 1;
		char* text2 = separate_the_specified_command(text, n);				//text2 = 2nd word
		n = strlen(text1) + strlen(text2) + 2;
		char* text3 = separate_the_specified_command(text, n);				//text3 = 3rd word
		n = strlen(text1) + strlen(text2) + strlen(text3) + 3;
		char* text4 = separate_the_specified_command(text, n);				//text4 = 4th word
		//SignUp:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		if (!strcmp(text1, "signup"))
		{
			if (!strcmp(text4, "buyer"))
				add_buyer(buyer, text2, text3);
			else if (!strcmp(text4, "seller"))
				add_seller(seller, text2, text3);
			else
				printf("\tError: role is incorrect.\n");
		}
		//Login:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		else if (!strcmp(text1, "login"))
		{
			if (!strcmp(text4, "buyer"))
			{
				current_buyer = login_check_buyer(buyer, text2, text3);
				if (current_buyer != NULL)
				{
					sys_user = 1;
					role = 'b';
				}
			}
			else if (!strcmp(text4, "seller"))
			{
				current_seller = login_check_seller(seller, text2, text3);
				if (current_seller != NULL)
				{
					sys_user = 1;
					role = 's';
				}
			}
			else
				printf("\tError: role is incorrect.\n");
		}
		//Show Goods:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		else if (!strcmp(text1, "show_goods"))
			show_goods(goods);
		//Error Command:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		else if (!strcmp(text1, "view") || !strcmp(text1, "logout") || !strcmp(text1, "deposit") || !strcmp(text1, "add_goods") || !strcmp(text1, "buy") || !strcmp(text1, "remove_goods"))
			printf("\tError: please login first to use this command.\n");
		else
			printf("\tError: the command is incorrect.\n");
		while (sys_user == 1)
		{
			//Get command:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			char* text = get_allinfo_command();									//text = All info command
			char* text1 = separate_the_specified_command(text, 0);				//text1 = 1st word
			int n = strlen(text1) + 1;
			char* text2 = separate_the_specified_command(text, n);				//text2 = 2nd word
			n = strlen(text1) + strlen(text2) + 2;
			char* text3 = separate_the_specified_command(text, n);				//text3 = 3rd word
			n = strlen(text1) + strlen(text2) + strlen(text3) + 3;
			char* text4 = separate_the_specified_command(text, n);				//text4 = 4th word
			//View:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			if (!strcmp(text1, "view"))
			{
				if (role == 'b')
				{
					printf("\tUsername: %s\n", current_buyer->username);
					printf("\tRole: Buyer\n");
					printf("\tAccount Balance: %d\n", current_buyer->Account_Balance);
					view_shopping_goods(current_buyer);
				}
				else if (role == 's')
				{
					printf("\tUsername: %s\n", current_seller->username);
					printf("\tRole: Seller\n");
					printf("\tAccount Balance: %d\n", current_seller->Account_Balance);
					view_goods(goods, current_seller);
				}
			}
			//Show Goods:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "show_goods"))
				show_goods(goods);
			//Deposit:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			else if (!strcmp(text1, "deposit")) {
				if (role == 'b') {
					if (!char_amount_check(text2))
					{
						current_buyer->Account_Balance += atoi(text2);
						printf("\tdeposit was successful.\n");
						printf("\tAccount Balance: %d\n", current_buyer->Account_Balance);
					}
					else
						printf("\tError: the amount of money must be a number larger than zero.\n");
				}
				else if (role == 's')
					printf("\tError: sorry..you are a seller and you can't use this command.\n");
			}
			//Add Goods:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			else if (!strcmp(text1, "add_goods")) {
				if (role == 's')
				{
					if (check_repeat_goods(goods,text2,current_seller) != 1)
					{
						if (char_amount_check(text3))
							printf("\tError: the amount of price must be a number larger than zero.\n");
						if (char_amount_check(text4))
							printf("\tError: the count of goods must be a number larger than zero.\n");
						if (!char_amount_check(text3) && !char_amount_check(text4))
							adding_goods(goods, current_seller, text2, atoi(text3), atoi(text4), check_repeat_goods(goods, text2, current_seller));
					}
					else
						printf("\tSorry..another seller sells this product;\n\tso you can't sell it.\n");
				}
				else
					printf("\tError: sorry..you are a buyer and you can't use this command.\n");
			}
			//Buy:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			else if (!strcmp(text1, "buy")) {
				if (role == 'b')
				{
					if (!char_amount_check(text3))
					{
						struct goods* current_goods = finding_goods(goods, text2, atoi(text3), text4);
						if (current_goods != NULL)
						{
							if (atoi(text3)*current_goods->price <= current_buyer->Account_Balance)
							{
								//
								current_goods->count -= atoi(text3);
								current_buyer->Account_Balance -= atoi(text3)*current_goods->price;
								current_goods->seller->Account_Balance += atoi(text3)*current_goods->price;
								//
								struct shopping_goods* current_shopping_goods = last_purchase(current_buyer);
								current_shopping_goods->name = (char*)malloc(strlen(text2) * sizeof(char));
								strcpy(current_shopping_goods->name, text2);
								current_shopping_goods->count = atoi(text3);
								current_shopping_goods->price = current_goods->price;
								current_shopping_goods->sellerman = (char*)malloc(strlen(text4) * sizeof(char));
								strcpy(current_shopping_goods->sellerman, text4);
								current_shopping_goods->ratibility = 1;
								printf("\tThe purchase was succesful.\n");
							}
							else
								printf("\tError: the account balance isn't enough.\n");
						}
					}
					else
						printf("\tError: the count of goods must be a number, larger than zero.\n");
				}
				else
					printf("\tError: sorry..you are a seller and you can't use this command.\n");
			}
			//Remove Goods:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "remove_goods")) {
				if (role == 's')
					remove_goods(goods, text2);
				else
					printf("\tError: sorry..you are a buyer and you can't use this command.\n");
			}
			//Change Goods Price:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "change_goods_price")) {
				if (role == 's')
				{
					if (!char_amount_check(text3))
						change_goods_price(goods, current_seller, text2, atoi(text3));
					else
						printf("\tError: the amount of price must be a number larger than zero.\n");
				}
				else
					printf("\tError: sorry..you are a buyer and you can't use this command.\n");
			}
			//Rate Goods:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "rate_goods")) {
				if (role == 'b')
				{
					rate_goods(goods, current_buyer, text2, text3, text4);
				}
				else
					printf("\tError: sorry..you are a seller and you can't use this command.\n");
			}
			//Search:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "search")) {
				if (!char_amount_check(text2) && (atoi(text2) <= 4))
				{
					int error_check = 0;
					int number_of_conditions = atoi(text2);
					char* a_name = NULL;
					char* a_seller_username = NULL;
					int a_max_price = -1;
					int a_min_price = -1;
					int char_amount = 0;
					char* goods_attribute_1 = NULL;				//1st word condition 1
					char* attribute_value_1 = NULL;				//2nd word condition 1
					char* goods_attribute_2 = NULL;				//1st word condition 2
					char* attribute_value_2 = NULL;				//2nd word condition 2
					char* goods_attribute_3 = NULL;				//1st word condition 3
					char* attribute_value_3 = NULL;				//2nd word condition 3
					char* goods_attribute_4 = NULL;				//1st word condition 4
					char* attribute_value_4 = NULL;				//2nd word condition 4
					printf("\tNow you must enter %d attribute:", number_of_conditions);

					if (number_of_conditions >= 1)
					{
						char* temp = get_allinfo_command();
						goods_attribute_1 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(goods_attribute_1, separate_the_specified_command(temp, 0));		//1st word condition 1
						int n = strlen(goods_attribute_1) + 1;
						attribute_value_1 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(attribute_value_1, separate_the_specified_command(temp, n));		//2nd word condition 1
						
						//what's the goods_attribute_1 ?!
						if (!strcmp(goods_attribute_1, "name")) {
							a_name = (char*)malloc(strlen(attribute_value_1) * sizeof(char));
							strcpy(a_name, attribute_value_1);
							error_check++;
						}
						else if (!strcmp(goods_attribute_1, "seller_username")) {
							a_seller_username = (char*)malloc(strlen(attribute_value_1) * sizeof(char));
							strcpy(a_seller_username, attribute_value_1);
							error_check++;
						}
						else if (!strcmp(goods_attribute_1, "max_price")) {
							a_max_price = atoi(attribute_value_1);
							error_check++;
						}
						else if (!strcmp(goods_attribute_1, "min_price")) {
							a_min_price = atoi(attribute_value_1);
							error_check++;
						}
						else if (goods_attribute_1 != NULL)
							printf("\tError: the 1st goods attribute is incorrect.\n");
					}

					if (number_of_conditions >= 2)
					{
						char* temp = get_allinfo_command();
						goods_attribute_2 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(goods_attribute_2, separate_the_specified_command(temp, 0));		//1st word condition 2
						int n = strlen(goods_attribute_2) + 1;
						attribute_value_2 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(attribute_value_2, separate_the_specified_command(temp, n));		//2nd word condition 2

						//what's the goods_attribute_2 ?!
						if (!strcmp(goods_attribute_2, "name")) {
							a_name = (char*)malloc(strlen(attribute_value_2) * sizeof(char));
							strcpy(a_name, attribute_value_2);
							error_check++;
						}
						else if (!strcmp(goods_attribute_2, "seller_username")) {
							a_seller_username = (char*)malloc(strlen(attribute_value_2) * sizeof(char));
							strcpy(a_seller_username, attribute_value_2);
							error_check++;
						}
						else if (!strcmp(goods_attribute_2, "max_price")) {
							a_max_price = atoi(attribute_value_2);
							error_check++;
						}
						else if (!strcmp(goods_attribute_2, "min_price")) {
							a_min_price = atoi(attribute_value_2);
							error_check++;
						}
						else if (goods_attribute_2 != NULL)
							printf("\tError: the 2nd goods attribute is incorrect.\n");
					}
					
					if (number_of_conditions >= 3)
					{
						char* temp = get_allinfo_command();
						goods_attribute_3 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(goods_attribute_3, separate_the_specified_command(temp, 0));		//1st word condition 3
						int n = strlen(goods_attribute_3) + 1;
						attribute_value_3 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(attribute_value_3, separate_the_specified_command(temp, n));		//2nd word condition 3

						//what's the goods_attribute_3 ?!
						if (!strcmp(goods_attribute_3, "name")) {
							a_name = (char*)malloc(strlen(attribute_value_3) * sizeof(char));
							strcpy(a_name, attribute_value_3);
							error_check++;
						}
						else if (!strcmp(goods_attribute_3, "seller_username")) {
							a_seller_username = (char*)malloc(strlen(attribute_value_3) * sizeof(char));
							strcpy(a_seller_username, attribute_value_3);
							error_check++;
						}
						else if (!strcmp(goods_attribute_3, "max_price")) {
							a_max_price = atoi(attribute_value_3);
							error_check++;
						}
						else if (!strcmp(goods_attribute_3, "min_price")) {
							a_min_price = atoi(attribute_value_3);
							error_check++;
						}
						else if (goods_attribute_3 != NULL)
							printf("\tError: the 3rd goods attribute is incorrect.\n");
					}
					
					if (number_of_conditions == 4)
					{
						char* temp = get_allinfo_command();
						goods_attribute_4 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(goods_attribute_4, separate_the_specified_command(temp, 0));		//1st word condition 4
						int n = strlen(goods_attribute_4) + 1;
						attribute_value_4 = (char*)malloc(strlen(temp) * sizeof(char));
						strcpy(attribute_value_4, separate_the_specified_command(temp, n));		//2nd word condition 4

						//what's the goods_attribute_4 ?!
						if (!strcmp(goods_attribute_4, "name")) {
							a_name = (char*)malloc(strlen(attribute_value_4) * sizeof(char));
							strcpy(a_name, attribute_value_4);
							error_check++;
						}
						else if (!strcmp(goods_attribute_4, "seller_username")) {
							a_seller_username = (char*)malloc(strlen(attribute_value_4) * sizeof(char));
							strcpy(a_seller_username, attribute_value_4);
							error_check++;
						}
						else if (!strcmp(goods_attribute_4, "max_price")) {
							a_max_price = atoi(attribute_value_4);
							error_check++;
						}
						else if (!strcmp(goods_attribute_4, "min_price")) {
							a_min_price = atoi(attribute_value_4);
							error_check++;
						}
						else if (goods_attribute_4 != NULL)
							printf("\tError: the 4th goods attribute is incorrect.\n");
					}

					if (error_check == number_of_conditions)
					{
						if (((a_max_price <= 0) && (a_max_price != -1)) || ((a_min_price <= 0) && (a_min_price != -1)))
							printf("\tError: the attribute value of price must be a number, larger than zero.\n");
						else
							search_command(goods, a_name, a_seller_username, a_max_price, a_min_price);
					}
				}
				else
					printf("\tError: the number of conditions must be integer and between [1,4].\n");
			}
			//Logout:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			else if (!strcmp(text1, "logout"))
			{
				printf("\tyou are logout successfully.\n");
				printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
				break;
			}
			//Error Command:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			else if (!strcmp(text1, "signup") || !strcmp(text1, "login"))
				printf("\tplease logout first to use this command.\n");
			else
				printf("\tError: the command is incorrect.\n");
			//Save in File:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
			save_buyer_in_file(buyer);
			save_seller_in_file(seller);
			save_goods_in_file(goods);
		}
		//Save in File:=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		save_buyer_in_file(buyer);
		save_seller_in_file(seller);
		save_goods_in_file(goods);
	}
}