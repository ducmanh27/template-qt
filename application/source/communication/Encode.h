#ifndef ENCODE_H
#define ENCODE_H
#define DEBUG
#include <QDebug>
#include <QIODevice>
#include <QObject>
#include "../interface/IEncode.h"
#include "../tcp_header/COTPHeader.h"
#include "../tcp_header/TPKTHeader.h"
#include "../tcp_header/S7Comm.h"

class Encode : public QObject, public IEncode{
    Q_OBJECT
public:
    explicit Encode(QObject *parent = nullptr);
    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> connectionRequestData() override;
    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> setupCommunicationData() override;
    std::pair<std::unique_ptr<uint8_t[]>, uint8_t> communicationPLCData(command Command, syntax_id SyntaxID,
                                                                        length_t Length, area MemoryArea,
                                                                        address_t Adress, data_t DataWrite) override;
    static QMap<syntax_id, uint8_t> syntaxID_Table;
    static QMap<area, uint8_t> areaTable;
private:
    static uint16_t pduRef;
signals:
};
#endif // ENCODE_H
