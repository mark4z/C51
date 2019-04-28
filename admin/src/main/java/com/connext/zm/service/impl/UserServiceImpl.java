package com.connext.zm.service.impl;

import com.connext.zm.dao.AuthorityRepository;
import com.connext.zm.dao.UserRepository;
import com.connext.zm.entity.Authority;
import com.connext.zm.entity.User;
import com.connext.zm.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class UserServiceImpl implements UserService {

  private UserRepository userRepository;
  private AuthorityRepository authorityRepository;

  @Autowired
  public UserServiceImpl(UserRepository userRepository, AuthorityRepository authorityRepository) {
    this.userRepository = userRepository;
    this.authorityRepository = authorityRepository;
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
    roles.forEach(i -> authorities.add(authorityRepository.findByNameEquals(i)));
    user.setAuthorities(authorities);
    userRepository.save(user);
  }

  @Override
  public List<User> allUser() {
    return userRepository.findAll();
  }

  @Override
  public User getUser() {
    Authentication auth = SecurityContextHolder.getContext().getAuthentication();
    org.springframework.security.core.userdetails.User user =
        (org.springframework.security.core.userdetails.User) auth.getPrincipal();
    User realUser = userRepository.findByUsername(user.getUsername()).get();
    return realUser;
  }

  @Override
  public User getUserById(String username) {
    User user = userRepository.findByUsername(username).get();
    return user;
  }

  @Override
  public void delete(String username) {
    User user = userRepository.findByUsername(username).get();
    userRepository.delete(user);
  }
}
