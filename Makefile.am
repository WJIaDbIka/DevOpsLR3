AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = funcA 
funcA_SOURCES = main.cpp FuncA.cpp FuncA.h
dist_man_MANS = FuncA.1
dist_pkgdata_DATA = data.txt

.PHONY:deb
deb:
	make DESTDIR=$(CURDIR)/deb install

