#
# Copyright (C) 2015 Ultramarin design AB <info@ultramarin.se>
#
# This file is part of ultralog.
#
# ultralog is free software; you can redistribute it and/or modify it
# under the terms of the GNU Affero General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
lib_LTLIBRARIES = libultralog.la

libultralog_la_CPPFLAGS = -I$(srcdir)/include -I./include
libultralog_la_LDFLAGS =

libultralog_la_CXXFLAGS = -Wall -pipe -std=c++11 -g -O2


# CURRENT : REVISION : AGE
libultralog_la_LDFLAGS += -version-info @LIBRARY_VERSION@


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ultralog.pc


# Source files
libultralog_la_SOURCES  =
libultralog_la_SOURCES += ultralog.cpp

# Header files
libultralogdir = $(includedir)
nobase_libultralog_HEADERS =
nobase_libultralog_HEADERS += ultralog.hpp
#nobase_libultralog_HEADERS += ultralog/ultralog.hpp

# Header files that is not to be installed
#noinst_HEADERS = not_included_in_installation.hpp
