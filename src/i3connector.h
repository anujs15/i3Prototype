#ifndef I3CONNECTOR_H
#define I3CONNECTOR_H

#include <QObject>
#include <QLocalSocket>
#include <QMap>
#include <QString>
#include <QByteArray>
#include <QProcess>

class I3Connector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString keyboardBuffer READ keyboardBuffer NOTIFY keyboardBufferChanged)

public:
    explicit I3Connector(QObject *parent = nullptr);
    ~I3Connector();

    QString keyboardBuffer() const;
    Q_INVOKABLE bool connectToI3();
    Q_INVOKABLE bool disconnectFromI3();

public slots:
    void handleKeySequence(const QString &sequence);
    
signals:
    void keyboardBufferChanged();
    void connectionStatusChanged(bool connected);
    
private slots:
    void readSocket();
    void handleSocketError(QLocalSocket::LocalSocketError socketError);
    
private:
    QLocalSocket *m_socket;
    QString m_socketPath;
    QString m_keyboardBuffer;
    bool m_connected;
    
    QByteArray formatI3Command(const QByteArray &payload, quint32 type);
    void sendCommand(const QByteArray &command);
    void getI3SocketPath();
    
    QMap<QString, QString> m_originalBindings;
    
    enum MessageType {
        RUN_COMMAND = 0,
        GET_WORKSPACES = 1,
        SUBSCRIBE = 2
    };
};

#endif
