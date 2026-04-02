#include "../include/SH1106_driver.h"
#include "../include/commons.h"

void oled_init(void) {

  uint8_t commands[] = {

      SH1106_START_COMMAND,     SH1106_CONTRAST,   0x00,
      SH1106_SEGMENT_NORMAL,    SH1106_COM_NORMAL, SH1106_ON,
      SH1106_RESUME_RAM_DISPLAY};

  __i2c1_print(commands, 6, DEV_ADDR);
}

void oled_off (void){
    uint8_t command [] = {
        SH1106_START_COMMAND,
        SH1106_OFF
    };
    __i2c1_print(command, 2, DEV_ADDR);
}

void oled_clear_page (uint8_t page_num){
    if (page_num > 7) return;

    uint8_t command [] = {
        SH1106_START_COMMAND,
        SH1106_SET_PAGE_ADDR + page_num,
        0x02,                               // RAM offset 
        0x10
    };

    __i2c1_print(command, 4, DEV_ADDR);
    uint8_t data [129];
    data[0] = SH1106_SEND_DATA;
    for (uint32_t i=1; i<129; i++){
        data[i] = 0x00;
    }

    __i2c1_print(data, 129, DEV_ADDR);
}
void oled_clear_screen (void){
    for (uint8_t i=0; i<8; i++){
        oled_clear_page (i);
    }
}

int8_t oled_print_string(uint8_t x, uint8_t y, const char *string) {
  x += 2; // RAM = 132 cols but screen = 128 cols

  uint8_t page = y / 8;
  uint8_t lower_nibble = x & ~(0xf << 4);
  uint8_t upper_nibble = 0x10 | (x >> 4);

  uint32_t size = strlen(string);

  // command ->
  uint8_t commands[] = {

      SH1106_START_COMMAND, SH1106_SET_PAGE_ADDR + page, lower_nibble,
      upper_nibble
  };

  __i2c1_print(commands, 4, DEV_ADDR);

  uint8_t data[CHARS_COLS_LENGTH * MAX_STR_LEN + 1];
  uint32_t data_ind = 1;
  data[0] = SH1106_SEND_DATA;
  for (uint32_t i = 0; i < size; i++) {
    for (uint32_t j = 0; j < CHARS_COLS_LENGTH; j++) {
      data[data_ind++] = FONTS[string[i] - ' '][j];
    }
  }
  __i2c1_print(data, 1 + size * CHARS_COLS_LENGTH, DEV_ADDR);
}
