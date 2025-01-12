#include <iostream>
#include <string>
#include <vector>

#define ASCII_START 65
#define ALPHABET_LEN 26 

std::string
decypher(std::string cipher_text, int i){
	using namespace std;
	vector<char> str(cipher_text.size());

	for(int a: cipher_text){
		int normalized = a-ASCII_START;
		normalized = (normalized+i)%ALPHABET_LEN + ASCII_START;
		str.push_back(static_cast<char>(normalized));
	}
	
	return string(str.begin(), str.end());
}

int main(){
	using namespace std;

	const string cipher_text = "KLLDPMXOHVLZLVKBRXDJRRGFUBSWRFODVV";

	for(int i=0; i<26; i++){
		cout << decypher(cipher_text, i) << " <-- " << i << endl;
	}
}
