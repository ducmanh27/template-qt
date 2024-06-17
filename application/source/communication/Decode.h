#ifndef DECODE_H
#define DECODE_H

#include <QDebug>
#include <QIODevice>
#include <QObject>
#include "../interface/IDecode.h"
#include "../tcp_header/COTPHeader.h"
#include "../tcp_header/TPKTHeader.h"
#include "../tcp_header/S7Comm.h"
#include "../tcp_header/ErrorTable.h"
#include "../tcp_header/Status.h"

class Decode : public QObject, public IDecode
{
    Q_OBJECT
public:
    explicit Decode(QObject *parent = nullptr);
    status connectionConfirm(QByteArray responseData) override;
    status communicationPLC(QByteArray responseData) override;
    static QList<uint8_t> ReadData;
signals:

private:
    ErrorTable err_header;

};

#endif // DECODE_H
