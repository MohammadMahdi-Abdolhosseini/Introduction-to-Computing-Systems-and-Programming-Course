#include <stdio.h>
/***********************************
//question 7:
//number of repeat a word in text.
***********************************/
int main() {
	char text[1000] = " ";
	//متن را وارد کن:
	gets(text);
	char word[20] = " ";
	//کلمه ای را که میخوای تعداد آن شمرده شود وارد کن:
	gets(word);
	int count = 0;
	for (int i = 0; i < 1000; i++)
	{
		int j = 0;
		if ((text[i - 1] == '.' || text[i - 1] == ',' || text[i - 1] == ' ' || i == 0) && word[j] == text[i])
			//. اگر حرف اول کلمه مورد نظر توی متن پیدا شد ، فقط در صورت اینکه حرف دیگری قبل آن نبود سایر حرف ها را چک کن
		{
			while (j < 20)
			{
				if (word[j] == text[i])
				{
					i++, j++;
					if (word[j] == '\0' && (text[i] == '.' || text[i] == ',' || text[i] == ' '))
						//. زمانیکه به آخر کلمه مورد نظر رسید ، اگر حرف دیگری بعد آن در متن نبود ، تعداد رو یک واحد اضافه کن
					{
						count++;
						break;
					}
				}
				else
					break;
			}
		}
	}
	printf("%d", count);
}