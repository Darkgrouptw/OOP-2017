#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// 員工資料
//////////////////////////////////////////////////////////////////////////
struct InfoClass {
	string Name;
	string Salary;
	string Bonus;
};

//////////////////////////////////////////////////////////////////////////
// Print 空白
//////////////////////////////////////////////////////////////////////////
void PrintBlank(int n)
{
	for (int i = 0; i < n; i++)
		cout << " ";
}

void main()
{
	int num;						// 次數
	InfoClass *infoArray;			// 陣列資料
	int MaxWords[] = {0 ,0, 0};		// 最大字數限制

	while (cin >> num)
	{
		// 初始化
		infoArray = new InfoClass[num];
		for (int i = 0; i < 3; i++)
			MaxWords[i] = 0;

		// 輸入資料
		for (int i = 0; i < num; i++)
		{
			cin >> infoArray[i].Name >> infoArray[i].Salary >> infoArray[i].Bonus;

			// 判斷字數大小
			MaxWords[0] = max(MaxWords[0], (int)infoArray[i].Name.length());
			MaxWords[1] = max(MaxWords[0], (int)infoArray[i].Salary.length());
			MaxWords[2] = max(MaxWords[0], (int)infoArray[i].Bonus.length());
		}

		// 輸出
		for (int i = 0; i < num; i++)
		{
			// 空白
			PrintBlank(MaxWords[0] - (int)infoArray[i].Name.length());
			cout << infoArray[i].Name << "|  ";

			PrintBlank(MaxWords[1] - (int)infoArray[i].Salary.length());
			cout << infoArray[i].Salary << "|  ";

			PrintBlank(MaxWords[2] - (int)infoArray[i].Bonus.length());
			cout << infoArray[i].Bonus << endl;
		}
		delete[] infoArray;
	}
}
