#include <ranges>
#include <print>
#include <iostream>

namespace rsv = std::ranges::views;

int main(){
	using namespace std;

	int determinant = 324;
	
	auto is_prime = [](int n){
		if(n<2) return false;
		for(int i=2; i*i<=n; i++){
			if(n%i == 0) return false;
		}
		return true;
	};

	auto is_factor = [determinant](int n){
		return determinant%n == 0;	
	};

	auto prime_factors = rsv::iota(2, determinant)
		| rsv::filter(is_prime)
		| rsv::filter(is_factor);
		


	for(auto p: prime_factors){
		cout << p << "\t";
	}
}
