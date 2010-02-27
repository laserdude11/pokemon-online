#ifndef ANALYZE_H
#define ANALYZE_H

#include <QtCore>
#include "network.h"

class BasicInfo;
class TeamBattle;
class BattleChoice;
class BattleConfiguration;

/* Commands to dialog with the server */
namespace NetworkReg
{
    enum Command
    {
        WhatAreYou = 0,
        WhoAreYou,
        Login,
        Logout,
        SendMessage,
        PlayersList,
        SendTeam,
        ChallengeStuff,
        EngageBattle,
        BattleFinished,
        BattleMessage,
        BattleChat,
        KeepAlive,
        AskForPass,
        Register,
        PlayerKick,
        PlayerBan,
        ServNumChange,
        ServDescChange,
        ServNameChange
    };

    enum ProtocolError
    {
        UnknownCommand = 0
    };
}

class TeamInfo;

class Analyzer : public QObject
{
    Q_OBJECT
public:
    Analyzer(QTcpSocket *sock, int id);
    ~Analyzer();

    /* functions called by the reg */
    void sendServer(const QString &name, const QString &desc, quint16 numplayers, const QString &ip);
    void sendInvalidName();
    void sendNameTaken();
    void sendAccept();

    bool isConnected() const;
    QString ip() const;

    /* Closes the connection */
    void close();

    /* Convenience functions to avoid writing a new one every time */
    void notify(int command);
    template<class T>
    void notify(int command, const T& param);
    template<class T1, class T2>
    void notify(int command, const T1& param1, const T2& param2);
    template<class T1, class T2, class T3>
    void notify(int command, const T1& param1, const T2& param2, const T3 &param3);
    template<class T1, class T2, class T3, class T4>
    void notify(int command, const T1& param1, const T2& param2, const T3 &param3, const T4 &param4);
signals:
    /* to send to the network */
    void sendCommand(const QByteArray &command);
    /* to send to the reg */
    void connectionError(int errorNum, const QString &errorDesc);
    void protocolError(int errorNum, const QString &errorDesc);
    void loggedIn(const QString &name, const QString &desc, quint16 num);
    void numChange(quint16 newnum);
    void nameChange(const QString &name);
    void descChange(const QString &desc);

    void disconnected();
public slots:
    /* slots called by the network */
    void error();
    void commandReceived (const QByteArray &command);
    void keepAlive();
private:
    Network &socket();
    const Network &socket() const;

    Network mysocket;
    QTimer *mytimer;
};

template<class T>
void Analyzer::notify(int command, const T& param)
{
    if (!isConnected())
        return;
    QByteArray tosend;
    QDataStream out(&tosend, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << uchar(command) << param;

    emit sendCommand(tosend);
}

template<class T1, class T2>
void Analyzer::notify(int command, const T1& param1, const T2 &param2)
{
    if (!isConnected())
        return;
    QByteArray tosend;
    QDataStream out(&tosend, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << uchar(command) << param1 << param2;

    emit sendCommand(tosend);
}

template<class T1, class T2, class T3>
void Analyzer::notify(int command, const T1& param1, const T2 &param2, const T3 &param3)
{
    if (!isConnected())
        return;
    QByteArray tosend;
    QDataStream out(&tosend, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << uchar(command) << param1 << param2 << param3;

    emit sendCommand(tosend);
}

template<class T1, class T2, class T3, class T4>
void Analyzer::notify(int command, const T1& param1, const T2 &param2, const T3 &param3, const T4 &param4)
{
    if (!isConnected())
        return;
    QByteArray tosend;
    QDataStream out(&tosend, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);

    out << uchar(command) << param1 << param2 << param3 << param4;

    emit sendCommand(tosend);
}

#endif // ANALYZE_H