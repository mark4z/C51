package com.connext.zm.controller;

import com.connext.zm.entity.User;
import com.connext.zm.service.UserService;
import com.connext.zm.util.Data;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@RestController
@RequestMapping("/user")
public class UserController {
  private final UserService userService;

  @Autowired
  public UserController(UserService userService) {
    this.userService = userService;
  }

  @GetMapping("/all")
  public List<User> allUser(Model model) {
    return userService.allUser();
  }

  @PostMapping("/add")
  public String addUser(
      @RequestParam String username, @RequestParam String password, @RequestParam String roles) {
    userService.CreateUser(username, password);
    List<String> role = Arrays.asList(roles.split(","));
    userService.setRole(username, role);
    return "true";
  }

  @GetMapping("/roles")
  public List<String> getUser() {
    List<String> roles = new ArrayList<>();
    User user = userService.getUser();
    user.getAuthorities().forEach(i -> roles.add(i.getName()));
    return roles;
  }

  @GetMapping("/{username}/delete")
  public Data deleteUser(@PathVariable String username) {
    Data data = new Data();
    userService.delete(username);
    return data;
  }

  @PostMapping("/{username}/role")
  public String setRole(@PathVariable String username, String role) {
    List<String> roles = Arrays.asList(role.split(","));
    userService.setRole(username, roles);
    return "Success";
  }
}
