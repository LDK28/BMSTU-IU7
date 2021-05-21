.PHONY : all debug runmem gcov clean func check unit

SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out
UTESTS_DIR := ./unit_tests

CC := gcc
ASM := nasm
CFLAGS := -std=gnu11 -masm=intel -mavx -mavx2 -O0 -w -I$(INC_DIR)

SRCS := $(wildcard $(SRC_DIR)/*.c)
INCS := $(filter-out $(INC_DIR)/main.h, $(SRCS:$(SRC_DIR)/%.c=$(INC_DIR)/%.h))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

EXEC := main.out
EXEC_NO_80387 := main_no_80387.out
EXEC_387 := main_387.out

all: $(EXEC)

$(EXEC) : CFLAGS += -DX87 -DASM -m80387
$(EXEC) : $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(U_CFLAGS)

$(EXEC_NO_80387) : CFLAGS += -DASM -mno-80387
$(EXEC_NO_80387) : $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(U_CFLAGS)

$(EXEC_387) : CFLAGS +=  -DX87 -DASM -m80387 -mfpmath=387
$(EXEC_387) : $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(U_CFLAGS)

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

${OUT_DIR}/%.o : ${SRC_DIR}/%.c $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(INC_DIR)/%.h:
	@

clean:
	@$(RM) $(EXEC) $(EXEC_387) $(EXEC_NO_80387) ${OUT_DIR}/* ./*.o
	@rm -rf $(OUT_DIR)
