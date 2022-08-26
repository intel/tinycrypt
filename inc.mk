
CC = gcc
CFLAGS=-I. -I./integer-underflow -I./buffer-overflow -fprofile-arcs -ftest-coverage
DEPS = $(wildcard */*.h) makefile

SRC = $(wildcard *.c)
ALL_SRC = $(filter-out $(wildcard */main.c), $(wildcard */*.c) $(wildcard *.c))

OBJ = $(SRC:.c=.o)
ALL_OBJ = $(ALL_SRC:.c=.o)

TESTED_SRC = $(filter-out $(wildcard */test_*.c) $(wildcard test_*.c) main.c,$(ALL_SRC))
ALL_TESTED_SRC = $(filter-out $(wildcard */test_*.c) $(wildcard */main.c) main.c,$(ALL_SRC))
GCOV_FILES = $(TESTED_SRC:.c=.c.gcov)
ALL_GCOV_FILES = $(ALL_TESTED_SRC:.c=.c.gcov)

NON_MAIN_OBJ = $(filter-out $(wildcard */main.o) main.o,$(OBJ))

SUBDIRS :=  $(shell find . -maxdepth 1 -mindepth 1 -type d -not -path './.*')

.PHONY: cov cov_msg compile_msg run clean tis tis_gui $(SUBDIRS)

#---------------------------- Standard directives -----------------------------

run: $(TARGET)
	@echo ""
	@echo "$(FONT_RED)Running executable $(FONT_BOLD)./$(TARGET)$(FONT_RESET) to produce binary coverage$(FONT_RESET)"
	@./$(TARGET)

cov_msg:
	@echo "TESTED file $(TESTED_SRC) GCOV files $(GCOV_FILES)"
	@echo "$(FONT_RED)Running $(FONT_BOLD)gcov$(FONT_RESET) to produce file test coverage$(FONT_RESET)"

cov: run cov_msg $(GCOV_FILES)

$(SUBDIRS):
	@echo "make clean $@"
	@cd $@; make clean; cd -

clean: $(SUBDIRS)
	rm -rf $(TARGET) *.gcov *.gcda *.gcno *.o compile_commands.json

compile_msg:
	@echo ""
	@echo "$(FONT_RED)Compiling sources to target $(FONT_BOLD)$(TARGET)$(FONT_RESET)"

$(TARGET): compile_msg $(ALL_OBJ)
	@echo "NON MAIN OBJ = $(ALL_OBJ)"
	@echo "$(FONT_CYAN)$(CC) -o $@ $(ALL_OBJ) main.o $(FONT_RESET)"
	@$(CC) -o $@ $(CFLAGS) $(ALL_OBJ)

%.o: %.c $(DEPS)
	@echo "Compiling $(FONT_BOLD)$<$(FONT_RESET)"
	@echo "$(FONT_CYAN)$(CC) -c $< $(CFLAGS) -o $@$(FONT_RESET)"
	@$(CC) -c $< $(CFLAGS) -o $@

%.c.gcov: %.c
	@echo "$(FONT_CYAN)gcov $<$(FONT_RESET)"
	@gcov $<

tis:
	@echo ""
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode"
	@echo "$(FONT_RED)tis-analyzer -tis-config-load tis-config.json $(TIS_OPTS) $(ALL_SRC)$(FONT_RESET)"
	@tis-analyzer -tis-config-load tis-config.json -val $(SRC)

tis_gui:
	@echo ""
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in interactive mode"
	@echo "$(FONT_RED)tis-analyzer -tis-config-load tis-config.json $(TIS_OPTS) $(ALL_SRC) -gui$(FONT_RESET)"
	@tis-analyzer -tis-config-load tis-config.json -val $(SRC) -gui
