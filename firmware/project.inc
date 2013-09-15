TARGET:=webdroid

DEFINES += STM32F10X_MD
DEFINES += USE_SRDPERIPH_DRIVER
DEFINES += VECT_TABLE_FLASH

STARTUP	:=	startup_stm32f10x_md.s

DRIVER	+=	stm32f10x_gpio
DRIVER	+=	stm32f10x_rcc
DRIVER	+=	stm32f10x_usart

SRC_DIR := src
CMSIS_DIR := cmsis
STDPERIPH_DIR := stm32_periph

SOURCES := hello.c