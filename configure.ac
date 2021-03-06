dnl ***************************************************************************
dnl configure.ac (Sequencer64)
dnl ---------------------------------------------------------------------------
dnl
dnl \file          configure.ac
dnl \library       Sequencer64
dnl \author        Chris Ahlstrom
dnl \date          2015-09-11
dnl \update        2016-11-14
dnl \version       $Revision$
dnl \license       $XPC_SUITE_GPL_LICENSE$
dnl
dnl   This script is for the Sequencer64 project, a repacking and fixing
dnl   of seq24 v0.9.2 and a direct fork from sequencer24.
dnl
dnl   Process this file with autoconf to produce a configure script.
dnl
dnl ---------------------------------------------------------------------------

AC_PREREQ(2.60)
AC_REVISION($Revision: 0.9$)dnl
AC_INIT(Sequencer64, [0.9.21], [ahlstromcj@gmail.com])
AC_CONFIG_AUX_DIR([aux-files])

dnl AC_CONFIG_SRCDIR([libseq64/src/midibus.cpp])

dnl Do we need the following?  No, but it cleans up a lot of warning messages.

AC_CANONICAL_SYSTEM

dnl See http://www.delorie.com/gnu/docs/automake/automake_24.html

AM_INIT_AUTOMAKE([dist-bzip2])
AC_CONFIG_HEADER([include/config.h])

dnl Prepends "SEQ64_" to a lot of the macro definitions, for a better
dnl guarantee of avoiding naming conflicts.

AX_PREFIX_CONFIG_H([include/seq64-config.h], [seq64])

dnl New for autoconf 2.60, prevents spurious datarootdir warnings.

AC_DEFUN([AC_DATAROOTDIR_CHECKED])

dnl 1. Package version information.  The first item is the name that covers
dnl    a number of libraries, all of whose names start with "midicvt".
dnl    We have to set up a "suite" name; since PACKAGE is defined to be the
dnl    name of the current project, we can't use that value in the package
dnl    configuration files.  It is replaced by MIDICVT_SUITE_NAME, which covers
dnl    all of the library projects.

PACKAGE=sequencer64
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE")
AC_SUBST(PACKAGE)

VERSION="0.9.21"
AC_DEFINE_UNQUOTED(VERSION, "$VERSION")
AC_SUBST(VERSION)

SEQUENCER64_SUITE_NAME="SEQUENCER64"
AC_SUBST([SEQUENCER64_SUITE_NAME])

dnl For now, the code to set this up is in the libseq64 and seq_gtkmm2
dnl Makefiles:
dnl
dnl GIT_VERSION=$(shell git describe --abbrev=7 --always --tags)
dnl GIT_VERSION="0.9.11-9-gc9ee500"
dnl AC_DEFINE_UNQUOTED(GIT_VERSION, "$GIT_VERSION")
dnl AC_DEFINE(GIT_VERSION, "$GIT_VERSION")
dnl AC_SUBST(GIT_VERSION)

dnl 1.a. Set up version information for this project.
dnl
dnl      This versioning is the libtool version.
dnl      Warning: These values are inserted into libtool's "version-info"
dnl      value, and have to follow libtool rules:
dnl
dnl      Format is 'current:revision:age', where
dnl
dnl      current = Number of the current interface.  If the interface has
dnl      changed, increment this number and set 'revision' to 0.  If the new
dnl      interface has removed elements of the preceding interface, backward
dnl      compatibility has been broken, and you must set 'age' to 0.
dnl
dnl      revision = Implementation number of the most recent interface,
dnl      where 0 is the first.  The runtime loader always uses the library
dnl      with the highest revision.  If you change any source modules,
dnl      increment this number.
dnl
dnl      age = The number of additional interface supported by this library.
dnl      The age must the less than or equal to 'current'.  If the new
dnl      interface is a superset of the preceding interface, 'age' must be
dnl      incremented.

SEQUENCER64_API_MAJOR="0"
AC_SUBST([SEQUENCER64_API_MAJOR])

SEQUENCER64_API_MINOR="9"
AC_SUBST([SEQUENCER64_API_MINOR])

SEQUENCER64_API_PATCH="0"
AC_SUBST([SEQUENCER64_API_PATCH])

SEQUENCER64_OFFICIAL_VERSION="$SEQUENCER64_API_MAJOR.$SEQUENCER64_API_MINOR.$SEQUENCER64_API_PATCH"

dnl For version 1.0.0, we will reset the libtool version information.

SEQUENCER64_LT_CURRENT="0"
AC_SUBST([SEQUENCER64_LT_CURRENT])

SEQUENCER64_LT_REVISION="0"
AC_SUBST([SEQUENCER64_LT_REVISION])

SEQUENCER64_LT_AGE="0"
AC_SUBST([SEQUENCER64_LT_AGE])

SEQUENCER64_LIBTOOL_VERSION="$SEQUENCER64_LT_CURRENT.$SEQUENCER64_LT_REVISION.$SEQUENCER64_LT_AGE"

dnl 1.b. Set up the version strings.  The primary version string of interest
dnl      is SEQUENCER64_API_VERSION.

SEQUENCER64_API_VERSION="$SEQUENCER64_API_MAJOR.$SEQUENCER64_API_MINOR"
AC_SUBST([SEQUENCER64_API_VERSION])

dnl 1.c. Report the version information in the progress output.

AC_MSG_CHECKING(major version)
AC_MSG_RESULT($SEQUENCER64_API_MAJOR)
AC_MSG_CHECKING(minor version)
AC_MSG_RESULT($SEQUENCER64_API_MINOR)
AC_MSG_CHECKING(patchlevel)
AC_MSG_RESULT($SEQUENCER64_API_PATCH)

dnl 1.d. Set up the suite name and current-project name.

SEQUENCER64_PROJECT_NAME="SEQUENCER64"
AC_SUBST([SEQUENCER64_PROJECT_NAME])

AC_DEFINE(_GNU_SOURCE, 1, [gnu source])

dnl 2. Libtool
dnl
dnl Initialize libtool in the default manner, which turns on shared
dnl libraries if available, and enable static libraries if they do not conflict
dnl with shared libraries.  Also sets the shell variable LIBTOOL_DEPS.
dnl
dnl The latest GNU documentation specifies version 2 of libtool, but Debian
dnl testing provides only 1.5 (Debian unstable now provides 2.2).  So we don't
dnl use these new macros, just the older, deprecated macros.
dnl
dnl LT_PREREQ([1.5])
dnl LT_INIT
dnl AC_SUBST([LIBTOOL_DEPS])
dnl
dnl See <http://www.delorie.com/gnu/docs/libtool/libtool_27.html> for the
dnl usage of LIBTOOL_DEPS.
dnl
dnl Uncomment the following if you want more straightforward debugging.  An
dnl alternative is to specify --disable-shared when running 'configure'.
dnl
dnl AC_DISABLE_SHARED

AC_PROG_LIBTOOL

LT_RELEASE="$SEQUENCER64_API_MAJOR.$SEQUENCER64_API_MINOR"
AC_SUBST([LT_RELEASE])

LT_CURRENT="$SEQUENCER64_API_MAJOR"
AC_SUBST([LT_CURRENT])

LT_REVISION="$SEQUENCER64_API_MINOR"
AC_SUBST([LT_REVISION])

LT_AGE="$SEQUENCER64_API_PATCH"
AC_SUBST([LT_AGE])

dnl 3. Set up expandable installation directory(ies).
dnl
dnl These directories are for the sequencer64 library.
dnl
dnl We want all of the header files and library files for the whole suite
dnl to be in the same sub-directory, sequencer64-1.1.  This will avoid
dnl clutter and put all our code in one place.
dnl
dnl      /usr/include/sequencer64-0.9/sequencer64
dnl      /usr/lib/sequencer64-0.9
dnl      /usr/man/man1
dnl      /usr/share/doc/sequencer64-0.9/doc/dox/html

sequencer64includedir="${includedir}/sequencer64-${SEQUENCER64_API_VERSION}"
AC_SUBST(sequencer64includedir)

sequencer64libdir="${libdir}/sequencer64-${SEQUENCER64_API_VERSION}"
AC_SUBST(sequencer64libdir)

sequencer64docdir="${datadir}/doc/sequencer64-${SEQUENCER64_API_VERSION}"
AC_SUBST(sequencer64docdir)

sequencer64datadir="${datadir}/sequencer64-${MIDICVT_API_VERSION}"
AC_SUBST(sequencer64datadir)

sequencer64doxygendir="${datadir}/doc/sequencer64-${SEQUENCER64_API_VERSION}"
AC_SUBST(sequencer64doxygendir)

dnl Do we have -Wl,--as-needed?  This option allows the linker to ignore, i.e.,
dnl not link against, some of the libraries supplied on its command line if
dnl they are not actually used by the shared library that is being created.
dnl For example, if you supply the -lm option on the command line to the linker
dnl but do not actually use any maths functions then the libm.so library will
dnl not be linked against.

AC_MSG_CHECKING(if --as-needed works)
AC_ARG_ENABLE(as_needed,
    [AS_HELP_STRING(--enable-as-needed,
         [Enable linker option -Wl,--as-needed (default=yes)])],
    [
    case "${enableval}" in
         yes) as_needed="1";;
         no) as_needed="";;
         *) AC_MSG_ERROR(bad value ${enableval} for --enable-as_needed);;
    esac
    ],[
        as_needed="unknown"
    ])
if test x"${as_needed}" = x"unknown"; then
    ac_old_ldflags="${LDFLAGS}"
    LDFLAGS="-Wl,--as-needed"
    AC_TRY_LINK(
                [],
                [],
                [as_needed="1"],
                [as_needed=""])
    LDFLAGS="${ac_old_ldflags}" 
fi
if test -n "$as_needed"; then
    AC_MSG_RESULT(yes)
    LDFLAGS="${LDFLAGS} -Wl,--as-needed"
else
    AC_MSG_RESULT(no)
fi

dnl Check for deprecated GTK constructs as per
dnl http://www.murrayc.com/permalink/2011/01/18/avoiding-use-of-deprecated-api/
dnl
dnl Looks too difficult, errors in gtk headers. Try gtkmm-3 directly instead.
dnl That is unworkable at this time, though.
dnl
dnl MM_ARG_ENABLE_WARNINGS([MM_WFLAGS],
dnl  [-Wall],
dnl  [-Wall -Wextra -Wno-missing-field-initializers -DGSEAL_ENABLE],
dnl  [G GDK GDK_PIXBUF PANGO GTK])

dnl 4. Get external flags, if any.

CFLAGS="${CFLAGS}"

dnl Checks for libraries.

AC_CHECK_LIB(rt, main, ,
    AC_MSG_ERROR([POSIX.1b Realtime library missing librt]))

dnl Convert from gtkmm-2.4 to gtkmm-3.0.  It currently builds either way.
dnl No! I was mistaken, because I had left some 2.4 paths in place below.

AC_CHECK_LIB(gtkmm-2.4, _init,,
    AC_MSG_ERROR(Essential library libgtkmm-2.4 not found))

dnl LATER:
dnl
dnl AC_CHECK_LIB(gtkmm-3.0, _init,,
dnl     AC_MSG_ERROR(Essential library libgtkmm-3.0 not found))

AC_CHECK_LIB(sigc-2.0, main,,
    AC_MSG_ERROR(Essential library libsigc++-2.0 not found))

dnl Checks for header files.

AC_HEADER_STDC
AC_CHECK_HEADERS(getopt.h)

dnl Checks for typedefs, structures, and compiler characteristics.

AC_C_CONST

dnl ALSA

AM_PATH_ALSA(0.9.0)

dnl Check for the presence of Doxygen.  Not an error to be missing, but
dnl we don't want to try to build documentation if it is not present.
dnl See http://www.gnu.org/software/autoconf-archive/ax_prog_doxygen.html
dnl
dnl AC_PROG_DOXYGEN

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found, continuing without Doxygen support])
fi

dnl 5.b. gcc support.

AC_GCC_VERSION

dnl C++ support.  Run tests in C++.  Note the order; avoids messy warnings.

AC_LANG_C
AC_PROG_CC
AC_LANG_CPLUSPLUS       dnl or AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_INSTALL
AC_PROG_LN_S

dnl 5.c. Mingw support.
dnl
dnl Checks for the MingW32 compiler environment. If present, sets shell
dnl variable MINGW32 to 'yes'. If not present, sets MINGW32 to the
dnl empty string.
dnl
dnl Also check to see if the user specified the MingW32 installation
dnl location.  On Debian, the installation is in /usr/i586-mingw32msvc/.
dnl The Mingw versions of the executables start with "i586".  For example,
dnl the compiler is "i586-mingw32msvc-gcc-3.4.5".
dnl
dnl http://www.wxwidgets.org/wiki/index.php/Cross-Compiling_Under_Linux
dnl
dnl is a good place to start learning about building Windows applications.

AC_XPC_MINGW32
AC_ARG_WITH(mingw32,[ --with-mingw32[=DIR] MingW32 installation location])

dnl gtkmm
dnl
dnl PKG_CHECK_MODULES(GTKMM, gtkmm-3.0 >= 3.0.0)

PKG_CHECK_MODULES(GTKMM, gtkmm-2.4 >= 2.4.0)
AC_SUBST(GTKMM_CFLAGS)
AC_SUBST(GTKMM_LIBS)

dnl Checks for the Cygwin environment. If present, sets shell variable
dnl CYGWIN to 'yes'; if not present, sets CYGWIN to the empty string.

AC_CYGWIN

dnl Clear out the X11 flags for the case where we are cross-compiling
dnl for i586-mingw32 targets, under UNIX.

if test "x$CYGWIN" = "xyes" -o "x$MINGW32" = "xyes" ; then
   X_CFLAGS=""
   X_LIBS=""
fi

dnl JACK SUPPORT

AC_ARG_ENABLE(jack,
    [AS_HELP_STRING(--disable-jack, [Disable JACK support])],
    [jack=$enableval],
    [jack=yes])

AC_ARG_ENABLE(jack-session,
    [AS_HELP_STRING(--disable-jack-session, [Disable JACK session support])],
    [jack_session=$enableval],
    [jack_session=yes])

dnl USER_LDFLAGS="${USER_LDFLAGS} $(pkg-config --libs jack )"
dnl features_list="${features_list} (Jack)"

if test "$jack" != "no"; then
    PKG_CHECK_MODULES(JACK, jack >= 0.90.0, jack_found="yes", jack_found="no")
    if test "$jack_found" = "yes"; then
        AC_DEFINE(JACK_SUPPORT, 1, [Define to enable JACK driver])
        AC_SUBST(JACK_CFLAGS)
        AC_SUBST(JACK_LIBS)

        dnl JACK session        
        if test "$jack_session" != "no"; then
            AC_CHECK_HEADER(jack/session.h, jack_session_found="yes",
                            jack_session_found="no")
            if test "$jack_session_found" = "yes"; then
                AC_DEFINE(JACK_SESSION, 1,
                          [Define to enable JACK session support])
            fi
        fi
        AC_MSG_RESULT([JACK support enabled.]);

    else
        AC_MSG_WARN([Could not find JACK library, disabling JACK support])
    fi
else
    AC_MSG_WARN([JACK support not enabled.]);
fi

dnl LASH support
dnl
dnl WARNING:  LASH support is too entangle in the GUI system at present in
dnl this code, so the default is to DISABLE it!  We need to separate out
dnl some of the perform code and other code from the GUI framework.

AC_ARG_ENABLE(lash,
    [AS_HELP_STRING(--disable-lash, [Disable LASH support])],
    [lash=$enableval],
    [lash=yes])

if test "$lash" != "no"; then
    PKG_CHECK_MODULES(LASH, lash-1.0 >= 0.5.0, lash_found="yes", lash_found="no")
    if test "$lash_found" = "yes"; then
        AC_DEFINE(LASH_SUPPORT, 1, [Define to enable LASH support])
        AC_SUBST(LASH_CFLAGS)
        AC_SUBST(LASH_LIBS)
        AC_MSG_RESULT([LASH support enabled.]);
    else
        AC_MSG_WARN([LASH not found, session support will not be built.])
    fi
else
    AC_MSG_WARN([LASH support not enabled.]);
fi

dnl PortMidi support
dnl
dnl TODO

dnl Support for highlighting empty sequences (in yellow).  If enabled, the
dnl macro SEQ64_HIGHLIGHT_EMPTY_SEQS is defined.  All macros produced by
dnl this configuration start with "SEQ64_".

AC_ARG_ENABLE(highlight,
    [AS_HELP_STRING(--disable-highlight, [Disable highlighting empty sequences])],
    [highlight=$enableval],
    [highlight=yes])

if test "$highlight" != "no"; then
    AC_DEFINE(HIGHLIGHT_EMPTY_SEQS, 1, [Define to enable highlighting empty sequences])
    AC_MSG_RESULT([Highlighting empty sequences enabled.]);
else
    AC_MSG_WARN([Highlighting empty sequences not enabled.]);
fi

dnl Support for using the event editor.  It can cause issues if used, and adds
dnl to the size of the application, so we want the option to disable it.  We
dnl leave it in the code, but comment out the menu entries to access it, until
dnl we can work out the issues.  Ah, finally worked them out, by adding calls
dnl to verify_and_link().

AC_ARG_ENABLE(eveditor,
    [AS_HELP_STRING(--disable-eveditor, [Disable using the event editor])],
    [eveditor=$enableval],
    [eveditor=yes])

if test "$eveditor" != "no"; then
    AC_DEFINE(ENABLE_EVENT_EDITOR, 1, [Define to enable the event editor])
    AC_MSG_RESULT([Event editor enabled.]);
else
    AC_MSG_WARN([Event editor not enabled.]);
fi

dnl Support for pausing playback in ALSA mode, including a pause button.
dnl If enabled, the macro SEQ64_PAUSE_SUPPORT is defined.

AC_ARG_ENABLE(pause,
    [AS_HELP_STRING(--disable-pause, [Disable pausing sequences and pause button])],
    [pause=$enableval],
    [pause=yes])

if test "$pause" != "no"; then
    AC_DEFINE(PAUSE_SUPPORT, 1, [Define to enable pausing and pause button])
    AC_MSG_RESULT([Pausing sequences and pause-button enabled.]);
else
    AC_MSG_WARN([Pausing sequences and pause-button not enabled.]);
fi

dnl Support for re-enabling the "statistics" code.
dnl If enabled, the macro SEQ64_STATISTICS_SUPPORT is defined.
dnl The default is for this feature to be disabled.

AC_ARG_ENABLE(statistics,
    [AS_HELP_STRING(--enable-statistics, [Enable statistics gathering])],
    [statistics=$enableval],
    [statistics=no])

if test "$statistics" != "no"; then
    AC_DEFINE(STATISTICS_SUPPORT, 1, [Define to enable statistics gathering])
    AC_MSG_RESULT([Statistics gathering enabled.]);
else
    AC_MSG_WARN([Statistics gathering not enabled.]);
fi

dnl Support for using the stazed JACK support.  Now enabled by default.
dnl It seems to work well, no complaints recently by user layk.  Also
dnl enables the stazed transport features, which are tightly coupled to stazed
dnl JACK support.

AC_ARG_ENABLE(seq32jack,
    [AS_HELP_STRING(--disable-seq32jack, [Disable JACK and Seq32 JACK support])],
    [seq32jack=$enableval],
    [seq32jack=yes])

if test "$seq32jack" != "no"; then
    AC_DEFINE(STAZED_JACK_SUPPORT, 1, [Define to enable Seq32 JACK support])
    AC_DEFINE(JACK_SUPPORT, 1, [Define to enable JACK driver])
    AC_MSG_RESULT([Seq32 JACK support enabled.]);
else
    AC_MSG_WARN([Seq32 JACK support not enabled.]);
fi

dnl Support for using the stazed LFO window support.  Now enabled by default.

AC_ARG_ENABLE(lfo,
    [AS_HELP_STRING(--disable-lfo, [Disable using Seq32 LFO window])],
    [lfo=$enableval],
    [lfo=yes])

if test "$lfo" != "no"; then
    AC_DEFINE(STAZED_LFO_SUPPORT, 1, [Define to enable Seq32 LFO window support])
    AC_MSG_RESULT([Seq32 LFO window support enabled.]);
else
    AC_MSG_WARN([Seq32 LFO window support not enabled.]);
fi

dnl Support for using the stazed chord generator.

AC_ARG_ENABLE(chords,
    [AS_HELP_STRING(--disable-chords, [Disable using the chord generator])],
    [chords=$enableval],
    [chords=yes])

if test "$chords" != "no"; then
    AC_DEFINE(STAZED_CHORD_GENERATOR, 1, [Define to enable the chord generator])
    AC_MSG_RESULT(Chord generator enabled.)
else
    AC_MSG_WARN([Chord generator not enabled.]);
fi

dnl Support for using the stazed transpose feature.  This affects sequence and
dnl song transpose, not the transpose tool.

AC_ARG_ENABLE(transpose,
    [AS_HELP_STRING(--disable-transpose, [Disable using global transpose])],
    [transpose=$enableval],
    [transpose=yes])

if test "$transpose" != "no"; then
    AC_DEFINE(STAZED_TRANSPOSE, 1, [Define to enable global transpose])
    AC_MSG_RESULT(Global seq32 transpose enabled.)
else
    AC_MSG_WARN([Global seq32 transpose not enabled.]);
fi

dnl Support for stripping unused mute-group specifications from the output MIDI
dnl file.  They are still left in the "rc" configuration file, but can be
dnl manually disabled by setting the mute-group size to 0 in that file.

AC_ARG_ENABLE(mutestrip,
    [AS_HELP_STRING(--disable-mutestrip,
        [Disable stripping empty mute groups from MIDI files])],
    [mutestrip=$enableval],
    [mutestrip=yes])

if test "$mutestrip" != "no"; then
    AC_DEFINE(STRIP_EMPTY_MUTES, 1, [Define to enable empty mute-group stripping])
    AC_MSG_RESULT(Empty mute-strip enabled.)
else
    AC_MSG_WARN([Empty mute-strip not enabled.]);
fi

dnl 6.0  Top portion of the config.h/sequencer64-config.h header files.
dnl      The sequencer64-config.h header file has "SEQUENCER64_" prepended
dnl      to these automatically for us.  Also, we can't use
dnl      #define SEQUENCER64_API_VERSION "${SEQUENCER64_API_VERSION}",
dnl      since the macro call in quotes does /not/ get expanded.
dnl
dnl Note: The AX_PREFIX_CONFIG_H macro called way above prepends
dnl       "SEQUENCER64_" to these values when it generated sequencer64-config.h.
dnl
dnl #define API_VERSION "0.9"             // defined on command line

AH_TOP(

#define VERSION_DATE_SHORT "2016-11-14"
#define VERSION "0.9.21"

)

dnl 7. Checks for build configuration.
dnl
dnl 7.a. Compiling with debugging, coverage, or profiling options.
dnl      Implemented in m4/xpc_debug.m4.
dnl
dnl      --enable-debug
dnl      --enable-coverage
dnl      --enable-profiling

AC_XPC_DEBUGGING

dnl 8.  Set up other options in the compiler macros.

APIDEF="-DAPI_VERSION=\"$SEQUENCER64_API_VERSION\""
WARNFLAGS="-Wall -Wextra -pedantic $WARNINGS"
SPEEDFLAGS="-ffast-math"
COMMONFLAGS="$WARNFLAGS -D_REENTRANT $APIDEF $DBGFLAGS $STACKCHK $NOERRLOG $NOTHISPTR"

dnl Add $WARNINGS_ENABLED to CXXFLAGS if you want to see all warnings, all
dnl the time.  WARNINGS_ENABLED="-Wall"

WARNINGS_DISABLED="-Wno-unused-parameter -Wno-non-virtual-dtor"

dnl We added -std=c++11 for g++ 4.8, and -Wno-deprecated-declarations to
dnl stop g++ 5.2 from griping about usage of std::auto_ptr<>.
dnl
dnl 2015-10-02:  After a Debian Sid update, the configfile module wouldn't
dnl compile because, we think, the sigc++ now required C++11 support.
dnl So we put that requirement back, and had to fix some issues with
dnl conditional compilation.

CFLAGS="$CFLAGS $COMMONFLAGS"
CXXFLAGS="$CFLAGS -std=c++11 -Wno-variadic-macros -Wno-deprecated-declarations"

AH_BOTTOM(
   /* Bottom of header config */
)

dnl Set up the Makefiles.  First, add Doxygen support conditionally, not using
dnl doc/dox/Makefile.  Then do the rest.
dnl
dnl ca 2016-05-07
dnl We decided to build the Doxygen documentation only manually, and have
dnl removed the doc directory from the Makefile.am, and commented out the
dnl following check.
dnl
dnl AM_CONDITIONAL([HAVE_DOXYGEN],
dnl     [test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN],
dnl     [AC_CONFIG_FILES([doc/dox/Makefile])])

AC_CONFIG_FILES([
 Makefile
 m4/Makefile
 libseq64/Makefile
 libseq64/include/Makefile
 libseq64/src/Makefile
 seq_gtkmm2/Makefile
 seq_gtkmm2/include/Makefile
 seq_gtkmm2/src/Makefile
 seq_portmidi/Makefile
 seq_portmidi/include/Makefile
 seq_portmidi/src/Makefile
 resources/pixmaps/Makefile
 Sequencer64/Makefile
 man/Makefile
])

AC_OUTPUT

cat << E_O_F

Now do 'make' to compile the Sequencer64-related projects.
Do 'make install' as root/sudo to install the Sequencer64 application.
Some tests can be run using the separate seq64-tests project.
Do 'make dist', etc. to create gzip and other archives.
To build the PDF documentation, make sure Doxygen and TexLive are installed,
change to the doc/dox directory, and run './make_dox reference'.  To clean
the documentation, run './make_dox clean'.  'install' and 'uninstall' are other
options for make_dox.

E_O_F

dnl configure.ac (sequencer64)
dnl
dnl vim: ts=4 sw=4 et ft=config
