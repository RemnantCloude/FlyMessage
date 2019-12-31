#include "fm_connectform.h"
#include "ui_connectform.h"
#include "aero.h"

FM_ConnectForm::FM_ConnectForm(QWidget *parent):
    QWidget (parent),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    setWindowTitle("联系我们");
    initWindowStyle();

}

FM_ConnectForm::~FM_ConnectForm()
{
    delete ui;
}

void FM_ConnectForm::setAeroStyle()
{
    HWND hwnd = (HWND)this->winId();
    DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_EX_LAYERED);

    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (hUser)
    {
        pfnSetWindowCompositionAttribute setWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (setWindowCompositionAttribute)
        {
            ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
            WINDOWCOMPOSITIONATTRIBDATA data;
            data.Attrib = WCA_ACCENT_POLICY;
            data.pvData = &accent;
            data.cbData = sizeof(accent);
            setWindowCompositionAttribute(hwnd, &data);
        }
    }
}

void FM_ConnectForm::initWindowStyle()
{
    //setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setAeroStyle();

    QImage alphaChannel(size(),QImage::Format_Alpha8);
    alphaChannel.fill(0);
    QPalette pal;
    pal.setBrush(QPalette::Window, QBrush(alphaChannel));
    setPalette(pal);
}
