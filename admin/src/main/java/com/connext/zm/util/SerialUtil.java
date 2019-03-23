package com.connext.zm.util;

public class SerialUtil {
    public static void start(String com) {
        try {
            (new TwoWaySerialComm()).connect(com);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}