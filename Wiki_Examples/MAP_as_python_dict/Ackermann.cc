#include <iostream> 
 
using namespace std;
 
long long ackermann(long long m, long long n) { 
	if (m == 0) { 
		return n+1; 
	} 
	if (n == 0) { 
		return ackermann(m-1, 1); 
	} 
	return ackermann(m-1, ackermann(m, n-1)); 

} 

int main(){
	long long m, n;
	m = 4;
	n = 1;
	cout << ackermann(m, n) << '\n';
}