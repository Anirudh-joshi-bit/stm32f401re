#include "commons.h"
#include "USART.h"
#include "USART_config.h"


volatile uint8_t ip_data [10];
volatile uint32_t ip_data_ind = 0;
volatile uint32_t ip_data_size = 10;

volatile uint8_t op_data [] = {
  'h', 'e', 'l', 'l', 'o', 't', 'h', 'e', '\n', '\r'
};
volatile uint32_t op_data_ind = 0;
volatile uint32_t op_data_size = 10;


int main() {

  __usart1_init();

  // do something
  while (1)
    ;
}
