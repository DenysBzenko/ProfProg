package com.example;

import java.io.*;
import java.util.*;

public class MsgPackDeserializer {

    public static void main(String[] args) {
        try (FileInputStream in = new FileInputStream("output.msgpack")) {
            Object obj = deserializeData(in);
            System.out.println(obj);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static Object deserializeData(InputStream in) throws IOException {
        int marker = in.read();
        switch (marker) {
            case 0xd1:
                return deserializeInt(in);
            case 0xd9:
                return deserializeString(in);
            case 0xde:
                return deserializeMap(in);
            default:
                throw new IOException("Unknown marker: " + marker);
        }
    }

    private static int deserializeInt(InputStream in) throws IOException {
        int byte1 = in.read();
        int byte2 = in.read();
        return (byte1 << 8) | byte2;
    }

    private static String deserializeString(InputStream in) throws IOException {
        int length = in.read();
        byte[] bytes = new byte[length];
        in.read(bytes);
        return new String(bytes);
    }

    private static Map<String, Object> deserializeMap(InputStream in) throws IOException {
        int size = (in.read() << 8) | in.read();
        Map<String, Object> map = new HashMap<>();
        for (int i = 0; i < size; i++) {
            String key = deserializeString(in);
            Object value = deserializeData(in);
            map.put(key, value);
        }
        return map;
    }
}
