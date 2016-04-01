#include "rabbit.h"
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <utility>
#include <functional>
using namespace std;

#define MP(x, y) make_pair(x, y)
#define SET(p) memset(p, -1, sizeof(p))
#define CLR(p) memset(p, 0, sizeof(p))
#define MEM(p, v) memset(p, v, sizeof(p))
#define CPY(d, s) memcpy(d, s, sizeof(s))
#define SZ(c) (int)c.size()
#define PB(x) push_back(x)
#define ff first
#define ss second
#define ll long long
#define ld long double
#define mod 1000000007
#define inf 1061109567LL
#define pii pair< int, int >
#define pll pair< ll, ll >
#define psi pair< string, int >
int main(int argc, char const *argv[])
{
	for(int i=0;i<8;i++)
		key[i] = 0;
	for(int i=0;i<2;i++)
		iv[i] = 0;
	vector <unsigned int> plaintext;
	for(int i=0;i<8;i++)
		plaintext.push_back(0);
	reset();
	key_setup();
	iv_setup();
	vector <unsigned int> cipher;
	cipher = encrypt(plaintext);
	for(int i=0;i<cipher.size();i++){
		printf("%02X %02X %02X %02X ",(cipher[i]&0x000000FF),(cipher[i]&0x0000FF00)>>8,
		(cipher[i]&0x00FF0000)>>16,(cipher[i]&0xFF000000)>>24);
	}
	cout<<endl;
	return 0;
}