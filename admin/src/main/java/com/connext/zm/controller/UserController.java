package com.connext.zm.controller;

import com.connext.zm.entity.Authority;
import com.connext.zm.entity.User;
import com.connext.zm.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Controller
@RequestMapping("/user")
public class UserController {
    private final UserService userService;

    @Autowired
    public UserController(UserService userService) {
        this.userService = userService;
    }

    @GetMapping("/all")
    public String allUser(Model model) {
        model.addAttribute("users", userService.allUser());
        return "index";
    }

    @PostMapping("/add")
    @ResponseBody
    public String addUser(@RequestParam String username, @RequestParam String password) {
        userService.CreateUser(username, password);
        return "Success";
    }

    @GetMapping("/{username}")
    public User getUser(@PathVariable String username) {
        return userService.getUser(username);
    }

    @GetMapping("/{username}/role")
    public String getUserRole(@PathVariable String username, Model model) {
        User user = userService.getUser(username);
        model.addAttribute("user", user);
        model.addAttribute("role", user.getAuthorities().stream().map(Authority::getName).collect(Collectors.toList()));
        return "user_role";
    }

    @PostMapping("/{username}/role")
    @ResponseBody
    public String setRole(@PathVariable String username, @RequestParam String role) {
        List<String> roles = Arrays.asList(role.split(","));
        userService.setRole(username, roles);
        return "Success";
    }
}
