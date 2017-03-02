#include <iostream>
#include <string>

using namespace std;

const int Max = 1000000;
//////////////////////////////////////////////////////////////////////////
//�@�^�ǬO���O�j��
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
//�@10 �i��  =>  n �i��
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

		// �s���ת��ܼ�
		int Number[3];							// �i��1�B �i��2�B���׼Ʀr
		string AnsNumber[2];					// �i��1�����סB�i��2������

		for (int i = stoi(inputValue); i <= Max && !IsFind; i++)
		{
			for (int j = 2; j <= 10 && !IsFind; j++)
			{
				string convertNumber = Number10ToN(i, j);
				if (IsPalindrome(convertNumber))
				{
					// �s����
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

		// ��X���G
		if (!IsFind)
			cout << "No answer." << endl;
		else
		{
			// ����
			cout << Number[2] << endl;
			cout << Number[0] << " " << AnsNumber[0] << endl;
			cout << Number[1] << " " << AnsNumber[1] << endl;
		}
	}
	return 0;
}