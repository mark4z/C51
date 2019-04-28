package com.connext.zm.service;

import com.connext.zm.entity.User;
import org.springframework.stereotype.Service;

import java.util.List;

public interface UserService {
    void CreateUser(String username, String password);

    /**
     * Add roles for user
     *
     * @param username  The user who want to add Roles.
     * @param roles Roles
     * @return true or false
     */
    void setRole(String username, List<String> roles);

    /**
     * Find all user.
     * @return All user.
     */
    List<User> allUser();

    /**
     * Find a user.
     * @return a user.
     */
    User getUser();

    User getUserById(String username);

    void delete(String username);
}
