
LD_SCRIPT = stm32f103rb_mem_map.ld

CPU = -mcpu=cortex-m3

TOOLCHAIN   = arm-none-eabi
COMPILER    = $(TOOLCHAIN)-gcc
OBJECT_COPY = $(TOOLCHAIN)-objcopy
OBJECT_DUMP = $(TOOLCHAIN)-objdump
OBJECT_SIZE = $(TOOLCHAIN)-size

ASM_FLAGS += -c
ASM_FLAGS += -x 
ASM_FLAGS += assembler-with-cpp
ASM_FLAGS += -O0
ASM_FLAGS += $(CPU)
ASM_FLAGS += -mthumb
ASM_FLAGS += -Wall

C_FLAGS += -c
C_FLAGS += $(CPU)
C_FLAGS += -mthumb
C_FLAGS += -Wall
C_FLAGS += -ggdb3
C_FLAGS += -I$(INC_DIR)
C_FLAGS += --specs=nosys.specs

L_FLAGS += $(CPU)
L_FLAGS += -mthumb
L_FLAGS += -Wall
L_FLAGS += --specs=nosys.specs
L_FLAGS += -nostdlib
L_FLAGS += -lgcc
L_FLAGS += -T./$(LD_SCRIPT)

OBJ_COPY_FLAGS += -S
OBJ_COPY_FLAGS += -O 
OBJ_COPY_FLAGS += binary

SRC_DIR  = ./src/
INC_DIR  = ./include/
BIN_DIR  = ./bin/
TEST_DIR = ./test/
TEST_LIB_DIR = $(TEST_DIR)c_test_lib/

TARGET = $(BIN_DIR)main

C_OBJECT_FILES := $(patsubst $(SRC_DIR)%.c,$(BIN_DIR)%.o,$(wildcard $(SRC_DIR)*.c))

ASM_OBJECT_FILES := $(patsubst $(SRC_DIR)%.S,$(BIN_DIR)%.o,$(wildcard $(SRC_DIR)*.S))

.PHONY: all
all: $(TARGET).bin

# compile the user provided application c source files
$(BIN_DIR)%.o: $(SRC_DIR)%.c
	$(COMPILER) $(C_FLAGS) $< -o $@

# compile the user provided application assmebly source files
$(BIN_DIR)%.o: $(SRC_DIR)%.S
	$(COMPILER) $(ASM_FLAGS) $< -o $@

$(TARGET).elf: $(C_OBJECT_FILES) $(ASM_OBJECT_FILES)
	$(COMPILER) $^ $(L_FLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJECT_COPY) $(OBJ_COPY_FLAGS) $< $@
	$(OBJECT_DUMP) -D $(TARGET).elf > $(TARGET).list
	$(OBJECT_SIZE) $<

write: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

# if ./bin/ does not exist, create the directory
$(BIN_DIR):
	mkdir $@

run: 
	$(TARGET)

clean:
	rm -f $(BIN_DIR)*.o
	rm -f $(BIN_DIR)*.out
	rm -f $(BIN_DIR)*.elf
	rm -f $(BIN_DIR)*.bin
