#include "rabbit.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	printf("Key:\n");
	for(int i=0;i<8;i++)
		cin>>key[i];
	printf("iv:\n");
	for(int i=0;i<2;i++)
		cin>>iv[i];
	vector <unsigned int> plaintext;
	int len;
	printf("Size of plaintext:\n");
	cin>>len;
	printf("Plaintext:\n");
	for(int i=0;i<len;i++){
		int x;
		cin>>x;
		plaintext.push_back(x);
	}
	encrypt(plaintext);
	return 0;
}