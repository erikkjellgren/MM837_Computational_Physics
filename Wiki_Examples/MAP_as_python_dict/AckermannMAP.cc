#include <iostream> 
#include <map> 
 
using namespace std;
typedef pair<long long,long long> python_like_key;
map<python_like_key,long long> python_like_dict; 
 
long long ackermann(long long m, long long n) { 
	python_like_key key(m,n);
	if (python_like_dict.find(key) != python_like_dict.end()) { 
		return(python_like_dict[key]); 
	} 

	long long result; 
	if (m == 0) { 
		result = n+1;
		python_like_dict[key] = result; 
		return result; 
	} 
	if (n == 0) { 
		result = ackermann(m-1, 1); 
		python_like_dict[key] = result; 
		return result; 
	} 
	result = ackermann(m-1, ackermann(m, n-1)); 
	python_like_dict[key] = result; 
	return result; 

} 

int main(){
	long long m, n;
	m = 4;
	n = 1;
	cout << ackermann(m, n) << '\n';
}