#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <algorithm>
#include <string>
#include <cstdio> 
#include <cctype>
#include <cstdio>
#include <fstream>
#include <windows.h> 
#include <ctime>
#define size 100
double revenue = 0;
int leap(int y) //判断闰年 
{
	if (y % 4 == 0 && y % 100 != 0)
		return 1;
	else if (y % 400 == 0)
		return 1;
	else
		return 0;
}
int month(int x, int y) //判断月份 
{
	if (leap(x))
	{
		if (y % 2 == 1 && y <= 7)
			return 31;
		else if (y >= 8 && y % 2 == 0)
			return 31;
		else if (y % 2 == 0 && y <= 7 && y >= 4 || y >= 8 && y % 2 == 1)
			return 30;
		else
			return 29;
	}
	else
		if (y % 2 == 1 && y <= 7)
			return 31;
		else if (y >= 8 && y % 2 == 0)
			return 31;
		else if (y % 2 == 0 && y <= 7 && y >= 4 || y >= 8 && y % 2 == 1)
			return 30;
		else
			return 28;
}
int num_f = 0, num_d = 0, num_e = 0; //actual number of array
int count_o = 0;  //actual number of array order
void sell();
void Selling_substract(int choice);
void menu();
void return_fun();
void Return_add(int choice);

void show_time() {
	time_t rawtime;
	struct tm* ptminfo;

	time(&rawtime);
	ptminfo = localtime(&rawtime);
	printf("current time : %02d/%02d/%02d %02d:%02d:%02d\n",
		ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
		ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
}
class Supermarket
{
	//public:
	string Name;
	double Cash;
	string temp;
	friend istream& operator>>(istream& in, Supermarket& A);
	friend ostream& operator<<(ostream& out, Supermarket& A);
	friend void output();
}Mymarket;

istream& operator>>(istream& in, Supermarket& A) { //重载输入运算符
	in >> A.temp >> A.Name >> A.temp >> A.Cash;
	return in;
}
ostream& operator<<(ostream& out, Supermarket& A) { //重载输出运算符
	out << "Name: " << A.Name << endl << "Cash: " << A.Cash << endl; //"Current Cash: ￥"
	return out;
}
class Goods
{
public:
	string name, color;
	string date;
	int y, m, d;//production_date
	double price;
	int quantity;
	string temp;
	int period;
	int num;
	int is_num;
	Goods()
	{
		quantity = 1;
		price = 0; //undefined item
		num = 0; //delta 
		is_num = 0;
	}
	friend Goods operator * (const int& n, Goods& g1);
	//virtual int get_type()=0; //0 Daily  //1 Food  //2 EAppliance
	virtual int get_type() { return 0; } //0 Daily  //1 Food  //2 EAppliance
	friend istream& operator>>(istream& in, Goods& A);
	friend ostream& operator<<(ostream& out, Goods& A);
	friend Goods operator + (Goods& g1, const Goods& g2); //in return
	friend Goods operator - (Goods& g1, const Goods& g2); //out sell	
	Goods& operator = (const Goods& g2) { //out sell
		name = g2.name;
		color = g2.color;
		date = g2.date;
		y = g2.y;
		m = g2.m;
		d = g2.d;
		price = g2.price;
		quantity = g2.quantity;
		period = g2.period;
		return *this;
	}
};
Goods operator * (const int& n, Goods& g1) {
	g1.quantity *= n;		return g1;
}
Goods operator + (Goods& g1, const Goods& g2) {	//if(g1.name==g2.name){
	g1.quantity += g2.quantity; return g1;}// else cout<<"Error when +";}
Goods operator - (Goods& g1, const Goods& g2) {	//if(g1.name==g2.name){
	if (g1.quantity >= g2.quantity) {
		g1.quantity -= g2.quantity;
		return g1;
	}
	else cout << "Transaction failed. Not enough Goods existed.";
}		
class DailyGoods : public Goods
{
public:

	virtual int get_type()
	{
		return 0;
	}
}daily[size];
class Food : public Goods
{
public:
	int period_g; //guarantee_period
	virtual int get_type()
	{
		return 1;
	}
}food[size];
class Electrical_Appliance : public Goods
{
public:
	virtual int get_type()
	{
		return 2;
	}
	string color;
	//int period_m; //maintenance_period 
}ele[size];
istream& operator>>(istream& in, Goods& A) { //重载输入运算符
	in >> A.temp >> A.name >> A.temp ;
	if(A.is_num==0)
	in>> A.quantity ;
	else
	in>> A.num; //order_delta_num
	in>> A.temp >> A.date;
	if (!A.get_type()); //0 Daily  
	else if (A.get_type() == 1) //1 F 
		in >> A.temp >> A.period;
	else if (A.get_type() == 2)//2 EA
		in >> A.temp >> A.color >> A.temp >> A.period;
	in >> A.temp >> A.price;
	return in;
}
ostream& operator<<(ostream& out, Goods& A) { //重载输出运算符
	out << "name: " << A.name << endl << "quantity: " ;
	if(A.is_num==0)
	out<< A.quantity ;
	else
	out<< A.num;//order_delta_num
	out << endl << "production_date: " << A.date << endl;
	if (!A.get_type()); //0 Daily
	else if (A.get_type() == 1) //1 F 
		out << "guarantee_period: " << A.period << endl;
	else if (A.get_type() == 2)//2 EA
		out << "color: " << A.color << endl << "maintenance_period: " << A.period << endl;
	out << "price: " << A.price << endl << endl;
	return out;
}
class Order {
public:
	int y, m, d;//production_date
	int ID;
	string time;
	string reason;
	Goods* p[size];
	double money;
public:
	Order()
	{
		ID = 100001;
		time = "2021/10/1";
		money = 0;
	}
};
class out : public Order//购货单 
{
public:void output_o()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "****** Order 购货单 ******\n";
	ofstream out_file("./order_out.txt"); //in All; 1,2,3Goods only
	if (!out_file) { cout << "\nError when exporting the file\n\n"; exit(-1); }
	cout << "Order ID: " << ID << endl;
	out_file << "Order ID: " << ID << endl;
	cout << "Transaction Time: " << time << endl;
	out_file << "Transaction Time: " << time << endl;
	cout << endl << ">>>Exporting order... Please wait. 订单导出中 ... 请耐心等待 .<<<" << endl;
	cout << "---List of Goods---" << endl;
	out_file << "---List of Goods---" << endl;
	money = 0;
	for (int i = 0; i < count_o; i++) {
		cout << *p[i], out_file << *p[i], money += p[i]->price * p[i]->num;
		p[i]->is_num=0;
	}
	cout << "Total cost: " << money << endl, out_file << "Total cost: " << money << endl; revenue += money;
	cout << "******Exporting order Successfully! 订单导出成功！******\n\n";
	cout << "\nPlease press enter to go back to main menu.";
	char c; getchar();//case3
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	count_o = 0; menu();
}
}order;
class in : public Order  //退货单
{
public:void output_i()
{
	system("cls");
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "****** Return 退货单 ******\n";
	ofstream out_file("./return_out.txt"); //in All; 1,2,3Goods only
	if (!out_file) { cout << "\nError when exporting the file\n\n"; exit(-1); }
	cout << "Order ID: " << ID << endl;
	out_file << "Order ID: " << ID << endl;
	cout << "Transaction Time: " << time << endl;
	out_file << "Transaction Time: " << time << endl;
	cout << endl << ">>>Exporting order... Please wait. 订单导出中 ... 请耐心等待 .<<<" << endl;
	cout << "Reason 退货理由： " << reason << endl;
	out_file << "Reason 退货理由： " << reason << endl;
	cout << "---List of Goods---" << endl;
	out_file << "---List of Goods---" << endl;
	count_o = 1;
	for (int i = 0; i < count_o; i++) {
		cout << *p[i], out_file << *p[i], money += p[i]->price * p[i]->num;	p[i]->is_num=0;
	}
	cout << "Total cost: " << money << endl, out_file << "Total cost: " << money << endl; revenue -= money;
	cout << "******Exporting order Successfully! 订单导出成功！******\n\n";
	cout << "\nPlease press enter to go back to main menu.";
	char c; getchar();//case3
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	count_o = 0; menu();
}
}in;
void input()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******System Initializing系统初始化******\n";
	ifstream in_file("./market_out.txt"); //in All; 1,2,3Goods only
	//ifstream in_file("./market_in.txt");
	if (!in_file) { cout << "\nError when importing the file\n\n"; exit(-1); }
	else cout << ">>>Importing data... 数据导入中 ... <<<\n\n";

	string temp, category;
	in_file >> Mymarket;//Supermarket
	cout << Mymarket;
	cout << endl << endl << ">>>Initializing Goods... Please wait. 货物数据初始化中 ... 请耐心等待 .<<<" << endl;
	int i = 0, j = 0, k = 0;
	while (in_file >> temp >> category)
	{
		if (category == "food") {
			in_file >> food[i];	cout << food[i++];
		}
		else if (category == "DailyGoods") {
			in_file >> daily[j];	cout << daily[j++];
		}
		else if (category == "ElectricalAppliance") {
			in_file >> ele[k];	cout << ele[k++];
		}
	}
	num_f = i, num_d = j, num_e = k;
	cout << "******Importing data Successfully! 数据导入成功！******\n\n";
	in_file.close();
}
void output()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******Save保存信息******\n";
	Mymarket.Cash += revenue;
	ofstream out_file("./market_out.txt"); //in All; 1,2,3Goods only
	if (!out_file) { cout << "\nError when exporting the file\n\n"; exit(-1); }
	else cout << endl << endl << ">>>Exporting data... Please wait.数据导出中 ... 请耐心等待 .<<<" << endl;

	string temp, category;
	out_file << Mymarket;//Supermarket
	cout << Mymarket;
	for (int i = 0; i < num_f; i++) {  //to be done
		out_file << "category: food" << endl;
		out_file << food[i];	cout << food[i];
	}
	for (int i = 0; i < num_d; i++) {
		out_file << "category: DailyGoods" << endl;
		out_file << daily[i];	cout << daily[i];
	}
	for (int i = 0; i < num_e; i++) {
		out_file << "category: ElectricalAppliance" << endl;
		out_file << ele[i];	cout << ele[i];
	}
	out_file.close();
	cout << "******Exporting data Successfully! 数据导出成功！******\n\n";
	cout << "\nPlease press enter to go back to main menu.";
	char c; getchar();//case3
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	menu();
}
void display(int type_k)
{
	if (type_k == 0) {
		cout << "category: food" << endl;
		for (int i = 0; i < num_f; i++) {
			cout << food[i];
		}
	}
	if (type_k == 1) {
		cout << "category: DailyGoods" << endl;
		for (int i = 0; i < num_d; i++) {
			cout << daily[i];
		}
	}
	if (type_k == 2) {
		cout << "category: ElectricalAppliance" << endl;
		for (int i = 0; i < num_e; i++) {
			cout << ele[i];
		}
	}
}
void display()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******Query查询商品******\n";
	display(0); display(1); display(2);
	cout << "Please press enter to go back to main menu.";
	char c; getchar();//case3
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	menu();
}
void revenue_fun()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******Revenue￥今日营业额******\n";
	cout << "\n\n\n\n\n\nRevenue今日营业额: ￥" << revenue << endl;
	cout << "\n\n\n\n\n\nPlease press enter to go back to main menu.";
	char c; getchar();//case3
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	menu();
}
void menu()
{
	int num_menu;
loop:
	system("cls");
	cout << "****** Supermarket Management System ******\n\n\n****** Software Menu Page 菜单界面 ******\n\n";
	cout << "①Sell商品售出\n②Return退货服务\n③Query查询商品\n④Revenue￥今日营业额\n⑤Save保存信息\n⑥Back to main menu <-返回主菜单\n\n\n您要进行的操作是？";
	cout << "\nPlease enter here with only an integer:";
	cin >> num_menu;
	switch (num_menu)
	{
	case 1:system("cls"); sell(); Sleep(5); break;
	case 2:system("cls"); return_fun(); Sleep(5); break;
	case 3:system("cls"); //Query
		display(); break;
	case 4:system("cls"); revenue_fun(); Sleep(5); break;
	case 5:system("cls");//save
		output(); Sleep(5); break;
	case 6:system("cls"); cout << "Back to main menu <-"; break;
	default:cout << "Input Error!Please enter an integer which is between 1 and 6."; Sleep(5); system("cls");
	}
	goto loop;
}
void sell()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******Sell商品售出******\n";
	cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n出售哪种商品？";
	cout << "\nUsing the number to represent the type of Goods to be sold,";
	cout << "\nPlease enter here with only an integer 请输入售出商品代码:";
	int num_menu; count_o = 0;
	int choice;
	while (cin >> num_menu) {
		switch (num_menu)//sell
		{
		case 0: break;
		case 1:choice = num_menu; system("cls"); //DailyGoods
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品售出******\n";
			display(1); Selling_substract(1);
			cout << "******Sell商品售出******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n出售哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be sold,";
			cout << "\nPlease enter here with only an integer 请输入售出商品代码:[enter 0 to exit]"; break;
		case 2:choice = num_menu;
			system("cls"); //Food
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品售出******\n";
			display(0); Selling_substract(0);
			cout << "******Sell商品售出******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n出售哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be sold,";
			cout << "\nPlease enter here with only an integer 请输入售出商品代码:[enter 0 to exit]"; break;
		case 3:choice = num_menu;
			system("cls"); //EA
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品售出******\n";
			display(2); Selling_substract(2);
			cout << "******Sell商品售出******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n出售哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be sold,";
			cout << "\nPlease enter here with only an integer 请输入售出商品代码:[enter 0 to exit]"; break;
		default:cout << "Input Error!Please enter an integer which is between 1 and 3.";
		}if (num_menu == 0) break;
	}
	system("cls");
	order.output_o();
}
void Selling_substract(int choice)
{
	Goods Temp;
	cout << "---Goods to be sold售出商品信息---\nname英文名称 : ";
	string name;
	cin >> name;
	cout << "Quantity售卖数量 (an integer): ";
	int num, i;
	cin >> num;
	if (choice == 0) {
		for (i = 0; i < num_f; i++)
			if (food[i].name == name) break;
		if (food[i].name == name) {
			food[i] - num * Temp;
			cout << "\n ******update:******" << endl;//rest
			cout << food[i];
			food[i].is_num=1;			food[i].num = num;
			order.p[count_o++] = &food[i];
		}
	}
	if (choice == 1) {
		for (i = 0; i < num_d; i++)
			if (daily[i].name == name) break;
		if (daily[i].name == name) {
			daily[i] - num * Temp;
			cout << "\n ******update:******" << endl;
			cout << daily[i];
			daily[i].is_num=1;			daily[i].num = num;
			order.p[count_o++] = &daily[i];
		}
	}
	if (choice == 2) {
		for (i = 0; i < num_e; i++)
			if (ele[i].name == name) break;
		if (ele[i].name == name) {
			ele[i] - num * Temp;
			cout << "\n ******update:******" << endl;
			cout << ele[i];
			ele[i].is_num=1;ele[i].num = num;
			order.p[count_o++] = &ele[i];
		}
	}
}
void return_fun()
{
	cout << "****** Supermarket Management System ******\n\n\n";
	cout << "******Return退货服务******\n";
	cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n退货哪种商品？";
	cout << "\nUsing the number to represent the type of Goods to be returned,";
	cout << "\nPlease enter here with only an integer 请输入退货商品代码:";
	int num_menu; int choice;
	while (cin >> num_menu) {
		switch (num_menu)//sell
		{
		case 0: break;
		case 1:system("cls"); choice = num_menu;//DailyGoods
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品退货******\n";
			display(1); Return_add(1);
				cout << "******Return退货服务******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n退货哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be returned,";
			cout << "\nPlease enter here with only an integer 请输入退货商品代码:[enter 0 to exit]"; break;
		case 2:choice = num_menu;
			system("cls"); //Food
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品退货******\n";
			display(0); Return_add(0);
			cout << "******Return退货服务******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n退货哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be returned,";
			cout << "\nPlease enter here with only an integer 请输入退货商品代码:[enter 0 to exit]"; break;
		case 3:choice = num_menu;
			system("cls"); //EA
			cout << "****** Supermarket Management System ******\n\n\n";
			cout << "******Sell商品退货******\n";
			display(2); Return_add(2);
			cout << "******Return退货服务******\n";
			cout << "①DailyGoods 日常用品类\n②Food 食品类\n③Electrical Appliance 家电类\n\n\n退货哪种商品？";
			cout << "\nUsing the number to represent the type of Goods to be returned,";
			cout << "\nPlease enter here with only an integer 请输入退货商品代码:[enter 0 to exit]"; break;
		default:cout << "Input Error!Please enter an integer which is between 1 and 3.";
		}if (num_menu == 0) break;
	}
	in.output_i();
}
void Return_add(int choice)
{
	Goods Temp;
	cout << "---Goods to be returned 退货信息---\nname英文名称 : ";
	string name;
	cin >> name;
	cout << "Quantity退货数量 (an integer): ";
	int num, i;
	cin >> num;
	count_o = 0;
	cout << "Order ID 订单编号 (int): ";
	string ID;
	cin >> in.ID;
	string reason;
	cout << "Reason 退货原因: "; getchar();
	getline(cin, in.reason);
	if (choice == 0) {
		for (i = 0; i < num_f; i++)
			if (food[i].name == name) break;
		food[i] + num * Temp;
		cout << "\n ******update:******" << endl;
		cout << food[i];
			food[i].is_num=1;			food[i].num = num;
		in.p[count_o++] = &food[i];
	}
	if (choice == 1) {
		for (i = 0; i < num_d; i++)
			if (daily[i].name == name) break;
		daily[i] + num * Temp;
		cout << "\n ******update:******" << endl;
		cout << daily[i];
			daily[i].is_num=1;			daily[i].num = num;
		in.p[count_o++] = &daily[i];
	}
	if (choice == 2) {
		for (i = 0; i < num_e; i++)
			if (ele[i].name == name) break;
		ele[i] + num * Temp;
		cout << "\n ******update:******" << endl;
		cout << ele[i];
		ele[i].is_num=1;			ele[i].num = num;
		in.p[count_o++] = &ele[i];
	}
}
int main()
{
	input();
	Sleep(2);
	cout << "Please press enter to the system now.";
	char c;
	while (c = getchar()) {
		if (c == '\n')  break;
	} //carriage return;
	menu();
	return 0;
}
