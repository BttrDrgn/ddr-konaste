#include <d3d.h>
#pragma comment(lib, "d3d9.lib")

typedef HRESULT(APIENTRY* EndScene) (IDirect3DDevice9*);
EndScene end_scene = NULL;