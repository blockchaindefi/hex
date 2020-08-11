all:
	make -C src $(MYOPT)

debug: MYOPT=debug
debug: all

#	make -C src debug

clean: MYOPT=clean
clean: all

#	make -C src clean

