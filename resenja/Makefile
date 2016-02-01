SUBDIRS = 3_AlgoritmiPretrageISortiranja 4_DinamickeStrukture

all: $(SUBDIRS)

3_AlgoritmiPretrageISortiranja:
	$(MAKE) -C $@
4_DinamickeStrukture:
	$(MAKE) -C $@

.PHONY: clean beauty $(SUBDIRS)

clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

beauty:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) beauty ); done

