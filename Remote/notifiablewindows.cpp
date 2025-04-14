#include "notifiable.h"
#include "notifiablewindows.h"
#include <QTimer>
#include <QResource>
#include <QWidget>


NotifiableWindows::NotifiableWindows(QWidget *parent)
    : parent(parent)
{
}

NotifiableWindows::~NotifiableWindows()
{
}

void NotifiableWindows::notify([[maybe_unused]] const QString &file_name, const QString &title, const QString &message) {
    HWND hwnd = (HWND) parent->winId();
    memset(&nid, 0, sizeof(NOTIFYICONDATA));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd; // Associated window
    nid.uID = 1000;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    nid.uFlags = NIF_ICON | NIF_MESSAGE; // Omit balloon info initially

    // Add the icon to the system tray.
    if (!Shell_NotifyIcon(NIM_ADD, &nid)) {
        qWarning("Shell_NotifyIcon(NIM_ADD) failed. Error: %lu", GetLastError());
    }

    nid.uFlags |= NIF_INFO;            // Add balloon tip information
    nid.dwInfoFlags = NIIF_INFO;       // Balloon icon type (information)
    nid.uTimeout = 2500;               // Display timeout

    // Copy title and message
    std::wstring title_w = title.toStdWString();
    std::wstring message_w = message.toStdWString();
    wcsncpy_s(nid.szInfoTitle, title_w.c_str(), _TRUNCATE);
    wcsncpy_s(nid.szInfo, message_w.c_str(), _TRUNCATE);

    // Show/update the notification
    if (!Shell_NotifyIcon(NIM_MODIFY, &nid)) {
        qWarning("Shell_NotifyIcon(NIM_MODIFY) failed. Error: %lu", GetLastError());
    }
}

HICON NotifiableWindows::loadHICONFromResource(const QString &file_name, int desired_width, int desired_height)
{
    QResource resource(file_name);
    if (!resource.isValid()) {
        qWarning("Resource %s is not valid!", qPrintable(file_name));
        return nullptr;
    }

    const uchar* data = resource.data();
    DWORD size = resource.size();

    HICON hIcon = CreateIconFromResourceEx(
        const_cast<BYTE*>(data), // pointer to icon image bits
        size,                    // size of resource data
        TRUE,                    // is it an icon? (TRUE) not a cursor.
        0x00030000,              // version number (commonly 0x00030000)
        desired_width,           // desired icon width
        desired_height,          // desired icon height
        LR_DEFAULTCOLOR          // load flags
        );

    if (!hIcon) {
        DWORD error = GetLastError(); // Get the specific error code
        qWarning("Failed to create HICON from resource: %s. Error code: %lu",
                 qPrintable(file_name), error);
    }

    return hIcon;
}
