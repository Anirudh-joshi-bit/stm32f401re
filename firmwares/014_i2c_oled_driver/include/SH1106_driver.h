#include "commons.h"
#include "font_bitmap.h"

#define MAX_STR_LEN                                         100
#define DEV_ADDR                                            0x3c
#define SH1106_ON                                           0xaf
#define SH1106_OFF                                          0xae
#define SH1106_START_COMMAND                                0x00
#define SH1106_CONTRAST                                     0x81
#define SH1106_SEGMENT_NORMAL                               0xa0
#define SH1106_SEGMENT_REVERSED                             0xa1
#define SH1106_COM_NORMAL                                   0xc0
#define SH1106_COM_REVERSE                                  0xc8
#define SH1106_SEND_DATA                                    0x40
#define SH1106_SET_PAGE_ADDR                                0xb0
#define SH1106_RESUME_RAM_DISPLAY                           0xA4


void oled_init (void);
uint32_t strlen (const char *msg);
void oled_off (void);
int8_t oled_print_string(uint8_t x, uint8_t y, const char *string) ;
void oled_clear_screen (void);
void oled_clear_page (uint8_t page_num);
