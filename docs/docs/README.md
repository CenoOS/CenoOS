# Introduction
![CenoOS](https://raw.githubusercontent.com/CenoOS/Ceno-RTOS/master/docs/assets/twitter_header_photo_1.png)
CenoOS is a real time operating system for IOT devices from cenocloud.

# Docuemnt

## Architecture Overview
![Architecture](https://raw.githubusercontent.com/CenoOS/Ceno-RTOS/master/docs/assets/arch2.png)
 
## Prepare

### 开发版
在根目录/conf/makefile.conf中修改如下配置:
```makefile
# 开发板支持
ARCH=arm32
BOARD=ek-TM4C123gxl
MCU=TM4C123GH6PM
LINK_FILE=link.ld
OCD_CFG_FILE=ek-tm4c123gxl.cfg
```
!> 其中选项对应board下支持的开发版

### 配置OPENOCD

```makefile
OPENOCD_SCRIPT_DIR=/usr/local/share/openocd/scripts/board
```

### 配置项目

```makefile
BASE_DIR=/Users/neroyang/project/Ceno-RTOS

```

### 构建

#### OPENOCD启动

```bash
cd user
make openOCD_connect
```

#### 构建

```bash
make clean
make build
```

#### 烧写

```bash
make flash
```

### 写在最后
have a good trial!

## Drivers+BSP

## HAL

## Kernel

## Network

# Community

# License
CenoOS is released under the Apache 2.0 license