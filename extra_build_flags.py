# CrazyCube C++ 
# c
# 参考：https://community.platformio.org/t/separate-settings-for-c-and-c-versions/21647/2
# CPPFLAGS for all,   CFLAGS for C， CXXFLAGS for C++

Import("env")
cpp = env["CPPFLAGS"]
# cpp += ["-Wno-write-strings"]
env.Replace(CPPFLAGS=cpp)

Import("env")
c = env["CFLAGS"]
c = [x for x in c if not "-std" in x]
c += ["-std=gnu11"]
# c += ["-Wno-implicit-function-declaration"]
env.Replace(CFLAGS=c)

cxx = env["CXXFLAGS"]
cxx = [x for x in cxx if not "-std" in x]
cxx += ["-std=gnu++17"]
# cxx += ["-Wno-narrowing"]
# cxx += ["-Wno-reorder"]
# cxx += ["-Wno-parentheses"]
# cxx += ["-Wno-sizeof-pointer-memaccess"]
# cxx += ["-Wno-cpp"]
# cxx += ["-Wno-register"]
env.Replace(CXXFLAGS=cxx)