package com.connext.zm.service.impl;

import com.connext.zm.dao.RecordRepository;
import com.connext.zm.entity.Record;
import com.connext.zm.service.RecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class RecordServiceImpl implements RecordService {

    private final RecordRepository recordRepository;

    @Autowired
    public RecordServiceImpl(RecordRepository recordRepository) {
        this.recordRepository = recordRepository;
    }

    @Override
    public void insert(Record record) {
        recordRepository.save(record);
    }

    @Override
    public List<Record> getAll() {
        return recordRepository.findAll();
    }
}
