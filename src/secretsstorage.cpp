/* -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the GNOME-keyring signond extension
 *
 * Copyright (C) 2011 Canonical Ltd.
 *
 * Contact: Alberto Mardegan <alberto.mardegan@canonical.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#include "secretsstorage.h"

#include <QDataStream>
#include <QtCore/QDebug>

#include <SignOn/AbstractSecretsStorage>

#include <KWallet/Wallet>

using namespace SignOn;
using namespace KWallet;

SecretsStorage::SecretsStorage(QObject *parent)
 : AbstractSecretsStorage(parent)
 , m_keyringName()
 , m_wallet(0)
{
    qDebug() << "Constructed";
}

SecretsStorage::~SecretsStorage()
{
    qDebug() << "Destroyed";
}

bool SecretsStorage::initialize(const QVariantMap &configuration)
{
    m_wallet = Wallet::openWallet(Wallet::NetworkWallet(), 0, Wallet::Synchronous);

    if (!m_wallet || !m_wallet->isOpen() || !m_wallet->isEnabled()) {
        qWarning("Wallet can't be accessed");
        return false;
    }

    if (!m_wallet->hasFolder("accounts")) {
        m_wallet->createFolder("accounts");
    }

    m_wallet->setFolder("accounts");
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
    m_wallet->removeFolder("accounts");
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
        map["username"] = username;
    }

    if (!password.isEmpty()) {
        map["password"] = password;
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

    if (!map.contains("username") || !map.contains("password")) {
        return false;
    }

    username = map["username"];
    password = map["password"];

    return true;
}

QVariantMap SecretsStorage::loadData(quint32 id, quint32 method)
{
    QString sId = QString::number(id);
    sId.append(+ "/" + QString::number(method));

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
    sId.append(+ "/" + QString::number(method));

    QByteArray serializedData;
    QDataStream stream(&serializedData, QIODevice::WriteOnly);
    stream << data;


    return m_wallet->writeEntry(sId, serializedData) == 0;
}

bool SecretsStorage::removeData(quint32 id, quint32 method)
{
    QString sId = QString::number(id);
    sId.append(+ "/" + QString::number(method));

    return m_wallet->removeEntry(sId) == 0;
}

bool SecretsStorage::storeSecret(SignonSecretType type,
                                 quint32 id,
                                 quint32 method,
                                 const QByteArray &secret)
{
//     GnomeKeyringResult ret;
//     guint32 createdItemId;
//
//     qDebug() << "Storing secret:" << id <<
//     "type:" << type <<
//     "method:" << method;
//
//     GnomeKeyringAttributeList *attributes = gnome_keyring_attribute_list_new();
//     gnome_keyring_attribute_list_append_uint32(attributes, "signon-type", type);
//     gnome_keyring_attribute_list_append_uint32(attributes, "signon-id", id);
//     if (type == Data) {
//         gnome_keyring_attribute_list_append_uint32(attributes,
//                                                    "signon-method", method);
//     }
//
//     QString displayName =
//     QString::fromLatin1("Ubuntu Web Account: id %1-%2").arg(id).arg(type);
//     QByteArray ba = displayName.toUtf8();
//
//     ret = gnome_keyring_item_create_sync(keyring(),
//                                          GNOME_KEYRING_ITEM_GENERIC_SECRET,
//                                          ba.constData(),
//                                          attributes,
//                                          secret.constData(),
//                                          TRUE,
//                                          &createdItemId);
//     gnome_keyring_attribute_list_free(attributes);
//     if (ret != GNOME_KEYRING_RESULT_OK) {
//         qDebug() << "Got error from GNOME keyring:" << ret;
//         return false;
//     }
//
//     Q_UNUSED(createdItemId);
    return true;
}

bool SecretsStorage::loadSecret(SignonSecretType type,
                                quint32 id,
                                quint32 method,
                                QByteArray &secret)
{
//     GList *found = 0;
//     GnomeKeyringResult ret;
//
//     qDebug() << "id:" << id << "type:" << type << "method:" << method;
//     GnomeKeyringAttributeList *attributes = gnome_keyring_attribute_list_new();
//     gnome_keyring_attribute_list_append_uint32(attributes, "signon-type", type);
//     gnome_keyring_attribute_list_append_uint32(attributes, "signon-id", id);
//     if (type == Data) {
//         gnome_keyring_attribute_list_append_uint32(attributes, "signon-method",
//                                                    method);
//     }
//
//     ret = gnome_keyring_find_items_sync(GNOME_KEYRING_ITEM_GENERIC_SECRET,
//                                         attributes,
//                                         &found);
//     gnome_keyring_attribute_list_free(attributes);
//     if (ret != GNOME_KEYRING_RESULT_OK) {
//         qDebug() << "Credentials loading failed:" << ret;
//         return false;
//     }
//
//     for (GList *list = found; list != 0; list = list->next) {
//         GnomeKeyringFound *result = (GnomeKeyringFound *)list->data;
//
//         if (!isActiveKeyring(result->keyring))
//             continue;
//
//         GnomeKeyringItemInfo *info;
//         ret = gnome_keyring_item_get_info_sync(result->keyring,
//                                                result->item_id,
//                                                &info);
//         if (ret != GNOME_KEYRING_RESULT_OK) {
//             qDebug() << "Error loading credentials:" << ret;
//             break;
//         }
//
//         gchar *data = gnome_keyring_item_info_get_secret(info);
//         secret = QByteArray(data);
//         g_free(data);
//         gnome_keyring_item_info_free(info);
//     }
//     gnome_keyring_found_list_free(found);
//
//     return ret == GNOME_KEYRING_RESULT_OK;
    return true;
}

bool SecretsStorage::removeSecrets(SignonSecretType type,
                                   quint32 id,
                                   quint32 method,
                                   QueryFields fields)
{
//     GList *found = 0;
//     GnomeKeyringResult ret;
//
//     GnomeKeyringAttributeList *attributes = gnome_keyring_attribute_list_new();
//     if (fields & IdField) {
//         gnome_keyring_attribute_list_append_uint32(attributes,
//                                                    "signon-id", id);
//     }
//     if (fields & MethodField) {
//         gnome_keyring_attribute_list_append_uint32(attributes,
//                                                    "signon-method", method);
//     }
//     if (fields & TypeField) {
//         gnome_keyring_attribute_list_append_uint32(attributes,
//                                                    "signon-type", type);
//     }
//
//     ret = gnome_keyring_find_items_sync(GNOME_KEYRING_ITEM_GENERIC_SECRET,
//                                         attributes,
//                                         &found);
//     if (ret != GNOME_KEYRING_RESULT_OK) {
//         if (ret == GNOME_KEYRING_RESULT_NO_MATCH) {
//             return true;
//         }
//         qDebug() << "Credentials search failed:" << ret;
//         return false;
//     }
//
//     for (GList *list = found; list != 0; list = list->next) {
//         GnomeKeyringFound *result = (GnomeKeyringFound *)list->data;
//
//         if (!isActiveKeyring(result->keyring))
//             continue;
//
//         ret = gnome_keyring_item_delete_sync(result->keyring, result->item_id);
//         if (ret != GNOME_KEYRING_RESULT_OK) {
//             qDebug() << "Error deleting credentials:" << ret;
//             break;
//         }
//     }
//     gnome_keyring_found_list_free(found);

//     return ret == GNOME_KEYRING_RESULT_OK;
    return true;
}

const char *SecretsStorage::keyring() const
{
//     return m_keyringName.isEmpty() ? 0 : m_keyringName.constData();
    return "a";
}

bool SecretsStorage::isActiveKeyring(const char *keyringName) const
{
//     /* This method is needed not to apply the same hack in different parts of
//      * the code.
//      */
//     const gchar *activeKeyringName = keyring();
//     if (qstrcmp(keyringName, activeKeyringName) == 0)
//         return true;
//
//     /* Unfortunately GNOME keyring doesn't return the proper name of the
//      * default keyring (it returns NULL). This means that if the active
//      * keyring is the default keyring the above string comparison would fail.
//      * In other words, if the current keyring is NULL, we have no clue on what
//      * to return from this method.
//      * https://bugzilla.gnome.org/show_bug.cgi?id=664454
//      *
//      * If the current keyring is NULL, we just return true.
//      */
//     if (activeKeyringName == 0) {
//         return true;
//     } else {
//         return false;
//     }
    return true;
}

#include "secretsstorage.moc"