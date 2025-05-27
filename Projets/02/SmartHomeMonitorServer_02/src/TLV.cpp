#include "TLV.hpp"
#include <arpa/inet.h>  // 字节序转换

//------------------ TLV编码 --------------------
std::vector<uint8_t> TLV::serialize() const {
    std::vector<uint8_t> buffer;

    // 编码Type (2字节大端)
    uint16_t net_type = htons(static_cast<uint16_t>(type));
    buffer.insert(buffer.end(), 
        reinterpret_cast<uint8_t*>(&net_type),
        reinterpret_cast<uint8_t*>(&net_type) + 2);

    // 编码Length (4字节大端)
    uint32_t net_length = htonl(length);
    buffer.insert(buffer.end(),
        reinterpret_cast<uint8_t*>(&net_length),
        reinterpret_cast<uint8_t*>(&net_length) + 4);

    // 编码Value
    buffer.insert(buffer.end(), value.begin(), value.end());
    return buffer;
}

//------------------ TLV解码 --------------------
bool TLV::parse(const std::vector<uint8_t>& data) {
    if (data.size() < 6) return false;  // 至少需要6字节头部

    // 解码Type
    uint16_t net_type;
    memcpy(&net_type, data.data(), 2);
    type = static_cast<TLVType>(ntohs(net_type));

    // 解码Length
    uint32_t net_length;
    memcpy(&net_length, data.data() + 2, 4);
    length = ntohl(net_length);

    // 校验数据长度
    if (data.size() - 6 != length) return false;

    // 提取Value
    value.assign(data.begin() + 6, data.end());
    return true;
}