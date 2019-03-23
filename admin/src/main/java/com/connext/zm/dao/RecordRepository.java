package com.connext.zm.dao;

import com.connext.zm.entity.Record;
import com.connext.zm.entity.User;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.repository.CrudRepository;

import java.util.List;
import java.util.Optional;

/**
 * @Author: Marcus
 * @Date: 2018/12/20 10:25
 * @Version 1.0
 */
public interface RecordRepository extends CrudRepository<Record, Integer> {
    List<Record> findAll();

    Page<Record> findAll(Pageable page);
}
