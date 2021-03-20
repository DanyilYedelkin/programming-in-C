#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*int main(){
	int n = 0, t = 0;
	int *numbers = (int*)calloc(n*2, sizeof(int));
	scanf("%d %d\n", &n, &t);
	if((n < 1) || (n > 1000) || (t < 1) || (t > pow(10, 6))){
		free(numbers);
		return 0;
	}
	int count = 0, count2 = 1;
	for(int i=0; i<n; i++, count+=2, count2+=2){
		int s = 0, v =0;
		scanf("%d %d", &s, &v);
		if((s < 1) || (s > 1000) || (v > 1000) || (v < -1000)){
			free(numbers);
			return 0;
		}
		numbers[count] = s;
		numbers[count2] = v;
	}
	numbers[count2+1] = '\0';
	printf("\n\n%d %d\n\n", count, count2);
	for(int i=0; i<n*2; i++){
		printf("%d ", numbers[i]);
	}
	double t_n = 0, sum = 0;
	for(int i=0, j=1; i<n*4; i+=2, j+=2){
		t_n = (double)numbers[i] / (double)numbers[j];
		sum += t_n;
	}
	printf("\n%f\n", sum);

    free(numbers);
	return 0;
}*/

int main(){
	// n - reprezentuje počet častí jednej jazdy, t - čas, k = konštanta 
	double n = 0, t = 0, k = 0, zero = 0.000000001;
	scanf("%lf %lf", &n, &t);
	if((n < 1) || (n > 1000) || (t < 1) || (t > pow(10, 6))){
		return 0;
	}
	// s - draha, v - rychlost
	double *s = (double*)calloc(n, sizeof(double));
	double *v = (double*)calloc(n, sizeof(double));
	for(int i=0; i<n; i++){
		scanf("%lf %lf", &s[i], &v[i]);
		if((s[i] < 1) || (s[i] > 1000) || (v[i] > 1000) || (v[i] < -1000)){
			free(s);
			free(v);
			return 0;
		} 
	}		
	for(double left = -1000, right = 2000, t_n = 0; (right - left)>zero; k = (right + left)/2){		
		t_n = 0;	
		for(int i=0; i<n; i++){
			// v = s*t - formula rychlosti => t = s/v => (t = S/(V+k))
			t_n += s[i]/(v[i] + k);
		}	
		if(t_n > t) left = k+zero;
		else if(t_n > 0 && t_n < t) right = k-zero;
		else if(t_n < t) left = k+zero;
		else right = k-zero;
	}
	//k += 0.000000003;
	free(s);
	free(v);
	printf("%.9lf\n", k);
	return 0;
}
