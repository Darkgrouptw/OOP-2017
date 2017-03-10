#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ElementSet
{
	int		NumberElement = 0;								// 放數字
	char	operationElement;								// 做 Operation
	int		state = 0;										// 0 代表沒有使用，1 代表數字，2 代表是 Operation，3 代表是負數後面要做一些 Operation
};

// 把輸入的字讀進來，然後 parse 成一堆 ElementSet 存起來
vector<ElementSet *> EvaluateString(string input)
{
	vector<ElementSet *> set;

	// 狀態
	// 0 => 讀數字
	// 1 => 讀字元
	int state = 0;

	// 加入第一個值
	ElementSet *tempE = new ElementSet();
	set.push_back(tempE);

	for (int i = 0; i < (int)input.length(); i++)
	{
		#pragma region 略過空白
		if (input[i] == ' ')
			continue;
		#pragma endregion
		
		// 是數字的時候
		if ((set[set.size() - 1]->state == 0 || set[set.size() - 1]->state == 2) && input[i] == '-')
		{
			set[set.size() - 1]->state = 3;
			continue;
		}
		#pragma region  數字 & 符號判斷
		switch (input[i])
		{
		case '+':
		case '-':
		case '*':
		case '/':
			// 判斷是否遇到Operation
			if (set[set.size() - 1]->state == 3)
			{
				set[set.size() - 1]->NumberElement *= -1;
				set[set.size() - 1]->state = 1;
			}

			// 把符號加進去
			tempE = new ElementSet();
			tempE->operationElement = input[i];
			tempE->state = 2;
			set.push_back(tempE);

			// 把空的加進去
			tempE = new ElementSet();
			set.push_back(tempE);
			break;

		default:
			tempE = set[set.size() - 1];
			tempE->NumberElement = tempE->NumberElement * 10 + input[i] - '0';
			if(tempE->state != 3)
				tempE->state = 1;
			break;
		}
		#pragma endregion
	}
	if (set[set.size() - 1]->state == 3)
	{
		set[set.size() - 1]->NumberElement *= -1;
		set[set.size() - 1]->state = 1;
	}

	return set;
}

// +-*/ 的優先順序 table
int PriorityTable(char operation)
{
	if (operation == '*' || operation == '/')
		return 2;
	return 1;
}

//中序轉後序
void InfixToPostfix(vector<ElementSet *> &forms)
{
	// 暫存的順序
	vector<ElementSet *> tempArray;							// 暫存的陣列

	vector<ElementSet *> operStack;							// 符號的陣列

	#pragma region Copy 一次順序
	for (int i = 0; i < forms.size(); i++)
		tempArray.push_back(forms[i]);
	#pragma endregion
	#pragma region 做中序轉後序
	// 先把東西清空，最後再把東西加進去
	forms.erase(forms.begin(), forms.end());

	for (int i = 0; i < tempArray.size(); i++)
		switch (tempArray[i]->state)
		{
		case 1:
			forms.push_back(tempArray[i]);
			break;
		case 2:
			int NowPriority = PriorityTable(tempArray[i]->operationElement);														// 現在符號的 優先順序
			int PrePriority = (operStack.size() == 0) ? -1 : PriorityTable(operStack[operStack.size() - 1]->operationElement);		// 前一個符號的 優先順序 (-1 代表沒有)

			if (PrePriority == -1 || NowPriority >= PrePriority)
				operStack.push_back(tempArray[i]);
			else if (NowPriority < PrePriority)
			{
				// 這邊需要把所有小於的 Operation 都丟出來
				while (NowPriority < PrePriority)
				{
					forms.push_back(operStack[operStack.size() - 1]);
					operStack.pop_back();
					PrePriority = (operStack.size() == 0) ? -1 : PriorityTable(operStack[operStack.size() - 1]->operationElement);
				}
				operStack.push_back(tempArray[i]);
			}
			break;
		}

	// 需要把剩餘的 operStack 丟出來
	for (int i = operStack.size() - 1; i >= 0; i--)
	{
		ElementSet *lastE = operStack[operStack.size() - 1];
		forms.push_back(lastE);
		operStack.pop_back();
	}
	#pragma endregion


}

// 做運算啦~~~
int PostifxOperation(vector<ElementSet *> forms)
{
	vector<double> numStack;								// 數字的陣列
	for (int i = 0; i < forms.size(); i++)
		switch (forms[i]->state)
		{
		case 1:
			numStack.push_back((double)forms[i]->NumberElement);
			break;
		case 2:
			double FirstNumber = numStack[numStack.size() - 1];
			double SecondNumber = numStack[numStack.size() - 2];
			numStack.pop_back();

			// 符號的判斷
			switch (forms[i]->operationElement)
			{
			case '+':
				numStack[numStack.size() - 1] = SecondNumber + FirstNumber;
				break;
			case '-':
				numStack[numStack.size() - 1] = SecondNumber - FirstNumber;
				break;
			case '*':
				numStack[numStack.size() - 1] = SecondNumber * FirstNumber;
				break;
			case '/':
				numStack[numStack.size() - 1] = SecondNumber / FirstNumber;
				break;
			}
			break;
		}
	return (int)numStack[0];
}

void main()
{
	// 總共有幾筆資料
	int num;
	cin >> num;
	getchar();														// 抓 enter
	
	string inputStr;
	for (int i = 0; i < num; i++)
	{
		// 把四則運算的式子讀進來
														
		getline(cin, inputStr);

		vector<ElementSet *> tempArray = EvaluateString(inputStr);
		InfixToPostfix(tempArray);
		cout << PostifxOperation(tempArray) << endl;
		// 測試分的是否正確
		/*for (int j = 0; j < (int)tempArray.size(); j++)
		{
			ElementSet *tempE = tempArray[j];
			if(tempE->state == 1)
				cout << tempE->NumberElement << " ";
			else
				cout << tempE->operationElement << " ";
		}
		cout << endl;*/
	}
	system("PAUSE");
}