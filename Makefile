BINARY = main

LDSCRIPT = stm32f4-discovery.ld

#############################################################################

LIBNAME		= opencm3_stm32f4
DEFS		= -DSTM32F4

FP_FLAGS	?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS	= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

################################################################################
# OpenOCD specific variables

OOCD		?= openocd
OOCD_INTERFACE	?= stlink-v2
OOCD_BOARD	?= stm32f4discovery

#############################################################################
# Be silent per default, but 'make V=1' will show all compiler calls.
ifneq ($(V),1)
Q		:= @
NULL		:= 2>/dev/null
endif

###############################################################################
# Executables

PREFIX		?= arm-none-eabi

CC		:= $(PREFIX)-gcc
CXX		:= $(PREFIX)-g++
LD		:= $(PREFIX)-gcc
AR		:= $(PREFIX)-ar
AS		:= $(PREFIX)-as
OBJCOPY		:= $(PREFIX)-objcopy
OBJDUMP		:= $(PREFIX)-objdump
GDB		:= $(PREFIX)-gdb
STFLASH		= $(shell which st-flash)
STYLECHECK	:= /checkpatch.pl
STYLECHECKFLAGS	:= --no-tree -f --terse --mailback
STYLECHECKFILES	:= $(shell find . -name '*.[ch]')


###############################################################################
# Source files

LDSCRIPT	?= $(BINARY).ld

OBJS		+= $(BINARY).o


ifeq ($(strip $(OPENCM3_DIR)),)
# user has not specified the library path, so we try to detect it

# where we search for the library
#LIBPATHS := /home/fnivek/arm_libs/libopencm3

#OPENCM3_DIR := $(wildcard $(LIBPATHS:=/locm3.sublime-project))
#OPENCM3_DIR := $(firstword $(dir $(OPENCM3_DIR)))

OPENCM3_DIR := /home/fnivek/arm_libs/libopencm3

ifeq ($(strip $(OPENCM3_DIR)),)
$(warning Cannot find libopencm3 library in the standard search paths.)
$(error Please specify it through OPENCM3_DIR variable!)
endif
endif

ifeq ($(V),1)
$(info Using $(OPENCM3_DIR) path to library)
endif

INCLUDE_DIR	= $(OPENCM3_DIR)/include
LIB_DIR		= $(OPENCM3_DIR)/lib
SCRIPT_DIR	= $(OPENCM3_DIR)/scripts

###############################################################################
# C flags

CFLAGS		+= -Os -g
CFLAGS		+= -Wextra -Wshadow -Wimplicit-function-declaration
CFLAGS		+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
CFLAGS		+= -fno-common -ffunction-sections -fdata-sections

###############################################################################
# C++ flags

CXXFLAGS	+= -Os -g
CXXFLAGS	+= -Wextra -Wshadow -Wredundant-decls  -Weffc++
CXXFLAGS	+= -fno-common -ffunction-sections -fdata-sections

###############################################################################
# C & C++ preprocessor common flags

CPPFLAGS	+= -MD
CPPFLAGS	+= -Wall -Wundef
CPPFLAGS	+= -I$(INCLUDE_DIR) $(DEFS)

###############################################################################
# Linker flags

LDFLAGS		+= --static -nostartfiles
LDFLAGS		+= -L$(LIB_DIR)
LDFLAGS		+= -T$(LDSCRIPT)
LDFLAGS		+= -Wl,-Map=$(*).map
LDFLAGS		+= -Wl,--gc-sections
ifeq ($(V),99)
LDFLAGS		+= -Wl,--print-gc-sections
endif

###############################################################################
# Used libraries

LDLIBS		+= -l$(LIBNAME)
LDLIBS		+= -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group
#LDLIBS		+= -lstdc++

###############################################################################
###############################################################################
###############################################################################

.SUFFIXES: .elf .bin .hex .srec .list .map .images
.SECONDEXPANSION:
.SECONDARY:

all: elf bin

elf: $(BINARY).elf
bin: $(BINARY).bin
hex: $(BINARY).hex
srec: $(BINARY).srec
list: $(BINARY).list

images: $(BINARY).images
flash: $(BINARY).flash

%.images: %.bin %.hex %.srec %.list %.map
	@#printf "*** $* images generated ***\n"

%.bin: %.elf
	@#printf "  OBJCOPY $(*).bin\n"
	$(Q)$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.hex: %.elf
	@#printf "  OBJCOPY $(*).hex\n"
	$(Q)$(OBJCOPY) -Oihex $(*).elf $(*).hex

%.srec: %.elf
	@#printf "  OBJCOPY $(*).srec\n"
	$(Q)$(OBJCOPY) -Osrec $(*).elf $(*).srec

%.list: %.elf
	@#printf "  OBJDUMP $(*).list\n"
	$(Q)$(OBJDUMP) -S $(*).elf > $(*).list

%.elf %.map: $(OBJS) $(LDSCRIPT) $(LIB_DIR)/lib$(LIBNAME).a
	@#printf "  LD      $(*).elf\n"
	$(Q)$(LD) $(LDFLAGS) $(ARCH_FLAGS) $(OBJS) $(LDLIBS) -o $(*).elf

%.o: %.c
	@#printf "  CC      $(*).c\n"
	$(Q)$(CC) $(CFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).c

%.o: %.cxx
	@#printf "  CXX     $(*).cxx\n"
	$(Q)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).cxx

%.o: %.cpp
	@#printf "  CXX     $(*).cpp\n"
	$(Q)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).cpp

clean:
	@#printf "  CLEAN\n"
	$(Q)$(RM) *.o *.d *.elf *.bin *.hex *.srec *.list *.map

stylecheck: $(STYLECHECKFILES:=.stylecheck)
styleclean: $(STYLECHECKFILES:=.styleclean)

# the cat is due to multithreaded nature - we like to have consistent chunks of text on the output
%.stylecheck: %
	$(Q)$(SCRIPT_DIR)$(STYLECHECK) $(STYLECHECKFLAGS) $* > $*.stylecheck; \
		if [ -s $*.stylecheck ]; then \
			cat $*.stylecheck; \
		else \
			rm -f $*.stylecheck; \
		fi;

%.styleclean:
	$(Q)rm -f $*.stylecheck;


%.stlink-flash: %.bin
	@printf "  FLASH  $<\n"
	$(Q)$(STFLASH) write $(*).bin 0x8000000

ifeq ($(STLINK_PORT),)
ifeq ($(BMP_PORT),)
ifeq ($(OOCD_SERIAL),)
%.flash: %.hex
	@printf "  FLASH   $<\n"
	@# IMPORTANT: Don't use "resume", only "reset" will work correctly!
	$(Q)$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		    -f board/$(OOCD_BOARD).cfg \
		    -c "init" -c "reset init" \
		    -c "flash write_image erase $(*).hex" \
		    -c "reset" \
		    -c "shutdown" $(NULL)
else
%.flash: %.hex
	@printf "  FLASH   $<\n"
	@# IMPORTANT: Don't use "resume", only "reset" will work correctly!
	$(Q)$(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
		    -f board/$(OOCD_BOARD).cfg \
		    -c "ft2232_serial $(OOCD_SERIAL)" \
		    -c "init" -c "reset init" \
		    -c "flash write_image erase $(*).hex" \
		    -c "reset" \
		    -c "shutdown" $(NULL)
endif
else
%.flash: %.elf
	@printf "  GDB   $(*).elf (flash)\n"
	$(Q)$(GDB) --batch \
		   -ex 'target extended-remote $(BMP_PORT)' \
		   -x $(SCRIPT_DIR)/black_magic_probe_flash.scr \
		   $(*).elf
endif
else
%.flash: %.elf
	@printf "  GDB   $(*).elf (flash)\n"
	$(Q)$(GDB) --batch \
		   -ex 'target extended-remote $(STLINK_PORT)' \
		   -x $(SCRIPT_DIR)/stlink_flash.scr \
		   $(*).elf
endif

.PHONY: images clean stylecheck styleclean elf bin hex srec list

-include $(OBJS:.o=.d)