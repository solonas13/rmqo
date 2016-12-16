# Specify extensions of files to delete when cleaning
CLEANEXTS   = o a 

# Specify the target file and the install directory
OUTPUTFILE  = librmqo.a
INCLUDEFILE  = rmq-offline.h
INSTALLDIR1  = ./librmqo/lib
INSTALLDIR2  = ./librmqo/include

CFLAGS= -g -D_USE_64 -msse4.2 -O3 -fomit-frame-pointer -funroll-loops 
 
LFLAGS= -std=c++11 -O3 -DNDEBUG 

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build librmqoffline.a from rmq-offline.o
$(OUTPUTFILE): rmq-offline.o
	ar cr $@ $^
	ranlib $@

# No rule to build rmq-offline.o from .cc 
# files is required; this is handled by make's database of
# implicit rules

.cc.o: 
	$(CC) $(CFLAGS)-c $(LFLAGS) $< 

.PHONY: install
install:
	mkdir -p $(INSTALLDIR1)
	cp -p $(OUTPUTFILE) $(INSTALLDIR1)
	mkdir -p $(INSTALLDIR2)
	cp -p $(INCLUDEFILE) $(INSTALLDIR2)

.PHONY: clean 
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done
	rm -r librmqo

# Indicate dependencies of .cc files on .hpp files
rmq-offline.o: rmq-offline.h
