AC_INIT(src/s2io.cpp)

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

RBIN="${R_HOME}/bin/R"
# https://github.com/r-spatial/sf/issues/1054:
# RVER=`"${RBIN}" --version | head -1 | cut -f3 -d" "`
RSCRIPT="${R_HOME}/bin/Rscript"
RVER=`"${RSCRIPT}" -e 'writeLines(paste(sep=".", base::version$major, base::version$minor))'`

RVER_MAJOR=`echo ${RVER} | cut  -f1 -d"."`
RVER_MINOR=`echo ${RVER} | cut  -f2 -d"."`
RVER_PATCH=`echo ${RVER} | cut  -f3 -d"."`

# pick all flags for testing from R
: ${CC=`"${RBIN}" CMD config CC`}
: ${CXX=${CXX11} ${CXX11STD}}
: ${CFLAGS=`"${RBIN}" CMD config CFLAGS`}
: ${CPPFLAGS=`"${RBIN}" CMD config CPPFLAGS`}
: ${LDFLAGS=`"${RBIN}" CMD config LDFLAGS`}
# AC_SUBST([CC],["clang"])
# AC_SUBST([CXX],["clang++"])
AC_MSG_NOTICE([CC: ${CC}])
AC_MSG_NOTICE([CXX: ${CXX}])
PKG_CPPFLAGS=""

# check header:
#s2headers=yes
#AC_CHECK_HEADERS("<s2/s2loop.h>",,s2headers=no)
#if test "${s2headers}" = no; then
#   AC_MSG_ERROR([no s2 headers found.])
#fi

#include "s2/s2point.h"
[cat > s2test.cpp <<_EOCONF
#include <s2/s2point.h>
#include <s2/s2loop.h>
#include <s2/s2polygon.h>
#include <s2/s2builder.h>
#ifdef __cplusplus
extern "C" {
#endif
int main() {
  std::vector<std::unique_ptr<S2Loop>> loops;
  std::vector<S2Point> vertices;
  S2Point p1(1.0, 0.0, 0.0);
  S2Point p2(0.0, 1.0, 0.0);
  S2Point p3(0.0, 0.0, 1.0);
  vertices.push_back(p1);
  vertices.push_back(p2);
  vertices.push_back(p3);
  loops.push_back(absl::make_unique<S2Loop>(vertices));
  return 1;
}
#ifdef __cplusplus
}
#endif
_EOCONF]

PKG_LIBS=-ls2
AC_MSG_CHECKING(s2geometry: linking with -ls2 only)
g++ -o s2test s2test.cpp ${PKG_LIBS} 2> errors.txt
if test `echo $?` -ne 0 ; then
result=no
AC_MSG_RESULT(no)
AC_ERROR([could not link to s2 library: is it installed?])
else
AC_MSG_RESULT(yes)
fi


# check linking:
#s2loop.h

# substitute:
AC_SUBST([PKG_LIBS], ["${PROJ_LIBS} ${PKG_LIBS}"])
AC_SUBST([PKG_CPPFLAGS], ["${PKG_CPPFLAGS}"])

#
# concluding substitution
#
AC_MSG_NOTICE([Package CPP flags: ${PKG_CPPFLAGS}])
AC_MSG_NOTICE([Package LIBS: ${PKG_LIBS}])

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT
