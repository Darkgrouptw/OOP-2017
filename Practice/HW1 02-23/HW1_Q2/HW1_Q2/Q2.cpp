#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// �Ʀr
//////////////////////////////////////////////////////////////////////////
struct BigInt
{
	string Number;
	bool IsVaild = false;


	// �P�_�O�_�O�Ʀr
	bool IsNumber()
	{
		for (int i = 0; i < (int)Number.length(); i++)
			if (Number[i] < '0' || Number[i] > '9')
				return false;
		return true;
	}
};

//////////////////////////////////////////////////////////////////////////
// �Ʀr�ۥ[�� Function
//////////////////////////////////////////////////////////////////////////
BigInt Add(BigInt lhs, BigInt rhs)
{
	BigInt result;
	int lNumber, rNumber, carry = 0;
	if (lhs.IsNumber() && rhs.IsNumber())
	{
		// ��V�ۤϡA���ۥ[
		reverse(lhs.Number.begin(), lhs.Number.end());
		reverse(rhs.Number.begin(), rhs.Number.end());

		// ���̤j����
		int LongestNumber = ((lhs.Number.length() > rhs.Number.length()) ? (int)lhs.Number.length() : (int)rhs.Number.length());

		for (int i = 0; i < LongestNumber; i++)
		{
			// �M��
			lNumber = 0;
			rNumber = 0;

			// �ۥ[���϶�
			if ((int)lhs.Number.length() > i)
				lNumber = (int)lhs.Number[i] - '0';

			if ((int)rhs.Number.length() > i)
				rNumber = (int)rhs.Number[i] - '0';

			lNumber += rNumber + carry;

			// �P�_���S���i��
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
	// ��J
	while (cin >> a.Number)
	{
		cin >> b.Number;

		// ���G��X
		BigInt result = Add(a, b);
		if (result.IsVaild)
			cout << result.Number << endl;
		else
			cout << "Not a valid number, please try again." << endl;
	}
}
