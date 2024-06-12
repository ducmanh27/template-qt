#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QDebug>
#include <cstdint>
#include <iostream>
class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);
    void show();
    uint8_t addNumber(uint8_t x, uint8_t y);
signals:
};

#endif // APPMANAGER_H
