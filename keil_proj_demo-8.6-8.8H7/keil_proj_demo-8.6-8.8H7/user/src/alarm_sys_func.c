#include "stdint.h"
#include "buzzer.h"
#include "led.h"

#define LED_COUNT   4U    /* 板载 LED 数量，U 表示 unsigned 无符号数 */
#define BLINK_TIMES 1U    /* 每颗 LED 闪烁次数 */ /* 将闪烁次数改为5 */
#define DELAY_MS    500U  /* LED 亮/灭持续时间，单位毫秒 */
#define BEEP_MS     300U  /* 蜂鸣器响一声的时长 */

uint8_t  current_led ;       /* 当前要操作的 LED 编号 */
uint16_t blink_times = BLINK_TIMES;/* 每颗 LED 闪烁次数 */
uint32_t delay_ms    = DELAY_MS;   /* 亮/灭延时 */
const uint8_t led_count = LED_COUNT; /* const 表示该变量不允许修改 */

uint8_t mode = 1U; /* 0:待机 1:运行流水灯 2:报警：流水灯+蜂鸣器 */


void blink_led(uint8_t led_num, uint16_t times, uint32_t delay_ms)
{
  uint16_t i = 0U; /* 循环计数变量 */

  /* if 判断：LED 编号只允许 1~4 */
  if (led_num > LED_COUNT)
  {
    return; /* return 直接结束当前函数 */
  }

  /* for 循环：初始化; 判断条件; 每次循环后执行 */
  for (i = 0U; i < times; i++)
  {
    led_on(led_num);          /* 点亮指定 LED */
    HAL_Delay(delay_ms);      /* 延时一段时间 */
    led_off(led_num);         /* 熄灭指定 LED */
    HAL_Delay(delay_ms);
  }
}

void beep(uint32_t beep_ms)
{
  buzzer_on();          /* 打开蜂鸣器 */
  HAL_Delay(beep_ms);   /* 保持响一段时间 */
  buzzer_off();         /* 关闭蜂鸣器 */
}





void alarm_sys_func(void)
{ 
  switch (mode)
  {
  case 0U:
    break;
  case 1U:
    current_led = 1U;    

    /* while 循环：条件成立就反复执行 {} 里的代码 */
    while (current_led <= led_count)
    {
      blink_led(current_led, blink_times, delay_ms);
      current_led++; /* 等价于 current_led = current_led + 1 */
    }
    break;
  case 2U:
    current_led = 1U;  
/* while 循环：条件成立就反复执行 {} 里的代码 */
    while (current_led <= led_count)
    {
      blink_led(current_led, blink_times, delay_ms);
      current_led++; /* 等价于 current_led = current_led + 1 */

    }
      beep(BEEP_MS);
    /* if / else 判断：让延时每次变快一点，到 100 后重新回到初始值 */
    if (delay_ms > 100U)
    {
      delay_ms -= 20U; /* 练习点：改成 += 20U 看速度变化方向 */
    }
    else
    {
      delay_ms = DELAY_MS;
    }
    break;
    default:
    break;
  }
}
  