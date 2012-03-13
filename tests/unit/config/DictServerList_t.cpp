// Klatch - a DICT client for KDE
// Copyright © 2012 Frank S. Thomas <frank@timepit.eu>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "config/DictServerList_t.h"
#include <QCoreApplication>
#include <QFile>
#include <QtTest/QtTest>
#include <KConfig>
#include "config/DictServerList.h"

void test_DictServerList::initTestCase() {
  rcfile_ = QCoreApplication::applicationDirPath()
    + "/test_DictServerList.rc";
}

void test_DictServerList::test_ctor() {
  QFile::remove(rcfile_);
  KConfig config{rcfile_, KConfig::SimpleConfig};

  DictServerList list{&config};
  QCOMPARE(list.rowCount(), 0);
  QCOMPARE(list.columnCount(), 2);
}

void test_DictServerList::test_appendServer() {
  QFile::remove(rcfile_);
  KConfig config{rcfile_, KConfig::SimpleConfig};

  DictServerList list{&config};
  list.appendServer(DictServerItem{"test1", 123});
  QCOMPARE(list.rowCount(), 1);
  QVERIFY(config.group("Dict").hasGroup("Server0"));

  list.appendServer(DictServerItem{"test2", 234});
  QCOMPARE(list.rowCount(), 2);
  QVERIFY(config.group("Dict").hasGroup("Server0"));
}
