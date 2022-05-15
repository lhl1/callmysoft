#include <iostream>
#include <stdio.h>
#include <ctime>
using namespace std;
bool IsLeapYear(int year)
{
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		return true;
	return false;
}
bool IsyearTrue(int year)
{//lhl
	if (year <= 0)
		return false;
	return true;
}
bool IsMonthTrue(int month)
{
	if (month < 1 || month>12)
		return false;
	return true;
}

bool IsDayTrue(int year, int month, int day)
{
	if (IsMonthTrue(month))
	{
		if (month == 4 || month == 6 || month == 9 || month == 11)
		{//lhl
			if (day >= 1 && day <= 30)
			{
				return true;
			}
			else return false;
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day >= 1 && day <= 31)
			{
				return true;
			}
			else return false;
		}
		else if (month == 2)
		{
			if (IsLeapYear(year))
			{
				if (day >= 1 && day <= 29)
					return true;
				else if (day >= 1 && day <= 28)
					return true;
			}
		}
	}
	return false;
}
int nextBirthday(int year, int month, int day)
{
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);   //获取当前年月日
	int now_year = t.tm_year + 1900;
	int now_month = t.tm_mon + 1;
	int now_day = t.tm_mday;

	//lhl

	//今年生日还没到
	int this_yearToBirthday = 0;

	if (now_month < month)
	{
		for (int i = now_month; i <= month; i++)
		{
			if (i == now_month)
			{
				if (i == 4 || i == 6 || i == 9 || i == 11)
				{
					this_yearToBirthday = this_yearToBirthday + 30 - now_day;
				}
				else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
				{//lhl
					this_yearToBirthday = this_yearToBirthday + 31 - now_day;
				}
				else if (i == 2)
				{
					if (IsLeapYear(year))
					{

						this_yearToBirthday = this_yearToBirthday + 29 - now_day;

					}
					else this_yearToBirthday = this_yearToBirthday + 28 - now_day;
				}
			}
			else  if (i == month)
			{
				this_yearToBirthday = this_yearToBirthday + day;
			}
			else
			{//lhl
				if (i == 4 || i == 6 || i == 9 || i == 11)
				{
					this_yearToBirthday = this_yearToBirthday + 30;
				}
				else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
				{
					this_yearToBirthday = this_yearToBirthday + 31;
				}
				else if (i == 2)
				{
					if (IsLeapYear(year))
					{

						this_yearToBirthday = this_yearToBirthday + 29;

					}
					else this_yearToBirthday = this_yearToBirthday + 28;
				}//lhl
			}
		}
		return this_yearToBirthday;
	}
	if (now_month == month && day >= now_day)
	{
		return day - now_day;
	}


	//不是当年生日：
	//当年剩余天数
	int this_year_remain = 1;
	for (int i = now_month; i <= 12; i++)
	{
		if (i == now_month)
		{
			if (i == 4 || i == 6 || i == 9 || i == 11)
			{//lhl
				this_year_remain = this_year_remain + 30 - now_day;
			}
			else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			{
				this_year_remain = this_year_remain + 31 - now_day;
			}
			else if (i == 2)
			{
				if (IsLeapYear(year))
				{
					this_year_remain = this_year_remain + 29 - now_day;
				}
				else this_year_remain = this_year_remain + 28 - now_day;
			}
		}
		else
		{
			if (i == 4 || i == 6 || i == 9 || i == 11)
			{
				this_year_remain = this_year_remain + 30;
			}
			else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			{
				this_year_remain = this_year_remain + 31;
			}
			else if (i == 2)
			{
				if (IsLeapYear(year + 1))
				{
					this_year_remain = this_year_remain + 29;
				}
				else this_year_remain = this_year_remain + 28;
			}
		}
		//lhl
	}
	//第二年到生日的天数
	int next_Year_next_birthday = 0;
	for (int i = 1; i <= month; i++)
	{
		if (i != month)
		{
			if (i == 4 || i == 6 || i == 9 || i == 11)
			{
				next_Year_next_birthday += 30;
			}
			else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			{
				next_Year_next_birthday += 31;
			}
			else if (i == 2)
			{//lhl
				if (IsLeapYear(year + 1))
				{

					next_Year_next_birthday += 29;

				}
				else next_Year_next_birthday += 28;
			}
		}
		else
		{
			next_Year_next_birthday += day;
		}

	}
	return  next_Year_next_birthday + this_year_remain;
}//lhl


int Calculate_the_age(int year, int month, int day)
{
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);   //获取当前年月日
	int now_year = t.tm_year + 1900;
	int now_month = t.tm_mon + 1;
	int now_day = t.tm_mday;
	int is_add_year = -1;
	if (now_month < month)
	{
		is_add_year = -1;

	}
	else if (now_month == month)
	{
		if (now_day < day)
		{
			is_add_year = -1;
		}
		else
		{
			is_add_year = 0;
		}
	}
	else
	{
		is_add_year = 0;
	}
	return now_year - year + is_add_year;
}//lhl
void cal_constellation(int month, int day)
{
	if (month == 1 && (day >= 21) || month == 2 && day <= 19)
	{
		cout << "水瓶座	01月21日 至 02月19日	创意、智慧 反叛、冷漠" << endl;
	}
	else if (month == 2 && day >= 20 || month == 3 && day <= 20)
	{
		cout << "双鱼座	02月20日 至 03月20日	浪漫、善解人意 粗心、意志薄弱" << endl;
	}
	else if (month == 3 && day >= 21 || month == 4 && day <= 20)
	{
		cout << "白羊座	03月21日 至 04月20日	积极、直率 自我、没有耐性" << endl;
	}
	else if (month == 4 && day >= 21 || month == 5 && day <= 21)
	{
		cout << "金牛座	04月21日 至 05月21日	可靠、有耐心 贪婪、古板" << endl;
	}
	else if (month == 5 && day >= 22 || month == 6 && day <= 21)
	{
		cout << "双子座	05月22日 至 06月21日	机智、适应力强 善变、不安份" << endl;
	}
	else if (month == 6 && day >= 22 || month == 7 && day <= 23)
	{
		cout << "巨蟹座	06月22日 至 07月23日	真挚、有包容力 不理性、多愁善感" << endl;
	}
	else if (month == 7 && day >= 24 || month == 8 && day <= 23)
	{
		cout << "狮子座	07月24日 至 08月23日	热心、有领导能力 武断、自以为是" << endl;
	}
	else if (month == 8 && day >= 24 || month == 9 && day <= 23)
	{
		cout << "处女座	08月24日 至 09月23日	头脑清晰、完美主义 保守、吹毛求疵" << endl;
	}
	else if (month == 9 && day >= 24 || month == 10 && day <= 23)
	{
		cout << "天秤座	09月24日 至 10月23日	和谐、平易近人 轻浮、优柔寡断" << endl;
	}
	else if (month == 10 && day >= 24 || month == 11 && day <= 22)
	{
		cout << "天蝎座	10月24日 至 11月22日	果然、实际 多疑、狂妄" << endl;
	}
	else if (month == 11 && day >= 23 || month == 12 && day <= 22)
	{
		cout << "射手座	11月23日 至 12月22日	活泼、思想开明 粗心、反覆无常" << endl;
	}//lhl
	else if (month == 12 && day >= 23 || month == 1 && day <= 22)
	{
		cout << "摩羯座	12月23日 至 01月22日	有原则、家庭观念 太现实、缺乏热情" << endl;
	}



}
bool is_true_input(int year, int month, int day)
{
	struct tm t;
	time_t now;
	time(&now);
	localtime_s(&t, &now);   //获取当前年月日
	int now_year = t.tm_year + 1900;
	int now_month = t.tm_mon + 1;
	int now_day = t.tm_mday;
	int is_add_year = -1;
	if (year > now_year)
	{
		return false;
	}

	if (month < 1 || month>12)
	{
		return false;
	}
	if (day < 1)
	{
		return false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30) return false;

	}
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day > 31) return false;
	}
	if (month == 2)
	{
		if (IsLeapYear(year))
		{
			if (day > 29) return false;
		}
		else
		{
			if (day > 28) return false;
		}
	}
	return true;
}
void showme_an(int year_input, int  month_input, int  day_input)
{
	cout << "以下为查询的数据:" <<endl;
	cout << "	年龄:  " << Calculate_the_age(year_input, month_input, day_input) << "周岁"<<endl;
	cout << "	星座: ";
	cal_constellation(month_input, day_input);

	int nextbir = nextBirthday(year_input, month_input, day_input);
	if (nextbir == 0)
	{
		cout << "	今天生日，祝TA生日快乐！" << endl;
	}
	else
	{
		cout << "	TA还有" << nextbir << "天生日" << endl;
	}
}



int main()
{
	
	cout << "请依次输入年月日,每次输入完一个数据回车结束" << endl;
	int flag_true = 1;
	while (flag_true)
	{
		int year_input;
		int month_input;
		int day_input;
		cout << "请输入年份:\n";
		cin >> year_input;
		cout << "请输入月份:\n";
		cin >> month_input;
		cout << "请输入日:\n";
		cin >> day_input;
		cout << "您的输入: " <<"\n	年： " <<year_input << "\n	月： " << month_input << "\n	日： " << day_input << endl << endl;
		if (is_true_input(year_input, month_input, day_input))
		{
			showme_an(year_input, month_input, day_input);
			flag_true = 0;
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			
		}
		
	}
	system("pause");
}