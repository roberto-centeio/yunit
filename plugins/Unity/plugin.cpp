/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Michał Sawicz <michal.sawicz@canonical.com>
 */

// Qt
#include <QtQml>
#include <QDBusConnection>

// self
#include "plugin.h"

// local
#include "preview.h"
#include "previewaction.h"
#include "previewinfohint.h"
#include "socialpreviewcomment.h"
#include "scope.h"
#include "scopes.h"
#include "categories.h"
#include "categoryfilter.h"
#include "bottombarvisibilitycommunicatorshell.h"
#include "launchermodel.h"

// libqtdee
#include "deelistmodel.h"

static const char* BOTTOM_BAR_VISIBILITY_COMMUNICATOR_DBUS_PATH = "/BottomBarVisibilityCommunicator";
static const char* DBUS_SERVICE = "com.canonical.Shell.BottomBarVisibilityCommunicator";

void UnityPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Unity"));
    qmlRegisterUncreatableType<Preview>(uri, 0, 1, "Preview", "Can't create Preview object in QML.");
    qmlRegisterUncreatableType<PreviewAction>(uri, 0, 1, "PreviewAction", "Can't create PreviewAction object in QML.");
    qmlRegisterUncreatableType<PreviewInfoHint>(uri, 0, 1, "PreviewInfoHint", "Can't create PreviewInfoHint object in QML.");
    qmlRegisterUncreatableType<SocialPreviewComment>(uri, 0, 1, "SocialPreviewComment", "Can't create SocialPreviewComment object in QML.");
    qmlRegisterType<Scope>(uri, 0, 1, "Scope");
    qmlRegisterType<Scopes>(uri, 0, 1, "Scopes");
    qmlRegisterType<Categories>(uri, 0, 1, "Categories");
    qmlRegisterType<CategoryFilter>(uri, 0, 1, "CategoryFilter");
    qmlRegisterType<DeeListModel>(uri, 0, 1, "DeeListModel");
    qmlRegisterType<LauncherModel>(uri, 0, 1, "LauncherModel");
    qmlRegisterUncreatableType<LauncherItem>(uri, 0, 1, "LauncherItem", "Can't create new Launcher Items in QML. Get them from the LauncherModel.");
    qmlRegisterUncreatableType<BottomBarVisibilityCommunicatorShell>(uri, 0, 1, "BottomBarVisibilityCommunicatorShell", "Can't create BottomBarVisibilityCommunicatorShell");
}

void UnityPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
#ifndef GLIB_VERSION_2_36
    g_type_init();
#endif

    QDBusConnection::sessionBus().registerService(DBUS_SERVICE);
    BottomBarVisibilityCommunicatorShell *bottomBarVisibilityCommunicator = &BottomBarVisibilityCommunicatorShell::instance();
    QDBusConnection::sessionBus().registerObject(BOTTOM_BAR_VISIBILITY_COMMUNICATOR_DBUS_PATH, bottomBarVisibilityCommunicator, QDBusConnection::ExportAllContents);
    engine->rootContext()->setContextProperty("bottomBarVisibilityCommunicatorShell", bottomBarVisibilityCommunicator);
}
