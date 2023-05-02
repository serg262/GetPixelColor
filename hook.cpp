#include "hook.h"

Hook* Hook::m_This;

int CALLBACK Hook::MouseProc(int nCode, DWORD wParam, DWORD lParam)
{
    switch (wParam)
    {
    case WM_LBUTTONDOWN:

Hook::m_This->hookEvent();
    break;

    default:
        break;
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}


Hook::Hook(QObject* parent)
    : QObject(parent)
{
    m_This = this;
    SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)&MouseProc, nullptr, 0);
}
