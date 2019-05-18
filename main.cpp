#include <iostream>
#include <chrono>
#include <array>
#include <vector>

using namespace std;

unsigned int fast_mod(unsigned long long int a, unsigned long long int b, unsigned long int c, unsigned int n = 0)
{
	if (n > 0)
	{
		if ((static_cast<unsigned long int>(1) << n - 1) > b) return 1;
		a = (a * a) % c;
	}
	n++;
	if ((b >> n - 1) & 1) return (a * fast_mod(a, b, c, n)) % c;
	return fast_mod(a, b, c, n);
}

array<unsigned long int, 2> sito(unsigned long int prime1, unsigned long int prime2)
{
	const unsigned long int SIZE = 2800000;
	bool* is_prime = new bool[SIZE]; // tablica booleanów 

	unsigned long int prime_counter = 0;

	for (int i = 2; i < SIZE; i++)
		is_prime[i] = 0;

	for (int i = 2; i*i < SIZE; i++)  //sprawdzanko która liczba jest pierwsza
	{							
		if (!is_prime[i])
			for (int j = i * i; j < SIZE; j += i)
				is_prime[j] = 1;
	}

	for (unsigned long int i = 2; i < SIZE; i++) // liczy na którym miejscu jest dana liczba pierwsza i przypisuje wartość jezeli znajdzie poszukiwaną liczbe
	{
		if (!is_prime[i])
		{
			prime_counter++;
		}
		if (prime_counter == prime1)
		{
			prime1 = i;
			break;
		}
	}

	prime_counter = 0;

	for (unsigned long int i = 2; i < SIZE; i++)
	{
		if (!is_prime[i])
		{
			prime_counter++;
		}
		if (prime_counter == prime2)
		{
			prime2 = i;
			break;
		}
	}

	delete[] is_prime;
	return { prime1, prime2 };
}

array<long int, 3> NWD(unsigned long int a, unsigned long int b, long int x0 = 1, long int x1 = 0, 
									long int y0 = 0, long int y1 = 1)
{
	unsigned long int temp;
	temp = a - (a / b) * b;
	if (!temp)
		return { static_cast<long int>(b), x1, y1 }; // tutaj wyrzuca ostateczny wynik
	
	//cout << "x: " << static_cast<long int>(x0 - x1 * (a / b)) // x2 = x0 - x1 * (a / b)
	//	<< "\ty:" << static_cast<long int>(y0 - y1 * (a / b)) << endl; // y2 = y0 - y1 * (a / b)
	return NWD(b, temp, x1, x0 - x1 * (a / b), y1, y0 - y1 * (a / b)); // NWD(a, b, x0, x1, y0, y1);
}

ostream& operator<<(ostream& os, array<unsigned long int, 2> rhs)
{
	os << "{ ";
	for (auto v : rhs) { os << v << " "; }
	os << '}';
	return os;
}

int main()
{
	
	unsigned long int prime1 = 237, prime2 = 426;
	array<unsigned long int, 2> primes;
	array<long int, 3> nwd;

	primes = sito(prime1, prime2);
	cout << prime1 << "  " << prime2 << endl;
	cout << primes[0] << "  " << primes[1] << endl;

	unsigned long int n = primes[0] * primes[1];
	unsigned long int m = (primes[0] - 1) * (primes[1] - 1);

	cout << "\nn: " << n << "\nm: " << m << "\n\n";
	unsigned long int e = 1703;
	
	nwd = NWD(e, m);
	while (nwd[1] < 0)
	{
		nwd[1] += m; nwd[2] -= 1703;
	}
	cout << "Nwd: " << nwd[0] << " x: " << nwd[1] << " y: " << nwd[2] << "\n\n";

	array<unsigned long int, 2> public_key = { n , e }, private_key = { n, nwd[1] };

	cout << public_key << " " << private_key << "\n\n";

	cout << "Przykladowy szyfrogram" << endl;
	cout << fast_mod(1969, public_key[1], public_key[0]) << endl;

	cout << "Deszyfracja przykładu" << endl;
	cout << fast_mod(fast_mod(1969, public_key[1], public_key[0]), private_key[1], private_key[0]) << endl;

	bool c;
	std::cin >> c;
	return 0;
}
