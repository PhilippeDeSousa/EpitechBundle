#include "PacketManager.hpp"

PacketManager::PacketType PacketManager::getPacketType(QByteArray &packet)
{
    QString str(packet);
    if (str.startsWith(PacketManager::magicUsername))
        return PacketType::Username;
    else if (str.startsWith(PacketManager::magicSound))
        return PacketType::Sound;
    else
        return PacketType::Other;
}

QByteArray PacketManager::CreateUsernamePacket(QString &username)
{
    QByteArray packet(magicUsername);
    packet.append(username);
    return packet;
}

QByteArray PacketManager::CreateSoundPacket(QString &username, std::vector<unsigned char> &soundData)
{
    QByteArray packet(magicSound);
    packet.append(username);
    packet.append('\0');
    packet.append(reinterpret_cast<const char*>(soundData.data()), soundData.size());
    return packet;
}

bool PacketManager::IsSoundPacketForMe(QByteArray &packet, QString &username)
{
    if (getPacketType(packet) == PacketType::Sound
            && getUsernameFromSoundPacket(packet) == username) {
        return true;
    } else {
        return false;
    }
}

std::vector<unsigned char> *PacketManager::getSoundFromPacket(QByteArray &packet)
{
    if (getPacketType(packet) == PacketType::Sound) {
        for (int i = 0; i < packet.size(); i++) {
            if (packet[i] == '\0')
                return new std::vector<unsigned char>(packet.begin() + i + 1, packet.end());
        }
    }
    return nullptr;
}

QString PacketManager::getUsernameFromUsernamePacket(QByteArray &packet)
{
    if (getPacketType(packet) == PacketType::Username) {
        QString str(packet);
        QRegularExpression re(regexUsernamePacketUsername);
        QRegularExpressionMatch match = re.match(str);
        if (match.hasMatch()) {
            QString res(match.captured(1));
            return res;
        }
    }
    return QString();
}

QString PacketManager::getUsernameFromSoundPacket(QByteArray &packet)
{
    QString str(packet);
    QRegularExpression re(regexSoundPacketUsername);
    QRegularExpressionMatch match = re.match(str);
    if (match.hasMatch()) {
        QString res(match.captured(1));
        return res;
    }
    return QString();
}
