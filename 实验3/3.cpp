#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
using namespace std;
int number_of_cards_left(int *pai)
{
	int sum_num = 0;
	for (int i = 3; i <= 17; i++)
	{
		sum_num = sum_num + pai[i];
	}
	return sum_num;
}
void deal_to(int *pai, int *who, int where,int deal_num)
{
	if (number_of_cards_left(pai) < 3)
		return;
	srand((unsigned)time(NULL)+ deal_num*1123);
	int rand_1 = (rand() % 15 + 3);
	while (pai[rand_1] <= 0)
	{
		rand_1 = (rand() % 15 + 3);
		if (pai[rand_1] != 0)
		{
			break;
		}
	}
	--pai[rand_1];
	who[where] = rand_1;
}
void deal_to_handown(int *pai,int *cards_in_one_hand,int cards_in_one_hand_p)
{
	for (int i = 3; i <= 17; i++)
	{
		while (pai[i] != 0)
		{
			cards_in_one_hand[cards_in_one_hand_p++] = i;
			--pai[i];
		}
	}
}
void show_pai(int *pai)
{
	for (int i = 3; i <= 17; i++)
	{
		cout << pai[i] << " ";
	}
	cout << endl;
}
void show_player(int *player)
{
	for (int i = 1; i <= 17; i++)
	{
		cout << player[i] << " ";
	}
	cout << endl;
}
void show_cards_in_one_hand(int *cards_in_one_hand)
{
	for (int i = 1; i <= 3; i++)
	{
		cout << cards_in_one_hand[i] << " ";
	}
	cout << endl;

}
void myquicksort(int *arr, int start, int end)
{
	if (start >= end)
		return;
	int pos = arr[start];
	int left = start;
	int right = end;
	while (left < right) {
		while (left < right && pos <= arr[right]) right--;
		arr[left] = arr[right];
		while (left < right && pos >= arr[left]) left++;
		arr[right] = arr[left];
	}
	arr[left] = pos;
	myquicksort(arr, start, left - 1);
	myquicksort(arr, left + 1, end);


}
void show_me_player(int *player)
{
	for (int i = 1; i <= 17; i++)
	{
		switch (player[i])
		{
		case 11:
			cout << "J" << " ";
			break;
		case 12:
			cout << "Q" << " ";
			break;
		case 13:
			cout << "K" << " ";
			break;
		case 14:
			cout << "A" << " ";
			break;
		case 15:
			cout << "2" << " ";
			break;
		case 16:
			cout << "小王" << " ";
			break;
		case 17:
			cout << "大王" << " ";
			break;
		default:
			cout << player[i] << " ";
		}
	}
	cout << endl;
}
void show_hands(int *hand)
{
	for (int i = 1; i <= 3; i++)
	{
		switch (hand[i])
		{
		case 11:
			cout << "J" << " ";
			break;
		case 12:
			cout << "Q" << " ";
			break;
		case 13:
			cout << "K" << " ";
			break;
		case 14:
			cout << "A" << " ";
			break;
		case 15:
			cout << "2" << " ";
			break;
		case 16:
			cout << "小王" << " ";
			break;
		case 17:
			cout << "大王" << " ";
			break;
		default:
			cout << hand[i] << " ";
		}
	}
	cout << endl;
}

int main()
{
	srand((unsigned)time(NULL));
	int flag = 1;
	while (1)
	{
		int pai[18] = { 0 };
		for (int i = 3; i <= 15; i++)
		{
			pai[i] = 4;
		}
		for (int i = 16; i <= 17; i++)
		{
			pai[i] = 1;
		}
		for (int i = 0; i <= 17; i++)
		{
			//cout << pai[i] << " ";
		}
		int play_1[18] = { 0 };
		int play_1_p = 1;
		int play_2[18] = { 0 };
		int play_2_p = 1;
		int play_3[18] = { 0 };
		int play_3_p = 1;
		int cards_in_one_hand[4] = { 0 };
		int cards_in_one_hand_p = 1;
		int deal_num = 1;
		while (number_of_cards_left(pai) > 3)
		{
			deal_to(pai, play_1, play_1_p, deal_num);
			++play_1_p;
			++deal_num;

			deal_to(pai, play_2, play_2_p, deal_num);
			++play_2_p;
			++deal_num;

			deal_to(pai, play_3, play_3_p, deal_num);
			++play_3_p;
			++deal_num;
		}
		cout << "Player1:  ";
		show_player(play_1);   //展示player1
		cout << "Player2:  ";
		show_player(play_2);	//展示player2
		cout << "Player3:  ";
		show_player(play_3);	//展示player3
		cout << "底牌:  ";
		show_pai(pai);			//底牌玩家发牌结果

		deal_to_handown(pai, cards_in_one_hand, cards_in_one_hand_p);    //底牌回收


		show_cards_in_one_hand(cards_in_one_hand);   //展示底牌
		cout << "--------------------" << endl;
		myquicksort(play_1, 1, 17);   //快排player
		myquicksort(play_2, 1, 17);	  //快排player		
		myquicksort(play_3, 1, 17);	  //快排player	
		myquicksort(cards_in_one_hand, 1, 3);

		cout << "排序后Player1:  ";
		show_player(play_1);   //展示player1
		cout << "排序后Player2:  ";
		show_player(play_2);	//展示player2
		cout << "排序后Player3:  ";
		show_player(play_3);	//展示player3
		cout << "排序后底牌:  ";
		show_cards_in_one_hand(cards_in_one_hand);   //展示底牌
		cout << endl << endl << "---------------------最终结果---------------------" << endl;


		cout << "Player1:  ";
		show_me_player(play_1);
		cout << "Player2:  ";
		show_me_player(play_2);
		cout << "Player3:  ";
		show_me_player(play_3);
		cout << "底牌:  ";
		show_hands(cards_in_one_hand);


		cout << endl << endl << endl <<"输入1再次发牌，输入0退出\n";
		cin >> flag;
		if (flag == 0)
			break;
		system("CLS");
		
	}


	
}