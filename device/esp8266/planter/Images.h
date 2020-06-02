#define img_temp_width 13
#define img_temp_height 25
const uint8_t img_temp_bits[] PROGMEM = {
    0xE0,
    0x00,
    0xF0,
    0x03,
    0x1C,
    0x03,
    0x0C,
    0x06,
    0x0C,
    0x06,
    0x0C,
    0x06,
    0x0C,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEC,
    0x06,
    0xEE,
    0x0E,
    0xE6,
    0x0D,
    0xF3,
    0x19,
    0xF3,
    0x19,
    0xFA,
    0x19,
    0xF6,
    0x0D,
    0x46,
    0x0C,
    0x1C,
    0x07,
    0xF8,
    0x03,
    0x60,
    0x00,
};

#define img_hum_width 17
#define img_hum_height 25
const uint8_t img_hum_bits[] PROGMEM = {
    0x00,
    0x01,
    0x00,
    0x80,
    0x03,
    0x00,
    0x80,
    0x03,
    0x00,
    0xC0,
    0x07,
    0x00,
    0xC0,
    0x07,
    0x00,
    0xC0,
    0x07,
    0x00,
    0xE0,
    0x0F,
    0x00,
    0xF0,
    0x1F,
    0x00,
    0xF0,
    0x1F,
    0x00,
    0xF8,
    0x3F,
    0x00,
    0xFC,
    0x7F,
    0x00,
    0xFC,
    0x7F,
    0x00,
    0xFE,
    0xFF,
    0x00,
    0xFE,
    0xFF,
    0x00,
    0xFE,
    0xFF,
    0x00,
    0xFF,
    0xFF,
    0x01,
    0xE7,
    0xFF,
    0x01,
    0xE7,
    0xFF,
    0x01,
    0xE6,
    0xFF,
    0x00,
    0x8E,
    0xFF,
    0x00,
    0x0E,
    0xFE,
    0x00,
    0x3C,
    0x7E,
    0x00,
    0xF8,
    0x3F,
    0x00,
    0xF0,
    0x1F,
    0x00,
    0x80,
    0x03,
    0x00,
};

#define img_soil_width 28
#define img_soil_height 25
const uint8_t img_soil_bits[] PROGMEM = {
    0x08,
    0x20,
    0x00,
    0x00,
    0x1C,
    0x78,
    0x00,
    0x00,
    0x3C,
    0xFC,
    0x00,
    0x00,
    0x78,
    0xFC,
    0x01,
    0x00,
    0xF0,
    0xCF,
    0x03,
    0x00,
    0xE0,
    0x87,
    0x07,
    0x00,
    0xC0,
    0x03,
    0x0F,
    0x00,
    0xC0,
    0x07,
    0x1E,
    0x00,
    0xF0,
    0x0F,
    0x3C,
    0x00,
    0x70,
    0x1E,
    0x78,
    0x00,
    0x3C,
    0x1C,
    0xF0,
    0x00,
    0x1C,
    0x18,
    0xE0,
    0x01,
    0x0E,
    0x00,
    0xE0,
    0x00,
    0x07,
    0x00,
    0xF0,
    0x00,
    0xBF,
    0xEF,
    0x3F,
    0x00,
    0xFF,
    0xFF,
    0x3F,
    0x00,
    0xFE,
    0xFF,
    0x1F,
    0x00,
    0xFE,
    0xFF,
    0x07,
    0x03,
    0xFC,
    0xFF,
    0x83,
    0x07,
    0xF8,
    0xFF,
    0x83,
    0x07,
    0xF0,
    0xFF,
    0xC0,
    0x07,
    0xE0,
    0x7F,
    0xC0,
    0x0F,
    0xC0,
    0x7F,
    0xC0,
    0x0F,
    0x80,
    0x3F,
    0x80,
    0x07,
    0x00,
    0x06,
    0x00,
    0x03,
};

#define img_wifi_on_width 18
#define img_wifi_on_height 18
const uint8_t img_wifi_on_bits[] PROGMEM = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x02,
    0x00,
    0xF0,
    0x3F,
    0x00,
    0xB8,
    0x7A,
    0x00,
    0x0E,
    0xC0,
    0x01,
    0x04,
    0x80,
    0x00,
    0xC0,
    0x0F,
    0x00,
    0xF0,
    0x3E,
    0x00,
    0x20,
    0x10,
    0x00,
    0x00,
    0x00,
    0x00,
    0x80,
    0x03,
    0x00,
    0x00,
    0x03,
    0x00,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};

#define img_wifi_off_width 18
#define img_wifi_off_height 18
const uint8_t img_wifi_off_bits[] PROGMEM = {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x0C,
    0x00,
    0x00,
    0x98,
    0x05,
    0x00,
    0xF0,
    0x3F,
    0x00,
    0x7C,
    0xFC,
    0x00,
    0xDE,
    0xE0,
    0x01,
    0x84,
    0x81,
    0x00,
    0xE0,
    0x0F,
    0x00,
    0xF0,
    0x3F,
    0x00,
    0x20,
    0x1C,
    0x00,
    0x00,
    0x18,
    0x00,
    0x80,
    0x17,
    0x00,
    0x00,
    0x63,
    0x00,
    0x00,
    0x01,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};