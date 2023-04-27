
/**
 * @file bridge_codelab.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "os/os.h"
#include "codelab/lab.h"

class CodelabOS: public OS
{
private:
    const char * kTag = "CodelabOS";
    Lab lab_;
public:
    CodelabOS(/* args */);
    ~CodelabOS();

public:
  void Init() override;
  void Routine() override;
};