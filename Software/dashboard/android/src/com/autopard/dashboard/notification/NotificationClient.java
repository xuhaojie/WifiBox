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

package com.autopard.dashboard.notification;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.pm.PackageManager;
//import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.ResolveInfo;
import android.content.ComponentName;
import android.content.Context;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import android.net.Uri;
import java.net.URISyntaxException;
import android.util.Log;
import com.autopard.dashboard.R;
import android.widget.Toast;

public class NotificationClient extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;

    public NotificationClient()
    {
        m_instance = this;
    }

    public static void notify(String s)
    {
        if (m_notificationManager == null) {
            m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
            m_builder = new Notification.Builder(m_instance);
	    m_builder.setSmallIcon(R.drawable.icon);
	    m_builder.setContentTitle("A message from Dashboard");
        }

        m_builder.setContentText(s);
        m_notificationManager.notify(1, m_builder.build());
    }


    public static void doStartApplicationWithPackageName(String packagename) {

    // 通过包名获取此APP详细信息，包括Activities、services、versioncode、name等等
    PackageInfo packageinfo = null;
    try {
	packageinfo = m_instance.getPackageManager().getPackageInfo(packagename, 0);
    } catch (Exception e) {
        e.printStackTrace();
    }
    if (packageinfo == null) {
	return;
    }

    // 创建一个类别为CATEGORY_LAUNCHER的该包名的Intent
    Intent resolveIntent = new Intent(Intent.ACTION_MAIN, null);
    resolveIntent.addCategory(Intent.CATEGORY_LAUNCHER);
    resolveIntent.setPackage(packageinfo.packageName);

    // 通过getPackageManager()的queryIntentActivities方法遍历
    List<ResolveInfo> resolveinfoList = m_instance.getPackageManager()
            .queryIntentActivities(resolveIntent, 0);

    ResolveInfo resolveinfo = resolveinfoList.iterator().next();
    if (resolveinfo != null) {
	// packagename = 参数packname
	String packageName = resolveinfo.activityInfo.packageName;
	// 这个就是我们要找的该APP的LAUNCHER的Activity[组织形式：packagename.mainActivityname]
	String className = resolveinfo.activityInfo.name;
	// LAUNCHER Intent
	Intent intent = new Intent(Intent.ACTION_MAIN);
	intent.addCategory(Intent.CATEGORY_LAUNCHER);

	// 设置ComponentName参数1:packagename参数2:MainActivity路径
	ComponentName cn = new ComponentName(packageName, className);

	intent.setComponent(cn);
	m_instance.startActivity(intent);
    }
}

    /*
    * 检查手机上是否安装了指定的软件
    * @param context
    * @param packageName：应用包名
    * @return
    */
    static public boolean isAvilible(Context context, String packageName){
       //获取packagemanager
       final PackageManager packageManager = context.getPackageManager();
     //获取所有已安装程序的包信息
       List<PackageInfo> packageInfos = packageManager.getInstalledPackages(0);
     //用于存储所有已安装程序的包名
       List<String> packageNames = new ArrayList<String>();
       //从pinfo中将包名字逐一取出，压入pName list中
       if(packageInfos != null){
	   for(int i = 0; i < packageInfos.size(); i++){
	       String packName = packageInfos.get(i).packageName;
	       packageNames.add(packName);
	   }
       }
     //判断packageNames中是否有目标程序的包名，有TRUE，没有FALSE
       return packageNames.contains(packageName);
    }

    static public void navi(int index){
        Log.i("Dashboard","enter navi");
	try {

	    if(index > 0){
                Log.i("Dashboard"," reandy call baidu");
		m_instance.callBaiduMap(m_instance.getBaseContext());
	    } else {
                Log.i("Dashboard"," reandy call gaode");
		m_instance.callGaodeMap(m_instance.getBaseContext());
	    }
	} catch (Exception e) {
            Log.e("Dashboard", e.getMessage());
	}
    }

    static public void callIntent(String action, String urlString){
        Log.i("Dashboard","callIntent width url:" + urlString);
	try {
	    Uri uri = Uri.parse(urlString);
	    Intent intent = new Intent(action, uri);
	    if(intent != null)
	    {
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
                Log.i("Dashboard","Before startActivity " + urlString);
		m_instance.startActivity(intent); //启动调用
	    }
            Log.i("Dashboard","After startActivity " + urlString);
	} catch (Exception e) {
            Log.e("Dashboard", e.getMessage());
	}
    }

    public void callBaiduMap(Context context){
	if(isAvilible(context,"com.baidu.BaiduMap")){//传入指定应用包名
	    try {

//		intent = Intent.getIntent("intent://map/direction?origin=latlng:34.264642646862,108.95108518068|name:我家&destination=大雁塔&mode=driving®ion=西安&src=yourCompanyName|yourAppName#Intent;scheme=bdapp;package=com.baidu.BaiduMap;end");
                //Intent intent = Intent.getIntent("intent://map/direction?origin=latlng:34.264642646862,108.95108518068|name:我家&destination=大雁塔&mode=driving®ion=西安&src=yourCompanyName|yourAppName#Intent;scheme=bdapp;package=com.baidu.BaiduMap;end");
                Intent intent = Intent.getIntent("baidumap://map/?");
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
		// 出行早知道
                //Intent intent = Intent.getIntent("baidumap://map/newsassistant");

/*
                intent = Intent.getIntent("intent://map/direction?" +
		    //"origin=latlng:"+"34.264642646862,108.95108518068&" +   //起点  此处不传值默认选择当前位置
		    "destination=latlng:"+location[0]+","+location[1]+"|name:我的目的地"+        //终点
		    "&mode=driving&" +          //导航路线方式
		    "region=北京" +           //
		    "&src=慧医#Intent;scheme=bdapp;package=com.baidu.BaiduMap;end");
*/
                Log.i("Dashboard","baidu context.startActivity(intent)");
		context.startActivity(intent); //启动调用
                Log.i("Dashboard","After startActivity");
	    } catch (URISyntaxException e) {
                Log.e("Dashboard", e.getMessage());
	    }
	} else {//未安装
	    //market为路径，id为包名
	    //显示手机上所有的market商店
            Log.i("Dashboard","baidumap not installed");
	    /*
	    Uri uri = Uri.parse("market://details?id=com.baidu.BaiduMap");
	    Intent intent = new Intent(Intent.ACTION_VIEW, uri);
	    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
	    context.startActivity(intent);
	    */
	}
    }

    public void callGaodeMap(Context context) {
	if (isAvilible(context, "com.autonavi.minimap")) {
	try{
	    //intent = Intent.getIntent("androidamap://navi?sourceApplication=慧医&poiname=我的目的地&lat="+location[0]+"&lon="+location[1]+"&dev=0");
	    Intent intent = Intent.getIntent("androidamap://navi?");
	    intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
            Log.i("Dashboard","gaode context.startActivity(intent)");
	    context.startActivity(intent);
	    } catch (URISyntaxException e) {
	        e.printStackTrace();
	    }
	}else{
            Log.i("Dashboard","gaodemap not installed");
            /*
	    Toast.makeText(context, "您尚未安装高德地图", Toast.LENGTH_LONG).show();
	    Uri uri = Uri.parse("market://details?id=com.autonavi.minimap");
	    intent = new Intent(Intent.ACTION_VIEW, uri);
	    context.startActivity(intent);
            */
        }
    }
/*
    public void callGoogleMap(Context context){
	if (isAvilible(context,"com.google.android.apps.maps")) {
	        Uri gmmIntentUri = Uri.parse("google.navigation:q="+location[0]+","+location[1] +", + Sydney +Australia");
		Intent mapIntent = new Intent(Intent.ACTION_VIEW, gmmIntentUri);
		mapIntent.setPackage("com.google.android.apps.maps");
		context.startActivity(mapIntent);
	}else {
	    Toast.makeText(context, "您尚未安装谷歌地图", Toast.LENGTH_LONG).show();
	    Uri uri = Uri.parse("market://details?id=com.google.android.apps.maps");
	    intent = new Intent(Intent.ACTION_VIEW, uri);
	    context.startActivity(intent);
	}
    }
*/
}
