#include <iostream>
#include <vector>

using namespace std;

#define	TEXT_SIZE	4
#define KEY_SIZE	4
#define STATE_SIZE	8 // 실제로는 256으로 사용

const int	PLAINTEXT[TEXT_SIZE] = { 1, 2, 2, 2 };
const int	KEY[KEY_SIZE] = { 1, 2, 3, 6 };

void	swap_ab(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	print_vector(vector<int> a)
{
	for (int i=0; i<a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << '\n';
}

void	initialize_ST(vector<int> &S, vector<int> &T)
{
	int	i;

	for (i=0; i<S.size(); i++)
	{
		S[i] = i;
		T[i] = KEY[i % KEY_SIZE];
	}
}

void	initial_permutation(vector<int> &S, vector<int> &T)
{
	int			i;
	int			j;
	vector<int>	ret(STATE_SIZE);

	j = 0;
	for (i=0; i<STATE_SIZE; i++)
	{
		j = (j + S[i] + T[i]) % STATE_SIZE;
		swap_ab(&S[i], &S[j]);
		cout << "ROUND : " << i << ", S : ";
		print_vector(S);
	}
}

vector<int>	get_Z(vector<int> &S, vector<int> &T)
{
	int			index;
	int			i;
	int			j;
	vector<int>	Z(TEXT_SIZE);

	j = 0;
	for (i=1; i<=TEXT_SIZE; i++)
	{
		j = (j + S[i]) % STATE_SIZE;
		swap_ab(&S[i], &S[j]);
		index = (S[i] + S[j]) % STATE_SIZE;
		Z[i - 1] += S[index];
	}
	return (Z);
}

vector<int>	get_encrypt(vector<int> Z)
{
	vector<int>	encrypt(TEXT_SIZE);

	for (int i=0; i<TEXT_SIZE; i++)
	{
		encrypt[i] = (PLAINTEXT[i] ^ Z[i]);	
	}
	return (encrypt);
}

int	main(void)
{
	vector<int>	S(STATE_SIZE);
	vector<int>	T(STATE_SIZE);
	vector<int>	Z;
	vector<int>	encrypt;

	initialize_ST(S, T);
	cout << "INIT VECTOR\n";
	cout << "S: ";
	print_vector(S);
	cout << "T: ";
	print_vector(T);
	cout << '\n';
	initial_permutation(S, T);
	cout << "AFTER PERMUTATION\nS: ";
	print_vector(S);
	cout << '\n';
	Z = get_Z(S, T);
	cout << "\nget Z : ";
	print_vector(Z);
	cout << '\n';
	encrypt = get_encrypt(Z);

	cout << "=================FINISH=================\n";
	cout << "PLAIN TEXT : ";
	for (int i=0; i<TEXT_SIZE; i++) cout << PLAINTEXT[i];
	cout << "\nZ : ";
	print_vector(Z);
	cout << '\n';
	cout << "ENCRYPT : ";
	print_vector(encrypt);
	cout<< '\n';
}
