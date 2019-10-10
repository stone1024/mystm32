//跑马灯的实现
typedef struct {
	unsigned int CON;
	unsigned int DAT;
}gpx2;
#define GPX2 (*(gpx2*)0x11000c40) //led2  gpx2-7

typedef struct {
	unsigned int CON;
	unsigned int DAT;
}gpx1;
#define GPX1 (*(gpx1*)0x11000c20) //led3 gpx1-0

typedef struct {
	unsigned int CON;
	unsigned int DAT;
}gpf3;
#define GPF3 (*(gpf3*)0x114001e0) //led4 gpf3-4  led5 gpf3-5

void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

int main()
{
		//打开led2、led3、led4、led5的GPIO口
	GPX2.CON = (GPX2.CON & ~(0xf<<28))| 1<<28;  //led2 gpx2_7
	GPX1.CON = (GPX1.CON & ~(0xf))| 1;  //led3  gpx1_0
	GPF3.CON = (GPF3.CON & ~(0xf<<16 | 0xf<<20))|(1<<16 |1<<20);//led4 gpf3_4 led5 gpf3_5
	
	while(1)
	{
		//点亮 led2
		GPX2.DAT |= (0x1<<7);
		mydelay_ms(500);
		//点亮led3
		GPX1.DAT |= 0x1;
		//关闭led2
		GPX2.DAT &= ~(0x1<<7);
		mydelay_ms(500);
		//on led4,off led3
		GPF3.DAT |= (0x1<<4);
		GPX1.DAT &= ~0x1;
		mydelay_ms(500);

		//on led5,off led4
		GPF3.DAT |= (0x1<<5);
		GPF3.DAT &= ~(0x1<<4);
		mydelay_ms(100);
		//off led5
		GPF3.DAT &= ~(0x1<<5);
		mydelay_ms(500);

	}

}
