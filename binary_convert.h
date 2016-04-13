#include <cstdio>
#include <string>
using namespace std;
inline void convert(unsigned int val){
	string s = "00000000000000000000000000000000";
	int i=31;
	while(val){
		if(val&1){
			s[i]+=1;
		}
		val/=2;
		i--;
	}
	puts(s.c_str());
}