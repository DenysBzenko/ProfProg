package com.example;

import java.io.*;
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
        serializeData(obj.getData(), out);
    }

    private static void serializeData(Object data, OutputStream out) throws IOException {
        if (data instanceof Integer) {
            serializeInt((int) data, out);
        } else if (data instanceof String) {
            serializeString((String) data, out);
        } else if (data instanceof List) {
            serializeMap((List<Map.Entry<String, MyDataType>>) data, out);
        }
    }

    private static void serializeInt(int value, OutputStream out) throws IOException {
        out.write(0xd1);  
        out.write((value >> 8) & 0xFF);
        out.write(value & 0xFF);
    }

    private static void serializeString(String value, OutputStream out) throws IOException {
        out.write(0xd9); 
        out.write(value.length());
        out.write(value.getBytes());
    }

    private static void serializeMap(List<Map.Entry<String, MyDataType>> map, OutputStream out) throws IOException {
        out.write(0xde);  
        out.write((map.size() >> 8) & 0xFF);
        out.write(map.size() & 0xFF);
        for (Map.Entry<String, MyDataType> entry : map) {
            serializeString(entry.getKey(), out);
            serializeData(entry.getValue().getData(), out);
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
