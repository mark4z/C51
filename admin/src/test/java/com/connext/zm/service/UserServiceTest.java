package com.connext.zm.service;

import com.connext.zm.dao.AuthorityRepository;
import com.connext.zm.dao.UserRepository;
import com.connext.zm.entity.Authority;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;


import javax.transaction.Transactional;

import static org.junit.Assert.*;

@RunWith(SpringRunner.class)
@SpringBootTest

public class UserServiceTest {
    @Autowired
    private UserService userService;
    @Autowired
    private AuthorityRepository authorityRepository;

    @Test
    public void createUser() {
        userService.CreateUser("admin", "123456");
    }
    @Test
    public void init(){
        authorityRepository.save(new Authority("admin"));
        authorityRepository.save(new Authority("view"));
        authorityRepository.save(new Authority("action"));
        authorityRepository.save(new Authority("user"));
        authorityRepository.save(new Authority("add"));
    }
    @Test
    public void test(){
        System.out.println(authorityRepository.findByNameEquals("admin"));
    }
}