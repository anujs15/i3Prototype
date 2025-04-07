#include "i3connector.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

I3Connector::I3Connector(QObject *parent)
    : QObject(parent)
    , m_socket(new QLocalSocket(this))
    , m_socketPath("")
    , m_keyboardBuffer("")
    , m_connected(false)
{
    getI3SocketPath();
    connect(m_socket, &QLocalSocket::readyRead, this, &I3Connector::readSocket);
    connect(m_socket, &QLocalSocket::errorOccurred, this, &I3Connector::handleSocketError);
}

I3Connector::~I3Connector()
{
    if (m_connected)
        disconnectFromI3();
        
    if (m_socket) {
        m_socket->disconnectFromServer();
        delete m_socket;
    }
}

QString I3Connector::keyboardBuffer() const
{
    return m_keyboardBuffer;
}

bool I3Connector::connectToI3()
{
    if (m_socketPath.isEmpty()) {
        qWarning() << "Cannot connect to i3: socket path not found";
        return false;
    }
    
    if (m_connected) {
        qDebug() << "Already connected to i3";
        return true;
    }
    
    qDebug() << "Connecting to i3 socket at" << m_socketPath;
    m_socket->connectToServer(m_socketPath);
    
    if (!m_socket->waitForConnected(1000)) {
        qWarning() << "Failed to connect to i3 socket:" << m_socket->errorString();
        return false;
    }
    
    QByteArray getModesCmd = formatI3Command(QByteArray(""), GET_WORKSPACES);
    sendCommand(getModesCmd);
    
    QProcess process;
    process.start("i3-msg", QStringList() << "-t" << "get_config");
    process.waitForFinished();
    QString config = QString::fromUtf8(process.readAllStandardOutput());
    
    QStringList lines = config.split('\n');
    for (const QString &line : lines) {
        if (line.contains("bindsym") || line.contains("bindcode")) {
            QString trimmed = line.trimmed();
            QString key = trimmed.mid(0, trimmed.indexOf(' '));
            if (!trimmed.isEmpty()) {
                m_originalBindings.insert(trimmed, trimmed);
                qDebug() << "Stored binding:" << trimmed;
            }
        }
    }
    
    QByteArray createEmptyModeCmd = formatI3Command(QByteArray("mode \"keyboard_interceptor\""), RUN_COMMAND);
    sendCommand(createEmptyModeCmd);
    
    QByteArray switchModeCmd = formatI3Command(QByteArray("mode keyboard_interceptor"), RUN_COMMAND);
    sendCommand(switchModeCmd);
    
    QByteArray hideBarCmd = formatI3Command(QByteArray("bar mode hide"), RUN_COMMAND);
    sendCommand(hideBarCmd);
    
    m_connected = true;
    emit connectionStatusChanged(m_connected);
    qDebug() << "Successfully connected to i3 and disabled all keybindings";
    return true;
}

bool I3Connector::disconnectFromI3()
{
    if (!m_connected) {
        qDebug() << "Not connected to i3";
        return true;
    }
    
    QByteArray defaultModeCmd = formatI3Command(QByteArray("mode default"), RUN_COMMAND);
    sendCommand(defaultModeCmd);
    
    QByteArray showBarCmd = formatI3Command(QByteArray("bar mode dock"), RUN_COMMAND);
    sendCommand(showBarCmd);
    
    m_socket->disconnectFromServer();
    m_connected = false;
    emit connectionStatusChanged(m_connected);
    qDebug() << "Disconnected from i3 and restored keybindings";
    return true;
}

void I3Connector::handleKeySequence(const QString &sequence)
{
    m_keyboardBuffer = sequence;
    emit keyboardBufferChanged();
    qDebug() << "Key sequence intercepted:" << sequence;
}

void I3Connector::readSocket()
{
    QByteArray data = m_socket->readAll();
    
    if (data.size() < 14) {
        qWarning() << "Received incomplete i3 message header";
        return;
    }
    
    char magic[6];
    memcpy(magic, data.constData(), 6);
    
    if (memcmp(magic, "i3-ipc", 6) != 0) {
        qWarning() << "Received invalid i3 message (wrong magic bytes)";
        return;
    }
    
    quint32 length, type;
    memcpy(&length, data.constData() + 6, 4);
    memcpy(&type, data.constData() + 10, 4);
    
    if (data.size() < 14 + length) {
        qWarning() << "Received incomplete i3 message payload";
        return;
    }
    
    QByteArray payload = data.mid(14, length);
    
    switch (type) {
        case GET_WORKSPACES:
            qDebug() << "Received workspace info:" << payload;
            break;
        case RUN_COMMAND:
            qDebug() << "Command result:" << payload;
            break;
        default:
            qDebug() << "Received unknown message type:" << type;
    }
}

void I3Connector::handleSocketError(QLocalSocket::LocalSocketError socketError)
{
    qWarning() << "i3 socket error:" << m_socket->errorString();
    m_connected = false;
    emit connectionStatusChanged(m_connected);
}

QByteArray I3Connector::formatI3Command(const QByteArray &payload, quint32 type)
{
    QByteArray command;
    command.append("i3-ipc");
    
    quint32 length = payload.length();
    command.append(reinterpret_cast<const char*>(&length), 4);
    command.append(reinterpret_cast<const char*>(&type), 4);
    command.append(payload);
    
    return command;
}

void I3Connector::sendCommand(const QByteArray &command)
{
    if (!m_connected) {
        qWarning() << "Cannot send command: not connected to i3";
        return;
    }
    
    m_socket->write(command);
    if (!m_socket->waitForBytesWritten(1000)) {
        qWarning() << "Failed to send command to i3:" << m_socket->errorString();
    }
}

void I3Connector::getI3SocketPath()
{
    QString socketPath = qgetenv("I3SOCK");
    
    if (!socketPath.isEmpty()) {
        m_socketPath = socketPath;
        qDebug() << "Found i3 socket path from environment:" << m_socketPath;
        return;
    }
    
    QProcess process;
    process.start("i3", QStringList() << "--get-socketpath");
    process.waitForFinished();
    socketPath = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    
    if (!socketPath.isEmpty()) {
        m_socketPath = socketPath;
        qDebug() << "Found i3 socket path from i3 command:" << m_socketPath;
        return;
    }
    
    qWarning() << "Failed to find i3 socket path";
}