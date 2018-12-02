#include "stdafx.h"
#include "dir_handler.h"
#include "png_image.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

DirectoryHandler::DirectoryHandler(const WCHAR* dirPath, Gdiplus::Image* newLogo)
    : m_dirPath(dirPath)
    , m_newLogo(newLogo)
{
    if (!CheckFileName())
    {
        return;
    }

    CRect margin(0, 0, 0, 0);
    if (CalculateMargin(margin))
    {
        CutEdge(margin);
    }
}

DirectoryHandler::~DirectoryHandler()
{
    for (auto image : m_images)
    {
        delete image;
    }
    m_images.clear();
}

BOOL DirectoryHandler::CheckFileName()
{
    _tprintf(_T("    CheckFileName() running...\n"));
    if (!m_dirPath.IsDirectory())
    {
        return FALSE;
    }

    CPath path;
    path.Combine(m_dirPath, _T("*"));

    WIN32_FIND_DATA findData;
    HANDLE hFind = ::FindFirstFile(path, &findData);

    if (INVALID_HANDLE_VALUE == hFind)
    {
        return FALSE;
    }

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (_tcscmp(_T("."), findData.cFileName)
                && _tcscmp(_T(".."), findData.cFileName))
            {
                _tprintf(_T("    %s   <Unexpect DIR>\n"), findData.cFileName);
            }
        }
        else
        {
            m_fileNames.push_back(findData.cFileName);
        }
    } while (::FindNextFile(hFind, &findData));

    ::FindClose(hFind);

    size_t fileCount = m_fileNames.size();
    if (0 == fileCount)
    {
        std::cout << "    No files found!\n";
        return FALSE;
    }
    else if (1 == fileCount)
    {
        std::cout << "    " << fileCount << " file found!\n";
    }
    else
    {
        std::cout << "    " << fileCount << " files found!\n";
        std::sort(m_fileNames.begin(), m_fileNames.end());

        std::set<CString> fileNames;
        for (auto name : m_fileNames)
        {
            fileNames.insert(name);
        }

        TCHAR* fmt = (fileCount < 100) ? _T("%0.2u.png") : _T("%0.3u.png");
        std::set<CString> expectNames;
        for (size_t index = 1; index <= fileCount; ++index)
        {
            CString name;
            name.Format(fmt, index);
            std::set<CString>::iterator it = fileNames.find(name);
            if (it == fileNames.end())
            {
                expectNames.insert(name);
            }
            else
            {
                fileNames.erase(it);
            }
        }

        BOOL needConfirm = FALSE;
        if (!fileNames.empty())
        {
            needConfirm = TRUE;
            std::cout << "    Unexpect file name found:\n";
            for (auto name : fileNames)
            {
                _tprintf(_T("        %s\n"), (const TCHAR*)name);
            }
        }

        if (!expectNames.empty())
        {
            needConfirm = TRUE;
            std::cout << "    Expect file name not found:\n";
            for (auto name : expectNames)
            {
                _tprintf(_T("        %s\n"), (const TCHAR*)name);
            }
        }

        if (needConfirm)
        {
            char ch = 0;
            do
            {
                if (ch != '\n')
                {
                    _tprintf(_T("    Continue? [y] for Yes [n] for No: "));
                }

                ch = std::cin.get();
                if (ch == 'y')
                {
                    break;
                }
                if (ch == 'n')
                {
                    return FALSE;
                }
            } while (TRUE);
        }
    }

    std::cout << std::endl;
    return TRUE;
}

UINT64 RectToUint64(const CRect& rc)
{
    const UINT64 mask = 0xFFFFull;
    UINT64 ret = 0;
    UINT64 l = rc.left;     l &= mask; ret |= (l << 48);
    UINT64 t = rc.top;      t &= mask; ret |= (t << 32);
    UINT64 r = rc.right;    r &= mask; ret |= (r << 16);
    UINT64 b = rc.bottom;   b &= mask; ret |= b;
    return ret;
}

void RectFromUint64(UINT64 u64, CRect& rc)
{
    const UINT64 mask = 0xFFFFull;
    rc.left   = static_cast<LONG>((u64 >> 48) & mask);
    rc.top    = static_cast<LONG>((u64 >> 32) & mask);
    rc.right  = static_cast<LONG>((u64 >> 16) & mask);
    rc.bottom = static_cast<LONG>(u64 & mask);
}

BOOL DirectoryHandler::CalculateMargin(CRect& margin)
{
    _tprintf(_T("    CalculateMargin() running...\n"));

    // 最多取20张图片作为样本，计算margin
    const size_t MAX_SAMPLE_COUNT = 20;
    size_t count = m_fileNames.size() < MAX_SAMPLE_COUNT
                   ? m_fileNames.size()
                   : MAX_SAMPLE_COUNT;

    std::map<UINT64, std::vector<CString>> marginToFileName;
    for (size_t i = 0; i < count; ++i)
    {
        CPath path;
        path.Combine(m_dirPath, m_fileNames[i]);
        HyRead::PngImage* image = new HyRead::PngImage(path);
        image->EraseLogo(m_newLogo);
        CRect rect(0, 0, 0, 0);
        image->CalculateMargin(rect);
        marginToFileName[RectToUint64(rect)].push_back(m_fileNames[i]);
        m_images.push_back(image);
    }

    m_fileNames.erase(m_fileNames.begin(), m_fileNames.begin() + count);
    if (marginToFileName.size() == 1)
    {
        // 所有样本文件的margin都一样
        RectFromUint64(marginToFileName.begin()->first, margin);
        return TRUE;
    }

    std::map<UINT64, std::vector<CString>>::iterator itMF = marginToFileName.begin();
    std::map<char, UINT64> indexToMargin;
    _tprintf(_T("    [0] Cancel\n"));
    char index = '1';
    while (itMF != marginToFileName.end())
    {
        indexToMargin[index] = itMF->first;

        CRect rect(0, 0, 0, 0);
        RectFromUint64(itMF->first, rect);
        _tprintf(_T("    [%c] Rect(%d, %d, %d, %d) for %lu file(s):\n"),
                 index, rect.left, rect.top, rect.right, rect.bottom, itMF->second.size());
        for (auto name : itMF->second)
        {
            _tprintf(_T("        %s\n"), (const TCHAR*)name);
        }
        ++index;
        ++itMF;
    }

    char ch = 0;
    do
    {
        if (ch != '\n')
        {
            _tprintf(_T("    Choose margin by [x]: "));
        }

        ch = std::cin.get();

        std::map<char, UINT64>::iterator itIM = indexToMargin.find(ch);
        if (itIM == indexToMargin.end())
        {
            if (ch == '0')
            {
                return FALSE;
            }
        }
        else
        {
            RectFromUint64(itIM->second, margin);
            break;
        }
    } while (TRUE);

    return TRUE;
}

void DirectoryHandler::CutEdge(const CRect& margin)
{
    _tprintf(_T("    CutEdge() running...\n"));
    size_t count = 0;
    for (auto image : m_images)
    {
        image->CutEdge(margin);
        image->Save();
        delete image;
        ++count;
        if (count % 20 == 0)
        {
            _tprintf(_T("    ...%lu files done!\n"), count);
        }
    }
    m_images.clear();

    for (auto name : m_fileNames)
    {
        CPath path;
        path.Combine(m_dirPath, name);
        HyRead::PngImage image(path);
        image.EraseLogo(m_newLogo);
        image.CutEdge(margin);
        image.Save();
        ++count;
        if (count % 20 == 0)
        {
            _tprintf(_T("    ...%lu files done!\n"), count);
        }
    }

    _tprintf(_T("    Total %lu files done!\n"), count);
}
