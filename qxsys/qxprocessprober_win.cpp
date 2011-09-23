#include <windows.h>
#include <w32api.h>
#include <tlhelp32.h>
#include "qxsys/qxprocessprober.h"

bool QxProcessProber::refreshProcessList()
{
    m_processMap.clear();

    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshotHandle == NULL) {
        m_error = RetrieveError;
        m_errorString = "Failed to load ToolHelp";
        return false;
    }

    PROCESSENTRY32 proc = { sizeof(proc) };

    if (Process32First(snapshotHandle, &proc)) {
        QString filename;
        filename = QString::fromWCharArray(proc.szExeFile);
        m_processMap[proc.th32ProcessID] = filename;
        while (Process32Next(snapshotHandle, &proc)) {
            filename = QString::fromWCharArray(proc.szExeFile);
            m_processMap[proc.th32ProcessID] = filename;
        }
    }

    return true;
}
