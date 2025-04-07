#ifndef KEYBOARDINTERCEPTOR_H
#define KEYBOARDINTERCEPTOR_H

#include <QObject>
#include <QEvent>
#include <QGuiApplication>
#include <QWindow>
#include <QKeyEvent>
#include <QDebug>

class KeyboardInterceptor : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool active READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QString currentKey READ currentKey NOTIFY currentKeyChanged)
    
public:
    explicit KeyboardInterceptor(QObject *parent = nullptr);
    ~KeyboardInterceptor();

    bool isActive() const;
    void setActive(bool active);
    QString currentKey() const;

public slots:
    Q_INVOKABLE bool startIntercepting();
    Q_INVOKABLE bool stopIntercepting();
    Q_INVOKABLE void clearBuffer();

signals:
    void activeChanged();
    void currentKeyChanged();
    void keySequenceIntercepted(const QString &sequence);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QString keyEventToString(QKeyEvent *keyEvent);
    bool m_active;
    QString m_currentKey;
    QString m_keyBuffer;
};

#endif
