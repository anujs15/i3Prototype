#include "keyboardinterceptor.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QWindow>

KeyboardInterceptor::KeyboardInterceptor(QObject *parent)
    : QObject(parent)
    , m_active(false)
    , m_currentKey("")
    , m_keyBuffer("")
{
    QObject* i3Connector = parent->findChild<QObject*>("i3Connector");
    if (i3Connector) {
        connect(this, SIGNAL(keySequenceIntercepted(QString)),
                i3Connector, SLOT(handleKeySequence(QString)));
    }
}

KeyboardInterceptor::~KeyboardInterceptor()
{
    stopIntercepting();
}

bool KeyboardInterceptor::isActive() const
{
    return m_active;
}

void KeyboardInterceptor::setActive(bool active)
{
    if (m_active == active)
        return;
        
    if (active)
        startIntercepting();
    else
        stopIntercepting();
}

QString KeyboardInterceptor::currentKey() const
{
    return m_currentKey;
}

bool KeyboardInterceptor::startIntercepting()
{
    if (m_active)
        return true;
        
    qApp->installEventFilter(this);
    
    for (QWindow* window : QGuiApplication::allWindows()) {
        window->installEventFilter(this);
    }
    
    m_active = true;
    emit activeChanged();
    
    for (QWindow* window : QGuiApplication::allWindows()) {
        if (window->isVisible()) {
            window->setKeyboardGrabEnabled(true);
        }
    }
    
    qDebug() << "Keyboard interception started with enhanced protection";
    return true;
}

bool KeyboardInterceptor::stopIntercepting()
{
    if (!m_active)
        return true;
        
    for (QWindow* window : QGuiApplication::allWindows()) {
        if (window->isVisible()) {
            window->setKeyboardGrabEnabled(false);
        }
    }
    
    qApp->removeEventFilter(this);
    for (QWindow* window : QGuiApplication::allWindows()) {
        window->removeEventFilter(this);
    }
    
    m_active = false;
    emit activeChanged();
    
    qDebug() << "Keyboard interception stopped";
    return true;
}

void KeyboardInterceptor::clearBuffer()
{
    m_currentKey = "";
    m_keyBuffer = "";
    emit currentKeyChanged();
}

bool KeyboardInterceptor::eventFilter(QObject *obj, QEvent *event)
{
    if (!m_active)
        return QObject::eventFilter(obj, event);
    
    if (event->type() == QEvent::KeyPress || 
        event->type() == QEvent::KeyRelease || 
        event->type() == QEvent::ShortcutOverride) {
        
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        
        if (keyEvent->key() == Qt::Key_Escape) {
            if (event->type() == QEvent::KeyPress && !keyEvent->isAutoRepeat()) {
                qDebug() << "ESC key pressed - closing application";
                QCoreApplication::quit();
            }
            return false;
        }
        
        if (event->type() == QEvent::KeyPress && !keyEvent->isAutoRepeat()) {
            QString keyText = keyEventToString(keyEvent);
            m_currentKey = keyText;
            
            if (!m_keyBuffer.isEmpty()) {
                m_keyBuffer += " ";
            }
            m_keyBuffer += keyText;
            
            if (m_keyBuffer.length() > 100) {
                m_keyBuffer = m_keyBuffer.right(100);
            }
            
            emit currentKeyChanged();
            emit keySequenceIntercepted(keyText);
            
            qDebug() << "Intercepted key press:" << keyText;
        }
        else if (event->type() == QEvent::KeyRelease && !keyEvent->isAutoRepeat()) {
            QString releasedKey = keyEventToString(keyEvent);
            qDebug() << "Key released:" << releasedKey;
        }
        
        return true;
    }
    
    return QObject::eventFilter(obj, event);
}

QString KeyboardInterceptor::keyEventToString(QKeyEvent *keyEvent)
{
    QString result;
    
    if (keyEvent->modifiers() & Qt::ControlModifier)
        result += "Ctrl+";
    if (keyEvent->modifiers() & Qt::AltModifier)
        result += "Alt+";
    if (keyEvent->modifiers() & Qt::ShiftModifier)
        result += "Shift+";
    if (keyEvent->modifiers() & Qt::MetaModifier)
        result += "Meta+";
    
    int keyInt = keyEvent->key();
    
    if (keyInt == 0 || keyInt == Qt::Key_unknown) {
        if (result.isEmpty()) {
            return QString();
        } else {
            return result.left(result.length() - 1);
        }
    }
    
    switch (keyInt) {
        case Qt::Key_Control:
            result = "Ctrl";
            break;
        case Qt::Key_Alt:
            result = "Alt";
            break;
        case Qt::Key_Shift:
            result = "Shift";
            break;
        case Qt::Key_Meta:
            result = "Meta";
            break;
        case Qt::Key_Return:
            result += "Enter";
            break;
        case Qt::Key_Space:
            result += "Space";
            break;
        case Qt::Key_Tab:
            result += "Tab";
            break;
        case Qt::Key_Backtab:
            result += "Backtab";
            break;
        case Qt::Key_Backspace:
            result += "Backspace";
            break;
        case Qt::Key_Delete:
            result += "Delete";
            break;
        case Qt::Key_Insert:
            result += "Insert";
            break;
        case Qt::Key_Home:
            result += "Home";
            break;
        case Qt::Key_End:
            result += "End";
            break;
        case Qt::Key_PageUp:
            result += "PageUp";
            break;
        case Qt::Key_PageDown:
            result += "PageDown";
            break;
        case Qt::Key_Up:
            result += "Up";
            break;
        case Qt::Key_Down:
            result += "Down";
            break;
        case Qt::Key_Left:
            result += "Left";
            break;
        case Qt::Key_Right:
            result += "Right";
            break;
        case Qt::Key_F1:
        case Qt::Key_F2:
        case Qt::Key_F3:
        case Qt::Key_F4:
        case Qt::Key_F5:
        case Qt::Key_F6:
        case Qt::Key_F7:
        case Qt::Key_F8:
        case Qt::Key_F9:
        case Qt::Key_F10:
        case Qt::Key_F11:
        case Qt::Key_F12:
            result += QKeySequence(keyEvent->key()).toString();
            break;
        default:
            if (!keyEvent->text().isEmpty() && keyEvent->text()[0].isPrint()) {
                result += keyEvent->text();
            } else {
                result += QKeySequence(keyEvent->key()).toString();
            }
    }
    
    return result;
}