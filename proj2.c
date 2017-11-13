#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define EPS 0.00000000001
// xplsek03, M.Plsek, proj2 KNOWN BUGS: does not support e in floats, rewrite taylor_tan for, strtod for checking e in double convention
	int checkAngle(double x) { // checks angle value from (0; 1.4>
		if(x > 0 && x <= 1.4)
			return 1;
		return 0;
	}

	int validArguments(int argc, char* argv[]) { // fction checks if arguments put by user are in valid format
	  int override = 0;
		for(int i = 2; i < argc; i++) {
		  if(argc > 4 && !strcmp(argv[1],"-c") && !strcmp(argv[3],"-m"))
        override = 1;
			for(int k = 0; argv[i][k] != '\0'; k++) {
				if(!isdigit(argv[i][k]) && argv[i][k] != '.' && argv[i][k] != 'e' && override == 0)
					return 0;
			}
		}
		return 1;
	}

	double myOwnPow(double x, int n) { // power
		int naKolikatou = 2*n - 1;
		double y = x;
		for(int i = 1; i < naKolikatou; i++)
			x = x * y;
		return x;
	}
	double taylor_tan(double x, unsigned int n) { // processing taylor_tan step by step
		unsigned long long citatel[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
		unsigned long long jmenov[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};
		double vysledek = (((double)citatel[n-1]) * (myOwnPow(x,n))) / ((double)jmenov[n-1]);
	return vysledek;
	}
	double cfrac_tan(double x, unsigned int n) { // processing cfrac_tan by sum of all steps
	double vysledek = 0;
	for(int i = n; i > 0; i--)
		vysledek = 1 / (((2*i - 1) / x) - vysledek);
	return vysledek;
	}

	int eps(double uhel) { // eps function , 10 dec places between n and n+1
    int n = 1;
    while(fabs(cfrac_tan(uhel,n) - cfrac_tan(uhel,n+1)) > EPS)
      n++;
    return n;
	}

  double vypocetDelka(double alfa, double c) { // calculate length D
        double delka = c / cfrac_tan(alfa,eps(alfa));
			return delka;
	}
 double vypocetVyska(double alfa, double beta, double c) { // calculate height V
        double vyska = c + (vypocetDelka(alfa, c) * cfrac_tan(beta,eps(beta)));
      return vyska;
	}

		void tiskniTan(int* N, int* M, double* tt) { // prints --tan output
		double sumTaylor = 0;
		for(int i = 1; i <= *M; i++) {
			sumTaylor += taylor_tan(*tt,i);
			if(i >= *N && i <= *M)
				printf("%d %e %e %e %e %e\n", i, tan(*tt), sumTaylor, fabs(tan(*tt) - sumTaylor), cfrac_tan(*tt,i), fabs(tan(*tt)-cfrac_tan(*tt,i)));
		}
	}

int main(int argc, char **argv) {

	if(!validArguments(argc, argv)) {
		printf("Incorrect argument input (type --help)");
		return 1;
	}
  double c = 1.5;

  if(argc > 1) {

    if(!strcmp("--help",argv[1]) && argc == 2) {
      char napoveda[] = "--tan A N M, where A is RAD angle (0;1.4>, N is start cycle and M is end cycle (0 < N <= M < 14)\n[-c X] -m A [B], where X is height of measurement starting point, A is RAD angle (0;1.4> and B is RAD angle (0;1.4>";
      printf("%s", napoveda);
      return 0;
    }
    else if(!strcmp("--tan",argv[1]) && argc == 5) {
      double tt = atof(argv[2]);
				if(!checkAngle(tt)) {
					fprintf(stderr,"%s", "Incorrect angle value (type --help)");
					return 1;
				}
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
    else if((argc == 5 || argc == 6) && !strcmp("-c",argv[1]) && !strcmp("-m",argv[3])) {
      c = atof(argv[2]);
      if(c > 0 && c <= 100) {
        if(argc == 5) {
          double alfa = atof(argv[4]);
						if(!checkAngle(alfa)) {
						fprintf(stderr,"%s", "Incorrect angle value (type --help)");
						return 1;
						}
          printf("%.10e\n", vypocetDelka(alfa,c));
          return 0;
        }
        if(argc == 6) {
          double alfa = atof(argv[4]);
          double beta = atof(argv[5]);
						if(!checkAngle(alfa) && !checkAngle(beta)) {
						fprintf(stderr,"%s", "Incorrect angle value (type --help)");
						return 1;
						}
          printf("%.10e\n%.10e\n", vypocetDelka(alfa,c), vypocetVyska(alfa,beta,c));
          return 0;
        }
      }
      else {
				fprintf(stderr, "%s", "Incorrect X value (type --help)");
				return 1;
      }
    }
    else if(!strcmp("-m",argv[1]) && (argc == 3 || argc == 4)) {
      if(argc == 3) {
        double alfa = atof(argv[2]);
						if(!checkAngle(alfa)) {
						fprintf(stderr,"%s", "Incorrect angle value (type --help)");
						return 1;
						}
        printf("%.10e\n", vypocetDelka(alfa,c));
        return 0;
      }
      if(argc == 4) {
        double alfa = atof(argv[2]);
        double beta = atof(argv[3]);
					if(!checkAngle(alfa) && !checkAngle(beta)) {
					fprintf(stderr,"%s", "Incorrect angle value (type --help)");
					return 1;
					}
        printf("%.10e\n%.10e\n", vypocetDelka(alfa,c), vypocetVyska(alfa,beta,c));
        return 0;
      }
    }
    else {
    fprintf(stderr, "%s", "Incorrect argument input (type --help)\n");
    return 1;
    }
  }
  else {
    fprintf(stderr, "%s", "No argument input (type --help)\n");
    return 1;
  }
return 0;
}
