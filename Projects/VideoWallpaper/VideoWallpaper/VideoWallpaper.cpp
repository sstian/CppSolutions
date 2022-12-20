#include <windows.h>
#include <stdio.h>

BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// 找它的下一个窗口，类名为WorkerW，隐藏它
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{
	// 视频路径，宽度，高度，无限循环。建议使用GetSystemMetrics()获取分辨率属性
	LPCWSTR lpParameter = L" D:\\Develop\\CppSolutions\\Projects\\VideoWallpaper\\VideoWallpaper\\media\\angry_birds.mp4 -noborder -x 1920 -y 1080 -loop 0";
	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	// ffplay.exe的路径
	if (CreateProcess(L"D:\\Program\\ffmpeg\\bin\\ffplay.exe", (LPWSTR)lpParameter, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		while (!FindWindow(L"SDL_app", 0));
		Sleep(200);												// 等待视频播放器启动完成

		HWND hProgman = FindWindow(L"Progman", 0);				// 找到Program Manager窗口
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	// 给它发特殊消息
		HWND hFfplay = FindWindow(L"SDL_app", 0);				// 找到视频窗口
		SetParent(hFfplay, hProgman);							// 将视频窗口设置为Program Manager的子窗口
		EnumWindows(EnumWindowsProc, 0);						// 找到第二个WorkerW窗口并隐藏它
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}