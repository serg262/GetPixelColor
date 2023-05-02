#ifndef HOOK_H
#define HOOK_H

#include <QObject>
#include <windows.h>

class  Hook : public QObject {
    Q_OBJECT

public:
    Hook(QObject* parent = nullptr);

private:
    static int CALLBACK MouseProc(int nCode, DWORD wParam, DWORD lParam);
    static Hook* m_This;

signals:
   void hookEvent();

private:

    void emitSignal();

};

#endif // HOOK_H
