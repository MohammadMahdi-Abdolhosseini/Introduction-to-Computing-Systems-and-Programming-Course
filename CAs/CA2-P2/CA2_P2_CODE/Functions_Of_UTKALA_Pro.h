struct buyer
{
	char* username;
	char* password;
	int Account_Balance;
	struct shopping_goods* goods;
	struct buyer *next;
};
struct seller
{
	char* username;
	char* password;
	int Account_Balance;
	struct seller *next;
};
struct goods
{
	char* name;
	int price;
	int count;
	struct goods *next;
	struct seller *seller;
	float rate;
	float sum_rate;
	int count_rate;
};
struct shopping_goods
{
	char* name;
	int price;
	int count;
	char* sellerman;
	struct shopping_goods *next;
	int ratibility;
};

//get_allinfo_command: get all informatin of entered command;
char* get_allinfo_command();

//separate_the_specified_command: return a specified word in command;
char* separate_the_specified_command(char* allinfo_command, int n);

//check_repeat_buyer: check out that the buyer-account we want to signup, didn't signup before;
int check_repeat_buyer(struct buyer* buyer, char* username);

//check_repeat_seller: check out that the seller-account we want to signup, didn't signup before;
int check_repeat_seller(struct seller* seller, char* username);

//last_buyer: it will return last node of buyer struct before NULL;
struct buyer* last_buyer(struct buyer* buyer);

//add_buyer: adding a buyer account at the end of the buyer linked list;
void add_buyer(struct buyer* buyer, char* username, char* password);

//last_seller: it will return last node of seller struct before NULL;
struct seller* last_seller(struct seller* seller);

//add_seller: adding a seller account at the end of the seller linked list;
void add_seller(struct seller* seller, char* username, char* password);

//login_check_buyer: check buyer user info for login;
struct buyer* login_check_buyer(struct buyer* buyer, char* username, char* password);

//login_check_seller: check seller user info for login;
struct seller* login_check_seller(struct seller* seller, char* username, char* password);

//view_shopping_goods: print shopping goods in view command for buyers;
void view_shopping_goods(struct buyer* current_buyer);

//sorting_goods: sort by name of goods;
void sorting_goods(struct goods* goods);

//view_goods: print goods in view command for sellers;
void view_goods(struct goods* goods, struct seller* current_seller);

//show_goods: print all goods in the system;
void show_goods(struct goods* goods);

//char_amount_check: check the value if included character or was zero return 1; 
int char_amount_check(char* text);

//check_repeat_goods: check out that the goods we want to add, didn't add before;
//return 0 if it wasn't repetitive; return 1 if it was repetitive and was for someone else; return 2 if it was for himself;
int check_repeat_goods(struct goods* goods, char* name_of_goods, struct seller* current_seller);

//adding_goods: add a goods to goods-struct and link to its seller;
//stats 0 means the goods wasn't repetitive; stats 2 means it was for himself;
int adding_goods(struct goods* goods, struct seller* current_seller, char* name_of_goods, int price_of_goods, int count_of_goods, int stats);

//finding_goods: find a specified goods and return that; this function used in buy command;
//if didn't find anything or there was error, return NULL;
struct goods* finding_goods(struct goods* goods, char* name_of_goods, int count_of_goods, char* seller_username);

//last_purchase: return last node in shopping_goods for current_buyer; that's mean return NULL node and malloc that;
struct shopping_goods* last_purchase(struct buyer* current_buyer);

//remove_goods: free a specified goods node that we want to delete it;
void remove_goods(struct goods* goods, char* name_of_goods);

//change_goods_price: finding a specified goods node and change price;
int change_goods_price(struct goods* goods, struct seller* current_seller, char* name_of_goods, int new_price);

//rate_goods: you can rate goods only once per purchase; after rating ratibility = 0;
int rate_goods(struct goods* goods, struct buyer* current_buyer, char* name_of_goods, char* seller_username, char* rate);

//search_command: if match found print result;
void search_command(struct goods* goods, char* name, char* seller_username, int max_price, int min_price);

//save_buyer_in_file: save format: username:password:Account_Balance:|goods_name(1):goods_price(1):goods_count(1):goods_sellerman(1):goods_ratibility(1):|goods_name(2): ...
void save_buyer_in_file(struct buyer* buyer);

//save_seller_in_file: save format: username:password:Account_Balance:
void save_seller_in_file(struct seller* seller);

//save_buyer_in_file: save format: goods_name(1):goods_price(1):goods_count(1):goods_seller_username(1):goods_rate(1)*100:goods_count_rate(1):goods_sum_rate(1):
void save_goods_in_file(struct goods* goods);

//read_word_from_file: get a string from file until ':';
char* read_word_from_file(FILE* fptr);

//load_buyer_from_file: load and create buyers
void load_buyer_from_file(struct buyer* buyer);

//load_seller_from_file: load and create sellers
void load_seller_from_file(struct seller* seller);

//load_goods_from_file: load and create goods
void load_goods_from_file(struct goods* goods, struct seller* seller);