#include <vector>
#include <iostream>

int main(){
	using namespace std;

	vector<int> w({1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,0,1,0,0,0,1});
	vector<int> z({1,0,1,0,0,1,1});

	for(size_t i=7; i<21; i++){
		int elem = z[i-7]+ z[i-7+1]+ z[i-7+4] + z[i-7+5] + z[i-7+6];
		z.push_back(elem % 2);
	}

	for(size_t i =0; i<z.size(); i++){
		cout << z[i];
		if (i%7==6) cout << "\t";
	}
		
}
