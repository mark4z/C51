package com.connext.zm.controller;

import com.connext.zm.entity.Record;
import com.connext.zm.service.RecordService;
import com.connext.zm.util.SerialUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/record")
public class RecordControl {
    private final RecordService recordService;
    private final SerialUtil serialUtil;

    @Autowired
    public RecordControl(RecordService recordService, SerialUtil serialUtil) {
        this.recordService = recordService;
        this.serialUtil = serialUtil;
    }

    @GetMapping("/all")
    List<Record> all(){
        return recordService.getAll();
    }
    @GetMapping("/normal")
    void normal(){
        serialUtil.send(0);
    }
    @GetMapping("/ew")
    void ew(){
        serialUtil.send(1);
    }
    @GetMapping("/sn")
    void sn(){
        serialUtil.send(2);
    }
    @GetMapping("/stop")
    void stop(){
        serialUtil.send(3);
    }
}
