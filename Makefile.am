## Process this file with automake to produce Makefile.in

include $(top_srcdir)/aminclude.am

SUBDIRS = src 

EXTRA_DIST = \
	doxygen.cfg \
	$(NULL)

dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)
