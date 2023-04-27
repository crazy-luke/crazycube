/**
 * @file hamming_window.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 
 * @version 1.0
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <inttypes.h>

class HammingWindow
{
private:
    float *m_coefficients;
    int m_window_size;

public:
    HammingWindow(int window_size);
    ~HammingWindow();
    void applyWindow(float *input);
};