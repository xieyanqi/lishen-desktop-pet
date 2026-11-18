# 黎深桌宠

一个《恋与深空》黎深同人桌宠。工作时，捧杯的白黎陪你计时，鼠标移过去他会随机说一句话。休息时换成黑黎，可以给他投喂甜食。

<img src="preview.png" alt="坐着捧杯子的 Q 版黎深桌宠预览" width="160">

[下载黎深桌宠安装包（.rmskin）](https://github.com/xieyanqi/lishen-desktop-pet/raw/refs/heads/main/LiShen-Desktop-Pet.rmskin)

## 第一次安装

适用于 Windows 11 或 64 位 Windows 10（1903 及以上）。整个过程用鼠标操作即可。

1. 打开 [Rainmeter 官网下载页](https://www.rainmeter.net/changes-5.0/)，点击 **Download Rainmeter 5.0 RC2**。如果打开的是 GitHub 发布页，在 **Assets** 里选 `Rainmeter-5.0.0.5363-RC2.exe`。运行安装文件，选 **Standard installation（标准安装）**。如果想让黎深随电脑启动，勾选 **Launch Rainmeter on startup（开机启动 Rainmeter）**。
2. 打开 Rainmeter。点击本页上方的 **下载黎深桌宠安装包**，在电脑的「下载」文件夹里双击 `LiShen-Desktop-Pet.rmskin`，点 **Install（安装）**。
3. 回到桌面，在右下角找黎深。找到了就可以拖到喜欢的位置。想立刻看一次提醒，右键黎深，选 **现在休息**。

## 从旧版升级

重新下载最新安装包，双击并点击 **Install（安装）** 即可。原来的休息项目保存在 Rainmeter 的设置里，升级后会继续读取。新版是 **1.2.1**，Rainmeter 管理窗口里会显示作者 **Astrizaynie**。

## 修改工作和休息时长

右键黎深，选择 **设置工作和休息时长**。记事本里默认是工作 **45 分钟**、休息 **5 分钟**。改等号右边的数字，每项可填 **1 到 999** 的整数。按 **Ctrl + S** 保存，桌宠通常会在三秒内读取新设置，并按已经过去的时间继续计时。

## 设置自己的休息项目

右键黎深，选 **设置休息项目**。记事本里已经放了几条示例，你可以把它们替换成自己的安排，每行写一项，例如：

```text
倒一杯水
去阳台走两步
站起来伸展一下肩颈
```

按 **Ctrl + S** 保存，再关掉记事本。下次提醒会读取你刚保存的项目。如果留空，会使用示例项目。

工作时，把鼠标停在白黎身上可以看剩余时间。到点时，举手版白黎和提醒气泡会出现约 4 秒，也可以点 **开始休息** 立即切换。之后黑黎会显示休息倒计时。倒计时归零后自动进入下一轮工作，也可以点 **结束休息** 提前回到白黎。

## 悬停语录与投喂

- **工作时**，把鼠标移到白黎身上，会从 87 条内置语录和你补充的句子里随机选一句。移开后再靠近，可以看到另一句。
- **休息时**，把鼠标移到黑黎身上，他的右上方会出现带蓝色雪花的小菜单。点击 **黑巧克力、草莓蛋糕或马卡龙**，黑黎会切换到吃甜食的表情约 10 秒，菜单会显示一个随机颜文字（共 56 种）。休息计时仍在运行，最后 10 秒内停止接收投喂。

## 补充与分享语录

在桌宠上右键，选 **补充我的语录**。在记事本里每行加一句，按 **Ctrl + S** 保存。以 `#` 开头的行视为说明。下次把鼠标移到白黎身上时，你新增的句子就会参与抽取。

语录保存在你自己的电脑上。想把某句分享给 Astrizaynie 时，可以右键选 **在 GitHub 主动分享语录**，在打开的 GitHub 页面里手动粘贴想分享的句子，再提交公开 Issue。只粘贴你愿意公开的句子。

## 开机启动与性能

新版每秒更新一次，语录文件等到第一次悬停时才读取。桌宠本身在本机运行，点击分享入口时才会打开 GitHub。

在 Windows 按 **Ctrl + Shift + Esc**，打开 **任务管理器 → 启动应用**，可以查看 Rainmeter 的「启动影响」。如果你希望 Rainmeter 完全不参与登录时启动，右键它选 **禁用**。以后需要桌宠时，从开始菜单搜索并打开 **Rainmeter**。如果它已经在运行，关闭自启不会把它关掉。[微软官方操作说明](https://support.microsoft.com/en-gb/windows/experience/startup-boot/configure-startup-applications-in-windows)

## 遇到问题

| 情况 | 怎么处理 |
| --- | --- |
| 点下载链接后没开始下载 | 打开 [安装包文件页](https://github.com/xieyanqi/lishen-desktop-pet/blob/main/LiShen-Desktop-Pet.rmskin)，点击文件右上角的下载图标 **Download raw file**。 |
| 双击安装包后，Windows 问用什么打开 | 先完成 Rainmeter 的标准安装，再双击以 `.rmskin` 结尾的文件。 |
| 安装完成，桌面上没有小人 | 点任务栏右下角的 Rainmeter 雨滴图标。在 **Manage（管理）→ Skins（皮肤）** 里展开 **LiShen**，选中 **LiShen.ini**，点 **Load（加载）**。看不到 LiShen 时，先点 **Refresh all（刷新全部）**。 |
| Rainmeter 提示版本太旧 | 装 [Rainmeter 5.0 RC2 或更新版本](https://www.rainmeter.net/changes-5.0/)，再双击桌宠安装包。 |
| 想关掉黎深 | 右键小人，选择 **Unload skin（卸载皮肤）**。想再用时，从 Rainmeter 的管理窗口重新加载 **LiShen.ini**。 |
| 安装包还要留着吗 | 确认黎深已出现在桌面后，可以删掉「下载」里的安装包。日常运行需要保留 Rainmeter 和已经安装的桌宠皮肤。 |

黎深和《恋与深空》为原作角色及作品。本项目为非官方同人制作。
