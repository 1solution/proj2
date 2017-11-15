/* proj2 proj2.c xplsek03, M.Plsek */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define EPS 0.00000000005

	int checkAngle(double x) { // checks angle value from (0; 1.4>
		if(x > 0 && x <= 1.4)
			return 1;
		return 0;
	}
	double taylor_tan(double x, unsigned int n) { // processing taylor_tan by sum of all steps
		unsigned long long citatel[] = {1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
		unsigned long long jmenov[] = {1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};
		double vysledek = 0;
		double xx = x * x;
			for(unsigned int i = 1; i < n+1; i++) { // to n je kolik se jich ma secist
				if(i != 1)
					x = x * xx;
				vysledek += (((double)citatel[i-1]) * x) / ((double)jmenov[i-1]);
			}
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
		int tiskniTan(int* N, int* M, double* tt) { // prints --tan output
		for(int i = *N; i <= *M; i++) {
			if(i >= *N && i <= *M)
				printf("%d %e %e %e %e %e\n", i, tan(*tt), taylor_tan(*tt,i), fabs(tan(*tt) - taylor_tan(*tt,i)), cfrac_tan(*tt,i), fabs(tan(*tt)-cfrac_tan(*tt,i)));
			else return 0;
		}
		return 1;
	}

int main(int argc, char **argv) {
  double c = 1.5;

  if(argc > 1) {
    if(!strcmp("--help",argv[1]) && argc == 2) {
      char napoveda[] = "--tan A N M, where A is RAD angle, N is start cycle and M is end cycle (0 < N <= M < 14)\n[-c X] -m A [B], where X is height of measurement starting point, A is RAD angle (0;1.4> and B is RAD angle (0;1.4>";
      printf("%s", napoveda);
      return 0;
    }
    else if(!strcmp("--tan",argv[1]) && argc == 5) {
      char *end;
      double tt = strtod(argv[2], &end);
				if(/* !checkAngle(tt) || */*end != '\0') {
					fprintf(stderr,"%s", "Incorrect angle value (type --help)");
					return 1;
				}
      int N = strtol(argv[3], &end, 10);
      char *end4;
      int M = strtol(argv[4], &end4, 10);
        if(0 < N && N <= M && M < 14 && M != 0 && *end == '\0' && *end4 == '\0' && !isinf(tt) && !isnan(tt))
          	tiskniTan(&N, &M, &tt);
        else {
					fprintf(stderr, "%s", "Incorrect N / M values (type --help)");
					return 1;
        }
      return 0;
    }
    else if((argc == 5 || argc == 6) && !strcmp("-c",argv[1]) && !strcmp("-m",argv[3])) {
      char *end;
      c = strtod(argv[2], &end);
      if(c > 0 && c <= 100 && *end == '\0') {
        if(argc == 5) {
          double alfa = strtod(argv[4], &end);
						if(!checkAngle(alfa) || *end != '\0') {
						fprintf(stderr,"%s", "Incorrect angle value (type --help)");
						return 1;
						}
          printf("%.10e\n", vypocetDelka(alfa,c));
          return 0;
        }
        if(argc == 6) {
          double alfa = strtod(argv[4], &end);
          char *end2;
          double beta = strtod(argv[5], &end2);
						if(!checkAngle(alfa) || !checkAngle(beta) || *end != '\0' || *end2 != '\0') {
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
      	char *end;
        double alfa = strtod(argv[2], &end);
						if(!checkAngle(alfa) || *end != '\0') {
						fprintf(stderr,"%s", "Incorrect angle value (type --help)");
						return 1;
						}
        printf("%.10e\n", vypocetDelka(alfa,c));
        return 0;
      }
      if(argc == 4) {
        char *end, *end3;
        double alfa = strtod(argv[2], &end);
        double beta = strtod(argv[3], &end3);
					if(!checkAngle(alfa) || !checkAngle(beta) || *end != '\0' || *end3 != '\0') {
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
