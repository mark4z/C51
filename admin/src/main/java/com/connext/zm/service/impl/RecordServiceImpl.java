package com.connext.zm.service.impl;

import com.connext.zm.dao.RecordRepository;
import com.connext.zm.entity.Record;
import com.connext.zm.service.RecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.stereotype.Service;

import java.util.Calendar;
import java.util.Date;
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
    public Page<Record> getAllByPage(Integer page) {
        return recordRepository.findAll(new PageRequest(page,10));
    }

    @Override
    public void remoteControl(int signal) {
        //serialUtil.send(signal);
    }

    @Override
    public List<Record> getToday() {

        Calendar calendar = Calendar.getInstance();
        calendar.setTime(new Date());
        calendar.set(Calendar.HOUR, 0);
        calendar.set(Calendar.MINUTE, 0);
        calendar.set(Calendar.SECOND, 0);
        Date date = calendar.getTime();
        return recordRepository.findByTimeAfter(date);
    }
}
