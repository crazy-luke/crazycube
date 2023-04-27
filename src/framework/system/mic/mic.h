/**
 * @file Mic.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 1.0
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "i2s_sampler.h"

#pragma once

#define MIC_I2S_SCK GPIO_NUM_27
#define MIC_I2S_LRC GPIO_NUM_25
#define MIC_I2S_DATA GPIO_NUM_26
#define SAMPLE_RATE 16000

#define SAMPLER_SHIFT_AUDIOMITOR 15
#define SAMPLER_SHIFT_ASSISTANT 11

class Mic {

private:
    I2SSampler *i2s_sampler_ = nullptr;
    const char *kTag = "Mic";
    TaskHandle_t task_handle();
    bool TaskIsCreated();    // 任务已经被创建
    bool TaskIsSuspended();  // 任务是否挂起状态
public:
    ~Mic();
    void Init();    //初始化
    void Start(TaskHandle_t processor_task_handle); //开始任务
    void Stop();    //停止任务
    void Stop(TaskHandle_t processor_taskhandle); //停止 taskhandle 任务的 Mic
    void Suspend(); //挂起任务
    void Suspend(TaskHandle_t processor_taskhandle); //挂起任务 taskhandle  任务的 Mic
    void Resume(uint32_t delay = 0);  //恢复任务

    bool IsProcessing(TaskHandle_t processor_taskhandle); //当前是否正在运行的 taskhandle    
    void SetProcessor(TaskHandle_t processor_taskhandle); // 设置需要通知的 AudioProcessorTask

    I2SSampler * sampler() { return i2s_sampler_;}
};

