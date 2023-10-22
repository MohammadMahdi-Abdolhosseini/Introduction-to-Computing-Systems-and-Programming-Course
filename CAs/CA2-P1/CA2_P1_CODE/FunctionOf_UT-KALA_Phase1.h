struct buyer
{
	char* username;
	char* password;
	int Account_Balance;
	struct shopping_goods** goods;
	int count_of_goods;
};
struct seller
{
	char* username;
	char* password;
	int Account_Balance;
	struct goods** goods;
	int count_of_goods;
};
struct goods
{
	char* name;
	int price;
	int count;
};
struct shopping_goods
{
	char* name;
	int price;
	int count;
	char* sellerman;
};

char* get_allinfo_command();

char* separate_the_only_command(char* allinfo_command);

char* separate_the_specified_command(char* allinfo_command, int n);

struct buyer* add_buyer(char* username, char* password);

struct seller* add_seller(char* username, char* password);

void show_goods(struct seller** seller, int numofseller);

int char_amount_check(char* text);
