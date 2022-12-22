LOGS = logs
RESULTS = _results

TEST_SRC1 = $(wildcard ../tests/test_*.c)
PROD_SRC2 = $(wildcard ../lib/source/*.c)
TEST_SRC = $(TEST_SRC1:../%=%)
PROD_SRC = $(PROD_SRC1:../%=%)
TEST_LOG = $(TEST_SRC:tests/%=$(LOGS)/%.tis.log)
TIS_REPORT =

TARGET = $(LOGS)/tis.log
ISSUES_FILE = $(LOGS)/tis-issues.log

include colors.mk
#include inc.mk

.PHONY: tis_preamble tis_report_preamble tis clean

.ONESHELL:

clean:
	@cd ..
	rm -rf $(TARGET) $(ISSUES_FILE) $(TEST_LOG) $(LOGS) $(RESULTS) ../tis_report.html ../tis_misra_report

%.c.tis.log: %.c
	# @cd ..
	@mkdir -p $(LOGS)
	$(eval SHORT := $(shell echo $< | sed 's/.*\/test_//'))
	@echo "" | tee $(LOGS)/$(SHORT).tis.log
	@echo "Date:" `date`  | tee -a $(LOGS)/$(SHORT).tis.log
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in batch mode"
	@echo "$(FONT_GREEN)tis-analyzer -tis-config-load tis.json -tis-report -info-json-results _results/$(SHORT).results.json -info-csv-all _results/$(SHORT).res$(FONT_RESET)" | tee -a $(LOGS)/$(SHORT).tis.log
	@tis-analyzer -tis-config-load tis.json -tis-report -tis-config-select-by-name $< | tee -a $(LOGS)/$(SHORT).tis.log
	@cat $(LOGS)/$(SHORT).tis.log >> $(TARGET)

tis_preamble:
	#@clear
	@cd ..
	pwd
	echo "deps = $(TEST_LOG)"
	echo "tests = $(TEST_SRC)"
	@mkdir -p $(LOGS) $(RESULTS)
	@echo "" | tee -a $(TARGET)
	@echo "Date:" `date`  | tee -a $(TARGET)
	@echo "Running $(FONT_BOLD)tis-analyzer$(FONT_RESET) in cmd line mode on all tests"

tis-all:
	./run_all.sh -n 5

tis: tis_preamble tis-all
	@cd ..
	echo "Current dir is $(pwd)"
	# Extract and count warnings
	@grep -E ":\[(kernel|value|sa)\] warning|              " $(TARGET) | grep -v -E "no side-effect|Calling undeclared function| Ignoring." | tee $(ISSUES_FILE)
	@echo "========================================="
	@echo "     " `grep ":\[kernel\] warning" $(ISSUES_FILE) | sort | uniq -c | wc -l` UNDEFINED BEHAVIOR ISSUES
	@echo "========================================="

	# Test if issues file contains warning, and exit with failure code if so
	@! grep -q warning $(ISSUES_FILE)

tis_report_preamble:
	TIS_REPORT = "-tis-report"

report: tis_preamble
	@cd ..
	echo $(TEST_LOG)
	echo $(PROD_SRC)
	@echo "$(FONT_CYAN)Generating HTML analysis report$(FONT_RESET)"
	@echo "$(FONT_GREEN)tis_report _results/ --skip-file test_.*.c$(FONT_RESET)"
	@tis-report _results/  --skip-file test_.*\.c
	#@tis-report _results/


