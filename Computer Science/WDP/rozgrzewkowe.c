#include<stdio.h>
#include<malloc.h>

int main(){
	int n;
	scanf("%d", &n);
	int *t;
	t = (int*)malloc((size_t)n*sizeof(int));
	int *koniec;
	koniec = (int*)malloc((size_t)n*sizeof(int));
	for(int i = 0; i < n; i++) scanf("%d", &t[i]);
	int res = 1;
	koniec[0] = 0;
	for(int i = 1; i < n; i++){
		int kon = i;
		while(kon > 0 && t[kon - 1] != 0 && t[i]%t[kon - 1] == 0){
			kon = koniec[kon - 1];
		}
		koniec[i] = kon;
		if(res < i - koniec[i] + 1) res = i - koniec[i] + 1;
	}
	printf("%d\n", res);
	free(t);
	free(koniec);
}
