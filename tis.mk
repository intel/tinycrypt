
TEST_SRC = $(wildcard tests/test_*.c)
PROD_SRC = $(wildcard lib/source/*.c)
TEST_LOG = $(TEST_SRC:.c=.c.tis.log)
TIS_REPORT =
LOGS = logs
RESULTS = _results
TARGET = $(LOGS)/tis.log
ISSUES_FILE = $(LOGS)/tis-issues.log

include colors.mk
include inc.mk

.PHONY: tis_preamble tis_report_preamble tis clean

clean:
	rm -rf $(TARGET) $(ISSUES_FILE) $(TEST_LOG) $(LOGS) $(RESULTS) tis_report.html

%.c.tis.log: %.c
	$(eval SHORT := $(shell echo $< | sed 's/.*\/test_//'))
	@echo "" | tee $(LOGS)/$(SHORT).tis.log
	@echo "Date:" `date`  | tee -a $(LOGS)/$(SHORT).tis.log
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode"
	@echo "$(FONT_GREEN)tis-analyzer -tis-config-load tis-config.json -slevel 100 -val -I./lib/include -I./tests/include $< $(PROD_SRC) -tis-report -info-json-results _results/$(SHORT).results.json -info-csv-all _results/$(SHORT).res$(FONT_RESET)" | tee -a $(LOGS)/$(SHORT).tis.log
	@tis-analyzer -slevel 100 -val -I./lib/include -I./tests/include $< $(PROD_SRC) -tis-report -tis-config-select-by-name $< | tee -a $(LOGS)/$(SHORT).tis.log
	@cat $(LOGS)/$(SHORT).tis.log >> $(TARGET)

tis_preamble:
	@clear
	@mkdir -p $(LOGS) $(RESULTS)
	@echo "" | tee -a $(TARGET)
	@echo "Date:" `date`  | tee -a $(TARGET)
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in cmd line mode on all tests"

tis: tis_preamble $(TEST_LOG)
	# Extract and count warnings
	@grep -E ":\[(kernel|value|sa)\] warning|              " $(TARGET) | grep -v -E "no side-effect|Calling undeclared function| Ignoring." | tee $(ISSUES_FILE)
	@echo "========================================="
	@echo "     " `grep ":\[kernel\] warning" $(ISSUES_FILE) | sort | uniq -c | wc -l` UNDEFINED BEHAVIOR ISSUES
	@echo "========================================="

	# Test if issues file contains warning, and exit with failure code if so
	@! grep -q warning $(ISSUES_FILE)

tis_report_preamble:
	TIS_REPORT = "-tis-report"

report: tis_preamble $(TEST_LOG)
	@echo "$(FONT_CYAN)Generating HTML analysis report$(FONT_RESET)"
	@echo "$(FONT_GREEN)tis_report _results/$(FONT_RESET)"
	@tis-report _results/


