
TEST_SRC = $(wildcard tests/test_*.c)
PROD_SRC = $(wildcard lib/source/*.c)
TEST_LOG = $(TEST_SRC:.c=.c.tis.log)
TIS_REPORT =

TARGET = tis.log
ISSUES_FILE = tis-issues.log

include colors.mk
include inc.mk

.PHONY: tis_preamble tis_report_preamble tis clean

clean:
	rm -f $(TARGET) $(ISSUES_FILE) $(TEST_LOG)

%.c.tis.log: %.c
	@echo "" | tee $<.tis.log
	@echo "Date:" `date`  | tee -a $<.tis.log
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode"
	@echo "$(FONT_GREEN)tis-analyzer -tis-config-load tis-config.json -slevel 100 -val -I./lib/include -Itests/include -D_TRUST_tests/test_aes.c lib/source/aes_decrypt.c lib/source/aes_encrypt.c$(FONT_RESET)" | tee -a $<.tis.log
	@tis-analyzer -tis-config-load tis-config.json -slevel 100 -val -I./lib/include -I./tests/include $<  $(TIS_REPORT)  $(PROD_SRC) | tee -a $<.tis.log

tis_preamble:
	@clear
	@echo "" | tee -a $(TARGET)
	@echo "Date:" `date`  | tee -a $(TARGET)
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in cmd line mode on all tests"

tis: tis_preamble $(TEST_LOG)
	# Consolidate all logs in one, then extract and count warnings
	cat $(TEST_LOG) >$(TARGET)
	@grep ":\[kernel\] warning" $(TARGET) | grep -v "no side-effect" | tee $(ISSUES_FILE)
	@echo "========================================="
	@echo "     " `wc -l < $(ISSUES_FILE)` UNDEFINED BEHAVIOR ISSUES
	@echo "========================================="

	# Test if issues file contains warning, and exit with failure code if so
	@! grep -q warning $(ISSUES_FILE)

tis_report_preamble:
	TIS_REPORT = "-tis-report"

tis_report: tis_preamble $(TEST_LOG)


