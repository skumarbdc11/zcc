
#define TEN (10)
#define TWENTY (TEN*2)

char g1=25;
short g2;
int g3,g4;

char buff[10]={1,2,3,4};

void test(char p1, short p2, int p3)
{
	char l1;
	short l2;
	int l3;

	g1 = p1+l3-l1;

	g3 = p3 % (++l3);

	if(g3<=TEN)
	{
		l2 = g2 * (p2--);
	}
	else
	{
		if(g3>=TWENTY)
		{
			l2 = g2 + p2;
		}
	}
}

void test1()
{
	while(g1>TEN)
	{
		g1++;

		g3 = g3+g4;
		if(g3>TWENTY)
			break;
	}
}

