#
# Copyright (C) 2014 The Regents of the University of California.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

AC_PREREQ([2.68])

AC_INIT([libbgpstream], [2.0.0], [bgpstream-info@caida.org])
AM_INIT_AUTOMAKE([foreign])

BGPSTREAM_MAJOR_VERSION=2
BGPSTREAM_MID_VERSION=0
BGPSTREAM_MINOR_VERSION=0

LIBBGPSTREAM_MAJOR_VERSION=2
LIBBGPSTREAM_MID_VERSION=0
LIBBGPSTREAM_MINOR_VERSION=0

AC_DEFINE_UNQUOTED([BGPSTREAM_MAJOR_VERSION],$BGPSTREAM_MAJOR_VERSION,
        [bgpstream major version])
AC_DEFINE_UNQUOTED([BGPSTREAM_MID_VERSION],$BGPSTREAM_MID_VERSION,
        [bgpstream mid version])
AC_DEFINE_UNQUOTED([BGPSTREAM_MINOR_VERSION],$BGPSTREAM_MINOR_VERSION,
        [bgpstream minor version])

AC_SUBST([BGPSTREAM_MAJOR_VERSION])
AC_SUBST([BGPSTREAM_MID_VERSION])
AC_SUBST([BGPSTREAM_MINOR_VERSION])

AC_DEFINE_UNQUOTED([LIBBGPSTREAM_MAJOR_VERSION],$LIBBGPSTREAM_MAJOR_VERSION,
        [libbgpstream major version])
AC_DEFINE_UNQUOTED([LIBBGPSTREAM_MID_VERSION],$LIBBGPSTREAM_MID_VERSION,
        [libbgpstream mid version])
AC_DEFINE_UNQUOTED([LIBBGPSTREAM_MINOR_VERSION],$LIBBGPSTREAM_MINOR_VERSION,
        [libbgpstream minor version])

AC_SUBST([LIBBGPSTREAM_MAJOR_VERSION])
AC_SUBST([LIBBGPSTREAM_MID_VERSION])
AC_SUBST([LIBBGPSTREAM_MINOR_VERSION])

LT_INIT

# Check if we should disable rpath.
#
# For advanced users: In certain configurations (e.g. when one of BGPStream's
# dependencies is located in a directory which also holds an old
# libbgpstream.so), the rpath attributes added by libtool cause problems with
# make check (or indeed with any non-installed binaries) as rpath will be
# preferred over LD_LIBRARY_PATH. This does not seem to be a problem with
# clang. When using --disable-rpath you will likely need to set LD_LIBRARY_PATH
# if you are using libraries in non-system locations. YMMV.
#
DISABLE_RPATH

AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_SRCDIR([lib/bgpstream.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CC_C99

AC_SYS_LARGEFILE

AH_VERBATIM([_GNU_SOURCE],
[/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif])

AC_CHECK_FUNCS([gettimeofday memset strdup strstr strsep strlcpy vasprintf])

# should we dump debug output to stderr and not optmize the build?

AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])

if test x"$debugit" = x"yes"; then
    AC_DEFINE([DEBUG],[],[Debug Mode])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h inttypes.h limits.h math.h stdlib.h string.h \
			      time.h sys/time.h])

# Checks for mandatory libraries

# this code is needed to get the right threading library on a mac
STASH_CFLAGS="$CFLAGS"
CFLAGS=
AX_PTHREAD(, [AC_MSG_ERROR([pthreads required])])
CFLAGS="$STASH_CFLAGS"
LIBS="$PTHREAD_LIBS $LIBS"
CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
CC="$PTHREAD_CC"

# check that wandio is installed and HTTP support is enabled
AC_SEARCH_LIBS([wandio_create], [wandio], [with_wandio=yes],
               [AC_MSG_ERROR(
  [libwandio required (http://research.wand.net.nz/software/libwandio.php)]
)])
AM_CONDITIONAL([WITH_WANDIO], [test "x$with_wandio" == xyes])

# build our bundled version of libparsebgp
AC_CONFIG_SUBDIRS([lib/formats/libparsebgp])

# Checks for doxygen
AC_CHECK_PROG([bgpstream_doxygen_avail], [doxygen], [yes], [no])
AC_MSG_CHECKING([whether to compile the docs])
AC_ARG_WITH([doxygen],
	[AS_HELP_STRING([--without-doxygen],
	  [do not compile the doxygen generated docs])],
	  [bgpstream_doxygen=no],
	  [if test "x$bgpstream_doxygen_avail" == xyes; then
	      bgpstream_doxygen=yes
	  else
		bgpstream_doxygen=no
	  fi
	  ])
AC_MSG_RESULT([$bgpstream_doxygen])
AM_CONDITIONAL(HAS_DOXYGEN, [test x"$bgpstream_doxygen" = xyes])

AC_MSG_NOTICE([])
AC_MSG_NOTICE([---- BGPStream configuration ----])

AC_MSG_NOTICE([checking format modules...])

# allow libparsebgp warnings to be silenced
AC_MSG_CHECKING([whether to silence libparsebgp warnings])
   AC_ARG_ENABLE([parser-warnings],
       [AS_HELP_STRING([--disable-parser-warnings],
               [disable BGP parse warnings (def=no)])],
               [enable_parser_warnings="$enableval"],
               [enable_parser_warnings=yes])
   if test x"$enable_parser_warnings" != x"no"; then
      disable_parser_warnings="no"
   else
      disable_parser_warnings="yes"
   fi
   AC_MSG_RESULT([$disable_parser_warnings])
   if test x"$disable_parser_warnings" == x"yes"; then
      AC_DEFINE([PARSEBGP_SILENCE_WARNING],[],[Disable parsebgp warnings])
   fi

AC_MSG_NOTICE([checking transport modules...])

# shall we build with support for the kafka transport module?
AC_MSG_CHECKING([whether to build kafka transport module])
AC_ARG_WITH([transport-kafka],
	[AS_HELP_STRING([--without-transport-kafka],
	  [do not compile the kafka transport module])],
	  [],
	  [with_transport_kafka=yes])
AC_MSG_RESULT([$with_transport_kafka])

AM_CONDITIONAL([WITH_TRANSPORT_KAFKA], [test "x$with_transport_kafka" != xno])

if test x"$with_transport_kafka" = xyes; then
   AC_CHECK_LIB([rdkafka], [rd_kafka_query_watermark_offsets], ,
               [AC_MSG_ERROR(
                 [librdkafka is required for kafka (--without-transport-kafka to disable)])])

   AC_DEFINE([WITH_TRANSPORT_KAFKA],[1],[Building kafka transport module])
fi

AC_MSG_NOTICE([])
AC_MSG_NOTICE([checking data interfaces...])

BS_WITH_DI([bgpstream_broker],[broker],[BROKER],[yes])
BS_WITH_DI([bgpstream_singlefile],[singlefile],[SINGLEFILE],[yes])
BS_WITH_DI([bgpstream_kafka],[kafka],[KAFKA],[yes])
BS_WITH_DI([bgpstream_betabmp],[betabmp],[BETABMP],[yes])
BS_WITH_DI([bgpstream_csvfile],[csvfile],[CSVFILE],[yes])
BS_WITH_DI([bgpstream_sqlite],[sqlite],[SQLITE],[no])

if test "x$bs_di_valid" != xyes; then
   AC_MSG_ERROR([At least one data interface must be enabled])
fi

# check for data interface dependencies
AC_MSG_NOTICE([checking data interface dependencies...])

if test "x$with_di_broker" == xyes; then
  CHECK_WANDIO_HTTP("http://bgpstream.caida.org/broker")
fi

if test "x$with_di_kafka" == xyes; then
   if test x"$with_transport_kafka" != xyes; then
      AC_MSG_ERROR([Kafka data interface requires Kafka transport module (--without-kafka to disable)])
   fi
fi

if test "x$with_di_betabmp" == xyes; then
   if test x"$with_transport_kafka" != xyes; then
      AC_MSG_ERROR([(Beta) BMP Stream data interface requires Kafka transport module (--without-betabmp to disable)])
   fi
fi

if test "x$with_di_sqlite" == xyes; then
   # check for sqlite library
   AC_CHECK_LIB([sqlite3], [sqlite3_open_v2], ,
               [AC_MSG_ERROR( [libsqlite3 required for sqlite data interface])])
fi

# configure enabled data interfaces
AC_MSG_NOTICE([configuring data interface parameters...])

# broker options
if test "x$with_di_broker" == xyes; then
   BS_DI_OPT(broker-url, BROKER_URL, Broker URL, https://bgpstream.caida.org/broker)

   AC_MSG_CHECKING([whether to enable broker debugging output])
   AC_ARG_ENABLE([broker-debug],
       [AS_HELP_STRING([--enable-broker-debug],
               [enable broker debug info (def=no)])],
               [broker_debug="$enableval"],
               [broker_debug=no])
   AC_MSG_RESULT([$broker_debug])
   if test x"$broker_debug" = x"yes"; then
      AC_DEFINE([BROKER_DEBUG],[],[Broker Debugging])
   fi
fi

# singlefile options
if test "x$with_di_singlefile" == xyes; then
   BS_DI_OPT(singlefile-rib-file, SINGLEFILE_RIB_FILE, RIB MRT file to read, not-set)
   BS_DI_OPT(singlefile-upd-file, SINGLEFILE_UPDATE_FILE, Updates MRT to read, not-set)
fi

# sqlite options
if test "x$with_di_sqlite" == xyes; then
   BS_DI_OPT(sqlite-db-file, SQLITE_DB_FILE, SQLite database, not-set)
fi

# csvfile options
if test "x$with_di_csvfile" == xyes; then
   BS_DI_OPT(csvfile-csv-file, CSVFILE_CSV_FILE, CSV file listing the MRT data to read, not-set)
fi

# RPKI configuration (ROAFetchLib)
AC_MSG_NOTICE([])
AC_MSG_NOTICE([---- RPKI support configuration ----])
AC_ARG_WITH([rpki],
        [AS_HELP_STRING([--with-rpki],
        [bulding with rpki support])],
        [],
        [with_rpki=no])
AM_CONDITIONAL([WITH_RPKI], [test "x$with_rpki" != xno])
if test x"$with_rpki" = xyes; then
    AC_CHECK_LIB([roafetch], [rpki_set_config],,
         [AC_MSG_ERROR(
            [ROAFetchlib is required (--without-rpki to disable)]
    )])
    AC_DEFINE([WITH_RPKI],[1],[Building with RPKI support])
    AC_DEFINE([RPKI_BROKER],["https://roa-broker.imp.fu-berlin.de"],[RPKI broker])
else
  AC_MSG_CHECKING([whether to build with RPKI support])
  AC_MSG_RESULT([no])
fi

AC_HEADER_ASSERT

AC_CONFIG_FILES([Makefile
		common/Makefile
		common/libpatricia/Makefile
		common/libinterval3/Makefile
		common/libinterval3/rb_tree/Makefile
		common/libcsv/Makefile
                common/libjsmn/Makefile
                docs/Makefile
	        docs/bgpstream.doxygen
		lib/Makefile
                lib/datainterfaces/Makefile
                lib/transports/Makefile
                lib/formats/Makefile
                lib/utils/Makefile
		tools/Makefile
		test/Makefile])
AC_OUTPUT
