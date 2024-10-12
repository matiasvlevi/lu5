BIN=bin/linux/lu5
# ---
# Run all examples
#
# `make examples`
# ---
EXAMPLES = $(wildcard *.lua)
examples: $(all) $(EXAMPLES:=.run)
%.lua.run: %.lua
	../$(BIN) --log 5 $<
	rm -f $@