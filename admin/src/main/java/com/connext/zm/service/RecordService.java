package com.connext.zm.service;

import com.connext.zm.entity.Record;

import java.util.List;

public interface RecordService {
    void insert(Record record);

    List<Record> getAll();
}
