#include <stdio.h>
#include "FunctionsOfPentagoL.h"
int main()
{
	int turn = 1, win=0;
	int array[6][6] = {0};
	while (2 > 1)
	{
		//پرینت صفحه بازی
		print_board(array);
		int x, y;
		while (2 > 1)
		{
			int num;

			//نمایش نوبت
			if (turn % 2 == 1)
				printf("Black Turn");
			else
				printf("White Turn");

			//گرفتن ورودی برای جای قرارگیری مهره
			printf("\nEnter value of i,j . please enter a two digits number: ");
			int ch = scanf_s("%d", &num);
			y = num / 10;
			x = num % 10;
			//بررسی خطاها
			if (x > 6 || x < 1 || y > 6 || y < 1 || array[y - 1][x - 1] == 1 || array[y - 1][x - 1] == 2)
			{
				printf("Error: ");
				//بررسی ورود کاراکتر
				if (ch != 1)
				{
					printf("you entered a character; ");
					num = scanf_s("%c", &ch);//خالی کردن بافر از کاراکتر وارد شده
				}
				printf("Try Again!\n");
			}
			//درصورت عدم وجود خطا حلقه را متوقف کن
			else
				break;
		}
		
		//اختصاص دادن جای انتخاب شده به بازیکنی که نوبتش هست
		if (turn % 2 == 1)
			array[y - 1][x - 1] = 1;
		else
			array[y - 1][x - 1] = 2;

		//پرینت بازی برای نمایش تغییرات انجام شده 
		print_board(array);

		int square_number;
		int rotate_direction;


		while (2 > 1)
		{
			//گرفتن ورودی برای شماره مربع
			printf("Enter Square Number: ");
			int ch = scanf_s("%d", &square_number);
			
			//بررسی خطاها
			if (square_number > 4 || square_number < 1)
			{
				printf("Error: only 1,2,3 or 4 ; ");

				//بررسی ورود کاراکتر
				if (ch != 1)
				{
					printf("you entered a character; ");
					scanf_s("%c", &ch);
				}
				printf("Try Again!\n");
			}
			//در صورت عدم وجود خطا حلقه را متوقف کن
			else
				break;
		}
		while (2 > 1)
		{
			//گرفتن ورودی برای جهت چرخش
			printf("Enter Rotate Direction (1 for clockwise , 2 for counter-clockwise): ");
			int ch = scanf_s("%d", &rotate_direction);

			//بررسی خطاها
			if (rotate_direction < 1 || rotate_direction > 2)
			{
				printf("Error: only 1 or 2 \n");
				//بررسی ورود کاکتر
				if (ch != 1)
				{
					printf("you entered a character; ");
					scanf_s("%c", &ch);
				}
				printf("Try Again!\n");
			}
			//در صورت عدم وجود خطا حلقه را متوقف کن
			else
				break;
		}

		int clockwise;
		if (rotate_direction == 1)
			clockwise = 1;
		else
			clockwise = 3;

		//چرخش را انجام بده
		rotation(square_number, clockwise, array);

		//اگر بیشتر از 8 مهره رو صفحه بود برد را چک کن چون تا قبل آن هیچ حالت بردی اتفاق نمی افتد
		if (turn > 8)
		{
			//چک کردن حالت های برد
			win = win_check(array);
			if (win != 0)
				break;//اگر حالت برد اتفاق افتاده بود حلقه را متوقف کن
		}
		//اگر 36 خونه پر شده بود مساوی اعلام کن
		if (turn == 36) {
			win = 3;
			break;
		}
		turn++;
	}

	//اعلام نتیجه بازی
	if (win == 1)
		printf("Black win");
	if (win == 2)
		printf("White win");
	if (win == 3)
		printf("Draw");
	getchar();
}

