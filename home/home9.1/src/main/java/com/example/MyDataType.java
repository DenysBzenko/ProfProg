package com.example;

import org.msgpack.core.MessageBufferPacker;
import org.msgpack.core.MessagePack;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MyDataType {
    private final Object data;

    public MyDataType(int value) {
        this.data = value;
    }

    public MyDataType(String value) {
        this.data = value;
    }

    public MyDataType(List<Map.Entry<String, MyDataType>> value) {
        this.data = value;
    }

    public Object getData() {
        return data;
    }

    public static void serialize(MyDataType obj, OutputStream out) throws IOException {
        MessageBufferPacker packer = MessagePack.newDefaultBufferPacker();
        serializeData(obj.getData(), packer);
        packer.close();
        out.write(packer.toByteArray());
    }

    private static void serializeData(Object data, MessageBufferPacker packer) throws IOException {
        if (data instanceof Integer) {
            packer.packInt((int) data);
        } else if (data instanceof String) {
            packer.packString((String) data);
        } else if (data instanceof List) {
            List<Map.Entry<String, MyDataType>> list = (List<Map.Entry<String, MyDataType>>) data;
            packer.packMapHeader(list.size());
            for (Map.Entry<String, MyDataType> entry : list) {
                packer.packString(entry.getKey());
                serializeData(entry.getValue().getData(), packer);
            }
        }
    }

    public static void main(String[] args) {
        try {
            MyDataType intData = new MyDataType(42);
            MyDataType stringData = new MyDataType("Hello, MsgPack");
            List<Map.Entry<String, MyDataType>> mapData = new ArrayList<>();
            mapData.add(Map.entry("key1", new MyDataType(123)));
            mapData.add(Map.entry("key2", new MyDataType("value2")));
            MyDataType mapDataType = new MyDataType(mapData);

            try (FileOutputStream out = new FileOutputStream("output.msgpack")) {
                serialize(intData, out);
                serialize(stringData, out);
                serialize(mapDataType, out);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
