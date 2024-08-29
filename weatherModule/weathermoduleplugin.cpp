#include "weathermoduleplugin.h"
#include "weathermodule.h"

#include <QtPlugin>

WeatherModulePlugin::WeatherModulePlugin(QObject *parent)
    : QObject(parent)
{}

void WeatherModulePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool WeatherModulePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *WeatherModulePlugin::createWidget(QWidget *parent)
{
    return new WeatherModule(parent);
}

QString WeatherModulePlugin::name() const
{
    return QLatin1String("WeatherModule");
}

QString WeatherModulePlugin::group() const
{
    return QLatin1String("Weather Module [user]");
}

QIcon WeatherModulePlugin::icon() const
{
    return QIcon();
}

QString WeatherModulePlugin::toolTip() const
{
    return QLatin1String("");
}

QString WeatherModulePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool WeatherModulePlugin::isContainer() const
{
    return false;
}

QString WeatherModulePlugin::domXml() const
{
    return QLatin1String(R"(<widget class="WeatherModule" name="weatherModule">
</widget>)");
}

QString WeatherModulePlugin::includeFile() const
{
    return QLatin1String("weathermodule.h");
}
