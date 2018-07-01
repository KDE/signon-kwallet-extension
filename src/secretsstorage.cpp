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

#include "secretsstorage.h"

#include <QDataStream>
#include <QDebug>

#include <SignOn/AbstractSecretsStorage>

#include <KWallet>

using namespace SignOn;
using namespace KWallet;

SecretsStorage::SecretsStorage(QObject *parent)
 : AbstractSecretsStorage(parent)
 , m_keyringName()
 , m_wallet(nullptr)
{
}

SecretsStorage::~SecretsStorage()
{
}

bool SecretsStorage::initialize(const QVariantMap &configuration)
{
    m_wallet = Wallet::openWallet(Wallet::NetworkWallet(), 0, Wallet::Synchronous);

    if (!m_wallet || !m_wallet->isOpen() || !m_wallet->isEnabled()) {
        qWarning("Wallet can't be accessed");
        return false;
    }

    if (!m_wallet->hasFolder(QStringLiteral("accounts"))) {
        m_wallet->createFolder(QStringLiteral("accounts"));
    }

    m_wallet->setFolder(QStringLiteral("accounts"));
    setIsOpen(true);
    return true;
}

bool SecretsStorage::close()
{
    if (m_wallet->closeWallet(Wallet::NetworkWallet(), false) == 0) {
        setIsOpen(false);
        return true;
    }

    return false;
}


bool SecretsStorage::clear()
{
    m_wallet->removeFolder(QStringLiteral("accounts"));
    return true;
}

bool SecretsStorage::updateCredentials(const quint32 id,
                                       const QString &username,
                                       const QString &password)
{
    QString sId = QString::number(id);
    if (username.isEmpty() && password.isEmpty()) {
        return false;//Nothing to do
    }

    QMap<QString, QString> map;
    if (m_wallet->readMap(sId, map) != 0) {
        return false;
    }

    if (!username.isEmpty()) {
        map[QStringLiteral("username")] = username;
    }

    if (!password.isEmpty()) {
        map[QStringLiteral("password")] = password;
    }

    return m_wallet->writeMap(sId, map) == 0;
}

bool SecretsStorage::removeCredentials(const quint32 id)
{
    return m_wallet->removeEntry(QString::number(id)) == 0;
}

bool SecretsStorage::loadCredentials(const quint32 id,
                                     QString &username,
                                     QString &password)
{
    QString sId = QString::number(id);
    if (!m_wallet->hasEntry(sId)) {
        return false;
    }

    QMap<QString, QString> map;
    if (m_wallet->readMap(sId, map) != 0) {
        return false;
    }

    username = map[QStringLiteral("username")];
    password = map[QStringLiteral("password")];

    return true;
}

QVariantMap SecretsStorage::loadData(quint32 id, quint32 method)
{
    QString sId = QString::number(id);
    sId.append(QLatin1Char('/') + QString::number(method));

    QVariantMap data;
    if (!m_wallet->hasEntry(sId)) {
        return data;
    }

    QByteArray binaryData;
    if (m_wallet->readEntry(sId, binaryData) != 0) {
        return data;
    }

    QDataStream stream(binaryData);
    stream >> data;
    return data;
}

bool SecretsStorage::storeData(quint32 id, quint32 method,
                               const QVariantMap &data)
{
    QString sId = QString::number(id);
    sId.append(QLatin1Char('/') + QString::number(method));

    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << data;


    return m_wallet->writeEntry(sId, serializedData) == 0;
}

bool SecretsStorage::removeData(quint32 id, quint32 method)
{
    QString sId = QString::number(id);
    sId.append(QLatin1Char('/') + QString::number(method));

    return m_wallet->removeEntry(sId) == 0;
}
