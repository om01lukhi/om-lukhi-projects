.PHONY : all app clean

all: lib-iec app

lib-iec:
	$(MAKE) -C libiec958-custom
app:
	$(MAKE) -C app
clean:
	$(MAKE) -C app clean
	$(MAKE) -C libiec958-custom clean
clean-app:
	$(MAKE) -C app clean
clean-lib-iec:
	$(MAKE) -C libiec958-custom clean
