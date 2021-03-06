#-------------------------------------------------------------------------
#
# Makefile for src/bin/pg_dump
#
# Portions Copyright (c) 1996-2016, PostgreSQL Global Development Group
# Portions Copyright (c) 1994, Regents of the University of California
#
# src/bin/pg_dump/Makefile
#
#-------------------------------------------------------------------------

PGFILEDESC = "pg_dump/pg_restore/pg_dumpall - backup and restore PostgreSQL databases"
PGAPPICON=win32

subdir = src/bin/pg_dump
top_builddir = ../../..
include $(top_builddir)/src/Makefile.global

override CPPFLAGS := -I$(libpq_srcdir) $(CPPFLAGS)
LDFLAGS += -L$(top_builddir)/src/fe_utils -lpgfeutils -lpq

BASE_OBJS=	pg_backup_archiver.o pg_backup_db.o pg_backup_custom.o \
	pg_backup_null.o pg_backup_tar.o pg_backup_directory.o \
	pg_backup_utils.o parallel.o compress_io.o dumputils.o

OBJS= $(BASE_OBJS) $(WIN32RES)
MGR_OBJS= $(BASE_OBJS:%.o=%_mgr.o) $(WIN32RES)

kwlookup.c: % : $(top_srcdir)/src/backend/parser/%
	rm -f $@ && $(LN_S) $< .

all: pg_dump pg_restore pg_dumpall mgr_dump mgr_restore mgr_dumpall

MGR_CFLAGS=$(patsubst -DADB,, $(patsubst -DPGXC,,$(CFLAGS)))
%_mgr.o: %.c %.o
	$(CC) $(MGR_CFLAGS) -DMGR_DUMP $(CPPFLAGS) -c $< -o $@

pg_dump: pg_dump.o common.o pg_dump_sort.o $(OBJS) | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(CFLAGS) pg_dump.o common.o pg_dump_sort.o $(OBJS) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)
mgr_dump: pg_dump_mgr.o common_mgr.o pg_dump_sort_mgr.o $(MGR_OBJS) | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(MGR_CFLAGS) pg_dump_mgr.o common_mgr.o pg_dump_sort_mgr.o $(MGR_OBJS) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)

pg_restore: pg_restore.o $(OBJS) | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(CFLAGS) pg_restore.o $(OBJS) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)
mgr_restore: pg_restore_mgr.o $(MGR_OBJS) | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(MGR_CFLAGS) pg_restore_mgr.o $(MGR_OBJS) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)

pg_dumpall: pg_dumpall.o dumputils.o | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(CFLAGS) pg_dumpall.o dumputils.o $(WIN32RES) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)
mgr_dumpall: pg_dumpall_mgr.o dumputils_mgr.o | submake-libpq submake-libpgport submake-libpgfeutils
	$(CC) $(MGR_CFLAGS) pg_dumpall_mgr.o dumputils_mgr.o $(WIN32RES) $(libpq_pgport) $(LDFLAGS) $(LDFLAGS_EX) $(LIBS) -o $@$(X)

install: all installdirs
	$(INSTALL_PROGRAM) pg_dump$(X) '$(DESTDIR)$(bindir)'/pg_dump$(X)
	$(INSTALL_PROGRAM) pg_restore$(X) '$(DESTDIR)$(bindir)'/pg_restore$(X)
	$(INSTALL_PROGRAM) pg_dumpall$(X) '$(DESTDIR)$(bindir)'/pg_dumpall$(X)
	$(INSTALL_PROGRAM) mgr_dump$(X) '$(DESTDIR)$(bindir)'/mgr_dump$(X)
	$(INSTALL_PROGRAM) mgr_restore$(X) '$(DESTDIR)$(bindir)'/mgr_restore$(X)
	$(INSTALL_PROGRAM) mgr_dumpall$(X) '$(DESTDIR)$(bindir)'/mgr_dumpall$(X)

installdirs:
	$(MKDIR_P) '$(DESTDIR)$(bindir)'

check:
	$(prove_check)

installcheck:
	$(prove_installcheck)

uninstall:
	rm -f $(addprefix '$(DESTDIR)$(bindir)'/, pg_dump$(X) pg_restore$(X) pg_dumpall mgr_dump$(X) mgr_restore$(X) mgr_dumpall$(X))

clean distclean maintainer-clean:
	rm -f pg_dump$(X) pg_restore$(X) pg_dumpall$(X) $(OBJS) pg_dump.o common.o pg_dump_sort.o pg_restore.o pg_dumpall.o
	rm -f mgr_dump$(X) mgr_restore$(X) mgr_dumpall$(X) $(MGR_OBJS) pg_dump_mgr.o common_mgr.o pg_dump_sort_mgr.o pg_restore_mgr.o pg_dumpall_mgr.o
	rm -rf tmp_check
