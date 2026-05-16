#include "commons.h"
#include <stdarg.h>
#include "USART.h"
#include "USART_config.h"
#include "stm32f401xe.h"

void printf(const char *msg, ...);

int main() {

  __usart1_init();
  
  char *string = "hii there";
  printf ("this is the string -> %s\n\r", string);
  printf ("this is the hax val -> %x\n\r", 0x22ff33);
  printf ("this is the integer -> %d\n\r", 100220);
  // do something
  while (1)
    ;
}
