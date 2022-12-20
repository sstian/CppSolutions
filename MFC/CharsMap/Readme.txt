【程序设计】
开发时间：2019.04.10 15:30 - 2019.04.13 15:46
软件名称：CharsMap 字符映射码
设计作者：Sears Saint Tian  - 田继辉 (st.tian@foxmail.com)
开发环境：Microsoft Visual Studio Professional 2017 version 15.9.7 & MFC SDI
环境参数：Windows SDK 版本 - 10.0.17763.0
附加说明：因为搜狗拼音/QQ拼音输入法会更改系统默认EUDC字体路径，本程序只针对安装的搜狗拼音输入法

【使用工具】
1. 专用字符编辑器：
    字符集 - Unicode，字符编码 - F8A1 ~ F8BA，说明 - 表示大写字母A-Z，文件 - EUDC，点阵 - 64 * 64；
    与选定字体链接文件：等线 - CharsMap，CharsMap.TTE, CharsMap.EUF，路径 - D:\CharsMap.TTE
2. 字符映射表：
    Windows + R => charmap，
    字体：所有字体（专用字符）
3. 注册表编辑器：
  Windows + R => regedit，
  路径：计算机\HKEY_CURRENT_USER\EUDC\936\SystemDefaultEUDCFont
  3.1. 系统默认路径：C:\Windows\Fonts\，存在 EUDC.EUF,  EUDC.TTE（然而并没有！） ;
  3.2. 若安装过搜狗拼音输入法，则路径被更改为：
  SystemDefaultEUDCFont = C:\Users\Snow-Angel\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC_1.TTE
  存在文件：OPTIONS.INI, SGPYEUDC_1.EUF, SGPYEUDC_1.TTE （不能删除，不能覆盖，但可以重命名）
  3.3 若安装QQ拼音输入法，则路径被更改为：
  SystemDefaultEUDCFont = C:\Users\Snow-Angel\AppData\Roaming\Tencent\QQPinyin\EUDC\QQPYEUDC_1.TTE

【解决方案】
1. 未安装搜狗拼音输入法；
2. 安装了搜狗拼音输入法：重命名搜狗文件，复制自己的文件到指定目录（没办法，只得针对这种情况了 -_-||）
3. 批处理命令获取系统路径：以 Windows 10 x64 教育版 用户Snow-Angel 为例子
系统路径含义系统路径（不区分大小写）对应的绝对路径
当前系统盘符：    %SystemDrive% 或 %HOMEDRIVE% => C:\Users\Snow-Angel>
当前系统目录：    %SystemRoot% 或 %Windir%            == 'C:\Windows'
当前用户文件夹： %UserProfile%                                   == 'C:\Users\Snow-Angel'
                      或 %HOMEPATH%                                 == '\Users\Snow-Angel'
所有用户文件夹： %AllUsersProfile%                             == 'C:\ProgramData'
临时文件夹1：     %temp%                                            == 'C:\Users\SNOW-Angel\AppData\Local\Temp'
临时文件夹2：     %SystemRoot%\Temp                       == 'C:\Windows\Temp'
程序文件夹：      "%ProgramFiles%"                              == '"C:\Program Files"'

【参考命令】
可参考下面几条批处理命令
@ECHO OFF
REM 重命名文件
REN C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*111

REM 自动复制当前已备份好的自造字库文件到默认位置
COPY  SGPYEUDC*.* C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC

REM 打开自造字符文件默认位置，以便手动复制已备份好的自造字符文件
START C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC

【脚本处理】
文件 Start.bat:
====================
@ECHO OFF

REM 重命名本地文件
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*_backup

REM 自动复制当前已备份好的自造字库文件到默认位置 
COPY  SGPYEUDC*.* %UserProfile%\AppData\LocalLow\SogouPY\EUDC\

文件 Recovery.bat：
====================
@ECHO OFF

REM 删除掉复制的文件
DEL %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???

REM 重命名还原为本地文件
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???_backup SGPYEUDC*.???
