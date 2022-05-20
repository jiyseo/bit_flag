#include <stdio.h>

enum bit_flags {
	FLAG_MINUS  = 0x01, //0000 0001
	FLAG_PLUS	= 0x02, //0000 0010
	FLAG_SPACE	= 0x04, //0000 0100

	FLAG_LED_B	= 0x10, //0001 0000
	FLAG_LED_G	= 0x20, //0010 0000
	FLAG_LED_R	= 0x40, //0100 0000
	FLAG_POWER	= 0x80, //1000 0000

	FLAG_LED	= FLAG_LED_R | FLAG_LED_G | FLAG_LED_B, // FLAG_LED = 0x70 임
};

/*
bit number(2의 제곱값, 2진 자리값)
  #7     #6     #5     #4     #3     #2     #1     #0(=2의 0제곱)
  0x80   0x40   0x20   0x10          0x04   0x02   0x01
  POWER  LED_R  LED_G  LED_B         SPACE  PLUS   MINUS

int a, b;
a = 5;
b = ~a;  // b = -a - 1 또는  b= -(a + 1)와 같음
// 즉 bit NOT 연산자 ~은 2의 보수값과 같음
// b에는 -6이 저장됨

*/

void dump_bitmap(int val, int bit_count) {
	unsigned int mask = 1 << --bit_count;

	while (mask) {
		putchar( (val & mask) ? '1' : '0');
		if (bit_count > 0 && bit_count-- % 4 == 0) putchar(' '); // 4자리마다 공백
		mask >>= 1;
	}
}

void dump_label(int val) {

	printf("POWER(%-3s) ", (val & FLAG_POWER) ? "ON" : "OFF");
	printf("LED_R(%-3s) ", (val & FLAG_LED_R) ? "ON" : "OFF");
	printf("LED_G(%-3s) ", (val & FLAG_LED_G) ? "ON" : "OFF");
	printf("LED_B(%-3s) ", (val & FLAG_LED_B) ? "ON" : "OFF");

	printf("LED(%-3s) ", (val & FLAG_LED) ? "ON" : "OFF");
//	printf("LED(%-3s) ", (val & (FLAG_LED_R|FLAG_LED_G|FLAG_LED_B)) ? "ON" : "OFF"); // 윗 문장과 같음
	printf("' '(%c) ", (val & FLAG_SPACE) ? 'o' : 'x');
	printf("'+'(%c) ", (val & FLAG_PLUS) ? 'o' : 'x');
	printf("'-'(%c) ", (val & FLAG_MINUS) ? 'o' : 'x');
}

void dump_bits(int val) {
	printf("%02X : ", val);
	dump_bitmap(val, 8);
	printf(" : ");
	dump_label(val);
	putchar('\n');
}

int main()
{
	int flag = 0;
	int bit, num, sw;

	printf("T#1: ");
	flag |= FLAG_POWER; // 해당 bit 켜기
	dump_bits(flag);

	printf("T#2: ");
	flag |= FLAG_LED_R; // 해당 bit 켜기
	dump_bits(flag);

	printf("T#3: ");
	flag |= (FLAG_LED_G | FLAG_LED_B); // 2개 bit 동시 켜기
	dump_bits(flag);

	printf("T#4: ");
	flag &= ~FLAG_POWER; // 해당 bit 끄기, FLAG_POWER 비트를 ~로 부정하면 해당 bit를 0으로 하고 나머지는 모두 1이 됨
	dump_bits(flag);

	printf("T#5: ");
	flag &= ~(FLAG_LED_G | FLAG_LED_B); // 2개 bit 동시 끄기
	dump_bits(flag);

	printf("T#6: ");
	flag ^= FLAG_POWER; // 해당 bit 반전, XOR(exclusive OR, 배타적 OR)로 0은 1로 1은 0으로 반전함
	dump_bits(flag);

	printf("T#7: ");
	flag ^= FLAG_POWER; // 해당 bit 반전, XOR(exclusive OR, 배타적 OR)로 0은 1로 1은 0으로 반전함
	dump_bits(flag);

	while (1) {
		printf("  7      6      5      4      3      2      1      0\n");
		printf("POWER  LED_R  LED_G  LED_B         SPACE  PLUS   MINUS\n");
		printf("bits num(-1:exit) : ");
		scanf("%d", &num);
		if (num < 0) break;
		printf("switch(on=1,off=0) : ");
		scanf("%d", &sw);
		bit = 1 << num;
		if (sw == 0) {
			flag &= ~bit;
		} else {
			flag |= bit;
		}
		dump_bits(flag);
	}

    return 0;
}
