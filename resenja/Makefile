SUBDIRS = 1_UvodniZadaci 2_Pokazivaci 3_AlgoritmiPretrageISortiranja 4_DinamickeStrukture A_IspitniRokovi

all: $(SUBDIRS)

1_UvodniZadaci:
	$(MAKE) -C $@
2_Pokazivaci:
	$(MAKE) -C $@
3_AlgoritmiPretrageISortiranja:
	$(MAKE) -C $@
4_DinamickeStrukture:
	$(MAKE) -C $@
A_IspitniRokovi:
	$(MAKE) -C $@

.PHONY: clean beauty $(SUBDIRS) license no_license

clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done

beauty:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) beauty ); done

license:
	-./add_license.sh

no_license:
	-./rm_license.sh

