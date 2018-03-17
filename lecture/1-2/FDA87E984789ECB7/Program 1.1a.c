#include <stdio.h>
#include <time.h>
long int RekurencyjnyFib(long x)
{
	int wynik=0;
	if (x < 2 && x>=0)
	    wynik=x;
	else 
	    wynik=RekurencyjnyFib(x-1) + RekurencyjnyFib(x-2);
	return wynik;
}

main()
{
struct tm *czas_pocz, *czas_koncowy;
time_t t1, t2;
long liczba, wynik;
  printf("Program obliczajacy n-ty wyraz ciagu Fibonacciego \n");
  printf("\nPodaj liczbe n= ");
  scanf("%d", &liczba);
  t1=time(NULL);
  czas_pocz=localtime(&t1);
  printf("\nCzas rozpoczecia obliczen - %.2d:%.2d:%.2d\n", czas_pocz->tm_hour,
   czas_pocz->tm_min, czas_pocz->tm_sec);
  printf("\nLicze...\n");
  wynik = RekurencyjnyFib(liczba);
  printf("Fibonacci(%d) = %d \n", liczba, wynik);
  printf("\n");
  t2=time(NULL);
  czas_koncowy=localtime(&t2);
  printf("Czas zakonczenia obliczen - %.2d:%.2d:%.2d\n", czas_koncowy->tm_hour,
          czas_koncowy->tm_min, czas_koncowy->tm_sec);
  printf("\nCzas obliczen: %f sekund", difftime(t2,t1));
  getche();
}

