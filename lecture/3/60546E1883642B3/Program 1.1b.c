#include <stdio.h>
#include <conio.h>
void f(void);

int main(void) {
  int i;

  for(i=0; i<10; i++) f();
  return 0;
  }

void f(void) {
  static int Licznik = 0;
  char znak;

  Licznik++;
  printf("Licznik = %d",Licznik);
  printf("\n");
  getche();
}
