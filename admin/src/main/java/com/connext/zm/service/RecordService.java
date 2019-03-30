package com.connext.zm.service;

import com.connext.zm.entity.Record;
import org.springframework.data.domain.Page;

import java.util.List;

public interface RecordService {
    void insert(Record record);

    List<Record> getAll();

    Page<Record> getAllByPage(Integer page);

    void remoteControl(int signal);

    List<Record> getToday();
}
