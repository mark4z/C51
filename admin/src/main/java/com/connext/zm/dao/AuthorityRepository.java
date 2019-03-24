package com.connext.zm.dao;

import com.connext.zm.entity.Authority;
import org.springframework.data.repository.CrudRepository;

public interface AuthorityRepository extends CrudRepository<Authority, Integer> {
    Authority findByNameEquals(String name);
}
