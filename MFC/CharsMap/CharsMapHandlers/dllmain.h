// dllmain.h: 模块类的声明。

class CCharsMapHandlersModule : public ATL::CAtlDllModuleT<CCharsMapHandlersModule>
{
public :
	DECLARE_LIBID(LIBID_CharsMapHandlersLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CHARSMAPHANDLERS, "{41db9072-db10-4179-a8cf-4d0bc9675bd0}")
};

extern class CCharsMapHandlersModule _AtlModule;
