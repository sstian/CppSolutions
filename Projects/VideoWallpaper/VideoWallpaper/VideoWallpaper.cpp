#include <windows.h>
#include <stdio.h>

BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// ��������һ�����ڣ�����ΪWorkerW��������
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{
	// ��Ƶ·������ȣ��߶ȣ�����ѭ��������ʹ��GetSystemMetrics()��ȡ�ֱ�������
	LPCWSTR lpParameter = L" D:\\Develop\\CppSolutions\\Projects\\VideoWallpaper\\VideoWallpaper\\media\\angry_birds.mp4 -noborder -x 1920 -y 1080 -loop 0";
	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	// ffplay.exe��·��
	if (CreateProcess(L"D:\\Program\\ffmpeg\\bin\\ffplay.exe", (LPWSTR)lpParameter, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		while (!FindWindow(L"SDL_app", 0));
		Sleep(200);												// �ȴ���Ƶ�������������

		HWND hProgman = FindWindow(L"Progman", 0);				// �ҵ�Program Manager����
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	// ������������Ϣ
		HWND hFfplay = FindWindow(L"SDL_app", 0);				// �ҵ���Ƶ����
		SetParent(hFfplay, hProgman);							// ����Ƶ��������ΪProgram Manager���Ӵ���
		EnumWindows(EnumWindowsProc, 0);						// �ҵ��ڶ���WorkerW���ڲ�������
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}