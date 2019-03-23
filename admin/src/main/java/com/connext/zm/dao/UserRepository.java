package com.connext.zm.dao;

import com.connext.zm.entity.User;
import org.springframework.data.repository.CrudRepository;

import java.util.List;
import java.util.Optional;

/**
 * @Author: Marcus
 * @Date: 2018/12/20 10:25
 * @Version 1.0
 */

public interface UserRepository extends CrudRepository<User, Integer> {
    /**
     * fetch data by phone
     *
     * @param username user's username
     * @return User
     */
    Optional<User> findByUsername(String username);

    List<User>  findAll();
}
