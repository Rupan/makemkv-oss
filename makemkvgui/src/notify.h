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
#ifndef APP_NOTIFY_H
#define APP_NOTIFY_H

void notifyInit();
void notifyStart(QMainWindow* mainWindow,unsigned long Id,const QString &Name);
void notifyUpdate(QMainWindow* mainWindow,unsigned int Value,unsigned int MaxValue,unsigned int TimeElapsed);
void notifyEvent(QMainWindow* mainWindow,unsigned long Id,const QString &Text,const QString &Name);
void notifyEvent(QMainWindow* mainWindow,unsigned long Id,const char* IdName,const QString &Text,const QString &Name);
void notifyFinish(QMainWindow* mainWindow);
void notifyCleanup();

void desktopShowFile(const QString &FileName);

#endif // APP_NOTIFY_H
