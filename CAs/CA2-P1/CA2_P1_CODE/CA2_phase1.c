#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FunctionOf_UT-KALA_Phase1.h"

int main() {
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\t\t\tWellcome to UT-KALA\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");	
	int numofbuyer = 0;//تعداد کل خریدار ها
	struct buyer** buyer = (struct buyer**)malloc(sizeof(struct buyer*));
	int numofseller = 0;//تعداد کل فروشنده ها
	struct seller** seller = (struct seller**)malloc(sizeof(struct seller*));
	while (1)
	{
		char role;//اختصاص نقش برای تفکیک ساده تر در حین برنامه
		int numofuser = -1;//شماره کاربر فعلی سیستم که در هر نقش جداست
		int same = 0;//متغییری جهت تشخیص یکسان بودن
		char* text = get_allinfo_command();//تابعی جهت گرفتن دستور ها از کاربر
		char* text1 = separate_the_only_command(text);//جداسازی کلمه اول دستور وارد شده جهت تشخیص نوع دستور
		int n = strlen(text1) + 1;
		char* text2 = separate_the_specified_command(text, n);//جداسازی کلمه دوم
		n = strlen(text1) + strlen(text2) + 2;
		char* text3 = separate_the_specified_command(text, n);//جداسازی کلمه سوم
		n = strlen(text1) + strlen(text2) + strlen(text3) + 3;
		char* text4 = separate_the_specified_command(text, n);//جداسازی کلمه چهارم
		if (!strcmp(text1, "signup"))
		{
			if (!strcmp(text4, "buyer"))
			{
				//بررسی و مقایسه نام کاربری که میخواهد ثبت نام کند با سایر کاربر ها تا تکراری نباشد
				for (int i = 0; i < numofbuyer; i++)
				{
					if (!strcmp(buyer[i]->username, text2))
					{
						printf("\tError: there is a buyer-account with the same username;\n\tif it's yours please login.\n");
						same = 1;
					}
				}
				if (!same)
				{
					buyer[numofbuyer] = add_buyer(text2, text3);//با استفاده از نام کاربری و رمز اکانت رو اضافه کن
					printf("\tyou're signed up. now, please login.\n");
					buyer[numofbuyer]->goods = (struct shpping_goods**)malloc(sizeof(struct shopping_goods*));//اختصاص حافظه برای محصولات کاربر ثبت نام شده
					numofbuyer++;//افزایش تعداد کل خریدار ها
					buyer = (struct buyer**)realloc(buyer, (numofbuyer + 1) * sizeof(struct buyer*));//اختصاص حافظه برای کاربر بعدی
				}
			}
			else if (!strcmp(text4, "seller"))
			{
				//بررسی و مقایسه نام کاربری که میخواهد ثبت نام کند با سایر کاربر ها تا تکراری نباشد
				for (int i = 0; i < numofseller; i++)
				{
					if (!strcmp(seller[i]->username, text2))
					{
						printf("\tError: there is a seller-account with the same username;\n\tif it's yours please login.\n");
						same = 1;
					}
				}
				if (!same)
				{
					seller[numofseller] = add_seller(text2, text3);//با استفاده از نام کاربری و رمز اکانت رو اضافه کن
					printf("\tyou're signed up. now, please login.\n");
					seller[numofseller]->goods = (struct goods**)malloc(sizeof(struct goods*));//اختصاص حافظه برای محصولات کاربر ثبت نام شده
					numofseller++;//افزایش تعداد کل فروشنده ها
					seller = (struct seller**)realloc(seller, (numofseller + 1) * sizeof(struct seller*));//اختصاص حافظه برای کاربر بعدی
				}
			}
			else
				printf("\tError: role is incorrect.\n");
		}
		else if (!strcmp(text1, "login"))
		{
			if (!strcmp(text4, "buyer"))
			{
				//بررسی و مقایسه نام و رمز کاربر با سایر کاربر ها
				for (int i = 0; i < numofbuyer; i++)
				{
					if (!strcmp(buyer[i]->username, text2))//اگر یک کاربر با این نام وجود داشت
					{
						if (!strcmp(buyer[i]->password, text3))//اگر رمز کاربر با رمز وارد شده یکسان بود
						{
							printf("\tlogin was successful.\n");
							printf("\tHi %s.\n", buyer[i]->username);
							numofuser = i;//شماره کاربر فعلی در این نقش
							role = 'b';//اختصاص نقش جهت استفاده راحت تر از برنامه
						}
						else
						{
							printf("\tError: the password is incorrect.\n");
							same = 1;//یک کاربر وجود دارد ولی رمز اشتباه است
						}
					}
				}
			}
			else if (!strcmp(text4, "seller"))
			{
				//بررسی و مقایسه نام و رمز کاربر با سایر کاربر ها
				for (int i = 0; i < numofseller; i++)
				{
					if (!strcmp(seller[i]->username, text2))//اگر یک کاربر با این نام وجود داشت
					{
						if (!strcmp(seller[i]->password, text3))//اگر رمز کاربر با رمز وارد شده یکسان بود
						{
							printf("\tlogin was successful.\n");
							printf("\tHi %s.\n", seller[i]->username);
							numofuser = i;//شماره کاربر فعلی در این نقش
							role = 's';//اختصاص نقش جهت استفاده راحت تر از برنامه
						}
						else
						{
							printf("\tError: the password is incorrect.\n");
							same = 1;//یک کاربر وجود دارد ولی رمز اشتباه است
						}
					}
				}
			}
			else {
				printf("\tError: role is incorrect.\n");
				same = 1;//نقش اشتباه است
			}
			if ((numofuser == -1) && (same == 0))//اگر رمز و نقش اشتباه نبود و لاگین خطا داشت
			{
				//یعنی هیچ اکانتی با این نام کاربری و در این نقش وجود ندارد
				printf("\tSorry..the login wasn't successful.\n\tif you aren't signed up, please sign up first.\n");
			}

		}
		else if (!strcmp(text1, "show_goods")) {
			show_goods(seller, numofseller);//نشان دادن تمام کالا های سیستم
		}
		else if (!strcmp(text1, "view")|| !strcmp(text1, "logout")|| !strcmp(text1, "deposit")|| !strcmp(text1, "add_goods")|| !strcmp(text1, "buy")) {
			//اگر از این دستور ها قبل از لاگین استفاده شد ارور بده
		    printf("\tError: please login first to use this command.\n");
		}
		else
		{
		    //اگر دستور وارد شده با هچکدام از دستور های سیستم یکسان نبود
			printf("\tError: the command is incorrect.\n");
		}
		while (numofuser != -1)//اگر لاگین انجام شد یا به عبارت دیگر اگر یک کاربر فعلی در سیستم شناسایی شد
		{
			char* text = get_allinfo_command();//تابعی جهت گرفتن دستور ها از کاربر
			char* text1 = separate_the_only_command(text);//جداسازی کلمه اول دستور وارد شده جهت تشخیص نوع دستور
			int n = strlen(text1) + 1;
			char* text2 = separate_the_specified_command(text, n);//جداسازی کلمه دوم
			n = strlen(text1) + strlen(text2) + 2;
			char* text3 = separate_the_specified_command(text, n);//جداسازی کلمه سوم
			n = strlen(text1) + strlen(text2) + strlen(text3) + 3;
			char* text4 = separate_the_specified_command(text, n);//جداسازی کلمه چهارم
			if (!strcmp(text1, "view"))
			{
					if (role == 'b')
					{
						//نمایش اطلاعات حساب
						printf("\tUsername: %s\n", buyer[numofuser]->username);
						printf("\tRole: Buyer\n");
						printf("\tAccount Balance: %d\n", buyer[numofuser]->Account_Balance);
						if (buyer[numofuser]->count_of_goods == 0)
						{
							//اگر تعداد کالا های خریداری شده صفر بود
							printf("\tBuys: No purchase.\n");
						}
						else
						{
							for (int i = 0; i < buyer[numofuser]->count_of_goods; i++)
							{
								//نمایش اطلاعات هر خرید
								printf("\tBuy[%d]:\n\t\tName: %s\n", i + 1, buyer[numofuser]->goods[i]->name);
								printf("\t\tPrice: %d\n", buyer[numofuser]->goods[i]->price);
								printf("\t\tCount: %d\n", buyer[numofuser]->goods[i]->count);
								printf("\t\tName of seller: %s\n", buyer[numofuser]->goods[i]->sellerman);
							}
						}
					}
					else if (role == 's')
					{
						//نمایش اطلاعات حساب
						printf("\tUsername: %s\n", seller[numofuser]->username);
						printf("\tRole: Seller\n");
						printf("\tAccount Balance: %d\n", seller[numofuser]->Account_Balance);
						if (seller[numofuser]->count_of_goods == 0)
						{
							//اگر تعداد کالا های برای فروش توسط این کاربر صفر بود
							printf("\tGoods: No Goods.\n");
						}
						else
						{
							for (int i = 0; i < seller[numofuser]->count_of_goods; i++)
							{
								//نمایش اطلاعات هر کالای برای فروش توسط این کاربر
								printf("\tGoods[%d]:\n\t\tName: %s\n", i + 1, seller[numofuser]->goods[i]->name);
								printf("\t\tPrice: %d\n", seller[numofuser]->goods[i]->price);
								printf("\t\tCount: %d\n", seller[numofuser]->goods[i]->count);
							}
						}
					}
			}
			else if (!strcmp(text1, "logout"))
			{
				printf("\tyou are logout successfully.\n");
				printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
				break;
			}
			else if (!strcmp(text1, "deposit")) {
				int char_amount = char_amount_check(text2);//متغییری جهت بررسی اینکه مقادیر وارد شده عدد باشه نه حرف 
				if (role == 'b') {
					if (char_amount == 0)//اگر کاراکتری در بین رشته وجود نداشت و بزرگتر از صفر بود
					{
						buyer[numofuser]->Account_Balance += atoi(text2);//مقدار جدید را به موجودی قبلی اضافه کن
						printf("\tdeposit was successful.\n");
						printf("\tAccount Balance: %d\n", buyer[numofuser]->Account_Balance);//نشان دادن موجودی فعلی
					}
					else
						printf("\tError: the amount of money must be a number larger than zero.\n");
				}
				else if (role == 's') {
					//کاربر فروشنده اجازه استفاده از این دستور را ندارد
					printf("\tError: sorry..you are a seller and you can't use this command.\n");
				}
			}
			else if (!strcmp(text1, "add_goods")) {
				same = 0;
				if (role == 's')
				{
					//بررسی برای اینکه بفهمیم کالایی که میخواد اضافه بشه قبلا توسط شخص دیگری اضافه نشده باشه
					for (int i = 0; i < numofseller; i++)
					{
						for (int j = 0; j < seller[i]->count_of_goods; j++)
						{
							if (!strcmp(seller[i]->goods[j]->name, text2) && (i != numofuser))
							{
								//اگر یک کاربر این کالا را اضافه کرده بود و همین کاربر فعلی نبود ارور بده
								printf("\tSorry..another seller sells this product;\n\tso you can't sell it.\n");
								same = 1;//کالای یکسان
							}
						}
					}
					if (!same)
					{
						int char_amount = char_amount_check(text3);//متغییری جهت بررسی اینکه مقادیر وارد شده عدد باشه نه حرف و صفر هم نباشه
						if (char_amount == 1)
						{
							//اگر در بین رشته کاراکتر وجود داشت یا مقدار آن صفر بود ارور بده
							printf("\tError: the amount of price must be a number larger than zero.\n");
							same = 1;//برای اینکه نشان بدیم خطا داشتیم
						}
						char_amount = 2 * char_amount_check(text4);
						if (char_amount == 2)
						{
							//اگر در بین رشته کاراکتر وجود داشت یا مقدار آن صفر بود ارور بده
							printf("\tError: the count of goods must be a number larger than zero.\n");
							same = 1;
						}
						if (same == 0)//اگر ورودی های قیمت و تعداد درست بود
						{
							//اختصاص حافظه برای استراکچر کالا به تعداد یکی بیشتر از کالا های اون شخص برای فروش
							seller[numofuser]->goods = (struct goods**)realloc(seller[numofuser]->goods, (seller[numofuser]->count_of_goods + 1) * sizeof(struct goods*));
							//اختصاص حافظه برای استرکچر کالا برای هر طبقه از آن یا هر سطر آن
							seller[numofuser]->goods[seller[numofuser]->count_of_goods] = (struct goods*)malloc(sizeof(struct goods));
							//اختصاص حافظه برای نام کالا
							seller[numofuser]->goods[seller[numofuser]->count_of_goods]->name = (char*)malloc(strlen(text2) * sizeof(char));
							int add = 0;//متغییری جهت بررسی اینکه کالایی که میخواد اضافه بشه آیا قبلا توسط همین کاربر اضافه شده است یا خیر
							int goods_num = 0;//شماره کالا اگر قبلا اضافه شده بود
							//بررسی اینکه کالایی که میخواد اضافه بشه آیا قبلا توسط همین کاربر اضافه شده است یا خیر 
							for (int j = 0; j < seller[numofuser]->count_of_goods; j++)
							{
								if (!strcmp(seller[numofuser]->goods[j]->name, text2))
								{
									add = 1;//کالا قبلا اضافه شده
									goods_num = j;//شماره کالا
								}
							}
							if (add == 1)
							{
								//اگر کالا قبلا اضافه شده پس فقط به تعداد آن اضافه کن
								seller[numofuser]->goods[goods_num]->count += atoi(text4);
							}
							else
							{
								//اضافه کردن کالا
								strcpy(seller[numofuser]->goods[seller[numofuser]->count_of_goods]->name, text2);
								seller[numofuser]->goods[seller[numofuser]->count_of_goods]->price = atoi(text3);
								seller[numofuser]->goods[seller[numofuser]->count_of_goods]->count = atoi(text4);
								seller[numofuser]->count_of_goods++;
							}
							printf("\tyour product is added.\n");
						}
					}
				}
				else
					printf("\tError: sorry..you are a buyer and you can't use this command.\n");
			}
			else if (!strcmp(text1, "show_goods")) {
			     show_goods(seller, numofseller);//نشان دادن تمام کالا های سیستم
		    }
			else if (!strcmp(text1, "buy")) {
			    if (role == 'b')
			    {
					same = 0;//متغییری جهت بررسی وجود کالای مورد نظر در بین فروشنده ها
					int sellerman = -1;//متغییری جهت تشخیص شماره فرد فروشنده از بین سایر فروشنده ها
					int numofgoods = -1;//متغییری جهت اختصاص شماره کالای مورد نظر
					//بررسی نام فروشنده
					for (int i = 0; i < numofseller; i++)
					{
						if (!strcmp(text4, seller[i]->username))
						{
							sellerman = i;//تعین شماره فروشنده
						}
					}
					if (sellerman != -1)
					{
						//مطابقت دادن کالای وارد شده با تمام کالاهای فروشنده
						for (int i = 0; i < seller[sellerman]->count_of_goods; i++)
						{
							if (!strcmp(text2, seller[sellerman]->goods[i]->name))
							{
								numofgoods = i;//شماره کالای مورد نظر در بین کالا های فروشنده
								same = 1;//نشان دهنده اینکه فروشنده این کالا را دارد
							}
						}
						if (same == 0)
						{
							//اگر اون فروشنده کالای وارد شده را نداشت
							printf("\tError: name of product is incorrect.\n");
						}
						if (numofgoods != -1)
						{
							int char_amount = char_amount_check(text3);//متغییری جهت بررسی اینکه مقادیر وارد شده عدد باشه نه حرف و صفر هم نباشه
							if (char_amount != 1)
							{
								int count = atoi(text3);//تعداد کالا
								if (count <= seller[sellerman]->goods[numofgoods]->count)//مقایسه تعداد کالا با تعداد موجود
								{
									if (count*seller[sellerman]->goods[numofgoods]->price <= buyer[numofuser]->Account_Balance)//مقایسه موجودی حساب با قیمت ضرب در تعداد کالا
									{
										//قیمت کل را از موجودی حساب کاربر کم کن
										buyer[numofuser]->Account_Balance -= count * seller[sellerman]->goods[numofgoods]->price;
										//تعداد را از بین کالای فروشنده کم کن
										seller[sellerman]->goods[numofgoods]->count -= count;
										//قیمت کم شده از حساب خریدار را به حساب فروشنده اضافه کن
										seller[sellerman]->Account_Balance += count * seller[sellerman]->goods[numofgoods]->price;
										//اختصاص مجدد حافظه به تعداد خرید به اضافه یک برای استراکچر کالای خریدار
										buyer[numofuser]->goods = (struct shopping_goods**)realloc(buyer[numofuser]->goods, (buyer[numofuser]->count_of_goods + 1) * sizeof(struct shopping_goods*));
										//اختصاص یک سطر از نوع استراکچر کالای خریداری شده به حافظه اختصاص شده بالا 
										buyer[numofuser]->goods[buyer[numofuser]->count_of_goods] = (struct shopping_goods*)malloc(sizeof(struct shopping_goods));
										//اختصاص حافظه برای نام کالا
										buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->name = (char*)malloc(strlen(text2) * sizeof(char));
										//اختصاص حافظه برای نام فروشنده
										buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->sellerman = (char*)malloc(strlen(text4) * sizeof(char));
										//نگهداری مشخصات کالای خریداری شده
										strcpy(buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->name, text2);//نام کالا
										strcpy(buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->sellerman, text4);//نام فروشنده
										buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->count = count;//تعداد خریداری شده
										buyer[numofuser]->goods[buyer[numofuser]->count_of_goods]->price = seller[sellerman]->goods[numofgoods]->price;//قیمت واحد هر کالا
										buyer[numofuser]->count_of_goods++;//اضافه شده به تعداد کالا های خریداری شده توسط این کاربر 
										printf("\tThe purchase was succesful.\n");
									}
									else
									{
										printf("\tError: the account balance isn't enough.\n");
									}
								}
								else
								{
									printf("\tError: the inventory of the goods isn't enough.\n");
								}
							}
							else
								printf("\tError: the count of goods must be a number, larger than zero.\n");
						}
					}
					else
					{
						printf("\tError: seller username is incorrect\n");
					}
			    }
				else
				{
					printf("\tError: sorry..you are a seller and you can't use this command.\n");
				}
            }
			else if (!strcmp(text1, "signup") || !strcmp(text1, "login")) {
				//ارور دادن در صورت ثبت نام و یا ورود یک کاربر دیگر در حالی که کاربر قبلی هنوز لاگ اوت نکرده
			    printf("\tplease logout first to use this command.\n");
			}
			else
			{
			    printf("\tError: the command is incorrect.\n");
			}
		} 
	}
}