package com.connext.zm.service;

import com.connext.zm.service.impl.UserServiceImpl;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest
public class RecordServiceTest {
    @Autowired
    private RecordService recordService;

    @Test
    public void send() {
        recordService.remoteControl(0);
    }
}