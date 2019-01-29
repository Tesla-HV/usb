FXLOAD=sudo ../libusb-1.0.22/examples/fxload

fw.ihx: fw.c
	sdcc -mmcs51 $< -o $@

load: fw.ihx
	$(FXLOAD) -i $<

clean:
	rm -f fw.ihx fw.asm fw.lk fw.lst fw.map fw.mem fw.rel fw.rst fw.sym
