#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG__VOICE_ALPHA_15X15
#define LV_ATTRIBUTE_IMG__VOICE_ALPHA_15X15
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG__VOICE_ALPHA_15X15 uint8_t _voice_alpha_15x15_map[] = {
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
  /*Pixel format: Alpha 8 bit, Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x06, 0xb6, 0x14, 0xb6, 0x1a, 0xb6, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x03, 0xb6, 0x17, 0xb6, 0x58, 0xb6, 0xb4, 0xb6, 0xec, 0xb6, 0x60, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x0b, 0xb6, 0x43, 0xb6, 0x8f, 0xb6, 0xb1, 0xb6, 0x4b, 0xb6, 0x8d, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0x0d, 0xb7, 0x03, 0x00, 0x00, 0xb6, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0xb6, 0x0c, 0xb6, 0x68, 0xb6, 0xc4, 0xb6, 0x73, 0xb6, 0x05, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0x63, 0xb6, 0x16, 0x00, 0x00, 0xb6, 0xf6, 
  0xb6, 0x0e, 0xb6, 0x5e, 0xb6, 0x74, 0xb6, 0xca, 0xb6, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0xc3, 0xb6, 0x2b, 0x00, 0x00, 0xb6, 0xf6, 
  0xb6, 0x80, 0xb6, 0x9b, 0xb6, 0x8a, 0xb6, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0xc3, 0xb6, 0x2b, 0x00, 0x00, 0xb6, 0xf6, 
  0xb6, 0xf7, 0x92, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0xc3, 0xb6, 0x2b, 0x00, 0x00, 0xb6, 0xf6, 
  0xb6, 0xc6, 0xb6, 0x8c, 0xb6, 0x62, 0xb6, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0xc3, 0xb6, 0x2b, 0x00, 0x00, 0xb6, 0xf6, 
  0xb6, 0x3c, 0xb6, 0x70, 0xb6, 0x8a, 0xb6, 0x95, 0xb6, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0xc3, 0xb6, 0x2b, 0x00, 0x00, 0xb6, 0xf6, 
  0x00, 0x00, 0xb6, 0x0a, 0xb6, 0x24, 0xb6, 0x6d, 0xb6, 0xb9, 0xb6, 0x5e, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x8c, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0x68, 0xb6, 0x17, 0x00, 0x00, 0xb6, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x0f, 0xb6, 0x5a, 0xb6, 0xad, 0xb6, 0xa8, 0xb6, 0x42, 0xb6, 0x8d, 0xb6, 0x6d, 0xb6, 0x08, 0xb6, 0x0f, 0xb7, 0x03, 0x00, 0x00, 0xb6, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x07, 0xb6, 0x1f, 0xb6, 0x5a, 0xb6, 0xb6, 0xb6, 0xec, 0xb6, 0x60, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0x06, 0xb6, 0x14, 0xb6, 0x1a, 0xb6, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0xad, 0x06, 0xd3, 0x9c, 0x14, 0xb2, 0x94, 0x1a, 0xd3, 0x9c, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0xad, 0x03, 0xf3, 0x9c, 0x17, 0xd3, 0x9c, 0x58, 0xd3, 0x9c, 0xb4, 0xd3, 0x9c, 0xec, 0xd3, 0x9c, 0x60, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb3, 0x9c, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0xa5, 0x0b, 0xd3, 0x9c, 0x43, 0xd3, 0x9c, 0x8f, 0xd3, 0x9c, 0xb1, 0xd3, 0x9c, 0x4b, 0xd3, 0x9c, 0x8d, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xf4, 0xa4, 0x0d, 0x75, 0xad, 0x03, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb3, 0x9c, 0x0c, 0xd3, 0x9c, 0x68, 0xd3, 0x9c, 0xc4, 0xd3, 0x9c, 0x73, 0xd3, 0x9c, 0x05, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xb3, 0x9c, 0x63, 0xd3, 0x9c, 0x16, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0xb2, 0x94, 0x0e, 0xb3, 0x9c, 0x5e, 0xb3, 0x9c, 0x74, 0xd3, 0x9c, 0xca, 0xd3, 0x9c, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0xc3, 0xb3, 0x9c, 0x2b, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0xd3, 0x9c, 0x80, 0xd3, 0x9c, 0x9b, 0xd3, 0x9c, 0x8a, 0xd3, 0x9c, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0xc3, 0xb3, 0x9c, 0x2b, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0xd3, 0x9c, 0xf7, 0x51, 0x8c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0xc3, 0xb3, 0x9c, 0x2b, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0xd3, 0x9c, 0xc6, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x62, 0xd3, 0x9c, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0xc3, 0xb3, 0x9c, 0x2b, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0xb3, 0x9c, 0x3c, 0xd3, 0x9c, 0x70, 0xd3, 0x9c, 0x8a, 0xd3, 0x9c, 0x95, 0xb2, 0x94, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0xc3, 0xb3, 0x9c, 0x2b, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0x00, 0x00, 0x00, 0xd3, 0x9c, 0x0a, 0xb3, 0x9c, 0x24, 0xd3, 0x9c, 0x6d, 0xd3, 0x9c, 0xb9, 0xd3, 0x9c, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x8c, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0x68, 0xf3, 0x9c, 0x17, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0x0f, 0xd3, 0x9c, 0x5a, 0xd3, 0x9c, 0xad, 0xd3, 0x9c, 0xa8, 0xd3, 0x9c, 0x42, 0xd3, 0x9c, 0x8d, 0xd3, 0x9c, 0x6d, 0x14, 0xa5, 0x08, 0xd3, 0x9c, 0x0f, 0x75, 0xad, 0x03, 0x00, 0x00, 0x00, 0xd3, 0x9c, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x94, 0x07, 0xb3, 0x9c, 0x1f, 0xd3, 0x9c, 0x5a, 0xd3, 0x9c, 0xb6, 0xd3, 0x9c, 0xec, 0xd3, 0x9c, 0x60, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb3, 0x9c, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0xad, 0x06, 0xd3, 0x9c, 0x14, 0xb2, 0x94, 0x1a, 0xd3, 0x9c, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0
  /*Pixel format: Alpha 8 bit, Red: 5 bit, Green: 6 bit, Blue: 5 bit  BUT the 2  color bytes are swapped*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xad, 0x75, 0x06, 0x9c, 0xd3, 0x14, 0x94, 0xb2, 0x1a, 0x9c, 0xd3, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xad, 0x75, 0x03, 0x9c, 0xf3, 0x17, 0x9c, 0xd3, 0x58, 0x9c, 0xd3, 0xb4, 0x9c, 0xd3, 0xec, 0x9c, 0xd3, 0x60, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xb3, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa5, 0x34, 0x0b, 0x9c, 0xd3, 0x43, 0x9c, 0xd3, 0x8f, 0x9c, 0xd3, 0xb1, 0x9c, 0xd3, 0x4b, 0x9c, 0xd3, 0x8d, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0xa4, 0xf4, 0x0d, 0xad, 0x75, 0x03, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xb3, 0x0c, 0x9c, 0xd3, 0x68, 0x9c, 0xd3, 0xc4, 0x9c, 0xd3, 0x73, 0x9c, 0xd3, 0x05, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xb3, 0x63, 0x9c, 0xd3, 0x16, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x94, 0xb2, 0x0e, 0x9c, 0xb3, 0x5e, 0x9c, 0xb3, 0x74, 0x9c, 0xd3, 0xca, 0x9c, 0xd3, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0xc3, 0x9c, 0xb3, 0x2b, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x9c, 0xd3, 0x80, 0x9c, 0xd3, 0x9b, 0x9c, 0xd3, 0x8a, 0x9c, 0xd3, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0xc3, 0x9c, 0xb3, 0x2b, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x9c, 0xd3, 0xf7, 0x8c, 0x51, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0xc3, 0x9c, 0xb3, 0x2b, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x9c, 0xd3, 0xc6, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x62, 0x9c, 0xd3, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0xc3, 0x9c, 0xb3, 0x2b, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x9c, 0xb3, 0x3c, 0x9c, 0xd3, 0x70, 0x9c, 0xd3, 0x8a, 0x9c, 0xd3, 0x95, 0x94, 0xb2, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0xc3, 0x9c, 0xb3, 0x2b, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x00, 0x00, 0x00, 0x9c, 0xd3, 0x0a, 0x9c, 0xb3, 0x24, 0x9c, 0xd3, 0x6d, 0x9c, 0xd3, 0xb9, 0x9c, 0xd3, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x8c, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0x68, 0x9c, 0xf3, 0x17, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0x0f, 0x9c, 0xd3, 0x5a, 0x9c, 0xd3, 0xad, 0x9c, 0xd3, 0xa8, 0x9c, 0xd3, 0x42, 0x9c, 0xd3, 0x8d, 0x9c, 0xd3, 0x6d, 0xa5, 0x14, 0x08, 0x9c, 0xd3, 0x0f, 0xad, 0x75, 0x03, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0xb2, 0x07, 0x9c, 0xb3, 0x1f, 0x9c, 0xd3, 0x5a, 0x9c, 0xd3, 0xb6, 0x9c, 0xd3, 0xec, 0x9c, 0xd3, 0x60, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xb3, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xad, 0x75, 0x06, 0x9c, 0xd3, 0x14, 0x94, 0xb2, 0x1a, 0x9c, 0xd3, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
#if LV_COLOR_DEPTH == 32
  /*Pixel format: Alpha 8 bit, Red: 8 bit, Green: 8 bit, Blue: 8 bit*/
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0x06, 0x99, 0x99, 0x99, 0x14, 0x93, 0x93, 0x93, 0x1a, 0x99, 0x99, 0x99, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0x03, 0x9b, 0x9b, 0x9b, 0x17, 0x97, 0x97, 0x97, 0x58, 0x98, 0x98, 0x98, 0xb4, 0x97, 0x97, 0x97, 0xec, 0x97, 0x97, 0x97, 0x60, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x95, 0x95, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa2, 0xa2, 0xa2, 0x0b, 0x98, 0x98, 0x98, 0x43, 0x98, 0x98, 0x98, 0x8f, 0x97, 0x97, 0x97, 0xb1, 0x96, 0x96, 0x96, 0x4b, 0x96, 0x96, 0x96, 0x8d, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x9d, 0x9d, 0x9d, 0x0d, 0xaa, 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x95, 0x95, 0x0c, 0x98, 0x98, 0x98, 0x68, 0x96, 0x96, 0x96, 0xc4, 0x97, 0x97, 0x97, 0x73, 0x99, 0x99, 0x99, 0x05, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x95, 0x95, 0x95, 0x63, 0x97, 0x97, 0x97, 0x16, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x92, 0x92, 0x92, 0x0e, 0x95, 0x95, 0x95, 0x5e, 0x95, 0x95, 0x95, 0x74, 0x96, 0x96, 0x96, 0xca, 0x97, 0x97, 0x97, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0xc3, 0x94, 0x94, 0x94, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x97, 0x97, 0x97, 0x80, 0x97, 0x97, 0x97, 0x9b, 0x98, 0x98, 0x98, 0x8a, 0x97, 0x97, 0x97, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0xc3, 0x94, 0x94, 0x94, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x97, 0x97, 0x97, 0xf7, 0x89, 0x89, 0x89, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0xc3, 0x94, 0x94, 0x94, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x97, 0x97, 0x97, 0xc6, 0x97, 0x97, 0x97, 0x8c, 0x97, 0x97, 0x97, 0x62, 0x97, 0x97, 0x97, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0xc3, 0x94, 0x94, 0x94, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x95, 0x95, 0x95, 0x3c, 0x96, 0x96, 0x96, 0x70, 0x96, 0x96, 0x96, 0x8a, 0x97, 0x97, 0x97, 0x95, 0x93, 0x93, 0x93, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0xc3, 0x94, 0x94, 0x94, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x0a, 0x95, 0x95, 0x95, 0x24, 0x96, 0x96, 0x96, 0x6d, 0x96, 0x96, 0x96, 0xb9, 0x98, 0x98, 0x98, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0x8c, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x98, 0x98, 0x98, 0x68, 0x9b, 0x9b, 0x9b, 0x17, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x99, 0x99, 0x99, 0x0f, 0x96, 0x96, 0x96, 0x5a, 0x96, 0x96, 0x96, 0xad, 0x96, 0x96, 0x96, 0xa8, 0x97, 0x97, 0x97, 0x42, 0x96, 0x96, 0x96, 0x8d, 0x96, 0x96, 0x96, 0x6d, 0x9f, 0x9f, 0x9f, 0x08, 0x99, 0x99, 0x99, 0x0f, 0xaa, 0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x00, 0x97, 0x97, 0x97, 0xf6, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0x92, 0x92, 0x07, 0x94, 0x94, 0x94, 0x1f, 0x96, 0x96, 0x96, 0x5a, 0x96, 0x96, 0x96, 0xb6, 0x97, 0x97, 0x97, 0xec, 0x97, 0x97, 0x97, 0x60, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x95, 0x95, 0x29, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0xaa, 0x06, 0x99, 0x99, 0x99, 0x14, 0x93, 0x93, 0x93, 0x1a, 0x99, 0x99, 0x99, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
#endif
};

const lv_img_dsc_t _voice_alpha_15x15 = {
  .header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 15,
  .header.h = 15,
  .data_size = 225 * LV_IMG_PX_SIZE_ALPHA_BYTE,
  .data = _voice_alpha_15x15_map,
};