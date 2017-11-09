#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	double myOwnPow(double x, int n) { // fce simuluje mocninu
		int naKolikatou = 2*n - 1;
		double y = x;
		for(int i = 1; i < naKolikatou; i++)
			x = x * y;
		return x;
	}
	double taylor_tan(double x, unsigned int n) { // fce vypocita v jednom kroku taylor_tan, pouze pro jeden krok. zpracovani az v main nebo do jine funkce
		unsigned long long citatel[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
		unsigned long long jmenov[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};
		double vysledek = (((double)citatel[n-1]) * (myOwnPow(x, n))) / ((double)jmenov[n-1]);
	return vysledek;
	}
	double cfrac_tan(double x, unsigned int n) { // fce vypocita tangens pomoci fraktalovych zlomku, tentokrat ale primo soucet vsech kroku
	double vysledek = 0;
	for(int i = n; i > 0; i--)
		vysledek = 1 / (((2*i - 1) / x) - vysledek);
	return vysledek;
	}

	int eps(double uhel) {
    int n = 1;
    while(fabs(cfrac_tan(uhel,n) - cfrac_tan(uhel,n+1)) > 0.00000000001)
      n++;
    return n;
	}

  struct Vysledky dopocitani(double alfa, double beta, double c) {

        double delka = c / cfrac_tan(alfa,eps(alfa)); // vyp delky
        double vyska = c + (delka * cfrac_tan(beta,eps(beta))); // vyp vysky
        struct Vysledky hold = {delka, vyska};
      return hold;
	}

int main(int argc, char *argv[]) {

    struct Vysledky {
    double delka;
    double vyska;
    };

	double tt = 1.024; // nacti argv1
  int N = 2; // nacti argv 2
  int M = 7; // nacti argv3
  double sumTaylor = 0;
  double alfa = 0.3;
  double beta = 1.3;
  double c = 1.5;

	for(int i = 1; i <= M; i++) {
		sumTaylor += taylor_tan(tt,i);
		if(i >= N && i <= M) {// TADY TO VEZME KAZDY KROK MEZI N A M, tzn tisk provadet asi tady
			printf("%d %e %e %e %e %e\n", i, tan(tt), sumTaylor, fabs(tan(tt) - sumTaylor), cfrac_tan(tt,i), fabs(tan(tt)-cfrac_tan(tt,i)));
		}
	}

return 0;
}
