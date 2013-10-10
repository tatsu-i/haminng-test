#define IXBIT_LEN 11
#define GXBIT_LEN 5

struct BIN {
	int8_t string16[17];
}bin;

int8_t *rbin(uint16_t num, uint8_t bit);
uint16_t _AND(uint16_t a, uint16_t b);
uint16_t bitdiv(uint16_t info, uint16_t gen);
uint16_t check(uint16_t cx);
uint16_t correct(uint16_t num, uint8_t bit);

