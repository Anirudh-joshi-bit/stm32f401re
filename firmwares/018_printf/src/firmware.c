#include "commons.h"
#include <stdarg.h>
#include "USART.h"
#include "USART_config.h"
#include "stm32f401xe.h"

void __usart2_init ();
void printf(const char *msg, ...);

int main() {

  __usart2_init();
  
  char *string = "hii there";
  printf ("hax val -> %x, string -> %s, integer -> %d\n\r", 0x22ff33, string, 1111111100);
  // do something
  while (1)
    ;
}
