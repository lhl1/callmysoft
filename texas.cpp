#include <iostream>
#include<time.h>
using namespace std;

class playingCard
{
public:
	int cardSize;     //牌面大小
	int cardType;	//牌面类型
	bool isExist=true;	//牌面还在不在，有没有发出去
	playingCard(int size, int type)
	{
		this->cardSize = size;
		this->cardType = type;
		this->isExist = true;
	}
	void showCard()
	{
		cout << cardSize << " type: " << cardType <<endl;
	}
	bool showisExist()
	{
		return this->isExist;
	}
};
 
class player 
{
public:
	playingCard *handCard[3];    //每名玩家两张手牌
	int haveCardsNumber;	//每名玩家拥有的手牌数量
	int handCard_p;			//每名玩家手牌指针位置
	player()
	{
		this->haveCardsNumber = 0;
		this->handCard_p = 1;
	}
	bool dealCard(playingCard *allOfTheCard[], int randCardNumber, int randCardType)
	{
		if (this->haveCardsNumber >= 2)
			return false;
		if (allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->showisExist())
		{
			handCard[handCard_p++] = new playingCard(randCardNumber, randCardType);
			
			allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->isExist = false;
			this->haveCardsNumber++;
			cout << "true" << endl;
		}
		else
		{
			return false;
		}
		return true;
	}
	void showHaveCards()
	{
		
		for (int i = 1; i <=this->handCard_p-1; i++)
		{
			cout << handCard[i]->cardSize<<" type: "<<handCard[i]->cardType<<"              " ;
		}
		cout << endl;
	}

};

class publicCards
{
public:
	playingCard *handCard[6];    //每名玩家两张手牌
	int haveCardsNumber;	//每名玩家拥有的手牌数量
	int handCard_p;			//每名玩家手牌指针位置
	publicCards()
	{
		this->haveCardsNumber = 0;
		this->handCard_p = 1;
	}
	bool dealCard(playingCard *allOfTheCard[], int randCardNumber, int randCardType)
	{
		if (this->haveCardsNumber >= 5)
			return false;
		if (allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->showisExist())
		{
			handCard[handCard_p++] = new playingCard(randCardNumber, randCardType);

			allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->isExist = false;
			this->haveCardsNumber++;
			cout << "true" << endl;
		}
		else
		{
			return false;
		}
		return true;
	}
	void showHaveCards()
	{

		for (int i = 1; i <= this->handCard_p - 1; i++)
		{
			cout << handCard[i]->cardSize << " type: " << handCard[i]->cardType << "              ";
		}
		cout << endl;
	}

};





int cardNumber(playingCard *allOfTheCard[])
{
	int cardSumNumber = 0;   //计算没发出的牌数量
	for (int i = 1; i <= 52; i++)
	{
		if (allOfTheCard[i]->showisExist())  //判断这张牌有没有发出去
		{
			++cardSumNumber;
		}
	}
	return cardSumNumber;
}






int main()
{
	
	playingCard *allOfTheCard[53];
	int playingCard_P = 1;
	for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			allOfTheCard[playingCard_P++] = new playingCard(i, j);
		}
	}
	int dealcout = 0;   //发牌数
	 
	 
	for (int i = 1; i <= 52; i++)
	{
		cout << "i: " <<i<<" "<< allOfTheCard[i]->cardSize << " type: " << allOfTheCard[i]->cardType << endl;
	}

	player p1,p2,p3,p4,p5,p6; 
	publicCards pub1;
	for (int i = 0; i < 2; i++)
	{
		while (!p1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		while (!p2.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		while (!p3.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		while (!p4.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		while (!p5.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		while (!p6.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
	}
	
	while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
	while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
	while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
	while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
	while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));

	p1.showHaveCards();
	p2.showHaveCards();
	p3.showHaveCards();
	p4.showHaveCards();
	p5.showHaveCards();
	p6.showHaveCards();
	cout << "--------------------------" << endl;
	pub1.showHaveCards();

    
}

 
