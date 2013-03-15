BIN = arch dmesg mesg mount umount renice setsid unshare
SBIN = swapon swapoff
ABIN = $(BIN) $(SBIN)

MAN = unshare.1 mount.8 umount.8 swapon.8 swapoff.8

CC ?= cc

CFLAGS += -std=c99

all: $(ABIN)

clean:
	rm -f $(ABIN:S/$/.o/) $(ABIN)

.for x in $(ABIN)
$(x): $(x).o
	$(CC) $(LDFLAGS) -o $(x) $(x).o

$(x).o:	$(x).c
	$(CC) $(CFLAGS) -c -o $(x).o $(x).c
.endfor

install: all
	mkdir -p $(DESTDIR)/bin
	cp $(ABIN) $(DESTDIR)/bin/
	chmod a+rx $(DESTDIR)/bin/*
	mkdir -p $(DESTDIR)/doc/man/man{1,8}
	for man in $(MAN); do cp $$man $(DESTDIR)/doc/man/man$$(echo $$man | sed -En 's/^.*([0-9])$$/\1/p'); done
