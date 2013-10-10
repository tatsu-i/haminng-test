#include <stdio.h>
#include <stdint.h>
#include "encode.h"

int main(int argc, char* argv[]) {
	uint16_t ix = 1702;//情報ビット
	uint16_t gx = 0x13;//b10011(生成多項式)
	uint16_t rx = bitdiv(ix, gx);//R(x)を計算
	uint16_t cx = rx|(ix<<(GXBIT_LEN-1));//C(x)を求める.
	uint16_t res = 0;

	// 組織符号表示
	printf("[組織符号化]\nC(x)=[%s]\n\t\tx_1 -> x_10\n\n", rbin(cx,15));

	// 誤り訂正
	printf("[誤り訂正]\nC(x)=0x%04x,I(x)=%d : 誤りなしの場合\n", cx, cx>>4);
	cx = cx ^ 0x04;// 誤りビットを入れてみる
	printf("C(x)=0x%04x,I(x)=%d : 誤りビットを加える", cx, cx>>4);
	if((res = check(cx)) != 0)// 誤りチェック
		printf("\n下位のビットから数えて%dビット目に誤り\n正しくはC(x)=0x%04x\n",
				res,correct(cx,res));// 誤り訂正
	else
		printf("\n誤りビットなし\n");
	return 0;
}
