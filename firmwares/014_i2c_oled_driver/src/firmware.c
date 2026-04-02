#include "../include/SH1106_driver.h"
#include "../include/commons.h"
#include "../include/I2C.h"

void delay(uint32_t count) {
  while (count--)
    ;
}

int main() {

  __i2c1_init();
  delay(10000);

  oled_init();
  oled_clear_screen();

  for (uint8_t i = 0; i < 128; i++) {
    oled_clear_page(0);
    oled_print_string(i, 0, "hello world :)");

    delay(100000);
  }
  oled_off();

  while (1)
    ;
}
