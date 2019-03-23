package com.connext.zm.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.http.HttpStatus;
import org.springframework.web.servlet.config.annotation.*;

/**
 * @Author: Marcus
 * @Date: 2018/12/22 11:01
 * @Version 1.0
 */
@Configuration
public class WebPathConfiguration implements WebMvcConfigurer {
    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/user/add").setViewName("user_add");
        registry.addViewController("/").setViewName("index");
    }
}
