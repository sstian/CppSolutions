@ECHO OFF

REM �����������ļ�
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*_backup

REM �Զ����Ƶ�ǰ�ѱ��ݺõ������ֿ��ļ���Ĭ��λ�� 
COPY  SGPYEUDC*.* %UserProfile%\AppData\LocalLow\SogouPY\EUDC\


