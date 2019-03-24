package com.connext.zm.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@Controller
public class IndexControl {
    @GetMapping("/")
    public String index(){
        return "index";
    }
}
