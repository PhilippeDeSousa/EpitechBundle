#ifndef PACKETMANAGER_HPP
#define PACKETMANAGER_HPP


#include <QString>
#include <QByteArray>
#include <vector>
#include <QRegularExpression>

class PacketManager
{
public:
    /// Magic bytes for a username packet
    static constexpr char magicUsername[] = "Username:";
    /// Used to capture the username from the sound packet
    static constexpr char regexUsernamePacketUsername[] = "Username:(.+)";
    /// Magic bytes for a sound packet
    static constexpr char magicSound[] = "Sound:";
    /// Used to capture the username from the username packet
    static constexpr char regexSoundPacketUsername[] = "Sound:(.+)";

    /// There are 2 packet types,
    /// the ones that are used to create the username list,
    /// and the sound packets
    enum PacketType {
        Username,
        Sound,
        Other
    };
    static PacketType getPacketType(QByteArray &packet);
    /// Username packet is:
    /// MagicUsername + my username
    static QByteArray CreateUsernamePacket(QString &username);
    /// Sound packet is:
    /// MagicSound + my username + '\0' + sound
    static QByteArray CreateSoundPacket(QString &username, std::vector<unsigned char> &soundData);
    /// returns true if it is a sound packet and it is for the username
    static bool IsSoundPacketForMe(QByteArray &packet, QString &username);
    /// returns nullptr if there is no data
    static std::vector<unsigned char> *getSoundFromPacket(QByteArray &packet);
    /// returns empty string if error
    static QString getUsernameFromUsernamePacket(QByteArray &packet);

private:
    /// returns an empty string if the regex doesn't match
    static QString getUsernameFromSoundPacket(QByteArray &packet);

};

#endif // PACKETMANAGER_HPP
