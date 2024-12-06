#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdint>

class Bitvector{

	uint16_t* mini_header;
	uint64_t* macro_header;
	int* countAs;


	public: 
		Bitvector(int size);
		int rank(int index);
		int count(char* query)

}
