#include "AppManager.h"

AppManager::AppManager(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Test class is created  ...";
}

void AppManager::show()
{
    qInfo() << "Test class sucessfully !";
}

uint8_t AppManager::addNumber(uint8_t x, uint8_t y)
{
    if ( x + y >= 255)
        throw std::out_of_range("Invalid input");
    return (x + y);
}

