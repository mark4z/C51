package com.connext.zm.config;

import com.connext.zm.util.SerialUtil;
import org.springframework.boot.CommandLineRunner;
import org.springframework.core.Ordered;
import org.springframework.stereotype.Component;

import java.util.Date;

@Component
public class MyCommandLineRunner implements CommandLineRunner, Ordered {
    @Override
    public int getOrder() {
        return 1;//返回执行顺序
    }

    @Override
    public void run(String... var1) throws Exception {
        SerialUtil.start("COM2");
    }
}
