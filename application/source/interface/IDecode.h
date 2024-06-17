#ifndef IDECODE_H
#define IDECODE_H
#include <QByteArray>
#include "../tcp_header/Status.h"
class IDecode{
public:
    // Note: The destructor of interface must be virtual, as is the case for all classes you intend to inherit from -
    // otherwise the destructor of the derived class will not be called when you delete an object through a base pointer,
    // and you’ll get corrupted program states like memory leaks
    // Deleting a base-class pointer that doesn't have a virtual destructor is invalid, and gives undefined behaviour.
    virtual ~IDecode() = default;
    virtual status connectionConfirm(QByteArray responseData) = 0;
    virtual status communicationPLC(QByteArray responseData) = 0;
};
#endif // IDECODE_H
