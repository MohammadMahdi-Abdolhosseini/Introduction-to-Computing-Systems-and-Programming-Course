#include "graphics.h"
void print_board(int turn, int array[][6])
{
	//کشیدن کادر و مربع های بازی
	setcolor(5);
	setlinestyle(0, 0, 5);
	rectangle(40, 40, 750, 750);

	setcolor(13);
	setlinestyle(4, 0, 4);
	line(43, 395, 750, 395);
	setcolor(13);
	setlinestyle(4, 0, 4);
	line(395, 43, 395, 750);

	//تعین نوبت
	if (turn % 2 == 1)
	{
		setcolor(6);
		settextstyle(10, 0, 4);
		outtextxy(780, 50, "it's Yellow turn");
	}
	else
	{
		setcolor(3);
		settextstyle(10, 0, 4);
		outtextxy(780, 50, "it's Blue turn");
	}
	//کشیدن دایره های صفحه بازی
	for (int a = 0, i = 95; i < 800 || a < 6; i += 120, a++)
	{
		for (int b = 0, j = 95; j < 800 || b < 6; j += 120, b++)
		{
			//کشیدن دایره های خالی
			if (array[a][b] == 0)
			{
				setcolor(8);
				setlinestyle(2, 0, 3);
				circle(i, j, 35);
			}
			//نشان دادن مهره های رنگ زرد
			else if (array[a][b] == 1)
			{
				setcolor(6);
				setlinestyle(0, 0, 1);
				circle(i, j, 36);
				setfillstyle(5, 6);
				floodfill(i, j, 6);
			}
			//نشان دادن مهره های رنگ آبی
			else if (array[a][b] == 2)
			{
				setcolor(3);
				setlinestyle(0, 0, 1);
				circle(i, j, 36);
				setfillstyle(4, 3);
				floodfill(i, j, 3);
			}
		}
	}
}

void choise_block(int turn, int array[][6])
{
	int a = 1, i = 95, j = 95, m = 0, n = 0;
	while (1)
	{
		//انتخاب جا برای قرار دادن مهره توسط دایره نشانگر
		if (a == 1)
		{
			//پاک کردن و پرینت مجدد برای نشان دادن تغییرات
			cleardevice();
			print_board(turn, array);

			
			//متن راهنمای استفاده از نرم افزار و اعلام هر مرحله از بازی
			setcolor(7);
			settextstyle(8, 0, 3);
			outtextxy(780, 100, "Select Slot");

			settextstyle(8, 0, 2);
			outtextxy(780, 160, " use A,S,D,W keys to move.");
			settextstyle(8, 0, 2);
			outtextxy(780, 190, " press Enter to select.");

			//نمایش دایره نشانگر
			setcolor(7);
			setlinestyle(0, 0, 10);
			circle(i, j, 36);
			a = 0;
			delay(200);
		}

		//استفاده از کلید ها و انجام تغییرات برای نشان دادن حرکت دایره نشانگر
		if (GetAsyncKeyState(65))
			if (i > 95)
				i -= 120, a = 1, m -= 1;
		if (GetAsyncKeyState(68))
			if (i < 695)
				i += 120, a = 1, m += 1;
		if (GetAsyncKeyState(87))
			if (j > 95)
				j -= 120, a = 1, n -= 1;
		if (GetAsyncKeyState(83))
			if (j < 695)
				j += 120, a = 1, n += 1;

		//در صورت انتخاب محل قرارگیری مهره
		if (GetAsyncKeyState(VK_RETURN))
		{
			//اگر خانه انتخاب شده پر بود علامت بده که پره
			if (array[m][n] == 1)
			{
				setcolor(4);
				setlinestyle(0, 0, 7);
				circle(i, j, 36);
				setcolor(4);
				setlinestyle(0, 0, 8);
				line(i + 22, j - 22, i - 22, j + 22);
			}
			else if (array[m][n] == 2)
			{
				setcolor(5);
				setlinestyle(0, 0, 7);
				circle(i, j, 36);
				setcolor(5);
				setlinestyle(0, 0, 8);
				line(i - 22, j - 22, i + 22, j + 22);

			}
			//اگر خانه انتخاب شده خالی بود مهره را بذار
			else if (array[m][n] == 0)
			{

				if (turn % 2 == 1)
					array[m][n] = 1;
				else
					array[m][n] = 2;
				break;
			}

		}
	}
}

void rotation(int square_number, int clockwise, int array[][6])
{
	//clockwise = ساعتگرد
	//اگر متغییر "ساعتگرد" یک بود در واقع انتخاب جهت چرخش پادساعتگرد بوده پس باید سه بار چرخش ساعتگرد انجام شود
	//اگر هم مقدار آن 3 بود انتخاب جهت ساعتگرد بوده و کافیست یک بار چرخش انجام شود
	while (clockwise < 4)
	{
		//انجام تغییرات برای چرخش با توجه به مربع انتخاب شده
		int m, n, p, q;
		if (square_number == 1)
			m = -1, n = -1;
		if (square_number == 3)
			m = -1, n = 2;
		if (square_number == 2)
			m = 2, n = -1;
		if (square_number == 4)
			m = 2, n = 2;

		//انجام تغییرات لازم برای چرخش
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
}

int rotate_direction(int turn, int array[][6])
{
	int a = 1, b, j = 170, clockwise = 1;

	//انتخاب جهت چرخش
	while (1)
	{

		if (a == 1)
		{
			//پاک کردن و پرینت مجدد برای نشان دادن تغییرات
			cleardevice();
			print_board(turn, array);

			//متن راهنمای استفاده از نرم افزار و اعلام هر مرحله از بازی
			setcolor(7);
			settextstyle(8, 0, 3);
			outtextxy(780, 100, "Select Rotate Direction");
			settextstyle(8, 0, 3);
			outtextxy(800, 160, "Clockwise");
			settextstyle(8, 0, 3);
			outtextxy(800, 190, "Counter-Clockwise");

			settextstyle(8, 0, 2);
			outtextxy(780, 250, " use W,S keys to move.");
			settextstyle(8, 0, 2);
			outtextxy(780, 280, " press Enter to select.");

			// تعین رنگ مناسب و حالت آن برای دایره نشانگر با توجه به نوبت هر بازیکن
			if (turn % 2 == 1)
			{
				setcolor(6);
				setlinestyle(0, 0, 1);
				circle(780, j, 10);
				setfillstyle(5, 6);
				floodfill(780, j, 6);
			}
			else
			{
				setcolor(3);
				setlinestyle(0, 0, 1);
				circle(780, j, 10);
				setfillstyle(4, 3);
				floodfill(780, j, 3);
			}

			a = 0;
			delay(200);
		}
		//ایجاد تغییرات لازم با حرکت داد دایره نشانگر
		if (GetAsyncKeyState(87))
			if (j > 170)
				j -= 30, a = 1;
		if (GetAsyncKeyState(83))
			if (j < 200)
				j += 30, a = 1;

		//انتخاب جهت چرخش انجام شد
		if (GetAsyncKeyState(VK_RETURN))
		{
			//اگر انتخاب شد که پاد ساعتگرد بچرخه
			if (j == 200)
				return clockwise;//مقدار متغییر که یک هستش را برگردون
			else
			{
				clockwise += 2;
				return clockwise;//انتخاب جهت ساعتگرد پس مقدار متغییر به اضافه 2 را برگردون که میشه 3
			}

		}
	}
}

int square_number_selector(int turn, int array[][6])
{

	int a = 1, i = 50, j = 50, m = 1, n = 0;

	while (1)
	{
		if (a == 1)
		{
			//پاک کردن و پرینت مجدد برای نشان دادن تغییرات
			cleardevice();
			print_board(turn, array);

			//متن راهنمای استفاده از نرم افزار و اعلام هر مرحله از بازی
			setcolor(7);
			settextstyle(8, 0, 3);
			outtextxy(780, 100, "Select Square Number");

			settextstyle(8, 0, 2);
			outtextxy(780, 160, " use A,S,D,W keys to move.");
			settextstyle(8, 0, 2);
			outtextxy(780, 190, " press Enter to select.");

			//کشیدن مربع نشانگر
			setcolor(7);
			setlinestyle(0, 0, 5);
			rectangle(i, j, i + 330, j + 330);
			a = 0;
			delay(200);
		}

		//ایجاد تغییرات لازم با زدن هر کلید برای نشان دادن حرکت مربع نشانگر
		if (GetAsyncKeyState(65))
			if (i > 50)
				i -= 360, a = 1, m -= 1;
		if (GetAsyncKeyState(68))
			if (i < 330)
				i += 360, a = 1, m += 1;
		if (GetAsyncKeyState(87))
			if (j > 50)
				j -= 360, a = 1, m -= 2;
		if (GetAsyncKeyState(83))
			if (j < 330)
				j += 360, a = 1, m += 2;
		
		//انتخاب مربع با زدن اینتر
		if (GetAsyncKeyState(VK_RETURN))
		{
			return m;
		}
	}

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