# don't override a BINARY imported from a personal.mk
@mk_if@eq ($(BINARY),)
@mk_empty@BINARY = cvc4
end@mk_if@

LOG_COMPILER = @srcdir@/../../run_regression
AM_LOG_FLAGS = $(RUN_REGRESSION_ARGS) @abs_top_builddir@/src/main/$(BINARY)$(EXEEXT)

if AUTOMAKE_1_11
# old-style (pre-automake 1.12) test harness
TESTS_ENVIRONMENT = \
	$(LOG_COMPILER) \
	$(AM_LOG_FLAGS) $(LOG_FLAGS)
endif

# These are run for all build profiles.
# If a test shouldn't be run in e.g. competition mode,
# put it below in "TESTS +="
TESTS =	\
	hd-sdiv.sy \
	stopwatch-bt.sy \
	array_sum_dd.sy \
	mpg_guard1-dd.sy \
	VC22_a.sy \
	inv_gen_n_c11.sy \
	unbdd_inv_gen_ex7.sy \
	icfp_easy_mt_ite.sy \
	three.sy \
	nia-max-square.sy \
	MPwL_d1s3.sy \
	process-arg-invariance.sy

EXTRA_DIST = $(TESTS)

# synonyms for "check" in this directory
.PHONY: regress regress1 test
regress regress1 test: check

# do nothing in this subdir
.PHONY: regress0 regress2 regress3 regress4
regress0 regress2 regress3 regress4:
