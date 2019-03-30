package com.connext.zm.service.impl;

import com.connext.zm.dao.UserRepository;
import com.connext.zm.entity.Authority;
import com.connext.zm.entity.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * @Author: Marcus
 * @Date: 2018/12/21 10:18
 * @Version 1.0
 */
@Service
@Transactional(rollbackOn = {Exception.class})
public class UserDetailServiceImpl implements UserDetailsService {
    private final UserRepository userRepository;

    @Autowired
    public UserDetailServiceImpl(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) throws BadCredentialsException {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isPresent()) {

            List<Authority> authorities = user.get().getAuthorities();
            List<GrantedAuthority> list = new ArrayList<GrantedAuthority>();
            authorities.forEach(i -> list.add(new GrantedAuthority() {
                @Override
                public String getAuthority() {
                    return i.getName();
                }
            }));
            return new org.springframework.security.core.userdetails.User(user.get().getUsername(), user.get().getPassword(), list);
        } else {
            throw new BadCredentialsException("用户未注册!");
        }
    }
}