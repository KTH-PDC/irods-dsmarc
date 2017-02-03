
# MAKEFILE for utility dsmarc.

# C compiler.
CC=g++

# TSM API include files directory. This is from the TSM API examples.
APIINC=include

# TSM API library.
APILIB=-lApiTSM64

# Flags, include files are in the current directory.
CFLAGS = -g -I$(APIINC) -m64 -DLINUX_CLIENT
#CFLAGS = -O -I$(APIINC) -m64 -DLINUX_CLIENT

# Libraries to link in.
LINKFLAGS = -lpthread -lcrypt -ldl $(APILIB)

# Timestamp.
STAMP=$(shell date +%Y-%m-%dT%H%M)

# Destination file.
DESTFILE=/var/lib/iRODS/server/bin/cmd/univMSSInterface.sh

# Manual pages destination directory. Needs root to access.
MANDEST=/usr/share/man/man8

# Save file.
SAVEFILE=$(DESTFILE).$(STAMP)

# Original file.
ORIGFILE=$(DESTFILE).orig

# Distribution directory.
DISTDIR=$(HOME)/tmp

# First pseudo target.
all: dsmarc

# DSMC archive utility.
dsmarc: dsmarc.c
	$(CC) $(CFLAGS) -o dsmarc dsmarc.c $(LINKFLAGS)

# Clean.
clean distclean:
	rm -f dsmarc
	rm -f core.*
	rm -f dsmerlog.pru dsmerror.log
	rm -f x.x xx.x
	rm -f x.*
	rm -rf x

# Make distribution tarball.
dist: distclean
	(cd ..; tar -z -cf $(DISTDIR)/dsmarc.tar.gz ./dsmarc)

# Save as a tar file.
save: distclean
	(cd ..; tar -z -cf $(DISTDIR)/dsmarc-save-$(STAMP).tar.gz ./dsmarc)

# Install files as root.
rootinstall:
	cp dsmarc.man $(MANDEST)/dsmarc.8

# Uninstall files as root.
rootuninstall:
	rm $(MANDEST)/dsmarc.8

# Install, overwrite MSS script but save before.
install: dsmarc
	cp -p $(DESTFILE) $(SAVEFILE)
	cp -p $(DESTFILE) $(ORIGFILE)
	cp dsmarc $(DESTFILE)

# Restore the original situation.
uninstall:
	cp -p $(ORIGFILE)  $(DESTFILE)

# Test.
test: dsmarc
	cp Makefile x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc stat /irods/irods/src/dsmarc/x.x
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	rm x.x
	dd if=/dev/zero of=x.x bs=1M count=512
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc stat /irods/irods/src/dsmarc/x.x
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc stage /irods/irods/src/dsmarc/x.x xx.x
	ls -l xx.x
	diff x.x xx.x
	rm x.x xx.x
	./dsmarc stat '/irods/irods/src/dsmarc/*'
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	-./dsmarc stat '/irods/irods/src/dsmarc/*'
	mkdir -p x/x/x
	touch x/x/x/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x/x/x/x.x \
		/irods/irods/src/dsmarc/x/x/x/x.x
	./dsmarc stat '/irods/irods/src/dsmarc/x/x/x/*'
	./dsmarc rm '/irods/irods/src/dsmarc/x/x/x/*'
	-./dsmarc stat '/irods/irods/src/dsmarc/x/x/x/*'
	rm -rf x
	./dsmarc mkdir /irods/irods/src/dsmarc/xx
	./dsmarc stat /irods/irods/src/dsmarc/xx
	./dsmarc rm /irods/irods/src/dsmarc/xx
	cp Makefile x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	sleep 1
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	sleep 2
	#sleep 60
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	sleep 5
	./dsmarc -d 5 stat /irods/irods/src/dsmarc/x.x
	./dsmarc -d 5 rm /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc mv /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/xx.x
	./dsmarc -d 5 stat /irods/irods/src/dsmarc/xx.x
	./dsmarc stage /irods/irods/src/dsmarc/xx.x xxx.x
	ls -l xxx.x
	diff x.x xxx.x
	./dsmarc rm /irods/irods/src/dsmarc/xx.x
	-./dsmarc rm /irods/irods/src/dsmarc/x.x
	rm x.x xxx.x
	dd if=/dev/zero of=x.x bs=1M count=512
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc mv /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/xx.x
	./dsmarc stat /irods/irods/src/dsmarc/xx.x
	./dsmarc stage /irods/irods/src/dsmarc/xx.x xx.x
	./dsmarc rm /irods/irods/src/dsmarc/xx.x
	diff x.x xx.x
	rm x.x xx.x
	cp Makefile x.x
	-./dsmarc rm '/irods/irods/src/dsmarc/x.*'
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.1
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.2
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.3
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.4
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc sync /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	./dsmarc -d 5 stat '/irods/irods/src/dsmarc/x.*'
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	./dsmarc stat '/irods/irods/src/dsmarc/x.*'
	./dsmarc retr '/irods/irods/src/dsmarc/x.*' ''
	ls -l x.x
	ls -l x.1 x.2 x.3 x.4
	diff x.x x.1
	diff x.x x.2
	diff x.x x.3
	diff x.x x.4
	rm x.x
	rm x.1 x.2 x.3 x.4
	-./dsmarc rm /irods/irods/src/dsmarc/x.1
	-./dsmarc rm /irods/irods/src/dsmarc/x.2
	-./dsmarc rm /irods/irods/src/dsmarc/x.3
	-./dsmarc rm /irods/irods/src/dsmarc/x.4
	-./dsmarc rm /irods/irods/src/dsmarc/x.x
	cat /etc/profile | ./dsmarc stream /irods/irods/src/dsmarc/x.x
	./dsmarc stage /irods/irods/src/dsmarc/x.x /irods/irods/src/dsmarc/x.x
	ls -l x.x
	diff /etc/profile /irods/irods/src/dsmarc/x.x
	rm x.x
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	cat /etc/profile | ./dsmarc stream /irods/irods/src/dsmarc/x.x
	cat /etc/profile | ./dsmarc stream /irods/irods/src/dsmarc/x.x
	./dsmarc ls /irods/irods/src/dsmarc/x.x
	-./dsmarc downstream /irods/irods/src/dsmarc/x.x
	./dsmarc purge 1 /irods/irods/src/dsmarc/x.x
	./dsmarc ls /irods/irods/src/dsmarc/x.x
	./dsmarc downstream /irods/irods/src/dsmarc/x.x >x.x
	diff /etc/profile x.x
	./dsmarc rm /irods/irods/src/dsmarc/x.x
	rm x.x
	echo "Test finished."

# End of file MAKEFILE.

