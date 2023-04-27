/**
 * @file os.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Root Application!
 * @version 1.0
 * @date 2022-10-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

class OS
{
public:
    virtual void Init() = 0;
    virtual void Routine() = 0;
};