#include <stdio.h>
#include <conio.h>
int jakas_funkcja(int n){
  printf("Wykonanie funkcji\n");  
  if  (n==1)
      return 1;
  else
     if ((n%2)==0)        // czy n jest parzyste?
        return jakas_funkcja(n-2)*n;
     else 
        return jakas_funkcja(n-1)*n;
}
int main() {
       int n;
       printf("Podaj n\n");
       scanf("%d",&n);
       printf("jakas_funkcja(%d)= %d",n, jakas_funkcja(n));
       getche();
       return 0;
}
