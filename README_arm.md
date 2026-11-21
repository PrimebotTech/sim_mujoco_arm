# Sim Mujoco

本文为启元机器人 ARM 平台 MuJoCo 物理仿真及运控框架的使用与集成指南。全套仿真、运控框架与可视化服务均运行于 Docker 容器中，提供开箱即用的隔离运行环境。

## 整体架构
```text
+---------------------------------------------------------------------------------+
| 宿主机                                                                          |
|                                                                                 |
|     +--------------------------------+       +----------------------------+     |
|     | 本地代码工作区                   |       | Web 浏览器                  |     |
|     | (仿真与运控工程源码)              |       | (noVNC 客户端)              |     |
|     | 例如: ~/native_arm_rk_workspace |       +--------------▲-------------+     |
|     +--------------+--------------+                         │                   |
|                    │ 目录挂载 (-v)                           │ Web 端口映射       |
|                    ▼                                        ▼                   |
| +-----------------------------------------------------------------------------+ |
| |                                                                             | |
| |   +-----------------------------+          +----------------------------+   | |
| |   |   运控框架 / 自研算法程序      |          |     noVNC / websockify     |   | |
| |   |  (mc_framework_xx / 用户程序)|          |       (Web 桌面服务)         |   | |
| |   |        (终端 2 运行)         |          |      (终端 1 后台服务)       |   | |
| |   +--------------▲--------------+          +--------------▲-------------+   | |
| |                  │                                        │ VNC 协议流       | |
| |    ROS2 控制下发  │ ▼ 关节控制命令 / 运动速度指令              │                 | |
| |                  │                                        │                 | |
| |    ROS2 状态反馈  │ ▲ 关节状态反馈 / 机身 IMU 数据     +------+------+          | |
| |                  │                                 | x11vnc 服务 |           | |
| |   +--------------▼--------------+                  +------▲------+          | |
| |   | sim_mujoco_arm (物理仿真引擎)  |                         │ X11 显示流       | |
| |   | (终端 1 运行)                |                  +------+------+          | |
| |   +--------------+--------------+                  | Xvfb 虚拟显示|          | |
| |                  │          OpenGL 画面渲染         | + fluxbox   |          | |
| |                  +-------------------------------->| (桌面管理)   |          | |
| |                                                    +-------------+          | |
| |                                                                             | |
| |                                 Docker 容器                                  | |
| |                环境: ROS2 Humble / Python 3 / C++ toolchain                  | |
| +-----------------------------------------------------------------------------+ |
+---------------------------------------------------------------------------------+
```

### 组件说明

| 组件 | 说明 | 获取方式 |
|------|------|----------|
| **Docker 容器** | 提供统一的 ROS2 Humble、Python、C++ 编译环境，隔离宿主机依赖 | 访问 [PrimeBot 开发者下载站](https://dev.primebot.com/download) 下载构建包并构建镜像（或导入现成镜像包）；也可从 [GitHub](https://github.com/PrimebotTech) 下载 |
| **sim_mujoco_arm** | MuJoCo 物理仿真引擎，模拟机器人本体动力学，发布关节状态与 IMU 数据，接收关节命令和速度指令 | 访问 [PrimeBot 开发者下载站](https://dev.primebot.com/download) 下载仿真程序压缩包并解压至工作区；也可从 [GitHub](https://github.com/PrimebotTech) 下载 |
| **mc_framework_xx** | 运控框架，订阅关节状态和 IMU 数据，下发关节控制命令给 sim_mujoco（亦可替换为用户自研算法） | 访问 [PrimeBot 开发者下载站](https://dev.primebot.com/download) 下载/ 官方二开交付源码包（或用户自研）；也可从 [GitHub](https://github.com/PrimebotTech) 下载 |

### ROS2 Topic 通信一览

| Topic | 发布者 | 订阅者 | 说明 |
|-------|--------|--------|------|
| `/aima/hal/joint/state` | sim_mujoco | mc_framework_xx | 关节角度/速度状态 |
| `/aima/hal/imu/state` | sim_mujoco | mc_framework_qxx | 机器人q整体 IMU 数据 |
| `/aima/hal/imu/torso/state` | sim_mujoco | mc_framework_txx | 机器人t整体 IMU 数据 |
| `/aima/hal/joint/command` | mc_framework_xx | sim_mujoco | 关节力矩/位置控制命令 |
| `/aima/mc/locomotion/velocity` | mc_framework_xx | sim_mujoco | 速度运动指令 |

---

## 快速开始

> **重要：** 请确保 `sim_mujoco_arm` 项目位于 `~/native_arm_rk_workspace` 目录下，否则容器内将无法访问仿真程序。

### 整体流程概览

```
构建 Docker 镜像 ──► 启动容器 ──► 配置虚拟显示与远程桌面 ──► 配置环境并启动仿真 ──► 浏览器访问仿真界面
                                                                    │
                                                                    ▼
                                                            另开终端启动运控框架
```

1. **构建 Docker 镜像** — 下载构建包，构建 ARM 环境镜像
2. **启动容器** — 用 `docker run` 创建并进入容器（主机终端）
3. **配置虚拟显示** — 在容器内启动 Xvfb + VNC，使仿真界面可通过浏览器访问
4. **配置环境并启动仿真** — 加载 ROS2 环境，启动 sim_mujoco 仿真
5. **浏览器访问** — 打开 `http://localhost:6080/vnc.html` 查看仿真界面
6. **启动运控框架** — 另开终端进入容器，启动 mc_framework_xx

### 1. 构建 Docker 容器镜像

前往 https://dev.primebot.com/download ，滚动页面到下方 **ARM 原生编译** 区域，下载 `docker_arm_native_arm` 构建包。

下载完成后，请参照项目内的 `ARM原生编译完整指南.md` 进行 rk 版本 Docker 镜像构建。

**⚠️** 镜像构建完成后，会自动进入容器，请先执行 `exit` 退出容器，后续步骤会重新创建并启动容器。

### 2. 创建并启动 Docker 容器

在主机终端执行以下操作启动容器：

```bash
docker run -it --rm \
  -p 6080:6080 \
  --name mujoco_gui_arm \
  --net=host \
  -v ~/native_arm_rk_workspace:/native_arm_rk_workspace \
  native-aarch64-rk:latest bash
```

> 说明：`~/native_arm_rk_workspace` 挂载到容器内的 `/native_arm_rk_workspace`，仿真程序位于容器中的 `/native_arm_rk_workspace/sim_mujoco_arm`。

### 3. 配置虚拟显示与远程桌面（容器内执行）

使用 Xvfb + x11vnc + noVNC 方案，无需主机 X11 环境，通过浏览器即可访问仿真界面。

复制以下命令块一次性执行，`x11vnc` 和 `websockify` 启动后会输出提示信息，按 **回车** 跳过即可：

```bash
# 清理可能残留的锁文件
rm -f /tmp/.X99-lock

# 启动 Xvfb 虚拟显示
Xvfb :99 -screen 0 1280x1024x24 &

# 设置 DISPLAY 并验证
export DISPLAY=:99
xdpyinfo | head -n 3

# 启动 x11vnc，将 :99 的显示共享到本地 5900 端口（输出提示信息按回车跳过）
x11vnc -display :99 -forever -nopw -listen localhost -rfbport 5900 &

# 启动 websockify，将 VNC 服务包装为 WebSocket，监听 6080 端口（输出提示信息按回车跳过）
websockify --web /usr/share/novnc 6080 localhost:5900 &

# 启动 fluxbox 窗口管理器（输出提示信息按回车跳过）
fluxbox &
```

> - 如果 `xdpyinfo` 输出包含 `name of display: :99`，说明虚拟显示配置成功。
> - `x11vnc` 启动后会输出类似以下内容，按 **回车** 即可继续：
>   ```
>   ******************************************************************************
>   Have you tried the x11vnc '-ncache' VNC client-side pixel caching feature yet?
>   ...
>   ```
> - `websockify` 启动后会输出类似以下内容，按 **回车** 即可继续：
>   ```
>     - Listen on :6080
>     - Web server. Web root: /usr/share/novnc
>     - No SSL/TLS support (no cert file)
>     - proxying from :6080 to localhost:5900
>   ```
> - `fluxbox` 启动成功后，按 **回车** 即可继续。

### 4. 配置环境并启动仿真（容器内执行）

一次性复制以下命令块，完成环境配置和仿真启动：

```bash
# 进入项目目录，清空可能干扰的 MuJoCo GL 后端设置
cd /native_arm_rk_workspace/sim_mujoco_arm
unset MUJOCO_GL
unset LIBGL_ALWAYS_INDIRECT

# 加载 ROS2 环境
source /opt/ros/humble/setup.bash

# 加载自定义消息包
source share/aimdk_msgs/local_setup.bash

# 进入 bin 目录并赋予执行权限
cd bin
chmod +x ./start_sim_for_mc.sh

# 启动仿真
./start_sim_for_mc.sh -s
```

启动后进入交互式选择界面：

- **q**（机器人系列）选择：**2**
- **t**（机器人型号）选择：**8**
- 按 **回车** 确认启动

### 5. 通过浏览器访问仿真界面

在主机浏览器中打开：

```
http://localhost:6080/vnc.html
```

> **性能优化提示：** 打开界面后，展开 **Rendering** 设置选项，找到 **OpenGL effects**，关闭 **Shadow** 和 **Reflection** 来提升帧数。

---

## 启动运控框架

仿真启动后，需要**再开一个终端**，同样进入容器内启动运控框架。

### 1. 进入容器并配置环境（主机终端执行）

```bash
# 进入已运行的容器
docker exec -it mujoco_gui_arm bash

# 设置 DISPLAY 环境变量（与 Xvfb 虚拟显示保持一致）
export DISPLAY=:99
```

### 2. 安装依赖并运行

> **注意：** 请先将运控框架项目放入 `~/native_arm_rk_workspace` 目录下，因为 Docker 容器启动时已将该目录映射为容器内的 `/native_arm_rk_workspace`，否则容器内无法访问运控框架代码。

> **说明：** 以下仅列出基本的安装和启动命令，详细的配置参数、运行模式及调优说明请参考对应项目中的 `README.md` 文档。

根据仿真选择的机器人型号和使用的语言版本，选择对应的命令块执行：

| 仿真选项 | Python 项目 | C++ 项目 |
|---|---|---|
| q=2 | `mc_framework_q1` | `mc_framework_q1_c` |
| t=8 | `mc_framework_t1` | `mc_framework_t1_c` |

运行 Python Q项目：

```bash
cd /native_arm_rk_workspace/mc_framework_q1

pip install -e . -i https://pypi.tuna.tsinghua.edu.cn/simple

source /opt/ros/humble/setup.bash

source install/setup.bash

python3 examples/run_q1.py
```

运行 c++ Q项目：
```bash
cd /native_arm_rk_workspace/mc_framework_q1_c

chmod +x ./run.sh

./run.sh
```

运行 Python T项目：

```bash
cd /native_arm_rk_workspace/mc_framework_t1

pip install -e . -i https://pypi.tuna.tsinghua.edu.cn/simple

source /opt/ros/humble/setup.bash

source install/setup.bash

python3 examples/run_t1.py
```

运行 c++ T项目：
```bash
cd /native_arm_rk_workspace/mc_framework_t1_c

chmod +x ./run.sh

./run.sh
```

