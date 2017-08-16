#include "utilities.hpp"

void InitMatrix (double * matrix, int size, int ldim)
{
	int current_value = 0;
	for (int current_address = 0; current_address < size * ldim ; current_address++)
	{
		if (current_address % ldim < size)
		{
			matrix[current_address] = current_value;
			std::cout << "matrix[" << current_address << "]= " << current_value << std::endl;
			current_value ++;
		}
		else
		{
			matrix[current_address] = 0;
			std::cout << "matrix[" << current_address << "]= " << 0 << std::endl;
		}
	}
}
