CLEANFILES = *~

if MAKE_DOXYGEN_DOC

OUTPUT_FILE = @DOXYGEN_LOG_FILE@
CLEANFILES += $(OUTPUT_FILE)

docs_dir = $(top_srcdir)/docs
DOCHTML = $(DESTDIR)/@DATADIR@/doc/@PACKAGE_NAME@/html

$(OUTPUT_FILE):
	@$(DOXYGEN) Doxyfile > /dev/null

all-local: $(OUTPUT_FILE)
	@warning=`cat $(OUTPUT_FILE) | grep warning: | wc -l`; \
	echo "@PACKAGE_NAME@ @VERSION@ - warning of documents ($$warning)."

clean-local:
	@rm -rf $(docs_dir)/html

install-data-local:
	@$(INSTALL) -d $(DOCHTML)
	@cp -R $(docs_dir)/html/* $(DOCHTML)

endif

