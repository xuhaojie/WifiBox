/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtAndroidExtras module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "notificationclient.h"
#if defined(Q_OS_ANDROID)
    #include <QtAndroidExtras/QAndroidJniObject>
#endif
NotificationClient::NotificationClient(QObject *parent)
    : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateAndroidNotification()));
}

void NotificationClient::setNotification(const QString &notification)
{
    if (m_notification == notification)
        return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

void NotificationClient::updateAndroidNotification()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(m_notification);
    QAndroidJniObject::callStaticMethod<void>("com/autopard/dashboard/notification/NotificationClient",
                                       "notify",
                                       "(Ljava/lang/String;)V",
                                       javaNotification.object<jstring>());
#endif
}

void NotificationClient::navi(int index)
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>("com/autopard/dashboard/notification/NotificationClient",
                                       "navi",
                                       "(I)V",
                                       index);
#endif
}

void NotificationClient::callIntent(QString action, QString url)
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject javaAction = QAndroidJniObject::fromString(action);
    QAndroidJniObject javaUrl = QAndroidJniObject::fromString(url);
    QAndroidJniObject::callStaticMethod<void>("com/autopard/dashboard/notification/NotificationClient",
                                       "callIntent",
                                       "(Ljava/lang/String;Ljava/lang/String;)V",
                                       javaAction.object<jstring>(),
                                       javaUrl.object<jstring>());
#endif


}

void NotificationClient::launchApp(QString packageName){
#if defined(Q_OS_ANDROID)
    QAndroidJniObject javaPackageName = QAndroidJniObject::fromString(packageName);
    QAndroidJniObject::callStaticMethod<void>("com/autopard/dashboard/notification/NotificationClient",
                                       "doStartApplicationWithPackageName",
                                       "(Ljava/lang/String;)V",
                                       javaPackageName.object<jstring>());
#endif
}

