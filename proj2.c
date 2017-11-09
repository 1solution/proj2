#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

	int eps(double uhel) { // fce zpresnuje vysledek na 10 mist, mezi n a n+1
    int n = 1;
    while(fabs(cfrac_tan(uhel,n) - cfrac_tan(uhel,n+1)) > 0.00000000001)
      n++;
    return n;
	}

  double vypocetDelka(double alfa, double c) { // vypocet D
        double delka = c / cfrac_tan(alfa,eps(alfa));
			return delka;
	}
 double vypocetVyska(double alfa, double beta, double c) { // vypocet V
        double vyska = c + (vypocetDelka(alfa, c) * cfrac_tan(beta,eps(beta)));
      return vyska;
	}

		void tiskniTan(int* N, int* M, double* tt) {
		double sumTaylor = 0;
		for(int i = 1; i <= *M; i++) {
			sumTaylor += taylor_tan(*tt,i);
			if(i >= *N && i <= *M)
				printf("%d %e %e %e %e %e\n", i, tan(*tt), sumTaylor, fabs(tan(*tt) - sumTaylor), cfrac_tan(*tt,i), fabs(tan(*tt)-cfrac_tan(*tt,i)));
		}
	}

int main(int argc, char **argv) {

  double c = 1.5; // default c = 1.5

  if(argv[1]) {
    if(strcmp("--help",argv[1]) == 0 && argc == 2) {
      char napoveda[] = "--tan A N M, where A is RAD angle (0;1.4>, N is start cycle and M is end cycle\n[-c X] -m A [B], where X is height of measurement starting point, A is RAD angle (0;1.4> and B is RAD angle (0;1.4>";
      printf("%s", napoveda);
      return 0;
    }
    else if(strcmp("--tan",argv[1]) == 0 && argc == 5) { // pak over jestli to jsou cisla. VSUDE. podminka pro uhel min a max (0;1.4> isinf a isnan
      double tt = atof(argv[2]);
      int N = atoi(argv[3]);
      int M = atoi(argv[4]);
        if(0 < N && N <= M && M < 14)
          tiskniTan(&N, &M, &tt);
        else {
        fprintf(stderr, "%s", "Incorrect N / M values (type --help)");
        return 1;
        }

      return 0;
    }
    else if(strcmp("-c",argv[1]) == 0) {
      c = atof(argv[2]);
      if(c > 0 && c <= 100) {
        if(argc == 5) {
          double alfa = atof(argv[4]);
          printf("%.10e\n", vypocetDelka(alfa,c));
          return 0;
        }
        if(argc == 6) {
          double alfa = atof(argv[4]);
          double beta = atof(argv[5]);
          printf("%.10e\n%.10e\n", vypocetDelka(alfa,c), vypocetVyska(alfa,beta,c));
          return 0;
        }
      }
      else {
      fprintf(stderr, "%s", "Incorrect X value (type --help)");
      return 1;
      }
    }
    else if(strcmp("-m",argv[1]) == 0) {
      if(argc == 3) {
        double alfa = atof(argv[2]);
        printf("%.10e\n", vypocetDelka(alfa,c));
        return 0;
      }
      if(argc == 4) {
        double alfa = atof(argv[2]);
        double beta = atof(argv[3]);
        printf("%.10e\n%.10e\n", vypocetDelka(alfa,c), vypocetVyska(alfa,beta,c));
        return 0;
      }
    }
  }
  else {
    fprintf(stderr, "%s", "No argument entered.\n");
    return 1;
  }

return 0;

system("PAUSE");

}
