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
    SecretsStorage(QObject *parent = nullptr);
    ~SecretsStorage();

    bool initialize(const QVariantMap& configuration) Q_DECL_OVERRIDE;
    bool close() Q_DECL_OVERRIDE;
    bool clear() Q_DECL_OVERRIDE;

    bool updateCredentials(const quint32 id, const QString& username, const QString& password) Q_DECL_OVERRIDE;
    bool removeCredentials(const quint32 id) Q_DECL_OVERRIDE;
    bool loadCredentials(const quint32 id, QString& username, QString& password) Q_DECL_OVERRIDE;

    QVariantMap loadData(quint32 id, quint32 method) Q_DECL_OVERRIDE;
    bool storeData(quint32 id, quint32 method, const QVariantMap& data) Q_DECL_OVERRIDE;
    bool removeData(quint32 id, quint32 method) Q_DECL_OVERRIDE;


    QByteArray m_keyringName;
    KWallet::Wallet* m_wallet;
};

#endif // KEYRING_SECRETS_STORAGE_H
