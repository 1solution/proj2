#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double myOwnPow(double x, int n) { // X: co na treti
	int naKolikatou = 2*n - 1;

	for(int i = 1; i < naKolikatou; i++)
		x *= x;

return x;
}

double taylor_tan(double x, unsigned int n) { // mezi hodnotama n a m se to ma scitat ty polynomy, tzn 5 bude od x^1 do x ^9 atd..)
	unsigned long long citatel[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
	unsigned long long jmenovatel[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};
	double vysledek;

	vysledek = (((double)citatel[n-1]) * (myOwnPow(x, n))) / jmenovatel[n-1];

	return vysledek;
}


int main() {

	printf("%e\n", taylor_tan(1.024, 1));
	printf("%e\n", taylor_tan(1.024, 2));
	printf("%e\n", taylor_tan(1.024, 3));
	printf("%e\n", taylor_tan(1.024, 4));
	printf("%e\n", taylor_tan(1.024, 5));
	printf("%e\n", taylor_tan(1.024, 6));
	printf("%e\n", taylor_tan(1.024, 7));
	printf("%e\n", taylor_tan(1.024, 8));
	printf("%e\n", taylor_tan(1.024, 9));
	printf("%e\n", taylor_tan(1.024, 10));
	printf("%e\n", taylor_tan(1.024, 11));
	printf("%e\n", taylor_tan(1.024, 12));
	printf("%e\n", taylor_tan(1.024, 13));

char b;

	scanf("%c", &b);

     return 0;
}
