# $Header: /space/home/eng/cjm/cvs/ngatutil/c/Makefile,v 1.5 2015-06-05 15:15:07 cjm Exp $

include			../../Makefile.common

PACKAGEDIR = ngat/util
PACKAGENAME = ngat.util

CNAME		= c
NGAT_UTIL_HOME  = ngatutil
BINDIR		= $(LT_BIN_HOME)/$(NGAT_UTIL_HOME)/$(CNAME)/$(HOSTTYPE)
INCDIR 		= ../include
DOCSDIR 	= $(LT_DOC_HOME)/ngat/cdocs/$(PACKAGEDIR)
CFLAGS 		= -g $(CCHECKFLAG) $(SHARED_LIB_CFLAGS) -I$(INCDIR) -I$(JNIINCDIR) -I$(JNIMDINCDIR) \
		-I$(CFITSIOINCDIR) -L$(LT_LIB_HOME)
LINTFLAGS 	= -I$(INCDIR) -I$(JNIINCDIR) -I$(JNIMDINCDIR) -I$(CFITSIOINCDIR)
DOCFLAGS 	= -static
SRCS 		= 	ngat_util_FileUtilities.c
HEADERS		=	$(SRCS:%.c=$(INCDIR)/%.h)
OBJS		=	$(SRCS:%.c=$(BINDIR)/%.o)
DOCS 		= 	$(SRCS:%.c=$(DOCSDIR)/%.html)

top: $(INCDIR)/ngat_util_FileUtilities.h shared docs

shared: $(LT_LIB_HOME)/libngatutil.so

$(LT_LIB_HOME)/libngatutil.so: $(OBJS)
	cc $(CCSHAREDFLAG) $(CFLAGS) $(OBJS) -o $@ $(TIMELIB) 

static: $(LT_LIB_HOME)/libngatutil.a

$(LT_LIB_HOME)/libngatutil.a: $(OBJS)
	ar rcv $@ $?

$(BINDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INCDIR)/ngat_util_FileUtilities.h: $(LT_JAVALIB_HOME)/ngat_util.jar
	$(JAVAH) -jni -d $(INCDIR) ngat.util.FileUtilities
	$(TOUCH) $@

docs: $(DOCS)

$(DOCS): $(SRCS)
	-$(CDOC) -d $(DOCSDIR) -h $(INCDIR) $(DOCFLAGS) $(SRCS)

checkout:
	$(CO) $(CO_OPTIONS) $(SRCS)
	#(cd $(INCDIR); $(CO) $(CO_OPTIONS) $(HEADERS);) (machine generated headers only atm)

checkin:
	-$(CI) $(CI_OPTIONS) $(SRCS)
	#-(cd $(INCDIR); $(CI) $(HEADERS);) (machine generated headers only atm)

depend:
	makedepend $(MAKEDEPENDFLAGS) -- $(CFLAGS) -- $(SRCS)

lint:
	$(LINT)	$(LINTFLAGS) $(SRCS)

clean: tidy
	-$(RM) $(RM_OPTIONS) $(OBJS) $(LT_LIB_HOME)/libngatutil.so

tidy:
	-$(RM) $(RM_OPTIONS) $(TIDY_OPTIONS)
	cd $(INCDIR); $(RM) $(RM_OPTIONS) $(TIDY_OPTIONS)

backup: tidy
	-$(RM) $(RM_OPTIONS) $(OBJS)

#
# $Log: not supported by cvs2svn $
# Revision 1.4  2008/06/27 10:51:03  cjm
# Added MAKEDEPENDFLAGS.
#
# Revision 1.3  2003/03/11 12:04:33  cjm
# Fixed Makefile include problem.
#
# Revision 1.2  2001/07/31 10:20:14  cjm
# FileUtilites renamed to FileUtilities.
#
# Revision 1.1  2001/06/20 15:56:30  cjm
# Initial revision
#
#

# DO NOT DELETE

ngat_util_FileUtilities.o: /usr/include/errno.h /usr/include/sys/errno.h
ngat_util_FileUtilities.o: /usr/include/stdio.h /usr/include/iso/stdio_iso.h
ngat_util_FileUtilities.o: /usr/include/sys/feature_tests.h
ngat_util_FileUtilities.o: /usr/include/sys/isa_defs.h
ngat_util_FileUtilities.o: /usr/include/sys/va_list.h
ngat_util_FileUtilities.o: /usr/include/stdio_tag.h /usr/include/stdio_impl.h
ngat_util_FileUtilities.o: /usr/include/stdlib.h
ngat_util_FileUtilities.o: /usr/include/iso/stdlib_iso.h
ngat_util_FileUtilities.o: /usr/include/unistd.h /usr/include/sys/types.h
ngat_util_FileUtilities.o: /usr/include/sys/machtypes.h
ngat_util_FileUtilities.o: /usr/include/sys/int_types.h
ngat_util_FileUtilities.o: /usr/include/sys/unistd.h
ngat_util_FileUtilities.o: /usr/local/j2sdk1.4.2_12/include/jni.h
ngat_util_FileUtilities.o: /usr/include/stdarg.h
ngat_util_FileUtilities.o: /usr/include/iso/stdarg_iso.h
ngat_util_FileUtilities.o: /usr/local/j2sdk1.4.2_12/include/solaris/jni_md.h
ngat_util_FileUtilities.o: /usr/include/sys/stat.h
ngat_util_FileUtilities.o: /usr/include/sys/time_std_impl.h
ngat_util_FileUtilities.o: /usr/include/sys/stat_impl.h
ngat_util_FileUtilities.o: ../include/ngat_util_FileUtilities.h
