#include <stdio.h>
#include "FunctionsOfPentagoL.h"
void print_board(int array[][6])
{
	for (int i = 0; i < 6; i++)
	{
		//اگر خط اول بود شماره هارو پرینت کن
		if (i == 0)
			printf("  1 2 3   4 5 6\n");
		//اگر خط چهارم بود خطچین پرینت کن
		if (i == 3)
			printf("  -------------\n");
		//پرینت شماره هر ردیف
		printf("%d ", i + 1);
		for (int j = 0; j < 6; j++)
		{
			//پرینت خط مرزی
			if (j == 3)
				printf("| ");
			//پرینت آرایه ها
			if (array[i][j] == 1)
				printf("B ");
			if (array[i][j] == 2)
				printf("W ");
			//پرینت . برای نشان دادن جای خالی
			if (array[i][j] == 0)
				printf(". ");
		}
		printf("\n");
	}
}

void rotation(int square_number, int clockwise, int array[][6])
{
	//انجام حرکت چرخش
	//در صورت انتخاب چرخش ساعتگرد
	//clockwise = 1
	//که این یعنی سه بار حلقه زیر را که در واقع چرخش  پادساعتگرد است را انجام بده
	//درصورت انتخاب چرخش پادساعتگرد
	//clockwise = 3
	// که این یعنی یک بار حلقه زیر را انجام بده تا چرخش پادساعتگرد اتفاق بیفتد
	while (clockwise < 4)
	{
		//مشخص کردن مربع گرفته شده و ایجاد تغییرات لازم برای چرخاندن آن
		int m, n, p, q;
		if (square_number == 2)
			m = -1, n = -1;
		if (square_number == 1)
			m = -1, n = 2;
		if (square_number == 3)
			m = 2, n = -1;
		if (square_number == 4)
			m = 2, n = 2;

		//انجام چرخش
		p = array[m + 3][n + 1];
		array[m + 3][n + 1] = array[m + 1][n + 1];
		array[m + 1][n + 1] = array[m + 1][n + 3];
		array[m + 1][n + 3] = array[m + 3][n + 3];
		array[m + 3][n + 3] = p;
		q = array[m + 2][n + 1];
		array[m + 2][n + 1] = array[m + 1][n + 2];
		array[m + 1][n + 2] = array[m + 2][n + 3];
		array[m + 2][n + 3] = array[m + 3][n + 2];
		array[m + 3][n + 2] = q;
		clockwise++;
	}
	//در نهایت برای نمایش تغییرات صفحه را مجددا پرینت کن
	print_board(array);
}

int win_check(int array[][6])
{
	int count = 0, blackwin = 0, whitewin = 0, win = 0;
	//چک کردن برد های عمودی
	int  a = 1, b = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			//اول ببین آیا حداقل چهار تا از یک رنگ تو یک ستون پشت سر هم هست یا نه
			if (array[j][i] == a)
				count++;
			else
				count = 0;
			//اگر چهارتا از یک رنگ پشت سر هم وجود داشت الان چک کن که ابتدا و انتهای آن آیا حداقل یک مهره هم رنگ به صورت ال یا حرکت اسب وجود دارد یا نه
			if (count >= 4)
			{
				if (i == 0)
				{
					if (array[j][1] == a || array[j - 3][1] == a)
					{
						b = a;
					}
				}
				else if (i == 5)
				{
					if (array[j][4] == a || array[j - 3][4] == a)
					{
						b = a;
					}
				}
				else if (array[j][i - 1] == a || array[j][i + 1] == a || array[j - 3][i - 1] == a || array[j - 3][i + 1] == a)
				{
					b = a;
				}
				if (b == 1)
					blackwin = 1;
				if (b == 2)
					whitewin = 1;
			}
		}
		if (i == 5 && a == 1)
		{
			a = 2;//برای چک کردن برد برای رنگ دیگر در حالت عمودی
			i = -1;
		}
	}
	//چک کردن برد های افقی تقریبا مشابه با حالت عمودی
	a = 1, b = 0;
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			if (array[j][i] == a)
				count++;
			else
				count = 0;
			if (count >= 4)
			{
				if (j == 0)
				{
					if (array[1][i] == a || array[1][i - 3] == a)
					{
						b = a;
					}
				}
				else if (j == 5)
				{
					if (array[4][i] == a || array[4][i - 3] == a)
					{
						b = a;
					}
				}
				else if (array[j - 1][i] == a || array[j + 1][i] == a || array[j - 1][i - 3] == a || array[j + 1][i - 3] == a)
				{
					b = a;
				}
				if (b == 1)
					blackwin = 1;
				if (b == 2)
					whitewin = 1;
			}
		}
		if (j == 5 && a == 1)
		{
			a = 2;
			j = -1;
		}
	}
	//چک کردن برد های اریب
	a = 1, b = 0;
	int e = 0, f = 0, g = -1, h = -1;
	for (int i = 1; i < 5; i++)
	{
		//برای  بررسی حالت های اریب ابتدا تمام حالت هایی را که ابتدای سر حالت ال شکل نه خودش درون یک مربع هستش را پیدا کردم
		//سپس با توجه به تقارن چهار طرفه با حل چند معادله ریاضی متوجه ارتباط آنها با یکدیگر شدم
		//و وجود متغیر های دیگر به همین سبب است که سایر مربع های کوچک هم چک شود
		if (array[f - h * 0][e - g * 0] == a && array[f - h * 1][e - g * 1] == a && array[f - h * 2][e - g * 2] == a && array[f - h * 3][e - g * 3] == a)
			if (array[f - h * 2][e - g * 4] == a || array[f - h * 4][e - g * 2] == a)
				b = a;
		if (array[f - h * 4][e - g * 4] == a && array[f - h * 1][e - g * 1] == a && array[f - h * 2][e - g * 2] == a && array[f - h * 3][e - g * 3] == a)
			if (array[f - h * 3][e - g * 5] == a || array[f - h * 5][e - g * 3] == a)
				b = a;
		if (array[f - h * 1][e - g * 0] == a && array[f - h * 2][e - g * 1] == a && array[f - h * 3][e - g * 2] == a && array[f - h * 4][e - g * 3] == a)
			if (array[f - h * 5][e - g * 2] == a || array[f - h * 3][e - g * 4] == a)
				b = a;
		if (array[f - h * 0][e - g * 1] == a && array[f - h * 1][e - g * 2] == a && array[f - h * 2][e - g * 3] == a && array[f - h * 3][e - g * 4] == a)
			if (array[f - h * 2][e - g * 5] == a || array[f - h * 4][e - g * 3] == a)
				b = a;
		if (array[f - h * 2][e - g * 1] == a && array[f - h * 3][e - g * 2] == a && array[f - h * 4][e - g * 3] == a && array[f - h * 5][e - g * 4] == a && array[f - h * 4][e - g * 5] == a)
			b = a;
		if (array[f - h * 2][e - g * 0] == a && array[f - h * 3][e - g * 1] == a && array[f - h * 4][e - g * 2] == a && array[f - h * 5][e - g * 3] == a && array[f - h * 4][e - g * 4] == a)
			b = a;
		if (array[f - h * 1][e - g * 2] == a && array[f - h * 2][e - g * 3] == a && array[f - h * 3][e - g * 4] == a && array[f - h * 4][e - g * 5] == a && array[f - h * 5][e - g * 4] == a)
			b = a;
		if (array[f - h * 0][e - g * 2] == a && array[f - h * 1][e - g * 3] == a && array[f - h * 2][e - g * 4] == a && array[f - h * 3][e - g * 5] == a && array[f - h * 4][e - g * 4] == a)
			b = a;
		if (b == 1)
			blackwin = 1;
		if (b == 2)
			whitewin = 1;
		if (i == 1)
			e = 0, f = 5, g = -1, h = 1;
		if (i == 2)
			e = 5, f = 0, g = 1, h = -1;
		if (i == 3)
			e = 5, f = 5, g = 1, h = 1;
		if (i == 4 && a == 1)
		{
			a = 2;//چک کردن برد به حالت اریب برای رنگ دیگر
			i = 0;
		}
	}
	//اگر حالت برد برای دو رنگ اتفاق افتاده بود
	if (blackwin == 1 && whitewin == 1)
		win = 3;
	//اگر حالت برد فقط برای رنگ اول پیش آمده بود
	else if (blackwin == 1)
	{
		win = 1;
	}
	//اگر حالت برد فقط برای رنگ دوم پیش آمده بود
	else if (whitewin == 1)
	{
		win = 2;
	}
	return win;
}
