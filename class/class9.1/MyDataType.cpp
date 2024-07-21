#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <variant>
#include <fstream>
#include <cstdint>

class MyDataType {
public:
    using DataType = std::variant<int16_t, std::string, std::vector<std::pair<std::string, MyDataType>>>;

    MyDataType(int16_t value) : data(value) {}
    MyDataType(const std::string& value) : data(value) {}
    MyDataType(const std::vector<std::pair<std::string, MyDataType>>& value) : data(value) {}

    const DataType& getData() const {
        return data;
    }

private:
    DataType data;
};


class MsgPackSerializer {
public:
    void serialize(const MyDataType& obj, std::ostream& out) {
        serializeData(obj.getData(), out);
    }

private:
    void serializeData(const MyDataType::DataType& data, std::ostream& out) {
        std::visit([&](const auto& value) {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, int16_t>) {
                serializeInt(value, out);
            } else if constexpr (std::is_same_v<T, std::string>) {
                serializeString(value, out);
            } else if constexpr (std::is_same_v<T, std::vector<std::pair<std::string, MyDataType>>>) {
                serializeMap(value, out);
            }
        }, data);
    }

    void serializeInt(int16_t value, std::ostream& out) {
        out.put(0xd1);  
        out.put(static_cast<char>((value >> 8) & 0xFF));
        out.put(static_cast<char>(value & 0xFF));
    }

    void serializeString(const std::string& value, std::ostream& out) {
        out.put(0xd9); 
        out.put(static_cast<uint8_t>(value.size()));
        out.write(value.data(), value.size());
    }

    void serializeMap(const std::vector<std::pair<std::string, MyDataType>>& map, std::ostream& out) {
        out.put(0xde);  
        out.put(static_cast<char>((map.size() >> 8) & 0xFF));
        out.put(static_cast<char>(map.size() & 0xFF));
        for (const auto& [key, val] : map) {
            serializeString(key, out);
            serializeData(val.getData(), out);
        }
    }
};

int main() {
   
    MyDataType intData(42);
    MyDataType stringData(std::string("Hello, MsgPack"));
    std::vector<std::pair<std::string, MyDataType>> mapData = {
        {"key1", MyDataType(123)},
        {"key2", MyDataType("value2")}
    };
    MyDataType mapDataType(mapData);

    MsgPackSerializer serializer;
    std::ofstream outFile("output.msgpack", std::ios::binary);

    serializer.serialize(intData, outFile);
    serializer.serialize(stringData, outFile);
    serializer.serialize(mapDataType, outFile);

    outFile.close();
    return 0;
}
