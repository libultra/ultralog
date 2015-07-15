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

if ENABLE_TESTAPPS_SET

AM_CXXFLAGS = -pipe -Wall -std=c++11 -I$(srcdir)/../src
LDADD = -L../src -lultralog


noinst_bindir =
noinst_bin_PROGRAMS =

noinst_bin_PROGRAMS += test_log
test_log_SOURCES    = test_log.cpp

endif
