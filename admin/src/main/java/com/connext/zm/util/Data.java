package com.connext.zm.util;

import com.connext.zm.entity.Authority;
import com.connext.zm.entity.User;

import java.util.List;

public class Data {
    public List<User> users;
    public User user;
    public List<Authority> authorities;
    public List<String> roles;
    public String username;
    public String password;

    @Override
    public String toString() {
        return "Data{" +
                "users=" + users +
                ", user=" + user +
                ", authorities=" + authorities +
                ", roles=" + roles +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<String> getRoles() {
        return roles;
    }

    public void setRoles(List<String> roles) {
        this.roles = roles;
    }

    public List<User> getUsers() {
        return users;
    }

    public void setUsers(List<User> users) {
        this.users = users;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public List<Authority> getAuthorities() {
        return authorities;
    }

    public void setAuthorities(List<Authority> authorities) {
        this.authorities = authorities;
    }
}
