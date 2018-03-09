从darknet改写的车辆检测demo，需要配置opencv和cuda(如果使用GPU)，不使用GPU的话把Makefile的第一行改成GPU=0。

1.下载weights
```
wget https://pjreddie.com/media/files/yolo.weights
```
2.make
```
make
```
3.运行两个shell文件即可(run-video.sh要改一下视频路径)。
```
./run-cam.sh
```
![Darknet Logo](http://pjreddie.com/media/files/darknet-black-small.png)

# Darknet
Darknet is an open source neural network framework written in C and CUDA. It is fast, easy to install, and supports CPU and GPU computation.

For more information see the [Darknet project website](http://pjreddie.com/darknet).

For questions or issues please use the [Google Group](https://groups.google.com/forum/#!forum/darknet).
