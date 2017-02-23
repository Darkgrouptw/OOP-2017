#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// 數字
//////////////////////////////////////////////////////////////////////////
struct BigInt
{
	string Number;
	bool IsVaild = false;


	// 判斷是否是數字
	bool IsNumber()
	{
		for (int i = 0; i < (int)Number.length(); i++)
			if (Number[i] < '0' || Number[i] > '9')
				return false;
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////
// 數字相加的 Function
//////////////////////////////////////////////////////////////////////////
BigInt Add(BigInt lhs, BigInt rhs)
{
	BigInt result;
	int lNumber, rNumber, carry = 0;
	if (lhs.IsNumber() && rhs.IsNumber())
	{
		// 方向相反，做相加
		reverse(lhs.Number.begin(), lhs.Number.end());
		reverse(rhs.Number.begin(), rhs.Number.end());

		// 拿最大長度
		int LongestNumber = ((lhs.Number.length() > rhs.Number.length()) ? (int)lhs.Number.length() : (int)rhs.Number.length());

		for (int i = 0; i < LongestNumber; i++)
		{
			// 清空
			lNumber = 0;
			rNumber = 0;

			// 相加的區塊
			if ((int)lhs.Number.length() > i)
				lNumber = (int)lhs.Number[i] - '0';

			if ((int)rhs.Number.length() > i)
				rNumber = (int)rhs.Number[i] - '0';

			lNumber += rNumber + carry;

			// 判斷有沒有進位
			if (lNumber >= 10)
			{
				carry = 1;
				lNumber %= 10;
			}
			else
				carry = 0;

			result.Number += to_string(lNumber);
		}

		if (carry == 1)
			result.Number += "1";

		reverse(result.Number.begin(), result.Number.end());
		result.IsVaild = true;
	}
	return result;
}

int main()
{
	BigInt a, b;
	// 輸入
	while (cin >> a.Number)
	{
		cin >> b.Number;

		// 結果輸出
		BigInt result = Add(a, b);
		if (result.IsVaild)
			cout << result.Number << endl;
		else
			cout << "Not a valid number, please try again." << endl;
	}
}
