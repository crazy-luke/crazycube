
###  [English Readme](README-ENGLISH.md) | [中文说明](README.md) 


# 疯狂豆立方应用系统

## 名词解释
  * CrazyCube：`超级立方豆`项目代号
  * AppOS：疯狂豆立方应用系统开发主体框架
  * 疯狂豆立方应用系统： `超级立方豆`固件系统（包含 AppOS + APP ）

## 关于
 `疯狂豆立方应用系统` 是为`超级立方豆`开发的固件系统。 
 由 C++ 编写, 代码风格 见[Code Style](code_style.md)
 
 本开源代码包含 AppOS 全套源码及典型的APP应用（APP覆盖了全部硬件掉调用场景）：
 
  1. 完整的交互系统，与超级立方豆官方固件正式版保持一致。
  2. 语音唤醒、语音聊天、蓝颜手势键盘、网络音频播放、Web 服务、小游戏 、文件夹等
  


## 编译与配置 

1. IDE

	[VSCode + PlatformIO](https://platformio.org/install/ide?install=vscode)
	
2. 工程配置  
	- 下载第三方依赖库：初次打开工程等待第三方库依赖库下载完成（会自动下载到`.pio/libdeps/CrazyCube`目录下）
	- 修改第三方依赖库配置：将  **conf_lib** 目录下所有文件复制到第三方库对应目录下 (想要了解细节可查看`conf_lib/README.md`)：
		* 例如：`conf_lib/lvgl/lv_conf.h` 复制到（覆盖原文件） `.pio/libdeps/CrazyCube/lvgl/lv_conf.h` 等

3. 编译和运行
	*  执行 `Upload ` 上传代码到立方豆
	*  执行 `Upload Filesystem Image` 上传文件资源到立方豆
	*  恭喜， 完成所有事项 🎉


## 注意事项
1. 出现问题不要怀疑代码，不要改动工程，检查自己的环境。
2.  第三方库下载大概 150MB ，请耐心等待，条件允许尽量不要使用 **离线库**，方便后续更新版本。
 
 

## 工程结构说明

### 工程目录
目录  				|说明
----------------	| -------------
lib/				|第三方依赖库（离线依赖目录)
.pio/				|第三方依赖库（在线下载依赖目录)
conf_lib/   		|第三方依赖库配置资料（第三方库配置文件)
extra/   			|扩展资料（可以不看）
data/           	|资源文件，包括 Web 网页、音频、图像资源等
src/				|项目源代码

src 项目源代码  	|说明
----------------	| -------------
app/        	|APP 应用
framework/	|系统 API
keychain/    	|数据持久化记录
lv/         	|lvgl 工具集 
os/       	|AppOS
outlander/   	|外部应用
tools/       |一般工具集
main.cpp	   |程序入口




###  第三方库依赖库

* `TFT_eSPI `	屏幕驱动
* `Gesture PAJ7620 `	红外手势驱动
* `I2Cdevlib-MPU6050` 	陀螺仪驱动
* `FastLED`	LED灯珠驱动	
* `lvgl` 图形库
* `OneButton`	按钮库
* `ESPAsyncWebServer-esphome`	Web服务
* `ESP32-audioI2S`	音频播放
* `ArduinoJson`	Json解析
* `TensorFlowLite_ESP32`	TensorflowLite
* `NimBLE-Arduino` 	蓝牙键盘
* `ESP32 BLE Keyboard`	蓝牙键盘

	
        
### PSRAM

本项目大量使用 PSRAM，可通过查找 ps_malloc，ps_calloc 关键字查找。 
如移植到其他工程可按实际情况替换 psram




## License

<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.

Copyright © 2023, 疯狂豆® 
  