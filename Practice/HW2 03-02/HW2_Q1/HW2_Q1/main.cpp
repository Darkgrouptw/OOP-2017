#include <iostream>
#include <string>

using namespace std;

const int Max = 1000000;
//////////////////////////////////////////////////////////////////////////
//　回傳是不是迴文
//////////////////////////////////////////////////////////////////////////
bool IsPalindrome(string text)
{
	string rev(text);
	reverse(rev.begin(), rev.end());
	if (text == rev)
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////
//　10 進制  =>  n 進制
//////////////////////////////////////////////////////////////////////////
string Number10ToN(int Number, int n)
{
	string output = "";
	string tempChar;
	while (Number > 0)
	{
		tempChar = to_string(Number % n);
		Number /= n;
		output = tempChar + output;
	}
	return output;
}
int main()
{
	string inputValue;
	while (cin >> inputValue)
	{
		bool IsFind = false;
		int PalindTime = 0;

		// 存答案的變數
		int Number[3];							// 進制1、 進制2、答案數字
		string AnsNumber[2];					// 進制1的答案、進制2的答案

		for (int i = stoi(inputValue); i <= Max && !IsFind; i++)
		{
			for (int j = 2; j <= 10 && !IsFind; j++)
			{
				string convertNumber = Number10ToN(i, j);
				if (IsPalindrome(convertNumber))
				{
					// 存答案
					Number[PalindTime] = j;
					AnsNumber[PalindTime] = convertNumber;

					PalindTime++;
					if (PalindTime == 2)
					{
						Number[2] = i;
						IsFind = true;
						break;
					}
				}
			}
			PalindTime = 0;
		}

		// 輸出結果
		if (!IsFind)
			cout << "No answer." << endl;
		else
		{
			// 答案
			cout << Number[2] << endl;
			cout << Number[0] << " " << AnsNumber[0] << endl;
			cout << Number[1] << " " << AnsNumber[1] << endl;
		}
	}
	return 0;
}