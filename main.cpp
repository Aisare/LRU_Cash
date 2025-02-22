#include "LRUCash.h"
#include <string>
#include <iostream>

/// <summary>
/// A class for calculating the factorial using the LRU cache
/// </summary>
class Factorial
{
	/// <summary>
	/// Cache LRU<int, int64_t>
	/// </summary>
	LRU_Cash<int, int64_t> cash;
public:
	/// <summary>
	/// The constructor where the cache size is initialized
	/// </summary>
	/// <param name="size_cash">cache size</param>
	Factorial(int size_cash) : cash(size_cash) {}
	/// <summary>
	/// factorial calculation function
	/// </summary>
	/// <param name="numb">from what number are we looking for the factorial</param>
	/// <returns>the factorial of a number</returns>
	int64_t Calc(int numb)
	{
		if (numb == 0 || numb == 1)
			return 1;

		int64_t value = cash.get(numb);
		if (value != 0)
			return value;

		value = numb * Calc(numb - 1);
		cash.put(numb, value);
		return value;
	}
};

int main()
{
	/*
	
	Example of calculating the factorial using the LRU cache
	
	*/
	Factorial factorial(10);

	std::cout << "10! = " << factorial.Calc(10) << std::endl;
	std::cout << "9! = " <<factorial.Calc(9) << std::endl;
	std::cout << "8! = " <<factorial.Calc(8) << std::endl;
	std::cout << "5! = " <<factorial.Calc(5) << std::endl;
	std::cout << "3! = " <<factorial.Calc(3) << std::endl;

	return 0;
}