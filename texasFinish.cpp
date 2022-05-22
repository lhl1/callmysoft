#include <iostream>
#include<time.h>
#include<vector>
#include<stdlib.h>
using namespace std;

class playingCard    //单张扑克牌属性
{
public:
	int cardSize;     //牌面大小 A,2,3,4,5,6,7,8,9,10,J,Q,K,A  从1到14   A比较特殊，在特殊情况下，算作两张独立牌    
	int cardType;	//牌面类型 1,2,3,4   对应   黑桃，红桃，方块，梅花
	bool isExist = true;	//这张牌还在不在，有没有发出去
	playingCard(int size, int type)  //构造一张牌，设置大小，类型，默认构造即存在此张牌
	{
		this->cardSize = size;
		this->cardType = type;
		this->isExist = true;//lhl
	}
	void showCard()         //展示这张牌的信息，大小，类型，是否存在
	{
		cout << cardSize << " type: " << cardType << "isExist: " << isExist << endl;
	}
	bool showisExist()       //展示这张牌是否存在,返回bool类型
	{

		return this->isExist;
	}
};
void  transformOutput(int a, int b)   //a为牌大小，b为牌类型，将牌的信息翻译成"红桃7"这种形式
{										//牌面大小 A,2,3,4,5,6,7,8,9,10,J,Q,K,A  从1到14   A比较特殊，在特殊情况下，算作两张独立牌
										//牌面类型 1,2,3,4   对应   黑桃，红桃，方块，梅花

	if (b == 1)
	{
		cout << "黑桃";
	}
	else if (b == 2)
	{//lhl
		cout << "红桃";
	}
	else if (b == 3)
	{
		cout << "方块";
	}
	else if (b == 4)
	{
		cout << "梅花";
	}


	if (a == 1)
	{
		cout << "A" << " ";
	}
	else if (a >= 2 && a <= 10)
	{
		cout << a << " ";
	}
	else if (a == 11)
	{
		cout << "J" << " ";
	}
	else if (a == 12)
	{
		cout << "Q" << " ";
	}
	else if (a == 13)
	{
		cout << "K" << " ";
	}
	else if (a == 14)
	{
		cout << "A" << " ";
	}
}//lhl


bool royalFlush(int cardTypes[][15])  //皇家同花顺
{                                       //皇家同花顺有四种情况  黑桃，红桃，方块，梅花  A K Q J 10
	//cout << "皇家同花顺判断开始" << endl;
	for (int j = 1; j <= 4; j++)       //遍历每种类型  看是否有   A K Q J 10 同色
	{
		if (cardTypes[j][10] == 1 && cardTypes[j][11] == 1 && cardTypes[j][12] == 1 && cardTypes[j][13] == 1 && cardTypes[j][14] == 1)
		{								//判断是否   A K Q J 10 同色  且 存在
			transformOutput(10, j);   //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
			transformOutput(11, j);
			transformOutput(12, j);
			transformOutput(13, j);
			transformOutput(14, j);//lhl
			cout << "    皇家同花顺" << endl;
			return true;			 //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
		}
	}
	//cout << "皇家同花顺判断结束" << endl;
	return false;					//返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()

}
bool straightFlush(int cardTypes[][15])  //同花顺
{                                       //同花顺必须 满足 相同花色，连续5张			
	//cout << "同花顺判断开始" << endl;
	int i = 13;				//每次连续5张开始位置  ，因为皇家同花顺已判断 14号位的A无需再次判断
	int start = i;			//因为要输出最大 的组合 ，所以从后向前遍历，如果从1开始，则会匹配到较小的组合
	for (int j = 1; j <= 4; j++)//lhl
	{
		i = 13;				//因为皇家同花顺已判断 14号位的A无需再次判断
		while (i >= 5)
		{
			start = i;    //更新到下一个开始连续5张判断的位置
			if (cardTypes[j][start] == 1 && cardTypes[j][start - 1] == 1 && cardTypes[j][start - 2] == 1 && cardTypes[j][start - 3] == 1 && cardTypes[j][start - 4] == 1)
			{                                    //判断是否   5张牌是否 同色  且 连续存在
				transformOutput(start - 4, j);   //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
				transformOutput(start - 3, j);
				transformOutput(start - 2, j);
				transformOutput(start - 1, j);//lhl
				transformOutput(start, j);
				cout << "   同花顺" << endl;
				return true;					 //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
			}
			i--;								 //每次向前移动一个位置进行判断
		}
	}
	//cout << "同花顺判断结束" << endl;
	return false;                       //返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}

bool fourOfAKind(int cardTypes[][15])  //四条
{									   //四条需要满足同大小的有四张牌，再带一张单牌即可
	//cout << "四条判断开始" << endl;
	int five = 0;//lhl
	for (int i = 14; i >= 1; i--)      //从后向前遍历，如果从1开始，则会匹配到较小的组合
	{									//遍历每个大小相同的牌，看是否有四张
		if (cardTypes[1][i] == 1 && cardTypes[2][i] == 1 && cardTypes[3][i] == 1 && cardTypes[4][i] == 1)
		{								//判断大小相同的牌是否有四张,相同则从后向前遍历，选一张牌输出，如果从1开始，则会匹配到较小的组合

			for (int ii = 14; ii >= i + 1; ii--)          //选择一张比这四张牌大的牌
			{                           //从后向前遍历
				for (int jj = 1; jj <= 4; jj++)
				{						//遍历每种类型
					if (cardTypes[jj][ii] == 1 && ii != i)
					{					//不能和这四张牌冲突 -> ii!=i

						transformOutput(i, 1);     //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
						transformOutput(i, 2);
						transformOutput(i, 3);
						transformOutput(i, 4);
						transformOutput(ii, jj);
						cout << "      四条" << endl;
						return true;       //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
					}
				}
			}


			for (int ii = i - 1; ii >= 1; ii--)    //没有一张比这四张牌大的牌，则选择小的牌
			{                                     //从后向前遍历
				for (int jj = 1; jj <= 4; jj++)
				{									//遍历每种类型
					if (cardTypes[jj][ii] == 1)
					{                              //存在一张比这四张牌大的牌
						transformOutput(ii, jj);      //输出结果
						transformOutput(i, 1);		 //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
						transformOutput(i, 2);
						transformOutput(i, 3);
						transformOutput(i, 4);
						cout << "      四条" << endl;
						return true;          //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
					}
				}
			}

		}
	}
	//cout << "四条判断结束" << endl;
	return false;                   //返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}
bool fullHouse(int cardTypes[][15])    //葫芦
{                                      //三带一对，没有颜色要求
	//cout << "葫芦判断开始" << endl;
	int everyCardNumber[15] = { 0 };    //统计每种大小牌出现的数量，其值代表 每种大小的牌 出现的数量，初始化为0

	for (int i = 14; i >= 1; i--)//lhl
	{
		for (int j = 1; j <= 4; j++)
		{                                //遍历每种大小相同，类型不同的牌是否存在
			if (cardTypes[j][i] == 1)
			{
				everyCardNumber[i]++;   //统计每种大小牌出现的数量
			}
		}
	}

	for (int i = 14; i >= 1; i--)      //从后向前遍历，如果从1开始，则会匹配到较小的组合
	{
		if (everyCardNumber[i] == 3)     //看看有没有出现3张大小相同的牌，不用>=3，不用考虑等于4，因为上一种情况  “四条”已经判断过出现4张大小相同的牌的情况
		{
			for (int j = 14; j >= 1; j--)    //从后向前遍历，如果从1开始，则会匹配到较小的组合
			{
				if (everyCardNumber[j] >= 2 && j != i)   //看看有没有出现两张以上的，j!=i 不能和选择的三张牌重合
				{
					int outNum = 0;            //除了三张牌，展示了多少张
					for (int treeout = 1; treeout <= 4; treeout++)
					{
						if (cardTypes[treeout][i] == 1)       //展示 这三张大小相同的牌
						{
							transformOutput(i, treeout);         //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
						}
					}
					for (int pairOut = 1; pairOut <= 4; pairOut++)
					{
						if (cardTypes[pairOut][j] == 1 && outNum < 2)   // outNum<2  防止出现  3334445  输出  333444 的情况，应输出33444
						{
							transformOutput(j, pairOut);    //展示 两张张大小相同的牌，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
							outNum++;                       //除了三张牌，展示了的牌+1
						}
					}
					cout << " 葫芦" << endl;
					return true;                            //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
				}
			}
		}
	}

	//cout << "葫芦判断结束" << endl;
	return false;                            //返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}


bool Flush(int cardTypes[][15])                //同花
{                                              //不要要求大小的顺序连贯，只要求花色相同
	//cout << "同花判断开始" << endl;
	int sameColor = 0;			     //相同花色的数量     
	for (int i = 1; i <= 4; i++)     //分开遍历四种类型的牌
	{
		sameColor = 0;                //每种类型遍历初始同色数量为0//lhl
		for (int j = 14; j >= 1; j--)    //从后向前遍历，如果从1开始，则会匹配到较小的组合
		{
			if (cardTypes[i][j] == 1)
			{
				sameColor++;              //有同类型的+1
			}
			if (sameColor == 5)          //凑齐5张同类型牌
			{
				for (int jj = j; jj <= 14; jj++)    //从后向前遍历，如果从1开始，则会匹配到较小的组合
				{
					if (cardTypes[i][jj] == 1)
					{								//展示这5张牌   
						transformOutput(jj, i);    //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式

					}
				}
				cout << "		同花" << endl;
				return true;				 //返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
			}
		}
	}
	//cout << "同花判断结束" << endl;
	return false;							 //返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}
bool straight(int cardTypes[][15])			//顺子
{											//连续5张大小依次排序，对类型没有要求
	//cout << "顺子判断开始" << endl;
	int straightNum = 0;       //顺子牌数，达到5则满足要求
	for (int start = 14; start >= 5; start--)		//设置每轮的初始值，从后向前，每次5个判断
	{												 //start >= 5  则 最小为  12345  顺子   最大 为10 J Q K A
		straightNum = 0;
		for (int i = start; i >= start - 4; i--)       //从后向前遍历，如果从1开始，则会匹配到较小的组合
		{
			for (int j = 1; j <= 4; j++)			//遍历每种类型
			{
				if (cardTypes[j][i] == 1)
				{
					straightNum++;
					break;							//如果有多张大小相同的牌，只计算一张
				}
			}
			if (straightNum == 5)	//lhl				//当有5张大小连续的牌，展示这五张
			{
				for (int ii = start - 4; ii <= start; ii++)		//从后向前遍历
				{
					for (int jj = 1; jj <= 4; jj++)
					{
						if (cardTypes[jj][ii] == 1)
						{
							transformOutput(ii, jj);
							break;						//如果有多张大小相同的牌，只计算一张
						}
					}
				}
				cout << "		顺子" << endl;
				return true;							//返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
			}
		}
	}
	//cout << "顺子判断结束" << endl;
	return false;								//返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}

bool threeOfAKind(int cardTypes[][15]) //三条
{										//有三张大小相同的牌
	//cout << "三条判断开始" << endl;
	int everyCardNumber[15] = { 0 };			//统计每种大小牌出现的数量，其值代表 每种大小的牌 出现的数量，初始化为0
	for (int i = 14; i >= 1; i--)
	{
		for (int j = 1; j <= 4; j++)			//遍历每种大小相同，类型不同的牌是否存在
		{
			if (cardTypes[j][i] == 1)
			{
				everyCardNumber[i]++;			//统计每种大小牌出现的数量
			}
		}
	}
	for (int i = 14; i >= 1; i--)				 //从后向前遍历，如果从1开始，则会匹配到较小的组合
	{
		if (everyCardNumber[i] == 3)			//看看有没有出现3张大小相同的牌，不用 >= 3，不用考虑等于4，因为上一种情况  “四条”已经判断过出现4张大小相同的牌的情况
		{
			int outNum = 0;						//除了三张牌，展示了多少张
			for (int ii = 1; ii <= 4; ii++)	//lhl		//从后向前遍历，如果从1开始，则会匹配到较小的组合
			{
				if (cardTypes[ii][i] == 1)			//展示 这三张大小相同的牌
				{
					transformOutput(i, ii);			 //左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
				}
			}
			for (int ii = 14; ii >= 1; ii--)		//展示另外两张牌
			{
				for (int jj = 1; jj <= 4; jj++)
				{
					if (cardTypes[jj][ii] == 1 && outNum < 2 && ii != i)		//展示的牌小于两张，防止多展示，跳过此次三张候选的牌
					{
						transformOutput(ii, jj);		//展示 两张的牌，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
						outNum++;					//除了三张牌，展示了的牌+1
					}
				}
				if (outNum >= 2)					//展示完了三张牌，和另外两张牌
				{
					cout << "		三条" << endl;
					return true;					//返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
				}

			}
		}
	}
	//cout << "三条判断结束" << endl;

	return false;									//返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()

}


bool twoPair(int cardTypes[][15])   //两对
{									//有两对大小相同的牌
	//cout << "两对判断开始" << endl;
	int pairNum = 0;	//有两张相同大小牌的组数
	int outpair = 0;   //输出的对数
	int everyCardNumber[15] = { 0 };				//统计每种大小牌出现的数量，其值代表 每种大小的牌 出现的数量，初始化为0
	for (int i = 14; i >= 1; i--)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (cardTypes[j][i] == 1)				//遍历每种大小相同，类型不同的牌是否存在
			{
				everyCardNumber[i]++;				//统计每种大小牌出现的数量
			}
		}
		if (everyCardNumber[i] == 2)              //计算对数，碰到一对的+1，因为上一层函数“ 三条 ”判断了对数为3的情况，所以这层不需要考虑
			pairNum++;
	}
	if (pairNum >= 2)							//如果有两对相同大小的牌
	{
		for (int i = 14; i >= 1; i--)				//从后向前遍历，如果从1开始，则会匹配到较小的组合
		{
			if (everyCardNumber[i] == 2 && outpair < 2)	//lhl		//判断这组是否有一对    并且两对没有输出完
			{
				for (int j = 1; j <= 4; j++)		//遍历每种类型
				{
					if (cardTypes[j][i] == 1)
					{
						transformOutput(i, j);		//输出这一对，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
					}
				}
				everyCardNumber[i] = 0;    //!!!!输出完则把这两对数量置为零，防止下面重复输出这两对的值
				outpair++;					//输出一对+1
			}
		}
		if (outpair == 2)				//输出了两对，则输出单张
		{
			for (int start = 14; start >= 1; start--)			//从后向前遍历，如果从1开始，则会匹配到较小的组合
			{
				if (everyCardNumber[start] > 0)				//这一项大小的牌存在
				{
					for (int jjj = 1; jjj <= 4; jjj++)		//遍历每种类型
					{
						if (cardTypes[jjj][start] == 1)
						{
							transformOutput(start, jjj);		//输出这张牌，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
							cout << "		两对" << endl;
							return true;						//返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
						}
					}
				}
			}
		}
	}



	//cout << "两对判断结束" << endl;
	return false;												//返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}

bool onePair(int cardTypes[][15])   //一对
{										//有一对大小相同的牌
	//cout << "一对判断开始" << endl;
	int pairNum = 0;			//有两张相同大小牌的组数
	int outNum = 0;   //输出的对数
	int everyCardNumber[15] = { 0 };		//统计每种大小牌出现的数量，其值代表 每种大小的牌 出现的数量，初始化为0
	for (int i = 14; i >= 1; i--)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (cardTypes[j][i] == 1)			//遍历每种大小相同，类型不同的牌是否存在
			{
				everyCardNumber[i]++;			//统计每种大小牌出现的数量
			}
		}
		if (everyCardNumber[i] == 2)			  //计算对数，碰到一对的+1，因为上上一层函数“ 三条 ”判断了对数为3的情况，所以这层不需要考虑
			pairNum++;
	}
	if (pairNum >= 1)						//如果有一对相同大小的牌
	{
		for (int i = 14; i >= 1; i--)				 //从后向前遍历，如果从1开始，则会匹配到较小的组合
		{
			if (everyCardNumber[i] == 2)
			{
				for (int j = 1; j <= 4; j++)		//遍历每种类型
				{
					if (cardTypes[j][i] == 1)
					{
						transformOutput(i, j);			//输出这一对，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
					}
				}
				everyCardNumber[i] = 0;				 //!!!!输出完则把这两对数量置为零，防止下面重复输出这两对的值
				break;
			}
		}
		for (int i = 14; i >= 1; i--)			//从后向前遍历，如果从1开始，则会匹配到较小的组合
		{
			if (everyCardNumber[i] == 1)			//这一项大小的牌存在
			{
				for (int j = 1; j <= 4; j++)			//遍历每种类型
				{
					if (cardTypes[j][i] == 1 && outNum < 3)		//因为需要输出一对，剩下三张牌也需要输出，看是否输出了三张牌
					{
						transformOutput(i, j);				//输出这张牌，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
						outNum++;					//输出牌数+1
					}
				}

			}
			if (outNum == 3)	//lhl			//输出牌数是否为3+2张
			{
				cout << "		一对" << endl;
				return true;				//返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
			}
		}
	}
	//cout << "一对判断结束" << endl;
	return false;							//返回错误，非此类型排列，继续下一种类型判断  ，继续 最大组合牌 判断  ，调用见 player->maxCombination()
}


bool highCards(int cardTypes[][15]) //高牌
{									//除了以上的情况，什么都组不成
	//cout << "高牌判断开始" << endl;
	int outNum = 0;						 //输出了多少张牌
	for (int i = 14; i >= 1; i--)			//从后向前遍历，如果从1开始，则会匹配到较小的组合
	{
		for (int j = 1; j <= 4; j++)		//遍历每种类型
		{
			if (cardTypes[j][i] == 1 && outNum < 5)		//判断5张牌有没有输出完
			{
				transformOutput(i, j);				//输出这张牌，左参数为牌大小，右参数为牌类型，将牌的信息翻译成"红桃7"这种形式
				outNum++;					//输出牌数+1
			}
		}
		if (outNum == 5)				//输出了5张牌
		{
			cout << "		高牌" << endl;
			return true;
		}
	}
	//cout << "高牌判断结束" << endl;			//返回正确，结束最大组合牌 判断  ，即为此牌最大，调用见 player->maxCombination()
	return false;					//返回错误，非此类型排列，这是最后的类型判断了，除非数据错误，否则不会出现
}



class player
{
public:
	playingCard *handCard[3];    //每名玩家两张手牌//lhl
	vector<playingCard> handCardAddPublicCards;		//每名玩家的两张手牌 + 公开牌的按大小排序
	int haveCardsNumber;	//每名玩家拥有的手牌数量
	int handCard_p;			//每名玩家手牌指针位置
	int cardTypes[5][15];	//每名玩家的两张手牌 + 公开牌  的二维数组，详细见excel表格	

	player()
	{
		this->haveCardsNumber = 0;		//初始构造玩家手上没有牌
		this->handCard_p = 1;			//玩家手牌handCard的指针，指向下一个空位置
	}
	bool dealCard(playingCard *allOfTheCard[], int randCardNumber, int randCardType)  //发牌1位置参数为牌堆 52 张 handCard 数组 的地址指针
	{																		//2位置为随机牌大小,3位置为随机牌类型
		if (this->haveCardsNumber >= 2)		  //如果player手上有2张牌则不发								
			return false;						//返回出错
		if (allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->showisExist())		//判断随机到的这个大小，这个类型的牌是否在牌堆里
		{
			handCard[handCard_p++] = new playingCard(randCardNumber, randCardType);     //把牌发到player手里(写入到handcard[])

			allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->isExist = false;   //牌已经发到玩家手里，从牌堆移除，不能再发了
			this->haveCardsNumber++;													//玩家牌数+1			
		}
		else
		{
			return false;									//返回发牌出错，再次由下次调用发牌
		}
		return true;										//返回发牌成功//lhl
	}
	void showHaveCards()			//展示玩家手里的牌，大小和类型			
	{

		for (int i = 1; i <= this->handCard_p - 1; i++)     //展示玩家手里的牌，handCard_p指向handCard[]下一个空位置
		{
			transformOutput(handCard[i]->cardSize, handCard[i]->cardType);
			 
		}
		cout << endl;
	}
	void showhandCardAddPublicCards()		//展示玩家的两张手牌 + 公开牌
	{

		for (vector<playingCard>::iterator i = this->handCardAddPublicCards.begin(); i != this->handCardAddPublicCards.end(); i++)
		{														//使用vector迭代器遍历两张手牌 + 公开牌							
			cout << i->cardSize << " type: " << i->cardType << "              ";
		}
		cout << endl;
	}
	void maxCombination()					//匹配最大出牌组合
	{
		int bak[5][15];				//备份玩家两张手牌 + 公开牌 二维数组
		memcpy(bak, cardTypes, sizeof(int) * 15 * 5);	//还原玩家两张手牌 + 公开牌 二维数组，防止修改造成判断错误，以下省略注解
		if (royalFlush(cardTypes))				//判断是否为皇家同花顺，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (straightFlush(cardTypes))			//判断是否为同花顺，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (fourOfAKind(cardTypes))	//lhl			//判断是否为四条，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (fullHouse(cardTypes))				//判断是否为葫芦，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (Flush(cardTypes))					//判断是否为同花，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (straight(cardTypes))				//判断是否为顺子，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (threeOfAKind(cardTypes))			//判断是否为三条，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (twoPair(cardTypes))					//判断是否为两条，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (onePair(cardTypes))					//判断是否为一条，如果是则输出，不是则进行下一类型判断
			return;
		memcpy(cardTypes, bak, sizeof(int) * 15 * 5);
		if (highCards(cardTypes))				//判断是否为高牌，如果是则输出，不是则为数据错误
			return;

	}
	void showcardTypes()		//展示player手上牌组成的二维数组		
	{
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 14; j++)
			{
				cout << cardTypes[i][j] << " ";
			}
			cout << endl;
		}
	}

};

void inputCards(player *p1)			//手动输入二维数组，用于测试
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 14; j++)//lhl
		{
			cin >> p1->cardTypes[i][j];
		}
	}
}











class publicCards
{
public:
	playingCard *handCard[6];    //公共牌6张牌
	int haveCardsNumber;	//公共牌数量
	int handCard_p;			//公共牌指针位置
	publicCards()
	{
		this->haveCardsNumber = 0;		//初始构造公共牌为空
		this->handCard_p = 1;			//公共牌handCard的指针，指向下一个空位置
	}
	bool dealCard(playingCard *allOfTheCard[], int randCardNumber, int randCardType)		//发牌           1位置参数为牌堆 52 张 handCard 数组 的地址指针
	{																				//2位置为随机牌大小,3位置为随机牌类型
		if (this->haveCardsNumber >= 5)				//如果公共牌有5张牌则不发	
			return false;	//lhl				//返回出错
		if (allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->showisExist())		//判断随机到的这个大小，这个类型的牌是否在牌堆里
		{
			handCard[handCard_p++] = new playingCard(randCardNumber, randCardType);			  //把牌发到公共牌(写入到handcard[])

			allOfTheCard[(randCardNumber - 1) * 4 + randCardType]->isExist = false;				//牌已经发到公共牌，从牌堆移除，不能再发了
			this->haveCardsNumber++;															//公共牌牌数+1	 
		}
		else
		{
			return false;				//返回发牌出错，再次由下次调用发牌
		}
		return true;					//返回发牌成功
	}
	void showHaveCards()				//展示公共牌，大小和类型
	{

		for (int i = 1; i <= this->handCard_p - 1; i++)
		{
			transformOutput(handCard[i]->cardSize, handCard[i]->cardType);
			//cout << handCard[i]->cardSize << " type: " << handCard[i]->cardType << "              ";
		}
		cout << endl;
	}

};
void addPlayerPublicCards(player *p1, publicCards * p2)			//把公共牌和player手上的牌合并，并写入vector<playingCard> handCardAddPublicCards 动态数组
{																//并创建二维数组 cardTypes[][]  两张手牌 + 公开牌  的二维数组，详细见excel表格	
	int flagFinish = 7;				//一共要写7张牌
	int minCard = 1000;				//用于定位最小的牌，定大一点
	int mintype = 10;				//用于定位最小的牌的类型 
	playingCard *flagCard = NULL;   //playingCard指针，用于定位并指向最小的牌，初始指空
	while (flagFinish)				//有没有写完7张牌
	{
		minCard = 1000;	//lhl		//用于定位最小的牌，定大一点
		flagCard = NULL;			//playingCard指针，用于定位并指向最小的牌，初始指空
		mintype = 10;				//用于定位最小的牌的类型 

		for (int i = 1; i <= 2; i++)		//遍历玩家上手最小的牌，并定位较小值
		{
			if (p1->handCard[i]->cardSize < minCard && p1->handCard[i]->isExist)			//这张牌有没有写过，是不是较小的牌
			{
				minCard = p1->handCard[i]->cardSize;				//得到较小值
				mintype = p1->handCard[i]->cardType;				//得到较小值类型
				flagCard = p1->handCard[i];							//得到较小值牌地址
			}
			else if (p1->handCard[i]->isExist && p1->handCard[i]->cardType < mintype  && p1->handCard[i]->cardSize == minCard)
			{															//大小相等，比较类型取较小值
				minCard = p1->handCard[i]->cardSize;			//得到较小值
				mintype = p1->handCard[i]->cardType;			//得到较小值类型
				flagCard = p1->handCard[i];						//得到较小值牌地址
			}
		}
		for (int i = 1; i <= 5; i++)			//遍历公共牌牌，并定位较小值
		{
			if (p2->handCard[i]->cardSize < minCard && p2->handCard[i]->isExist)		//这张牌有没有写过，是不是较小的牌
			{
				minCard = p2->handCard[i]->cardSize;		//得到较小值
				mintype = p2->handCard[i]->cardType;		//得到较小值类型
				flagCard = p2->handCard[i];					//得到较小值牌地址
			}
		}
		if (flagCard)			//如果定位到了较小值
		{
			p1->handCardAddPublicCards.push_back(*flagCard);			//压入vector<playingCard> handCardAddPublicCards 动态数组
			flagCard->isExist = false;					//写入完，不可重复写，退出候选
		}

		flagFinish--;							//写入了一张，需要写入7张
	}
	for (vector<playingCard>::iterator i = p1->handCardAddPublicCards.begin(); i != p1->handCardAddPublicCards.end(); i++)
	{													//使用vector迭代器遍历,创建二维数组 cardTypes[][]  两张手牌 + 公开牌  的二维数组，详细见excel表格	
		p1->cardTypes[i->cardType][i->cardSize]++;		//遍历vector<playingCard> handCardAddPublicCards 动态数组，创建二维数组
		if (i->cardSize == 1)
		{
			p1->handCardAddPublicCards.push_back(playingCard(14, i->cardType));
		}
	}



	for (int i = 1; i <= 5; i++)
	{
		p2->handCard[i]->isExist = true;			//还原公共牌，以供下一player进行添加//lhl
	}
}




int cardNumber(playingCard *allOfTheCard[])		//计算没有公共牌发出去的牌数量
{
	int cardSumNumber = 0;   //计算没发出的牌数量
	for (int i = 1; i <= 52; i++)		//遍历牌堆
	{
		if (allOfTheCard[i]->showisExist())  //判断这张牌有没有发出去
		{
			++cardSumNumber;	//计算没发出的牌数量
		}
	}
	return cardSumNumber;
}

int main()
{
	int flag = 1;  //标记是否结束1为继续，0为结束
	int playingNum = 1;			//统计游玩局数
	srand((unsigned)time(NULL));	//创建随机数种，得到较真随机数，根据时间来，如果直接rand()，为伪随机数，每次运行随机数相同
	while (flag)
	{
		cout << "第" << playingNum << "局\n" << endl;
		playingCard *allOfTheCard[53];		//创建52张牌
		int playingCard_P = 1;		//52张牌指针
		for (int i = 1; i <= 13; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				allOfTheCard[playingCard_P++] = new playingCard(i, j);		//写入52张牌
			}
		}
		int dealcout = 0;   //发牌数


		//for (int i = 1; i <= 52; i++)	//输出52张牌大小，类型
		//{
		//	cout << "i: " << i << " " << allOfTheCard[i]->cardSize << " type: " << allOfTheCard[i]->cardType << endl;
		//}

		player p1, p2, p3, p4, p5, p6;		//创建6名玩家
		publicCards pub1;					//公共牌
		for (int i = 0; i < 2; i++)		//发给每名玩家2张牌
		{					//不用独立函数，是因为rand()在函数中调用，每次调用随机数基本相同，得不到想要的结果
			while (!p1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));		//发给player1 1张牌，如果牌发过return false，则再次随机发牌，直到成功，下方省略
			while (!p2.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));		//发给player2 1张牌，如果牌发过return false，则再次随机发牌，直到成功，下方省略
			while (!p3.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
			while (!p4.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
			while (!p5.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
			while (!p6.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));
		}

		for (int i = 0; i < 5; i++)	//lhl		//发给公共牌 5张牌
		{
			while (!pub1.dealCard(allOfTheCard, rand() % 13 + 1, rand() % 4 + 1));		//发给公共牌 1张牌，如果牌发过return false，则再次随机发牌，直到成功，下方省略
		}
		//cout << "底牌:   ";
		addPlayerPublicCards(&p1, &pub1);		//player1写入 手牌 + 公开牌 ，并创建7张牌二维数组，下方省略
		addPlayerPublicCards(&p2, &pub1);
		addPlayerPublicCards(&p3, &pub1);
		addPlayerPublicCards(&p4, &pub1);
		addPlayerPublicCards(&p5, &pub1);
		addPlayerPublicCards(&p6, &pub1);//lhl
		//p1.showhandCardAddPublicCards();				
		//p1.showcardTypes();
		//cout << endl;
		//cout << "测试程序:" << "请输入7张牌二维数组, 输出最大组合,默认为随机7张" << endl;
		//cout << "例如:" << endl;
		//cout << "0 0 0 0 0 0 0 1 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 1 0 1 0 0 0\n0 0 0 0 0 0 0 0 0 1 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 1 0 0\n" << endl;
		//cout << "请输入:" << endl;
		//inputCards(&p1);					//手动输入二维	手牌 + 公开牌
		//cout << endl;
		cout << "Player1手牌 : ";
		p1.showHaveCards();
		cout << "Player2手牌 : ";
		p2.showHaveCards();
		cout << "Player3手牌 : ";
		p3.showHaveCards();
		cout << "Player4手牌 : ";
		p4.showHaveCards();
		cout << "Player5手牌 : ";
		p5.showHaveCards();
		cout << "Player6手牌 : ";
		p6.showHaveCards();
		cout << "公共牌 : ";
		pub1.showHaveCards();			//展示公共牌
		cout << endl;
		cout << "Player1最佳组合 : ";
		p1.maxCombination();					//player1 匹配最大组合，并输出，下方省略
		cout << "Player2最佳组合 : ";
		p2.maxCombination();
		cout << "Player3最佳组合 : ";
		p3.maxCombination();
		cout << "Player4最佳组合 : ";
		p4.maxCombination();
		cout << "Player5最佳组合 : ";
		p5.maxCombination();
		cout << "Player6最佳组合 : ";
		p6.maxCombination();
		cout << "\n输入一继续发牌，输入0结束:\n" << endl;
		cin >> flag;
		playingNum++;				//游玩局数+1
	}

	cout << endl;
	system("pause");
	
}



