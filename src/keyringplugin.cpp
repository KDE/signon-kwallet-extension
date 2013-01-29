#include "keyringplugin.h"
#include "secretsstorage.h"

#include <SignOn/AbstractSecretsStorage>

Q_EXPORT_PLUGIN2(KeyringPlugin, KeyringPlugin)

SignOn::AbstractSecretsStorage* KeyringPlugin::secretsStorage(QObject* parent) const
{
    return new SecretsStorage();
}

#include "keyringplugin.moc"