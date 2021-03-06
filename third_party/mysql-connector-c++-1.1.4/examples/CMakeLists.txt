#
# Copyright (c) 2008, 2014, Oracle and/or its affiliates. All rights reserved.
#
# The MySQL Connector/C++ is licensed under the terms of the GPLv2
# <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>, like most
# MySQL Connectors. There are special exceptions to the terms and
# conditions of the GPLv2 as it is applied to this software, see the
# FLOSS License Exception
# <http://www.mysql.com/about/legal/licensing/foss-exception.html>.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation; version 2 of the License.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
#


SET(CMAKE_VERBOSE_MAKEFILE 0)



SET(MYSQLCPPCONN_BUILD_EXAMPLES 1 CACHE BOOL "build-examples")
IF(MYSQLCPPCONN_BUILD_EXAMPLES)
	INCLUDE_DIRECTORIES(${MYSQLCPPCONN_SOURCE_DIR})
	LINK_DIRECTORIES(${MYSQLCPPCONN_SOURCE_DIR}/cppconn)

	IF(WIN32)
		INCLUDE_DIRECTORIES(${MYSQLCPPCONN_SOURCE_DIR/cppconn})

		IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
			LINK_DIRECTORIES(${MYSQL_DIR}/lib/debug)
		ELSEIF(CMAKE_BUILD_TYPE STREQUAL "")
			LINK_DIRECTORIES(${MYSQL_DIR}/lib/opt)
		ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")

		ADD_DEFINITIONS("-D_SCL_SECURE_NO_WARNINGS")

    SET(MY_TARGET_LINK_LIBRARIES mysqlcppconn)
    IF(MYSQLCLIENT_STATIC_BINDING)
      SET(MY_TARGET_LINK_LIBRARIES ${MY_TARGET_LINK_LIBRARIES})
    ENDIF(MYSQLCLIENT_STATIC_BINDING)

    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
    FIND_LIBRARY(MYSQLCPPCONN_DYNLOAD_MYSQL_LIB
      NAMES 
        libmysql
      PATHS
        ${MYSQL_LIB_DIR}
        ${MYSQL_LIB_DIR}/lib/${libsuffixDist}
        ${MYSQL_LIB_DIR}/lib  #mysqlclient may be in lib for some c/c distros
        ${MYSQL_LIB_DIR}/libmysql/${libsuffixBuild}
        ${MYSQL_LIB_DIR}/client/${libsuffixBuild}
        $ENV{MYSQL_LIB_DIR}
        $ENV{MYSQL_LIB_DIR}/lib/${libsuffixDist}
        $ENV{MYSQL_LIB_DIR}/lib  #mysqlclient may be in lib for some c/c distros
        $ENV{MYSQL_LIB_DIR}/libmysql/${libsuffixBuild}
        $ENV{MYSQL_LIB_DIR}/client/${libsuffixBuild}
        $ENV{MYSQL_DIR}/lib/${libsuffixDist}
        $ENV{MYSQL_DIR}/lib  #mysqlclient may be in lib for some c/c distros
        $ENV{MYSQL_DIR}/libmysql/${libsuffixBuild}
        $ENV{MYSQL_DIR}/client/${libsuffixBuild}
        $ENV{ProgramFiles}/MySQL/*/lib/${libsuffixDist}
        $ENV{ProgramFiles}/MySQL/*/lib
        $ENV{SystemDrive}/MySQL/*/lib/${libsuffixDist}
        $ENV{SystemDrive}/MySQL/*/lib)

	ELSEIF(NOT WIN32)
		SET(MY_TARGET_LINK_LIBRARIES mysqlcppconn-static)
    IF(MYSQLCLIENT_STATIC_BINDING)
      SET(MY_TARGET_LINK_LIBRARIES ${MY_TARGET_LINK_LIBRARIES})
    ENDIF(MYSQLCLIENT_STATIC_BINDING)
    FIND_LIBRARY(MYSQLCPPCONN_DYNLOAD_MYSQL_LIB
      NAMES 
        libmysqlclient_r.so
        libmysqlclient.so
      PATHS
        ${MYSQL_LIB_DIR}
        ${MYSQL_LIB_DIR}/libmysql_r/.libs
        ${MYSQL_LIB_DIR}/lib
        ${MYSQL_LIB_DIR}/lib/mysql
        $ENV{MYSQL_LIB_DIR}
        $ENV{MYSQL_LIB_DIR}/libmysql_r/.libs
        $ENV{MYSQL_LIB_DIR}/lib
        $ENV{MYSQL_LIB_DIR}/lib/mysql
        $ENV{MYSQL_DIR}/libmysql_r/.libs
        $ENV{MYSQL_DIR}/lib
        $ENV{MYSQL_DIR}/lib/mysql
        ${MYSQL_CLIB_DIR}
        ${MYSQL_CLIB_DIR}/libmysql_r/.libs
        ${MYSQL_CLIB_DIR}/lib
        ${MYSQL_CLIB_DIR}/lib/mysql
        /usr/lib/mysql
        /usr/local/lib/mysql
        /usr/local/mysql/lib
        /usr/local/mysql/lib/mysql
        /opt/mysql/mysql/lib
        /opt/mysql/mysql/lib/mysql)
	ENDIF(WIN32)

  ADD_DEFINITIONS("-DDYNLOAD_MYSQL_LIB=\"${MYSQLCPPCONN_DYNLOAD_MYSQL_LIB}\"")
  MESSAGE(STATUS "MySQL dynamic load test library: ${MYSQLCPPCONN_DYNLOAD_MYSQL_LIB}")

	IF(CMAKE_COMPILER_IS_GNUCC AND MYSQLCPPCONN_GCOV_ENABLE)
		SET(MY_GCOV_LINK_LIBRARIES gcov)
	ENDIF(CMAKE_COMPILER_IS_GNUCC AND MYSQLCPPCONN_GCOV_ENABLE)

	ADD_EXECUTABLE(connect connect.cpp)
	SET_TARGET_PROPERTIES(connect PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(connect ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(connection_meta_schemaobj connection_meta_schemaobj.cpp)
	SET_TARGET_PROPERTIES(connection_meta_schemaobj PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(connection_meta_schemaobj ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(debug_output debug_output.cpp)
	SET_TARGET_PROPERTIES(debug_output PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(debug_output ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(exceptions exceptions.cpp)
	SET_TARGET_PROPERTIES(exceptions PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(exceptions ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(prepared_statement prepared_statement.cpp)
	SET_TARGET_PROPERTIES(prepared_statement PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(prepared_statement ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(resultset resultset.cpp)
	SET_TARGET_PROPERTIES(resultset PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(resultset ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(resultset_binary resultset_binary.cpp)
	SET_TARGET_PROPERTIES(resultset_binary PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(resultset_binary ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})


	ADD_EXECUTABLE(resultset_meta resultset_meta.cpp)
	SET_TARGET_PROPERTIES(resultset_meta PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(resultset_meta ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(resultset_types resultset_types.cpp)
	SET_TARGET_PROPERTIES(resultset_types PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(resultset_types ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(statement statement.cpp)
	SET_TARGET_PROPERTIES(statement PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(statement ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

	ADD_EXECUTABLE(dynamic_load dynamic_load.cpp)
	SET_TARGET_PROPERTIES(dynamic_load PROPERTIES
						LINK_FLAGS "${MYSQLCPPCONN_LINK_FLAGS_ENV} ${MYSQL_LINK_FLAGS}"
						COMPILE_FLAGS "${MYSQLCPPCONN_COMPILE_FLAGS_ENV} ${MYSQL_CXXFLAGS}")
	TARGET_LINK_LIBRARIES(dynamic_load ${MY_TARGET_LINK_LIBRARIES} ${MY_GCOV_LINK_LIBRARIES}
						  ${MYSQLCPPCONN_BOOST_SYSTEM_LIBS}
						  ${MYSQLCPPCONN_BOOST_THREAD_LIBS} ${MYSQLCPPCONN_ICU_LIBRARY})

ENDIF(MYSQLCPPCONN_BUILD_EXAMPLES)

MESSAGE(STATUS "Configuring examples")
