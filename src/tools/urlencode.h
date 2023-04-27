#pragma once

#include <WString.h>

class UrlEncode
{
private:
    unsigned char H2Int(char c);
public:
    String Decode(String str);
    String Encode(String str);
};