#pragma once

#ifdef DLLDEMO_EXPORT
#define DLLDEMO __declspec(dllexport)
#else
#define DLLDEMO __declspec(dllimport)
#endif // DLLDEMO_EXPORT

// If used by C++ code, we need to export the C interface
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	DLLDEMO int add(int a, int b);
	DLLDEMO int sub(int a, int b);

#ifdef __cplusplus
}
#endif // __cplusplus