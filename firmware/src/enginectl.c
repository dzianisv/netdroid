/**
 * @author Denis Vashchuk
 * @brief Implementation of PWM engines control
 * @copyright BSUIR 2013
 *
 * Due to schematic:
 * 	PB8, PB9 - left front engine ctl | TIM4_CH3. TIM4_CH4
 * 	PB0, PB1 - right front engine ctl | TIM3_CH3, TIM3_CH4
 * 	PB6, PB7 -  left back engine ctl 
 * 	PA6, PA7 - right back engine ctl
 */


#include "enginectl.h"
#include <stm32f10x_tim.h>

#define PWM_PERIOD 100

/**
 * Init engine control GPIOs
 */
void engine_init()
{
	/* Enable gpio pins for engine */
	GPIO_InitTypeDef gpio_a;
	gpio_a.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_a.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_a.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio_a);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpio_b;
	gpio_b.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_b.GPIO_Pin = GPIO_Pin_0;
	gpio_b.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio_b);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* timers */
	TIM_TimeBaseInitTypeDef timer_config;
	timer_config.TIM_CounterMode=TIM_CounterMode_Up;
	timer_config.TIM_ClockDivision=0;
	timer_config.TIM_Prescaler = 0;
	timer_config.TIM_Period = PWM_PERIOD-1;
	TIM_TimeBaseInit(TIM3, &timer_config);


	TIM_OCInitTypeDef timer_oconfig;
	timer_oconfig.TIM_OCMode = TIM_OCMode_PWM1;
	timer_oconfig.TIM_OutputState = TIM_OutputState_Enable;
	timer_oconfig.TIM_Pulse = 0;
	timer_oconfig.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &timer_oconfig);
	TIM_OC2Init(TIM3, &timer_oconfig);
	TIM_OC3Init(TIM3, &timer_oconfig);
	TIM_OC4Init(TIM3, &timer_oconfig);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
}

/**
 * All function engine_go_* and engine_turn_* are blocking
 */

/**
 * Go forward
 * @param time time in ms
 * @param speed max value PWM_PERIOD
 */
void engine_go_forward(int time, int speed)
{
	TIM3->CCR1 = speed;
	TIM3->CCR2 = speed;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = speed;
}

void engine_go_back(int time, int speed)
{
	TIM3->CCR1 = speed;
	TIM3->CCR2 = speed;
	TIM3->CCR3 = speed;
	TIM3->CCR4 = speed;
}

void engine_turn_right_forward(int angle)
{
}

void engine_turn_left_forward(int angle)
{

}

void engine_turn_right_back(int angle)
{
}

void engine_turn_left_back(int angle)
{
}
