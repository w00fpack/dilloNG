SUBDIRS = speeddial_icons

dist_doc_DATA = user_help.html \
	speeddial.html \
	db1.png \
	db2.png

man_MANS = dillo.1
EXTRA_DIST = \
	README \
	Cookies.txt \
	dillo.1.in \
	user_help.html

dillo.1: $(srcdir)/dillo.1.in Makefile
	sed 's%/usr/local%${prefix}%g' < $(srcdir)/dillo.1.in > dillo.1
