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

#ifndef KEYRING_PLUGIN_H
#define KEYRING_PLUGIN_H

#include <QtCore/QObject>
#include <SignOn/ExtensionInterface>

class KeyringPlugin: public QObject, public SignOn::ExtensionInterface3
{
    Q_OBJECT
    Q_INTERFACES(SignOn::ExtensionInterface3)
    #if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.nokia.SingleSignOn.ExtensionInterface/3.0")
    #endif


    public:
        KeyringPlugin(QObject *parent = 0) : QObject(parent)
        {
            setObjectName("kwallet-keyring");
        }

    // reimplemented methods
    SignOn::AbstractSecretsStorage *secretsStorage(QObject *parent = 0) const;
};

#endif // KEYRING_PLUGIN_H

