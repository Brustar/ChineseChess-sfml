#include "Dialog.h"
#include <Windows.h>
#include <tchar.h>
#include "commdlg.h"
#include "../StringUtil.h"

void Dialog::alert(int row, int col)
{
    string buffer;
    buffer.append("row:").append(1, row + '0').append(",col:").append(1, col + '0');
    MessageBox(NULL, buffer.c_str(), _T("chess coordinate"), MB_OK);
}

int Dialog::confirm(string msg)
{
    return MessageBox(NULL, msg.c_str(), _T("you win!"), MB_YESNO | (MB_ICONQUESTION == IDYES));
}

void Dialog::showSavefile(string content)
{
    OPENFILENAME ofn;
    TCHAR szFileName[MAX_PATH] = {0};
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = _T("txt");
    if (GetSaveFileName(&ofn))
    {
        FILE* fp;
        if (fopen_s(&fp, szFileName, "w") != 0)
        {
            perror("fail to write");
            exit(1);
        }
        setlocale(LC_ALL, "zh_CN.utf8");
        int rc = fputs(content.c_str(), fp);
        if (rc == EOF)
            perror("fputws()");
        fclose(fp);
    }
}

bool Dialog::showOpenfile(RenderWindow* window, char buf[])
{
    char szBuffer[MAX_PATH] = { 0 };
    OPENFILENAME ofn = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = _T("fen文件(*.fen)\0*.fen\0所有文件(*.*)\0*.*\0");   // 文件过滤
    ofn.lpstrFile = szBuffer;
    ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
    ofn.nFilterIndex = 0;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
    if (GetOpenFileName(&ofn))
    {
        FILE* fp;
        int len;
        if (fopen_s(&fp, szBuffer, "r") != 0)
        {
            perror("fail to read");
            exit(1);
        }
        wstring title;
        StringUtil::char_to_wchar(&szBuffer[0],title);
        window->setTitle(title);
        while (fgets(buf, MAX_LINE, fp) != NULL)
        {
            len = strlen(buf);
            buf[len - 1] = '\0';
            return true;
        }
        fclose(fp);
    }
    return false;
}
