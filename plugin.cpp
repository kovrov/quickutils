#include "plugin.h"
#include "timecomponent.h"

#include <qqml.h>

void QuickutilsPlugin::registerTypes(const char *uri)
{
    // @uri utils.time
    qmlRegisterType<Time>(uri, 1, 0, "Time");
}
