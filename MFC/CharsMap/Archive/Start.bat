@ECHO OFF

REM 重命名本地文件
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*_backup

REM 自动复制当前已备份好的自造字库文件到默认位置 
COPY  SGPYEUDC*.* %UserProfile%\AppData\LocalLow\SogouPY\EUDC\


