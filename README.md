# graduation-project  
SD卡备份中是用于zenq的linux系统上的一些文件，比如设备树，灯光操作等。  
olddata中是以前放入的一些文件，暂时没有什么用处。  
1.txt是分析出来的数据的示例。
agenttest.c是用来测试bluz中的agent的源码文件，暂时无用。  
dbustest1.c是插入蓝牙适配器之后，用来连接mindwave用的代码。  
doc是文档，里面介绍一些基本步骤。  
marshal.c和marshal.h是编译dbustest1.c时使用到的。  
pmake中存放着一些用到的linux命令。  
result.txt中存放的是收集到的mindwave的原始的串口数据。  
simple-agent是python写成的agent，用于bluez。  
test1.c是用来通过socket连接mindwave，读取其中的数据流的。  
获取数组.cpp是用来根据数字，获取需要的图片的数组。  
作图文档是一些数字在你图中的位置信息。  

有点乱，回头等比较完善了，再整理下。  

question:
SW和LD基本上加上，连接指示的灯光也设立，gpio76用于启动脚本启动程序用。
目前打算在PL部分做KNN算法和带通滤波器
准备在linux系统上做脑波信号的存储工作，初始准备是两个文件，一个文件记录raw原始波，另一个文件记录11种波形。	搞定
linux系统时间重置的问题，考虑下。
SW控制的问题，目前可用SW剩下7个，也就是可以有127种功能。考虑下软件中怎么嵌入SW变化时功能的变化。	搞定