#include "rabbit_optimise.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	freopen("input.txt","r",stdin);
	freopen("output_optimise.txt","w",stdout);
	for(int i=0;i<8;i++)
		cin>>key[i];
	for(int i=0;i<2;i++)
		cin>>iv[i];
	vector <unsigned int> plaintext;
	int len;
	cin>>len;
	for(int i=0;i<len;i++){
		int x;
		//cin>>x;
		plaintext.push_back(0);
	}
	clock_t t = clock();
	encrypt_optimise(plaintext);
	t = clock()-t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	cerr<<time_taken<<endl;
	return 0;
}