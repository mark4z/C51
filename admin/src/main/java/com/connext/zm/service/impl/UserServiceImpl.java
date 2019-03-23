package com.connext.zm.service.impl;

import com.connext.zm.dao.UserRepository;
import com.connext.zm.entity.Authority;
import com.connext.zm.entity.User;
import com.connext.zm.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class UserServiceImpl implements UserService {

    private UserRepository userRepository;

    @Autowired
    public UserServiceImpl(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public void CreateUser(String username, String password) {
        User newUser = new User();
        newUser.setUsername(username);
        newUser.setPassword(new BCryptPasswordEncoder().encode(password));
        userRepository.save(newUser);
    }

    @Override
    public void setRole(String username, List<String> roles) {
        User user = userRepository.findByUsername(username).get();
        List<Authority> authorities = new ArrayList<>();
        roles.forEach(i -> authorities.add(new Authority(i)));
        user.setAuthorities(authorities);
        userRepository.save(user);
    }

    @Override
    public List<User> allUser() {
        return userRepository.findAll();
    }

    @Override
    public User getUser(String username) {
        return userRepository.findByUsername(username).get();
    }
}
