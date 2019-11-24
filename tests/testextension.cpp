/*************************************************************************************
 *  Copyright (C) 2013 by Alejandro Fiestas Olivares <afiestas@kde.org>              *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#include <QTest>
#include <QObject>

#include "../src/keyringplugin.h"
#include "../src/secretsstorage.h"

class testExtension : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void testUpdateLoadRemoveCredentials();
    void testStoreLoadAndRemoveData();

private:
    SecretsStorage *m_storage;
};

void testExtension::initTestCase()
{
    KeyringPlugin *plugin = new KeyringPlugin(this);
    m_storage = qobject_cast<SecretsStorage *>(plugin->secretsStorage(0));
    QVERIFY2(m_storage, "SecretsStorage pointer is null");
    QCOMPARE(m_storage->initialize(QVariantMap()), true);
}

void testExtension::testUpdateLoadRemoveCredentials()
{
    QString user, password;
    QVERIFY(m_storage->updateCredentials(42, "testUser", "testPassword"));
    QVERIFY(m_storage->loadCredentials(42, user, password));
    QCOMPARE(user, QString("testUser"));
    QCOMPARE(password, QString("testPassword"));
    QVERIFY(m_storage->removeCredentials(42));

    user = "";
    password = "";
    QVERIFY(!m_storage->loadCredentials(42, user, password));
    QCOMPARE(user, QString());
    QCOMPARE(password, QString());

    m_storage->updateCredentials(44, "user44", "pass44");
    m_storage->updateCredentials(43, "user43", "pass43");
    m_storage->clear();

    QVERIFY(!m_storage->loadCredentials(43, user, password));
    QCOMPARE(user, QString());
    QCOMPARE(password, QString());

    QVERIFY(!m_storage->loadCredentials(44, user, password));
    QCOMPARE(user, QString());
    QCOMPARE(password, QString());
}

void testExtension::testStoreLoadAndRemoveData()
{
    QVariantMap data;
    data["int"] = 4;
    data["string"] = QString("string");
    data["bool"] = false;

    QVERIFY(m_storage->storeData(43, 2, data));

    data = m_storage->loadData(43, 2);
    QCOMPARE(data["int"].toInt(), 4);
    QCOMPARE(data["string"].toString(), QString("string"));
    QCOMPARE(data["bool"].toBool(), false);

    QVERIFY(m_storage->removeData(43, 2));

}

QTEST_MAIN(testExtension)

#include "testextension.moc"
