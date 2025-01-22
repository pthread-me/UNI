#include <functional>
#include <numeric>
#include <ranges>
#include <print>
#include <iostream>


namespace rsv = std::ranges::views ;

int main(){
	using namespace std;
	
	int number;
	cin>>number;

	auto is_prime = [](int n){
		if(n<2) return false;
		for(int i=2; i*i<=n; i++){
			if(n%i==0){
				return false;
			}
		}
		return true;
	};	

	auto zeta = [](int p){
		return 1 - 1/static_cast<double>(p);
	};

	auto zeta_list = rsv::iota(2, number+1) 
		| rsv::filter(is_prime)
		| rsv::transform(zeta);

	auto zeta_product = accumulate(zeta_list.begin(), zeta_list.end(), 
			1.0, std::multiplies<>());
	
	print(stdout, "{}", zeta_product);
}
