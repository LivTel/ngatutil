# $Header: /space/home/eng/cjm/cvs/ngatutil/c/Makefile,v 1.4 2008-06-27 10:51:03 cjm Exp $

include			../../Makefile.common

PACKAGEDIR = ngat/util
PACKAGENAME = ngat.util

INCDIR = ../include
DOCSDIR = $(LT_DOC_HOME)/ngat/cdocs/$(PACKAGEDIR)
CFLAGS = -g $(CCHECKFLAG) -I$(INCDIR) -I$(JNIINCDIR) -I$(JNIMDINCDIR) -I$(CFITSIOINCDIR) -L$(LT_LIB_HOME)
LINTFLAGS = -I$(INCDIR) -I$(JNIINCDIR) -I$(JNIMDINCDIR) -I$(CFITSIOINCDIR)
DOCFLAGS = -static
SRCS 		= 	ngat_util_FileUtilities.c
HEADERS		=	$(SRCS:%.c=%.h)
OBJS		=	$(SRCS:%.c=%.o)
DOCS 		= 	$(SRCS:%.c=$(DOCSDIR)/%.html)

top: $(INCDIR)/ngat_util_FileUtilities.h shared docs

shared: $(LT_LIB_HOME)/libngatutil.so

$(LT_LIB_HOME)/libngatutil.so: $(OBJS)
	cc $(CCSHAREDFLAG) $(CFLAGS) $(OBJS) -o $@ $(TIMELIB) 

static: $(LT_LIB_HOME)/libngatutil.a

$(LT_LIB_HOME)/libngatutil.a: $(OBJS)
	ar rcv $@ $?

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

ngat_util_FileUtilities.o: /usr/include/errno.h /usr/include/features.h
ngat_util_FileUtilities.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
ngat_util_FileUtilities.o: /usr/include/bits/errno.h
ngat_util_FileUtilities.o: /usr/include/linux/errno.h
ngat_util_FileUtilities.o: /usr/include/asm/errno.h /usr/include/stdio.h
ngat_util_FileUtilities.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/include/stddef.h
ngat_util_FileUtilities.o: /usr/include/bits/types.h
ngat_util_FileUtilities.o: /usr/include/bits/wordsize.h
ngat_util_FileUtilities.o: /usr/include/bits/typesizes.h /usr/include/libio.h
ngat_util_FileUtilities.o: /usr/include/_G_config.h /usr/include/wchar.h
ngat_util_FileUtilities.o: /usr/include/bits/wchar.h /usr/include/gconv.h
ngat_util_FileUtilities.o: /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/include/stdarg.h
ngat_util_FileUtilities.o: /usr/include/bits/stdio_lim.h
ngat_util_FileUtilities.o: /usr/include/bits/sys_errlist.h
ngat_util_FileUtilities.o: /usr/include/getopt.h /usr/include/stdlib.h
ngat_util_FileUtilities.o: /usr/include/bits/waitflags.h
ngat_util_FileUtilities.o: /usr/include/bits/waitstatus.h
ngat_util_FileUtilities.o: /usr/include/endian.h /usr/include/bits/endian.h
ngat_util_FileUtilities.o: /usr/include/sys/types.h /usr/include/time.h
ngat_util_FileUtilities.o: /usr/include/sys/select.h
ngat_util_FileUtilities.o: /usr/include/bits/select.h
ngat_util_FileUtilities.o: /usr/include/bits/sigset.h
ngat_util_FileUtilities.o: /usr/include/bits/time.h
ngat_util_FileUtilities.o: /usr/include/sys/sysmacros.h /usr/include/alloca.h
ngat_util_FileUtilities.o: /usr/include/unistd.h
ngat_util_FileUtilities.o: /usr/include/bits/posix_opt.h
ngat_util_FileUtilities.o: /usr/include/bits/confname.h
ngat_util_FileUtilities.o: /usr/java/j2sdk1.4.2_06/include/jni.h
ngat_util_FileUtilities.o: /usr/java/j2sdk1.4.2_06/include/linux/jni_md.h
ngat_util_FileUtilities.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
ngat_util_FileUtilities.o: ../include/ngat_util_FileUtilities.h
