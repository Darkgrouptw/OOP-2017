#include <iostream>
#include <vector>

using namespace std;

// 兩個數字一個 pair， A >= B
struct numPair
{
	int numA = 0;
	int numB = 0;
};

// 古埃及的分數
vector<numPair>* EgyptianFraction(int num)
{
	vector<numPair> *numArray = new vector<numPair>();
	int tempNum = 0;
	for(long long int i = num * 2; i <= num * (num + 1); i++)
		if (i * num % (i - num) == 0)
		{
			numPair p;
			p.numA = (int)i;
			p.numB = (int)(i * num / (i - num));

			// 存進陣列裡
			numArray->push_back(p);
		}
	return numArray;
}

void main()
{
	// 這題是什麼鬼的古埃及分數的東西 ??????
	int num;											// 總用要輸入幾筆資料
	int tempNum;										// 要跑 1/x = 1/A + 1/B
	cin >> num;

	vector<vector<numPair> *>		outputArray;		// 用來輸出的陣列


	// 做運算
	for (int i = 0; i < num; i++)
	{
		cin >> tempNum;
		outputArray.push_back(EgyptianFraction(tempNum));
	}

	// Output 值
	vector<numPair> *tempPair;
	for (int i = 0; i < num; i++)
	{
		tempPair = outputArray[i];
		cout << tempPair->size() << endl;
		for (int j = 0; j < (int)tempPair->size(); j++)
			cout << (*tempPair)[j].numA << " " << (*tempPair)[j].numB << endl;
		cout << endl;
	}
	outputArray.erase(outputArray.begin(), outputArray.end());
	system("PAUSE");
}