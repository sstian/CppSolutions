��������ơ�
����ʱ�䣺2019.04.10 15:30 - 2019.04.13 15:46
������ƣ�CharsMap �ַ�ӳ����
������ߣ�Sears Saint Tian  - ��̻� (st.tian@foxmail.com)
����������Microsoft Visual Studio Professional 2017 version 15.9.7 & MFC SDI
����������Windows SDK �汾 - 10.0.17763.0
����˵������Ϊ�ѹ�ƴ��/QQƴ�����뷨�����ϵͳĬ��EUDC����·����������ֻ��԰�װ���ѹ�ƴ�����뷨

��ʹ�ù��ߡ�
1. ר���ַ��༭����
    �ַ��� - Unicode���ַ����� - F8A1 ~ F8BA��˵�� - ��ʾ��д��ĸA-Z���ļ� - EUDC������ - 64 * 64��
    ��ѡ�����������ļ������� - CharsMap��CharsMap.TTE, CharsMap.EUF��·�� - D:\CharsMap.TTE
2. �ַ�ӳ���
    Windows + R => charmap��
    ���壺�������壨ר���ַ���
3. ע���༭����
  Windows + R => regedit��
  ·���������\HKEY_CURRENT_USER\EUDC\936\SystemDefaultEUDCFont
  3.1. ϵͳĬ��·����C:\Windows\Fonts\������ EUDC.EUF,  EUDC.TTE��Ȼ����û�У��� ;
  3.2. ����װ���ѹ�ƴ�����뷨����·��������Ϊ��
  SystemDefaultEUDCFont = C:\Users\Snow-Angel\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC_1.TTE
  �����ļ���OPTIONS.INI, SGPYEUDC_1.EUF, SGPYEUDC_1.TTE ������ɾ�������ܸ��ǣ���������������
  3.3 ����װQQƴ�����뷨����·��������Ϊ��
  SystemDefaultEUDCFont = C:\Users\Snow-Angel\AppData\Roaming\Tencent\QQPinyin\EUDC\QQPYEUDC_1.TTE

�����������
1. δ��װ�ѹ�ƴ�����뷨��
2. ��װ���ѹ�ƴ�����뷨���������ѹ��ļ��������Լ����ļ���ָ��Ŀ¼��û�취��ֻ�������������� -_-||��
3. �����������ȡϵͳ·������ Windows 10 x64 ������ �û�Snow-Angel Ϊ����
ϵͳ·������ϵͳ·���������ִ�Сд����Ӧ�ľ���·��
��ǰϵͳ�̷���    %SystemDrive% �� %HOMEDRIVE% => C:\Users\Snow-Angel>
��ǰϵͳĿ¼��    %SystemRoot% �� %Windir%            == 'C:\Windows'
��ǰ�û��ļ��У� %UserProfile%                                   == 'C:\Users\Snow-Angel'
                      �� %HOMEPATH%                                 == '\Users\Snow-Angel'
�����û��ļ��У� %AllUsersProfile%                             == 'C:\ProgramData'
��ʱ�ļ���1��     %temp%                                            == 'C:\Users\SNOW-Angel\AppData\Local\Temp'
��ʱ�ļ���2��     %SystemRoot%\Temp                       == 'C:\Windows\Temp'
�����ļ��У�      "%ProgramFiles%"                              == '"C:\Program Files"'

���ο����
�ɲο����漸������������
@ECHO OFF
REM �������ļ�
REN C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*111

REM �Զ����Ƶ�ǰ�ѱ��ݺõ������ֿ��ļ���Ĭ��λ��
COPY  SGPYEUDC*.* C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC

REM �������ַ��ļ�Ĭ��λ�ã��Ա��ֶ������ѱ��ݺõ������ַ��ļ�
START C:\Users\Administrator\AppData\LocalLow\SogouPY\EUDC

���ű�����
�ļ� Start.bat:
====================
@ECHO OFF

REM �����������ļ�
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.* SGPYEUDC*.*_backup

REM �Զ����Ƶ�ǰ�ѱ��ݺõ������ֿ��ļ���Ĭ��λ�� 
COPY  SGPYEUDC*.* %UserProfile%\AppData\LocalLow\SogouPY\EUDC\

�ļ� Recovery.bat��
====================
@ECHO OFF

REM ɾ�������Ƶ��ļ�
DEL %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???

REM ��������ԭΪ�����ļ�
REN %UserProfile%\AppData\LocalLow\SogouPY\EUDC\SGPYEUDC*.???_backup SGPYEUDC*.???
