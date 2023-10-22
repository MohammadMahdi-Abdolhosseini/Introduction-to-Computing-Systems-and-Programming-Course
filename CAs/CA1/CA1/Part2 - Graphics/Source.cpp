#include "graphics.h"
#include <stdio.h>
#include "PentagoL_functions_graphics.h"

int main()
{
	int i, j, a = 1;
	i = 95 , j = 95;
	int exit = 0;
	
	//ساختن پنجره بازی
	initwindow(1200, 800, "PentagoL");
	setbkcolor(0);
	cleardevice();



	while(exit==0)
	{

		int turn = 1, win = 0;
		int square_number, clockwise;
		int array[6][6] = { 0 };
		//صفحه بازی رو پرینت کن
		print_board(turn, array);

		while (turn < 37)
		{
			//انتخاب مهره
			choise_block(turn, array);

			//انتخاب مربع برای چرخش
			square_number = square_number_selector(turn, array);
			
			//انتخاب جهت چرخش
			clockwise = rotate_direction(turn, array);

			//انجام چرخش
			rotation(square_number, clockwise, array);

			//صفحه بازی روپرینت کن
			print_board(turn, array);

			//اگر تعداد مهره های گذاشته شده بیشتر از 8 بود برد را چک کن چون تا قبل آن برد اتفاق نمی افتد
			if (turn > 8)
			{
				win = win_check(array);
				if (win != 0)
					break;//اگر حداقل یکی از حالت های برد اتفاق افتاد بود
			}

			//تغییر نوبت
			turn++;
		}

		//اکنون بازی تمام شده
		j = 220, a=1;
		while (1)
		{

			if (a == 1)
			{
				//پاک کردن و پرینت مجدد برای نمایش تغییرات
				cleardevice();
				print_board(turn, array);


				//اگر رنگ اول برده بود
				if (win == 1)
				{
					setcolor(6);
					setlinestyle(1, 0, 5);
					rectangle(780, 95, 1160, 163);

					setcolor(7);
					settextstyle(8, 0, 6);
					outtextxy(790, 103, "Yellow WIN!");


					/*setlinestyle(1, 0, 4);
					rectangle(775, 95, 1160, 160);
					setfillstyle(1, 8);
					floodfill(780, 100, 5);
					settextstyle(8, 0, 6);
					outtextxy(788, 103, "Yellow WIN!");*/

				}
				// اگر رنگ دوم برده بود
				if (win == 2)
				{

					setcolor(3);
					setlinestyle(1, 0, 5);
					rectangle(780, 95, 1160, 163);

					setcolor(7);
					settextstyle(8, 0, 6);
					outtextxy(790, 103, " Blue WIN!");


					/*rectangle(775, 95, 1160, 160);
					settextstyle(8, 0, 6);
					outtextxy(785, 100, "Blue WIN!");*/
				}
				//اگر بازی برنده نداشت و یا هر دو رنگ حالت برد داشتند مساوی اعلام کن
				else 
				{
					setcolor(8);
					setlinestyle(1, 0, 5);
					rectangle(780, 95, 1160, 163);

					setcolor(7);
					settextstyle(8, 0, 6);
					outtextxy(790, 103, "   Draw!");
				}

				//متن راهنمای استفاده از نرم افزار و اعلام هر مرحله از بازی
				setcolor(7);
				settextstyle(8, 0, 3);
				outtextxy(800, 220, "Play Again");
				settextstyle(8, 0, 3);
				outtextxy(800, 250, "Exit");

				settextstyle(8, 0, 2);
				outtextxy(780, 300, " use W,S keys to move.");
				settextstyle(8, 0, 2);
				outtextxy(780, 330, " press Enter to select.");

				//نمایش دایره نشانگر
				setcolor(8);
				setlinestyle(0, 0, 1);
				circle(780, j+12, 5);
				setfillstyle(1, 8);
				floodfill(780, j+10, 8);

				a = 0;
				delay(200);
			}

			//ایجاد تغییرات لازم با زدن کلیدها برای حرکت دایره نشانگر
			if (GetAsyncKeyState(87))
				if (j > 220)
					j -= 30, a = 1;
			if (GetAsyncKeyState(83))
				if (j < 250)
					j += 30, a = 1;

			//انتخاب بازی مجدد و یا خروج از بازی
			if (GetAsyncKeyState(VK_RETURN))
			{
				if (j == 250)
					exit = 1;
				break;//در صورت انتخاب خروج
			}
		}


	}

	//نمایش نام طراح نرم افزار و خروج بعد از چند لحظه
	cleardevice();
	delay(200);
	setcolor(8);
	settextstyle(10, 0, 3);
	outtextxy(495, 320, "Designed by");
	setcolor(7);
	settextstyle(8, 0, 3);
	outtextxy(505, 350, "Mohommad");
	settextstyle(8, 0, 3);
	outtextxy(510, 370, "Mahdi");
	settextstyle(8, 0, 3);
	outtextxy(515, 390, "Abdolhosseini");
	delay(1000);
	
	while (!kbhit)
	{
		delay(200);
	}

}
