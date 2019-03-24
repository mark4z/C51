package com.connext.zm.controller;

import com.connext.zm.service.RecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/record")
public class RecordControl {
    private final RecordService recordService;

    @Autowired
    public RecordControl(RecordService recordService) {
        this.recordService = recordService;
    }

    @GetMapping("/normal")
    void normal(){
        recordService.remoteControl(0);
    }
    @GetMapping("/ew")
    void ew(){
        recordService.remoteControl(1);
    }
    @GetMapping("/sn")
    void sn(){
        recordService.remoteControl(2);
    }
    @GetMapping("/stop")
    void stop(){
        recordService.remoteControl(3);
    }
}
