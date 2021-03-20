#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	// n - reprezentuje počet častí jednej jazdy, t - čas, t_n - čas na n-častí S
	double n = 0, t = 0, t_n = 0, zero = 0.000000001;
	scanf("%lf %lf", &n, &t);
	if((n < 1) || (n > 1000) || (t < 1) || (t > pow(10, 6))) return 0;
	
	double table[1000][2];
	double *s = (double*)calloc(n, sizeof(double));
	double *v = (double*)calloc(n, sizeof(double));
	for(int i = 0; i < n; i++){
		scanf("%lf %lf", &s[i], &v[i]);
		if((s[i] < 1) || (s[i] > 1000) || (v[i] > 1000) || (v[i] < -1000)){
			free(s);
			free(v);
			return 0;
		}
		table[i][0] = s[i];
		table[i][1] = v[i];
	}
	double k_max = 10000, k_min = (-table[0][1]);

	for(int i = 1; i < n; i++){
		if (k_min < (-v[i])) k_min = -v[i];
	}
	for(double k = (k_max + k_min)/2; (k_max - k_min) > zero; k = (k_max + k_min)/2){
		t_n = 0;
		// v = s*t - formula rychlosti => t = s/v => (t = S/(V+k))
		for(int i = 0; i < n; i++) t_n += s[i]/(v[i] + k);	
		if (t_n > t) k_min = k;
		else if(t_n < t) k_max = k;
	}
	free(s);
	free(v);

	printf("%.9lf\n", k_max);

	return 0;
}

