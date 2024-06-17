#ifndef ERRORTABLE_H
#define ERRORTABLE_H

#include <QObject>
#include <QMap>

class ErrorTable : public QObject
{
    Q_OBJECT
public:
    explicit ErrorTable(QObject *parent = nullptr);
    QString getErrorDescription(int error_class, int error_code);
private:
    static QMap<uint16_t, QString> errorClass;
    static QMap<uint16_t, QString> errorCode;
signals:

};
#endif // ERRORTABLE_H
