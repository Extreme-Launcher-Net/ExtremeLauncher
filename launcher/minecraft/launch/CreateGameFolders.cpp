#include "CreateGameFolders.h"

#include <io/stream_reader.h>
#include <io/stream_writer.h>
#include <tag_compound.h>
#include <tag_list.h>
#include <ui/pages/instance/ServersPage.h>

#include <sstream>

#include "FileSystem.h"
#include "launch/LaunchTask.h"
#include "minecraft/MinecraftInstance.h"

CreateGameFolders::CreateGameFolders(LaunchTask* parent) : LaunchStep(parent) {}

// uncommited - start
static std::unique_ptr<nbt::tag_compound> parseServersDat(const QString& filename)
{
    try {
        QByteArray input = FS::read(filename);
        std::istringstream foo(std::string(input.constData(), input.size()));
        auto pair = nbt::io::read_compound(foo);

        if (pair.first != "")
            return nullptr;

        if (pair.second == nullptr)
            return nullptr;

        return std::move(pair.second);
    } catch (...) {
        return nullptr;
    }
}

static bool serializeServerDat(const QString& filename, nbt::tag_compound* levelInfo)
{
    try {
        if (!FS::ensureFilePathExists(filename)) {
            return false;
        }
        std::ostringstream s;
        nbt::io::write_tag("", *levelInfo, s);
        QByteArray val(s.str().data(), (int)s.str().size());
        FS::write(filename, val);
        return true;
    } catch (...) {
        return false;
    }
}
// uncommited - end

void CreateGameFolders::executeTask()
{
    auto instance = m_parent->instance();

    if (!FS::ensureFolderPathExists(instance->gameRoot())) {
        emit logLine("Couldn't create the main game folder", MessageLevel::Error);
        emitFailed(tr("Couldn't create the main game folder"));
        return;
    }

    // HACK: this is a workaround for MCL-3732 - 'server-resource-packs' folder is created.
    if (!FS::ensureFolderPathExists(FS::PathCombine(instance->gameRoot(), "server-resource-packs"))) {
        emit logLine("Couldn't create the 'server-resource-packs' folder", MessageLevel::Error);
    }

    // uncommited - start

    try {
        QString serversDatPath = FS::PathCombine(instance->gameRoot(), "servers.dat");

        nbt::tag_list nbt_server_list;
        QStringList server_list_existing;
        QStringList server_list_new = serverList;

        // load existing
        if (auto serversDat = parseServersDat(serversDatPath)) {
            nbt_server_list = serversDat->at("servers").as<nbt::tag_list>();
        }

        for (auto iter = nbt_server_list.begin(); iter != nbt_server_list.end(); iter++) {
            auto& serverTag = (*iter).as<nbt::tag_compound>();

            std::string addressStr(serverTag["ip"]);
            QString m_address = QString::fromUtf8(addressStr.c_str());
            server_list_existing << m_address;

            qCDebug(taskLogC) << "Found server: " << m_address;

            //Server s(serverTag);
            //servers.append(s);
        }

        // remove existing servers?
        for (const QString& server : server_list_existing) {
            server_list_new.removeAll(server);
        }

        // add new servers
        nbt::tag_list nbt_server_list_new;
        for(const QString& server : server_list_new) {
            nbt::tag_compound nbt_server;
            nbt_server["name"] = "Minecraft Server";
            nbt_server["ip"] = server.toStdString();

            nbt_server_list_new.push_back(std::move(nbt_server));
        }

        // readd old servers
        for (auto iter = nbt_server_list.begin(); iter != nbt_server_list.end(); iter++) {
            auto& nbt_server = (*iter).as<nbt::tag_compound>();
            nbt_server_list_new.push_back(std::move(nbt_server));
        }

        // save file
        nbt::tag_compound out;
        out.insert("servers", nbt::value(std::move(nbt_server_list_new)));

        if (!serializeServerDat(serversDatPath, &out)) {
            qCDebug(taskLogC) << "Failed to save server list:" << serversDatPath << "Will try again.";
        }

    } catch (...) {

    }

    // uncommited - end

    emitSucceeded();
}
