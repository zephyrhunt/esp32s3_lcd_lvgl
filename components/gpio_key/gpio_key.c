#include "gpio_key.h"
#include "string.h"
#include "driver/gpio.h"
static KEY_Dev *head = NULL;

#define BUTTON_UP   2
#define BUTTON_DOWN 1

#define BUTTON_SUP   47
#define BUTTON_SMID  48
#define BUTTON_SDOWN 45

#define event_cb(ev) handle->cb((KEY_Event)ev)
void KEYC_Handle_Loop(KEY_Dev *handle);

void KEYC_HalInit()
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = ((1ULL<<BUTTON_UP) | (1ULL<<BUTTON_DOWN) | (1ULL<<BUTTON_SUP) | (1ULL<<BUTTON_SMID) | (1ULL<<BUTTON_SDOWN));
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = true;
    gpio_config(&io_conf);
}

uint8_t KEYC_GetKeyLevel(uint8_t id)
{
    switch (id) {
        case 0:
            return gpio_get_level(BUTTON_UP);
        case 1:
            return gpio_get_level(BUTTON_DOWN);
        case 2:
            return gpio_get_level(BUTTON_SUP);
        case 3:
            return gpio_get_level(BUTTON_SDOWN);
        case 4:
            return gpio_get_level(BUTTON_SMID);
        default:
            return  1;
    }

    return 0;
}

void KEYC_Init()
{
    KEYC_HalInit();
}
void KEYC_Rigister(KEY_Dev* key_handle, GetPinLevl pin_level, uint8_t press_level, uint8_t key_id)
{
    key_handle->state = 0;
    key_handle->repeats = 0;
    key_handle->next = NULL;
    key_handle->event = NONE_PRESS;
    key_handle->get_key_level = pin_level;
    key_handle->tri_level = press_level;
    key_handle->last_level = !press_level; //叹气
    key_handle->key_id = key_id;
}

void KEYC_TickInc()
{
    // head 就是第一个按键
    KEY_Dev *target;
    for (target = head; target; target=target->next) {
        KEYC_Handle_Loop(target);
    }
}
/*
 * @brief 创建回调函数
 */
void KEYC_Attach(KEY_Dev* key_handle, KeyCallback cb)
{
    key_handle->cb = cb;
}

// 放到链表当中
uint8_t KEYC_Start(KEY_Dev *handle)
{
    KEY_Dev *target = head;
    //遍历一片判断是否已经存在
    while (target){
        if (target == handle)return 0; //已经存在
        target = target->next;
    }
    handle->next = head;
    head = handle;
    return 1; //初始化成功
}

void KEYC_Stop(KEY_Dev *handle)
{

}

void KEYC_Handle_Loop(KEY_Dev *handle)
{
    uint8_t level = handle->get_key_level(handle->key_id);
    // record every time tri time after first press
    if (handle->state != 0) ++handle->ticks;
    //消斗
    if (level != handle->last_level){
        ++handle->debounce_ticks;
        if (handle->debounce_ticks >= KEY_DEBOUNCE_TICKS){
            handle->last_level = level;
            handle->debounce_ticks = 0;
        }
    }else{
        handle->debounce_ticks = 0;
    }

    switch (handle->state) {
        case 0://状态0未开始按下
            if (level == handle->tri_level){
                handle->event = PRESS_DOWN;
                event_cb(PRESS_DOWN);
                handle->ticks = 0;
                handle->state = 1;
                handle->repeats = 1;
            }else{
                handle->event = NONE_PRESS;
            }
            break;
        case 1://状态1，从状态0来，已经按下了，如果弹起说明是按下一次
            if (level != handle->tri_level){
                handle->event = PRESS_UP;
                handle->ticks = 0;
                handle->state = 2;
                handle->repeats = 1;
                event_cb(PRESS_UP);
            }else if(handle->ticks > KEY_LONG_TICKS){
                handle->event = LONG_PRESS_START;
                handle->state = 5;
                event_cb(LONG_PRESS_START);
            }
            break;
        case 2://状态2，从状态1或3来，状态1检测了一次，检测是否有连击
            if (level == handle->tri_level){
                handle->event = PRESS_DOWN;
                handle->ticks = 0;
                handle->state = 3;
                ++handle->repeats;
            }else if (handle->ticks > KEY_SHORT_TICKS){ //保持相同电平(空闲)时间
                if (handle->repeats == 1) {
                    handle->event = SINGLE_CLICK;
                    event_cb(SINGLE_CLICK);
                }else if(handle->repeats == 2){
                    handle->event = DOUBLE_CLICK;
                    event_cb(DOUBLE_CLICK);
                }//else if (handle->repeats == 2){
//                    printf("double\n");
//                    handle->event = DOUBLE_CLICK;
//                    event_cb(DOUBLE_CLICK);
//                }
                handle->state = 0;
            }
            break;
        case 3:
            if (level != handle->tri_level){
                handle->event = PRESS_UP;
                event_cb(PRESS_UP);
                if (handle->ticks < KEY_SHORT_TICKS){
                    handle->ticks = 0;
                    handle->state = 2; //再次返回2，连击次数+1
                }else{
                    handle->state = 0;
                }
            }else if (handle->ticks > KEY_SHORT_TICKS){
                handle->state = 0;
            }
            break;
        case 5:
            if (level == handle->tri_level){
                handle->event = LONG_PRESS_HOLD;
                event_cb(LONG_PRESS_HOLD);
            }else{
                event_cb(PRESS_UP);
                handle->event = PRESS_UP;
                handle->state = 0;
            }
            break;
        default:
            handle->state = 0;
            break;
    }
}

