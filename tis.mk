
TEST_SRC = $(wildcard tests/test_*.c)
PROD_SRC = $(wildcard lib/source/*.c)
TEST_LOG = $(TEST_SRC:.c=.c.tis.log)

TARGET = tis.log
include colors.mk
include inc.mk

.PHONY: tis_preamble tis clean

clean:
	rm -f $(TARGET) $(TEST_LOG)

%.c.tis.log: %.c
	@echo "" | tee $<.tis.log
	@echo "Date:" `date`  | tee -a $<.tis.log
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode"
	@echo "$(FONT_RED)tis-analyzer -tis-config-load tis-config.json -val -I./lib/include -Itests/include tests/test_aes.c lib/source/aes_decrypt.c lib/source/aes_encrypt.c$(FONT_RESET)" | tee -a $<.tis.log
	@tis-analyzer -tis-config-load tis-config.json -slevel 100 -val -I./lib/include -I./tests/include $< $(PROD_SRC) | tee -a $<.tis.log

tis_preamble:
	@clear
	@echo "Sources = $(PROD_SRC)"
	@echo "Tests = $(TEST_SRC)"
	@echo "" | tee -a $(TARGET)
	@echo "Date:" `date`  | tee -a $(TARGET)
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode on all tests"

tis: tis_preamble $(TEST_LOG)
	cat $(TEST_LOG) >$(TARGET)
	@grep ":\[kernel\] warning" $(TARGET) | grep -v "no side-effect" | tee issues.log
	@echo "========================================="
	@echo "     " `wc -l < issues.log` ERRORS
	@echo "========================================="
	@$(shell '[ -s "issues.log" ]')
	@exit $(.SHELLSTATUS)
