package com.connext.zm;

import com.connext.zm.util.SerialUtil;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.data.jpa.repository.config.EnableJpaAuditing;

@SpringBootApplication
@EnableJpaAuditing
public class ZmApplication {

    public static void main(String[] args){
        SpringApplication.run(ZmApplication.class, args);
    }

}
