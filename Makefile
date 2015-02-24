BINARY = main

LDSCRIPT = stm32f4-discovery.ld

OPENCM3_DIR := /home/fnivek/arm_libs/libopencm3
TOOLCHAIN_DIR := /home/fnivek/sat/arm-none-eabi/lib/thumb/cortex-m4/float-abi-hard/fpuv4-sp-d16
#TOOLCHAIN_DIR := /home/fnivek/sat/arm-none-eabi

OBJS += usb.o motor_controler.o

include Makefile.include