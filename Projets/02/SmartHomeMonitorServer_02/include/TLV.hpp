#ifndef TLV_HPP
#define TLV_HPP

#include <cstdint>
#include <vector>
#include <string>

// TLV类型定义 (可扩展)
enum class TLVType : uint16_t {
    INVALID   = 0x0000,
    STRING    = 0x0001,  // UTF-8字符串
    INT32     = 0x0002,  // 32位整数
    BINARY    = 0x0003,  // 二进制数据
    NESTED    = 0x0004,  // 嵌套的TLV列表
    // 可继续扩展...
};

// TLV基础单元
struct TLV {
    TLVType type;         // 2字节
    uint32_t length;      // 4字节 (Value字段的字节长度)
    std::vector<uint8_t> value; // 变长数据

    // 构造函数
    TLV(TLVType t = TLVType::INVALID, 
        const std::vector<uint8_t>& v = {})
        : type(t), length(v.size()), value(v) {}
};

// TLV列表容器 (用于嵌套结构)
class TLVList {
public:

    void add(const TLV& tlv);
    const std::vector<TLV>& items() const;
    std::vector<uint8_t> serialize() const;
    bool parse(const std::vector<uint8_t>& data);
    
private:
    std::vector<TLV> items_;
};

#endif // TLV_HPP