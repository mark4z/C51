package com.connext.zm.service.impl;

import com.connext.zm.dao.RecordRepository;
import com.connext.zm.entity.Record;
import com.connext.zm.service.RecordService;
import com.connext.zm.util.SerialUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class RecordServiceImpl implements RecordService {

    private final RecordRepository recordRepository;
    //private final SerialUtil serialUtil;

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

    @Override
    public void remoteControl(int signal) {
        //serialUtil.send(signal);
    }
}
