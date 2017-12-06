#ifndef BITMANIPULATION_HPP_INCLUDED
#define BITMANIPULATION_HPP_INCLUDED

#include <iostream>
#include <bitset>

typedef unsigned long long uint64;

namespace bitmanipulations{
inline uint64 deltaSwap(uint64 bits, uint64 mask, int delta) {
uint64 x = (bits ^ ((uint64)bits >> delta)) & mask;
	return bits ^ x ^ ((uint64)x << delta);
};

inline uint64 horizontalMirror(uint64 t){
	t = deltaSwap(t, 0x0F0F0F0F0F0F0F0F, 4);
	t = deltaSwap(t, 0x3333333333333333, 2);
	return deltaSwap(t, 0x5555555555555555, 1);
};

inline uint64 verticalMirror(uint64 t){
	t = deltaSwap(t, 0x00000000FFFFFFFF, 32);
	t = deltaSwap(t, 0x0000FFFF0000FFFF, 16);
	return deltaSwap(t, 0x00FF00FF00FF00FF, 8);
};

inline uint64 diagonalMirror135(uint64 bits) {
	bits = deltaSwap(bits, 0x00000000F0F0F0F0, 28);
	bits = deltaSwap(bits, 0x0000CCCC0000CCCC, 14);
	return deltaSwap(bits, 0x00AA00AA00AA00AA,  7);
};

inline uint64 diagonalMirror45(uint64 bits) {
	bits = deltaSwap(bits, 0x000000000F0F0F0F, 36);
	bits = deltaSwap(bits, 0x0000333300003333, 18);
	return deltaSwap(bits, 0x0055005500550055, 9);
};

inline uint64 slashConv(uint64 n){
	n = (n & ~0xF0F0F0F0F0F0F0F0) | ((n & 0xF0F0F0F0F0F0F0F0) << 32) | ((n & 0xF0F0F0F0F0F0F0F0) >> 32);
	n = (n & ~0xCCCCCCCCCCCCCCCC) | ((n & 0xCCCCCCCCCCCCCCCC) << 16) | ((n & 0xCCCCCCCCCCCCCCCC) >> 48);
	return (n & ~0xAAAAAAAAAAAAAAAA) | ((n & 0xAAAAAAAAAAAAAAAA) << 8) | ((n & 0xAAAAAAAAAAAAAAAA) >> 56);
}

inline uint64 backSlashConv(uint64 n){
	n = (n & ~0xF0F0F0F0F0F0F0F0) | ((n & 0xF0F0F0F0F0F0F0F0) >> 32) | ((n & 0xF0F0F0F0F0F0F0F0) << 32);
	n = (n & ~0xCCCCCCCCCCCCCCCC) | ((n & 0xCCCCCCCCCCCCCCCC) >> 16) | ((n & 0xCCCCCCCCCCCCCCCC) << 48);
	return (n & ~0xAAAAAAAAAAAAAAAA) | ((n & 0xAAAAAAAAAAAAAAAA) >> 8) | ((n & 0xAAAAAAAAAAAAAAAA) << 56);
}

const int bitsCountTable[256] = {
	0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

inline int bitCount(uint64 bits){
	int num  = 0;

	for (int i=0 ; i < sizeof(bits) ; i++ ) {
		num += bitsCountTable[(bits >> (8*i)) & 0xff];
	}

	return num;
};

inline void showbinary(uint64 t) {
	using namespace std;
	bitset<64> n = t;
	for (int i = 0; i < 64; i++) {
		if ((i % 8) == 0) {
			cout << endl;
		}
		if (n[i]) {
			cout << "1";
		}	else{
			cout << "0";
		}
	}
	cout << endl;
	return;
};
};// namespace bitmanipulations

#endif //BITMANIPULATION_HPP_INCLUDED
