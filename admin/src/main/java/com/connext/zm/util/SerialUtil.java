package com.connext.zm.util;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.io.OutputStream;
@Component
public class SerialUtil {
    private final TwoWaySerialComm comm;

    @Autowired
    public SerialUtil(TwoWaySerialComm comm) {
        this.comm = comm;
    }

    public void start(String com) {
        try {
            comm.connect("COM2");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public void send(int opinion){
        comm.sendData((byte) opinion);
    }
}