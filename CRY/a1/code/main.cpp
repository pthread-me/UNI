#include <iostream>


constexpr int non_negative_mod(int a, int m){
	return ((a%m)+m)%m;
}

constexpr int representative(int residue, int multiple, int modulo){
	for(int i=0;; i+=multiple){
		if(non_negative_mod(i, modulo) == residue){
			return i;
		}
	}
}

int main(){
	using namespace std;
	
	/* q5.a logic
	 *
	for(int x=-50; x<=50; x++){
		if(non_negative_mod(x, 17) == 7){
			cout << x << " , ";
		}
	}
	*/

	for(int i=0; i<17; i++){
		cout << representative(i, 3, 17) << " , " << flush;	
	}
}
