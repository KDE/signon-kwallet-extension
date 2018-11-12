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

#ifndef KEYRING_SECRETS_STORAGE_H
#define KEYRING_SECRETS_STORAGE_H

#include <SignOn/AbstractSecretsStorage>

#include <QByteArray>
#include <QObject>

namespace KWallet {
    class Wallet;
}
class SecretsStorage: public SignOn::AbstractSecretsStorage
{
    Q_OBJECT

public:
    explicit SecretsStorage(QObject *parent = nullptr);
    ~SecretsStorage() override;

    bool initialize(const QVariantMap& configuration) override;
    bool close() override;
    bool clear() override;

    bool updateCredentials(const quint32 id, const QString& username, const QString& password) override;
    bool removeCredentials(const quint32 id) override;
    bool loadCredentials(const quint32 id, QString& username, QString& password) override;

    QVariantMap loadData(quint32 id, quint32 method) override;
    bool storeData(quint32 id, quint32 method, const QVariantMap& data) override;
    bool removeData(quint32 id, quint32 method) override;


    QByteArray m_keyringName;
    KWallet::Wallet* m_wallet;
};

#endif // KEYRING_SECRETS_STORAGE_H
