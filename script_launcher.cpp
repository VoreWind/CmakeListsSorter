#include "script_launcher.h"

#include <QString>
#include <QDir>
#include <QProcess>

void ScriptLauncher::LaunchCmakeFormatScript(const QString &base_dir)
{
    QDir::setCurrent(base_dir);
    QProcess * exec =new QProcess();
    exec->execute("./ci/helpers/apply-cmake-format.sh");
}
