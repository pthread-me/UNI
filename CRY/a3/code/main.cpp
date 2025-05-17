#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace rsv = std::ranges::views;

int main(){
	using namespace std;

	pair<int,int> key(7,8);
	
	auto cipher = [](string text, pair<int,int> key){
		auto [k1, k2] = key;
		auto ciphered = string_view(text)
			| rsv::transform([k1, k2](char a){
				return a*k1 + k2;
			});
	};

	auto ciphered = cipher("abc", key);
}
