#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
unsigned int key[8];
unsigned int iv[2];
unsigned int X[8];
unsigned int C[8],old_C[8];
unsigned int A[8];
unsigned int carry;
unsigned int rotate_left(unsigned int v, unsigned int k) {
	return (k%32 == 0) ? v : ((v << k) | (v >> (32 - k)));
}
void reset(){
	for(int i=0;i<8;i++){
		X[i] = C[i] = 0;
	}
	A[0] = A[3] = A[6] = 0x4D34D34D;
	A[1] = A[4] = A[7] = 0xD34D34D3;
	A[2] = A[5] = 0x34D34D34;
}
void counter_system(){
	long long temp;
	long long b=0;
	for(int i=0;i<8;i++) old_C[i]=C[i];

	temp = (C[0] & 0xFFFFFFFFll) + (A[0] & 0xFFFFFFFFll) + carry;
    C[0] = (unsigned int) (temp & 0xFFFFFFFFll);

	for(int i=1;i<8;i++) {
		temp = (C[i] & 0xFFFFFFFFll) + (A[i] & 0xFFFFFFFFll) + (old_C[i-1]>C[i-1]);
		C[i] = (unsigned int) (temp & 0xFFFFFFFFll);
	}
	carry = (old_C[7]>C[7]);
}
void next_state(){
	counter_system();
	unsigned int g[8];
	long long temp;
	for(int i=0;i<8;i++) {
		temp = (X[i] + C[i]) & 0xFFFFFFFF;
		temp = temp*temp;
		g[i] = (unsigned int)( ((temp) ^ (temp >> 32))& 0xFFFFFFFF);
	}
	for(int i=0;i<8;i++){
		if(i&1)
			X[i] = g[i] + rotate_left(g[(i+7)%8],8) + g[(i+6)%8];
		else
			X[i] = g[i] + rotate_left(g[(i+7)%8],16) + rotate_left(g[(i+6)%8],16);
	}
}
void iv_setup(){
	C[0]^=iv[0];
	C[2]^=iv[1];
	C[4]^=iv[0];
	C[6]^=iv[1];
	C[1]^=( ((iv[1]>>16)<<16) | ((iv[0]>>16)) );
	C[3]^=( (iv[1]<<16) | ((iv[0]<<16)>>16) );
	C[5]^=( ((iv[1]>>16)<<16) | ((iv[0]>>16)) );
	C[7]^=( (iv[1]<<16) | ((iv[0]<<16)>>16) );
	for(int i=0;i<4;i++){
		next_state();
	}
}
void key_setup(){
	for(int i=0;i<8;i++){
		if(i&1){
			X[i] = (key[(i+5)%8]<<16) | key[(i+4)%8];
			C[i] = (key[i]<<16) | (key[(i+1)%8]);
		}
		else{
			X[i] = (key[(i+1)%8]<<16) | key[i];
			C[i] = (key[(i+4)%8]<<16) | (key[(i+5)%8]);
		}
	}
    carry=0;
	for(int i=0;i<4;i++){
		next_state();
	}
	for (int i = 0; i < 8; i++)
        C[(i + 4) & 0x7] ^= X[i];

}
void encrypt(vector <unsigned int> plain_text){
	reset();
	key_setup();
	iv_setup();
	vector <unsigned int> cipher_text;
	for(int i=0;i<plain_text.size();){
		next_state();
		for(int j=0;j<8 && i<plain_text.size();j+=2,i++){
			cipher_text.push_back(plain_text[i] ^ X[j] ^ (X[(j+5)%8]>>16) ^ (X[(j+3)%8]<<16) );
		}
	}
	printf("Cipher text in hex:\n");
	for(int i=0;i<cipher_text.size();i++){
		printf("%02X %02X %02X %02X ",(cipher_text[i]&0x000000FF),(cipher_text[i]&0x0000FF00)>>8,
		(cipher_text[i]&0x00FF0000)>>16,(cipher_text[i]&0xFF000000)>>24);
	}
	cout<<endl;
}