#include "binary_convert.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
unsigned long long maxsize = 4294967296ll;
unsigned int key[8];
unsigned int iv[2];
unsigned int X[8];
unsigned int C[8],old_C[8];
unsigned int A[8];
unsigned int carry;
unsigned int g[8];
inline unsigned int rotate_left_optimise(unsigned int v, unsigned int k) {
	return (k & 31 == 0) ? v : ((v << k) | (v >> (32 - k)));
}
inline void reset_optimise(){
	for(int i=0;i<8;i++){
		X[i] = C[i] = 0;
	}
	A[0] = A[3] = A[6] = 0x4D34D34D;
	A[1] = A[4] = A[7] = 0xD34D34D3;
	A[2] = A[5] = 0x34D34D34;
}
inline void counter_system_optimise(){
	long long temp;
	long long b=0;
	for(int i=0;i<8;i++) old_C[i]=C[i];

	temp = (C[0] & (maxsize-1)) + (A[0] & (maxsize-1)) + carry;
    C[0] = (unsigned int) (temp & (maxsize-1));

	for(int i=1;i<8;i++) {
		temp = (C[i] & (maxsize-1)) + (A[i] & (maxsize-1)) + (old_C[i-1]>C[i-1]);
		C[i] = (unsigned int) (temp & (maxsize-1));
	}
	carry = (old_C[7]>C[7]);
}
inline void next_state_optimise(){
	counter_system_optimise();
	long long temp;
	for(int i=0;i<8;i++) {
		temp = (X[i] + C[i]) & (maxsize-1);
		temp = temp*temp;
		g[i] = (unsigned int)( ((temp) ^ (temp >> 32))& (maxsize-1));
	}
	for(int i=0;i<8;i++){
		if(i&1)
			X[i] = g[i] + rotate_left_optimise(g[(i+7) & 7],8) + g[(i+6) & 7];
		else
			X[i] = g[i] + rotate_left_optimise(g[(i+7) & 7],16) + rotate_left_optimise(g[(i+6) & 7],16);
	}
}
inline void iv_setup_optimise(){
	C[0]^=iv[0];
	C[2]^=iv[1];
	C[4]^=iv[0];
	C[6]^=iv[1];
	C[1]^=( ((iv[1]>>16)<<16) | ((iv[0]>>16)) );
	C[3]^=( (iv[1]<<16) | ((iv[0]<<16)>>16) );
	C[5]^=( ((iv[1]>>16)<<16) | ((iv[0]>>16)) );
	C[7]^=( (iv[1]<<16) | ((iv[0]<<16)>>16) );
	next_state_optimise();
	next_state_optimise();
	next_state_optimise();
	next_state_optimise();
}
inline void key_setup_optimise(){
	for(int i=0;i<8;i++){
		if(i&1){
			X[i] = (key[(i+5)&7]<<16) | key[(i+4)&7];
			C[i] = (key[i]<<16) | (key[(i+1)&7]);
		}
		else{
			X[i] = (key[(i+1)&7]<<16) | key[i];
			C[i] = (key[(i+4)&7]<<16) | (key[(i+5)&7]);
		}
	}
    carry=0;
	next_state_optimise();
	next_state_optimise();
	next_state_optimise();
	next_state_optimise();
	for (int i = 0; i < 8; i++)
        C[(i + 4) &7] ^= X[i];

}
inline void encrypt_optimise(vector <unsigned int> plain_text,bool do_iv_setup=true){
	reset_optimise();
	key_setup_optimise();
	if(do_iv_setup)
		iv_setup_optimise();
	vector <unsigned int> cipher_text;
	for(int i=0;i<plain_text.size();){
		next_state_optimise();
		for(int j=0;j<8 && i<plain_text.size();j+=2,i++){
			unsigned int temp = plain_text[i] ^ X[j] ^ (X[(j+5)%8]>>16) ^ (X[(j+3)%8]<<16);
			cipher_text.push_back(temp);
			convert(temp);
		}
	}
	//printf("Cipher text in hex:\n");
	for(int i=0;i<cipher_text.size();i++){
		//printf("%02X %02X %02X %02X ",(cipher_text[i]&0x000000FF),(cipher_text[i]&0x0000FF00)>>8,
		//(cipher_text[i]&0x00FF0000)>>16,(cipher_text[i]&0xFF000000)>>24);
	}
	//cout<<endl;
}