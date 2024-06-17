#ifndef IENCODE_H
#define IENCODE_H
#include <cstdint>

#include "../tcp_header/Status.h"
#include "../tcp_header/S7Comm.h"

class IEncode{
public:
    // Note: The destructor of interface must be virtual, as is the case for all classes you intend to inherit from -
    // otherwise the destructor of the derived class will not be called when you delete an object through a base pointer,
    // and you’ll get corrupted program states like memory leaks
    // Deleting a base-class pointer that doesn't have a virtual destructor is invalid, and gives undefined behaviour.
    virtual ~IEncode() = default;
    virtual std::pair<std::unique_ptr<uint8_t[]>, uint8_t> connectionRequestData() = 0;
    virtual std::pair<std::unique_ptr<uint8_t[]>, uint8_t> setupCommunicationData() = 0;
    virtual std::pair<std::unique_ptr<uint8_t[]>, uint8_t> communicationPLCData(command Command, syntax_id SyntaxID,
                                                                                length_t Length, area MemoryArea,
                                                                                address_t Adress, data_t DataWrite) = 0;
};

#endif // IENCODE_H
