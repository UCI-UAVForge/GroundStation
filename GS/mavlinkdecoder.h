#ifndef MAVLINKDECODER_H
#define MAVLINKDECODER_H

#include <QObject>
#include <QThread>
#include <QFile>
#include <QVariant>
#include <QMap>
#include <QVector>
#include <QDateTime>
#include "common/common/mavlink.h"

class ConnectionManager;

class MAVLinkDecoder : public QObject
{
    Q_OBJECT
public:
    MAVLinkDecoder(QObject *parent=0);
    ~MAVLinkDecoder();

    void passManager(ConnectionManager *manager) { m_connectionManager = manager; }
    mavlink_field_info_t getFieldInfo(QString msgname,QString fieldname);
    QList<QString> getFieldList(QString msgname);
    QString getMessageName(uint8_t msgid);
    quint64 getUnixTimeFromMs(int systemID, quint64 time);

signals:
    void protocolStatusMessage(const QString& title, const QString& message);
    void valueChanged(const int uasId, const QString& name, const QString& unit, const QVariant& value, const quint64 msec);
    void textMessageReceived(int uasid, int componentid, int severity, const QString& text);
    void receiveLossChanged(int id,float value);

public slots:
    QList<QPair<QString,QVariant> > receiveMessage(mavlink_message_t message);
    void sendMessage(mavlink_message_t msg);
    QPair<QString,QVariant> emitFieldValue(mavlink_message_t* msg, int fieldid, quint64 time);

private:
    int getSystemId() { return 252; }
    int getComponentId() { return 1; }
    quint64 groundTimeMilliseconds()
    {
        QDateTime time = QDateTime::currentDateTime();
        time = time.toUTC();
        /* Return seconds and milliseconds, in milliseconds unit */
        quint64 seconds = time.toTime_t() * static_cast<quint64>(1000);
        return static_cast<quint64>(seconds + (time.time().msec()));
    }

private:
    bool m_loggingEnabled;
    QFile *m_logfile;
    ConnectionManager *m_connectionManager;
    bool m_throwAwayGCSPackets;
    bool m_enable_version_check;
    bool versionMismatchIgnore;
    QMap<int,qint64> totalReceiveCounter;
    QMap<int,qint64> currReceiveCounter;
    QMap<int,QMap<int,uint8_t> > lastIndex;
    QMap<int,qint64> totalLossCounter;
    QMap<int,qint64> currLossCounter;
    bool m_multiplexingEnabled;

    QMap<int,int> componentID;
    QMap<int,bool> componentMulti;
    QMap<uint16_t, bool> messageFilter;               ///< Message/field names not to emit
    QMap<uint16_t, bool> textMessageFilter;           ///< Message/field names not to emit in text mode
    mavlink_message_t receivedMessages[256];    ///< Available / known messages
    mavlink_message_info_t messageInfo[256];    ///< Message information
    QMap<int,quint64> onboardTimeOffset;
    QMap<int,quint64> firstOnboardTime;
    QMap<int,quint64> onboardToGCSUnixTimeOffsetAndDelay;
};

#endif // MAVLINKDECODER_H
