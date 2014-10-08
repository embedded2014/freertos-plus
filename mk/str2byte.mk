exploit: $(OUTDIR)/$(TOOLDIR)/str2byte
ifeq (exploit.str, $(wildcard exploit.str))
	@echo "generated exploit.byte!"
	@$(OUTDIR)/$(TOOLDIR)/str2byte < exploit.str
else
	@echo "exploit.str not found!"
endif

$(OUTDIR)/%/str2byte: %/str2byte.c
	@mkdir -p $(dir $@)
	@echo "    CC      "$@
	@gcc -Wall -o $@ $^
