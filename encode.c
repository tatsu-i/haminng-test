#include <stdio.h>
#include <stdint.h>
#include "encode.h"


// 二進数の逆順文字列生成関数
// num : 反転する数値
// bit : 反転する数値のbit数
// 戻り値 : 二進数文字列
int8_t *rbin(uint16_t num, uint8_t bit){
	int i = 0;
	uint16_t shnum = num;
	bin.string16[0]='\0';
	
	for(;i < bit; i++, shnum >>= 1)
		sprintf(bin.string16, "%s%01d", bin.string16, shnum&1);
	return bin.string16;
}

// AND演算関数
// 0,0 = 0
// 0,1 = 0
// 1,0 = 1
// 1,1 = 1
// 戻り値 : 演算結果
uint16_t _AND(uint16_t a, uint16_t b){
	int i = 0;
	uint16_t ret = 0;
	uint16_t sha = a;
	uint16_t shb = b;

	for(;i < 16; i++, sha >>= 1, shb >>= 1)
		if(sha&1 == 1)ret |= 1<<i;
		else ret |= ((sha&shb)&1)<<i;
	return ret;
}

// R(x)の計算を行う関数
// info : I(x)
// gen : G(x)
// 戻り値 : 演算結果
uint16_t bitdiv(uint16_t info, uint16_t gen){
	int i= 0;
	uint16_t res = info;
	uint16_t shgen = gen;

	for(;i < IXBIT_LEN; i++, shgen <<= 1)
		if((((res&shgen)>>i)&1) == 1)
			res = res^shgen;
		else
			res = _AND(res,shgen);
	return res>>IXBIT_LEN;
}

// 誤り検出関数
// cx : 検査対象ビット C(x)
uint16_t check(uint16_t cx){
	int i = 0;
	uint16_t shcx = cx;
	uint16_t checkbit = 0;
	uint8_t check_table[]={
			0x1,0x2,0x4,0x8,0x3,
			0x6,0xc,0xb,0x5,0xa,
			0x7,0xe,0xf,0xd,0x9
	};// 検査ビット

	for(;i<15;i++, shcx >>= 1)
		if(shcx&1 == 1)
			checkbit^=check_table[i];
	if(checkbit == 0)
		return 0;
	else
		for(i=0;i<15;i++)
			if(checkbit == check_table[i])return i+1;
}

// 誤り訂正関数
// num : 訂正対象ビット C(x)
// bit : 誤りを含むビット数
uint16_t correct(uint16_t num, uint8_t bit){
	int i = 0;
	uint16_t ret = num;

	for(;i<16;i++)
		if(i == (bit-1)){
			ret ^= (1<<i);
			break;
		}
	return ret;
}
