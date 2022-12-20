@ECHO OFF

REM 删除掉复制的文件
DEL %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???

REM 重命名还原为本地文件
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???_backup SGPYEUDC*.???