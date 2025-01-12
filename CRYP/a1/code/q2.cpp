#include <iostream>
#include <vector>
#include <fstream>
#include <tokenizer.hpp>
#include <boost/bimap.hpp>


inline int non_negative_mod(int a, int m){
	return ((a%m)+m)%m;
}

std::pair<char, char>
decipher(char a, char b, boost::bimap<char, std::pair<int, int>> key_map){
	using namespace std;

		
	pair<int, int> const &a_pos = key_map.left.find(a)->second;
	pair<int, int> const &b_pos = key_map.left.find(b)->second;

	char a_prime;
	char b_prime;

	if(a_pos.first == b_pos.first){
		a_prime = key_map.right.find(pair(a_pos.first, non_negative_mod(a_pos.second -1, 5)))->second;	
		b_prime = key_map.right.find(pair(b_pos.first, non_negative_mod(b_pos.second -1, 5)))->second;	
	}else if(a_pos.second == b_pos.second){
		a_prime = key_map.right.find(pair(non_negative_mod(a_pos.first -1, 5), a_pos.second))->second;
		b_prime = key_map.right.find(pair(non_negative_mod(b_pos.first -1, 5), b_pos.second))->second;
	}else{
		a_prime = key_map.right.find(pair(a_pos.first, b_pos.second))->second;
		b_prime = key_map.right.find(pair(b_pos.first, a_pos.second))->second;
	}
	return pair(a_prime, b_prime);	
}


int main(){
	using namespace std;
	
	fstream input("key.txt");
	string line;
	
	boost::bimap<char, pair<int, int>> key_map;
	string cipher_text;

	//storing the i,j positions of each letter in the key matrix
	for(int i=0; getline(input, line); i++){
		auto tokens = tokenize(line, " ");
		for(int j=0; j<tokens.size(); j++){
			key_map.insert({*tokens.at(j).c_str(), pair(i, j)});
		}
	}
	input.close();

	input.open("cipher_text.txt");
	getline(input, cipher_text);
	input.close();

	for(auto iter=cipher_text.begin(); iter <= cipher_text.end()-1; iter+=2){
		auto deciphered = decipher(*iter, *(iter+1), key_map);
		cout << deciphered.first << deciphered.second;
	}

}

