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

#include "utility/string_t.h"
#include <QString>
#include <QStringList>
#include <QtTest/QtTest>
#include "utility/string.h"

void test_string::test_split_arguments() {
  QFETCH(QString, input);
  QFETCH(QStringList, result);

  QCOMPARE(split_arguments(input), result);
}

void test_string::test_split_arguments_data() {
  QTest::addColumn<QString>("input");
  QTest::addColumn<QStringList>("result");

  QTest::newRow("one quoted string") << "one two"
    << (QStringList() << "one" << "two");
  QTest::newRow("one quoted string") << "'one' two"
    << (QStringList() << "one" << "two");
  QTest::newRow("one quoted string") << "\"one\" two"
    << (QStringList() << "one" << "two");

  QTest::newRow("two quoted strings") << "\"one\" 'two' 3"
    << (QStringList() << "one" << "two" << "3");
  QTest::newRow("two quoted strings") << "one \"two\" '3'"
    << (QStringList() << "one" << "two" << "3");
  QTest::newRow("two quoted strings") << "'one' two \"3\""
    << (QStringList() << "one" << "two" << "3");

  QTest::newRow("spaces in quotes") << " one \"two 3\""
    << (QStringList() << "one" << "two 3");
  QTest::newRow("spaces in quotes") << "\"one two 3\""
    << (QStringList() << "one two 3");
  QTest::newRow("spaces in quotes") << " \"one two\"  3  "
    << (QStringList() << "one two" << "3");

  QTest::newRow("quotes in quotes") << "\"one 'two'\"  3"
    << (QStringList() << "one 'two'" << "3");
  QTest::newRow("quotes in quotes") << "\"'one' 'two'\" 3"
    << (QStringList() << "'one' 'two'" << "3");
  QTest::newRow("quotes in quotes") << "\"'one  two'\" 3"
    << (QStringList() << "'one  two'" << "3");

  QTest::newRow("escaped sq") << "'one\\'two' 3"
    << (QStringList() << "one\\'two" << "3");
  QTest::newRow("escaped dq") << "\"one \\\" two\" 3"
    << (QStringList() << "one \\\" two" << "3");
}

void test_string::test_trimmed_left() {
  QFETCH(QString, input);
  QFETCH(QString, result);

  QCOMPARE(trimmed_left(input), result);
}

void test_string::test_trimmed_left_data() {
  QTest::addColumn<QString>("input");
  QTest::addColumn<QString>("result");

  QTest::newRow("no space") << "test" << "test";
  QTest::newRow("one space") << " test" << "test";
  QTest::newRow("two spaces") << "  test" << "test";

  QTest::newRow("one tab") << "\t test" << "test";
  QTest::newRow("two tabs") << "\t\t test" << "test";

  QTest::newRow("CR LF") << "\r\n test" << "test";
  QTest::newRow("LF CR") << "\n\r test" << "test";

  QTest::newRow("one trailing space") << "test " << "test ";
  QTest::newRow("two trailing spaces") << "test  " << "test  ";
  QTest::newRow("trailing CR LF") << "test\r\n" << "test\r\n";
}
