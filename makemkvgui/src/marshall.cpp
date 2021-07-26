/*
    MakeMKV GUI - Graphics user interface application for MakeMKV

    Copyright (C) 2007-2021 GuinpinSoft inc <makemkvgui@makemkv.com>

    You may use this file in accordance with the end user license
    agreement provided with the Software. For licensing terms and
    conditions see License.txt

    This Software is distributed on an "AS IS" basis, WITHOUT WARRANTY
    OF ANY KIND, either express or implied. See the License.txt for
    the specific language governing rights and limitations.

*/
#include <lgpl/aproxy.h>
#include <strings.h>

void CApClient::SignalExit()
{
    ExecCmd(apCallSignalExit,0,0);
    m_mem->flags |= (AP_SHMEM_FLAG_EXIT | 1);
}

void CApClient::CancelAllJobs()
{
    ExecCmd(apCallCancelAllJobs,0,0);
}

void CApClient::OnIdle()
{
    ExecCmd(apCallOnIdle,0,0);
}

bool CApClient::UpdateAvailableDrives(uint32_t Flags)
{
    m_mem->args[0]=Flags;
    ExecCmd(apCallUpdateAvailableDrives,1,0);
    return (m_mem->args[0]!=0);
}

bool CApClient::CloseDisk(unsigned int EjectId)
{
    m_mem->args[0]=EjectId;
    ExecCmd(apCallCloseDisk,1,0);
    return (m_mem->args[0]!=0);
}

int CApClient::GetSettingInt(ApSettingId Id)
{
    m_mem->args[0]=Id;
    ExecCmd(apCallGetSettingInt,1,0);
    return (int)(m_mem->args[0]);
}

const char* CApClient::GetSettingString(ApSettingId Id)
{
    m_mem->args[0]=Id;
    ExecCmd(apCallGetSettingString,1,0);
    if (0==m_mem->args[0]) return NULL;
    return (char*)(m_mem->strbuf);
}

void CApClient::SetSettingInt(ApSettingId Id,int Value)
{
    m_mem->args[0]=Id;
    m_mem->args[1]=Value;
    ExecCmd(apCallSetSettingInt,2,0);
}

void CApClient::SetSettingString(ApSettingId Id, const utf8_t* Value)
{
    SetSettingString(Id, SetUtf8(Value));
}

void CApClient::SetSettingString(ApSettingId Id, const utf16_t* Value)
{
    SetSettingString(Id, SetUtf16(Value));
}

void CApClient::SetSettingString(ApSettingId Id, size_t ValueSize)
{
    m_mem->args[0]=Id;
    if (0 == ValueSize)
    {
        m_mem->args[1]=0;
    } else {
        m_mem->args[1]=1;
    }
    ExecCmd(apCallSetSettingString,2,ValueSize);
}

bool CApClient::SaveSettings()
{
    ExecCmd(apCallSaveSettings,0,0);
    return (m_mem->args[0]!=0);
}

const char* CApClient::GetAppString(unsigned int Id,unsigned int Index1,unsigned int Index2)
{
    if (m_shutdown) return "";
    m_mem->args[0] = Id;
    m_mem->args[1] = Index1;
    m_mem->args[2] = Index2;
    ExecCmd(apCallAppGetString,3,0);
    if (m_mem->args[0]==0)
    {
        return NULL;
    } else {
        return (char*)m_mem->strbuf;
    }
}

