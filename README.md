# ConnectionClient - Qt 即时通讯客户端

基于 C++ 与 Qt (Widgets) 开发的桌面即时通讯（IM）客户端，界面采用清爽的粉色主题。配合配套的 TCP 服务端使用，支持账号注册登录、好友搜索添加、实时单聊、文件断点/分块传输以及本地历史消息持久化。

---

## 💡 这是个什么项目？

本项目是一个典型的 **C/S 架构即时通讯客户端**：
- **客户端负责**：用户交互界面、网络多线程通信收发、文件读取与下载存储、本地 SQLite 聊天历史记录管理。
- **服务端交互**：基于 TCP Socket 协议与后端服务器长连接，传输基于自定义数据包协议的 JSON 控制指令与二进制文件流。

> **注意**：本项目为**客户端源码**，需配合后端通讯服务端运行。如果本地测试，请确保服务端已启动并正确配置 IP 端口。

---

## 🎯 核心功能

1. **账号系统**
   - **注册与登录**：支持新用户注册，系统自动下发专属用户 ID；支持用户名/密码登录。
   - **个人信息管理**：支持在线修改个人昵称与登录密码。

2. **好友系统**
   - **精准搜索**：支持按用户 ID 或昵称搜索用户并发送添加好友请求。
   - **请求审批**：收到好友申请时弹窗提示，支持一键同意或拒绝。
   - **好友列表**：展示全部好友、实时在线状态及信息查看。

3. **即时聊天**
   - **一对一单聊**：类微信/QQ 的气泡式消息对话界面（头像、时间戳、左右气泡）。
   - **本地聊天记录**：基于本地 SQLite 数据库（`chat.db`）自动存储消息，再次打开会话自动还原历史记录。

4. **文件传输**
   - **文件发送**：支持任意类型文件分块（64KB Chunk）流式发送，不限制文件格式。
   - **文件接收**：接收到的文件自动存放于程序运行目录下的 `ReceivedFiles/` 文件夹（重名自动按序号重命名）。
   - **文件消息卡片**：聊天窗口展示文件名称与格式化大小（KB/MB/GB），点击直接在系统文件管理器中打开文件所在目录。

---

## 🛠️ 技术亮点

- **UI 与网络通信多线程分离**：网络核心（`client`）通过 `moveToThread` 运行在独立的 `QThread` 工作线程中，收发大文件或网络波动时主界面完全不卡顿。
- **自定义 TCP 二进制通信协议**：设计了固定 8 字节包头（`Type` 4 字节 + `Length` 4 字节）+ 动态包体，彻底解决 TCP 通信中的粘包与拆包问题。
- **轻量本地存储**：无需额外安装 MySQL 等外部数据库，本地直接通过 Qt 驱动的 SQLite 文件数据库读写聊天记录。

---

## 📡 数据通信协议与数据结构

客户端与服务端之间采用 **TCP 长连接**，所有数据传输均封装为**带 8 字节定长包头**的自定义协议帧，彻底规避 TCP 粘包与半包问题。

### 1. 底层数据包封包格式 (TCP Frame)

| 字节偏移 | 字段名 | 数据类型 | 字节序 | 作用与说明 |
| :--- | :--- | :--- | :--- | :--- |
| `0 ~ 3` | `Type` | `quint32` (4 字节) | 大端 (Big-Endian) | 包类型标识：<br>• `1`：JSON 业务指令报文<br>• `2`：二进制文件数据块<br>• `3`：文件元信息头 |
| `4 ~ 7` | `Length` | `quint32` (4 字节) | 大端 (Big-Endian) | 后续包体（Payload）的有效字节长度 |
| `8 ~ ...`| `Payload` | 二进制 / UTF-8 | - | 具体载荷内容（紧凑 JSON 字符串或原始文件数据流） |

---

### 2. 客户端发送的数据结构 (Client ➔ Server)

| 业务场景 | 报文标识 (`type`) | 字段结构 | 示例 Payload | 说明 |
| :--- | :--- | :--- | :--- | :--- |
| **用户注册** | `register` | `name`: string<br>`pwd`: string | `{"type":"register","name":"alice","pwd":"123"}` | 发起新用户注册 |
| **用户登录** | `login` | `name`: string<br>`pwd`: string | `{"type":"login","name":"alice","pwd":"123"}` | 发起登录验证 |
| **发送文本消息** | `message` | `sendid`: string<br>`receiveid`: string<br>`content`: string<br>`sendTime`: string (ISO) | `{"type":"message","sendid":"10001","receiveid":"10002","content":"你好","sendTime":"2026-10-14T15:00:00.000"}` | 发送单聊文本消息 |
| **按 ID 申请好友** | `addfriend` | `addname`: `""`<br>`addid`: string | `{"type":"addfriend","addname":"","addid":"10002"}` | 根据用户数字 ID 发起好友申请 |
| **按昵称申请好友** | `addfriend` | `addname`: string<br>`addid`: `""` | `{"type":"addfriend","addname":"张三","addid":""}` | 根据用户昵称发起好友申请 |
| **同意好友申请** | `acceptfriend`| `addname`: string | `{"type":"acceptfriend","addname":"张三"}` | 接收方同意对方的好友申请 |
| **修改个人昵称** | `changename` | `name`: string | `{"type":"changename","name":"新昵称"}` | 修改当前用户的昵称 |
| **修改登录密码** | `changepwd` | `oldpwd`: string<br>`newpwd`: string | `{"type":"changepwd","oldpwd":"123","newpwd":"456"}` | 修改当前用户的登录密码 |
| **发送文件元信息** | *(底层 Type 3)* | `filename`: string<br>`size`: int64<br>`sendid`: string<br>`receiveid`: string | `{"filename":"demo.zip","size":1048576,"sendid":"10001","receiveid":"10002"}` | 开始发送文件前通知对方准备接收 |
| **发送文件数据块** | *(底层 Type 2)* | 原始二进制数据流 | 每次发送最大 64KB (`64 * 1024` 字节) 数据块 | 流式循环读取文件并发送分块 |

---

### 3. 客户端接收与解析的数据结构 (Server ➔ Client)

| 业务场景 | 报文标识 (`type`) | 字段结构 | 示例 Payload | 客户端解析与处理行为 |
| :--- | :--- | :--- | :--- | :--- |
| **注册响应** | `register_response` | `status`: string (`"success"`/`"fail"`)<br>`message`: string<br>`userid`: int | `{"type":"register_response","status":"success","message":"注册成功","userid":10001}` | 弹窗展示系统分配的数字 UserID，切回登录界面 |
| **登录响应** | `login_response` | `success`: bool<br>`message`: string | `{"type":"login_response","success":true,"message":"ok:10001"}` | 验证成功后提取用户 ID（`message.mid(3)`），启动主界面 |
| **好友列表下发** | `friend_list` | `friends`: Array of Object:<br>• `user_id`: string<br>• `name`: string<br>• `status`: int<br>• `online`: bool | `{"type":"friend_list","friends":[{"user_id":"10002","name":"李四","status":0,"online":true}]}` | 解析并初始化所有好友项，创建对应的会话和聊天窗口 |
| **接收聊天消息** | `message` | `sendid`: string<br>`receiveid`: string<br>`content`: string<br>`sendTime`: string (ISO) | `{"type":"message","sendid":"10002","receiveid":"10001","content":"在吗？","sendTime":"2026-10-14T15:00:00.000"}` | 追加聊天气泡，并同步插入本地 SQLite 数据库（`chatlog`） |
| **加好友申请反馈** | `addfriend_response` | `status`: string (`"success"`/`"fail"`)<br>`message`: string | `{"type":"addfriend_response","status":"success","message":"好友请求已发送"}` | 弹窗提示用户请求是否已成功到达服务端 |
| **收到新好友申请** | `addfriend_request` | `addid`: string<br>`addname`: string<br>`status`: int<br>`online`: bool | `{"type":"addfriend_request","addid":"10003","addname":"王五","status":0,"online":true}` | 弹出确认提示框询问是否同意添加该好友 |
| **同意好友通知** | `acceptfriend_response` | `userid`: string<br>`username`: string<br>`userstatus`: int<br>`online`: bool | `{"type":"acceptfriend_response","userid":"10003","username":"王五","userstatus":0,"online":true}` | 将新通过的好友动态插入联系人与会话列表 |
| **修改昵称反馈** | `changename_response` | `status`: string (`"success"`/`"fail"`) | `{"type":"changename_response","status":"success"}` | 提示昵称修改结果，并刷新界面 |
| **修改密码反馈** | `changepwd_response` | `status`: string (`"success"`/`"fail"`)<br>`message`: string | `{"type":"changepwd_response","status":"success","message":"修改成功"}` | 弹窗反馈密码更新结果 |
| **接收文件通知** | *(底层 Type 3 或)*<br>`file_notify` | `filename`: string<br>`size`: int64<br>`sendid`: string | `{"filename":"demo.zip","size":1048576,"sendid":"10002"}` | 在 `ReceivedFiles/` 目录中建立空文件（重名自动顺延），准备接收数据流 |
| **接收文件数据块** | *(底层 Type 2)* | 原始二进制数据流 | 每次接收的数据分块 | 流式写入目标文件；当接收字节达到 `size` 时关闭文件并在聊天气泡区生成文件卡片 |

---

### 4. 客户端本地 C++ 核心数据结构与存储

#### 核心结构体 (`allstructs.h`)
| 结构体名 | 成员属性 | 描述 |
| :--- | :--- | :--- |
| `FriendInfo` | `QString userID`<br>`QString name`<br>`int status`<br>`bool online` | 好友信息实体，注册为 Qt 元对象（`Q_DECLARE_METATYPE`）以便信号槽跨线程传递 |
| `FriendListMessage` | `QString type`<br>`QList<FriendInfo> friends` | 好友列表复合数据体 |
| `Message` | `QString type`<br>`QString sendid`<br>`QString receiveid`<br>`QString content`<br>`QDateTime sendTime` | 聊天消息实体（普通文字或以 `file:` 为前缀的文件记录） |

#### 本地 SQLite 数据表 (`chat.db` ➔ `chatlog`)
| 字段名 | 字段类型 | 约束 | 说明 |
| :--- | :--- | :--- | :--- |
| `id` | `INTEGER` | `PRIMARY KEY AUTOINCREMENT` | 自增主键 |
| `sendid` | `varchar(20)` | - | 发送者用户 ID |
| `receiveid` | `varchar(20)` | - | 接收者用户 ID |
| `content` | `TEXT` | - | 消息内容（普通文本或 `file:本地全路径`） |
| `sendTime` | `varchar(20)` | - | 消息发送时间戳（ISO 8601 格式） |

---

## 📦 目录结构

```text
ConnectionClient/
├── main.cpp                  # 程序入口，高 DPI 适配与元类型注册
├── ConnectionClient.pro      # Qt 项目工程文件 (qmake)
│
├── client.cpp / .h           # 网络底层核心（TCP Socket、线程收发、协议打包/解包）
├── allstructs.h              # 全局数据结构（用户信息、消息体、好友列表）
├── dbmanage.cpp / .h         # 本地 SQLite 数据库操作封装（chat.db）
├── filehandle.cpp / .h       # JSON 与 Message 结构体序列化/转换处理
│
├── loginwidget.cpp / .h      # 登录/注册界面（无边框圆角、阴影动效、抖动提示）
├── mywindow.cpp / .h         # 主界面（侧边导航菜单、堆叠多页面调度）
├── messagewidget.cpp / .h    # 消息会话主页面（左侧会话列表 + 搜索 + 右侧聊天区）
├── chatwidget.cpp / .h       # 单聊窗口组件（消息展示区、输入框、文件发送）
├── linemessage.cpp / .h      # 文本消息气泡组件
├── filelinemessage.cpp / .h  # 文件消息气泡组件（展示文件大小，点击打开路径）
├── friendlistitem.cpp / .h   # 好友列表项自定义控件
├── personalwidget.cpp / .h   # 个人资料与修改密码/昵称页面
│
├── images/                   # 界面图标资源（发送、头像、文件等）
├── font/                     # 自定义界面字体 (fonttt.ttf)
└── static.qrc                # Qt 资源集合文件
```

---

## 🚀 编译与运行

### 1. 环境准备
- **操作系统**：Windows 10 / 11
- **开发工具**：Qt Creator（推荐）
- **Qt 版本**：Qt 5.12 及以上（包含 5.15.2，支持 Qt 6，需安装 `Widgets`, `Network`, `Sql` 模块）
- **编译器**：MinGW (32-bit / 64-bit) 或 MSVC

### 2. 配置服务器地址（重要）
在本地运行前，请先指定客户端连接的服务端 IP 和端口：
打开 [client.cpp](client.cpp#L34-L35)，修改第 34~35 行：
```cpp
// 替换为您实际的服务端 IP 和监听端口
aimip = "127.0.0.1";  // 若本地测试改为 127.0.0.1，或填写实际服务器公网/局域网IP
aimport = "12345";    // 对应服务端的监听端口
```

### 3. 构建运行
- **使用 Qt Creator（推荐）**：
  1. 打开 Qt Creator，点击 `打开项目`，选择 `ConnectionClient.pro`。
  2. 选择构建套件（如 Desktop Qt 5.15.2 MinGW）。
  3. 点击左下角绿色箭头 **运行**（`Ctrl + R`）。
- **命令行编译**：
  ```bash
  cd ConnectionClient
  qmake ConnectionClient.pro
  mingw32-make
  # 运行生成的可执行文件
  ./debug/ConnectionClient.exe  # 或 release 目录下的 exe
  ```

---

## 📖 使用说明

1. **新用户注册**：
   - 首次启动程序显示登录窗口，点击下方的 **“注册账号”** 切换至注册模式。
   - 输入心仪的用户名与密码，点击“注 册”。
   - 注册成功后系统弹窗提示您的专属数字 ID，随后切回登录模式。
2. **账号登录**：
   - 输入注册时的用户名与密码，点击“登 录”即可进入主界面。
3. **添加好友**：
   - 在左侧会话栏顶部的搜索框中输入对方的 **用户 ID** 或 **昵称**，点击“搜索”。
   - 若本地未添加该好友，会弹出请求添加的确认对话框，点击“是”发送申请。
   - 对方客户端会收到弹窗提示，点击同意后双方自动加入好友列表。
4. **发送消息与文件**：
   - 在左侧列表中点击对应好友打开聊天窗口。
   - 输入文本后点击右下角 **“发送”** 或回车发送消息。
   - 点击 **“发送文件”** 可选择任意本地文件发送；对方收到后会显示文件卡片，文件自动保存在软件目录下的 `ReceivedFiles/` 目录中，点击卡片上的图标可直接在文件管理器中定位该文件。
5. **修改个人资料**：
   - 点击左侧侧边栏的 **“个人信息”** 菜单项，可以更新昵称或修改登录密码。