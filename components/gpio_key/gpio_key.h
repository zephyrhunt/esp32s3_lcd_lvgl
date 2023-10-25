
#ifndef GPIO_KEYC_H
#define GPIO_KEYC_H

#include "stdint.h"
#define KEY_TICKS_INTERVAL    5	//ms
#define KEY_DEBOUNCE_TICKS    1	//MAX 8, 双击间隔时间

#define KEY_SHORT_TICKS       (30 /KEY_TICKS_INTERVAL)
#define KEY_LONG_TICKS        (300 /KEY_TICKS_INTERVAL)

typedef enum {
    PRESS_DOWN = 0, //按键每次按下触发
    PRESS_UP,       //按键每次松开触发
    PRESS_REPEAT,   //重复按下触发，repeat记录连击次数
    SINGLE_CLICK,   //单击按键事件
    DOUBLE_CLICK,   //双击按键事件
    LONG_PRESS_START, //长按触发
    LONG_PRESS_HOLD,  //长按期间一直触发
    number_of_event, //能够记录上面添加了几类事件
    NONE_PRESS
}KEY_Event;

typedef void (*KeyCallback)(KEY_Event event);

typedef struct KEY{
    uint16_t ticks;
    uint16_t repeats;
    uint8_t event;
    uint8_t state;
    uint8_t tri_level; //触发电平
    uint8_t key_id;

    uint16_t debounce_ticks;
    uint8_t last_level;
    // 注：建议使用全局指针
    uint8_t (*get_key_level)(uint8_t key_id_); //声明一个函数指针类型
    KeyCallback cb;
    struct KEY *next;
}KEY_Dev;

typedef uint8_t (*GetPinLevl)(uint8_t);
uint8_t KEYC_GetKeyLevel(uint8_t id);
void KEYC_Attach(KEY_Dev* key_handle, KeyCallback cb);
void KEYC_Rigister(KEY_Dev* key_handle, GetPinLevl pinLevl, uint8_t press_level, uint8_t key_id);
uint8_t KEYC_Start(KEY_Dev *handle);
void KEYC_TickInc();
void KEYC_Init();
#endif //MAIN_KEYC_H
