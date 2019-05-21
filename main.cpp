#include <QCoreApplication>

#include <QCommandLineParser>
#include <QDir>
#include <QDirIterator>
#include <QFile>

#include <QDebug>

#include <script_launcher.h>
#include <string_reorganizer.h>

static const QString kDefaultDirPath =
    "/home/jenkins/Repos/mca/ca_infrastructure";
static const QString kNameFilter = "txt";

static const QString kLDebugFilepath =
    "/home/jenkins/Repos/mca/ca_infrastructure/subsystems/client_cryptography/"
    "CMakeLists.txt";

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QString lookup_directory = kDefaultDirPath;

  QCommandLineParser parser;
  parser.setApplicationDescription(
      "Sorter of the likn lists of CMakeLists.txt");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument(
      "source", QCoreApplication::translate(
                    "main", "Source directory to be recursively scanned."));

  QCommandLineOption format_drectory_option(
      QStringList() << "f"
                    << "format-directory",
      QCoreApplication::translate(
          "main", "<directory> from which cmake-format is launched"),
      QCoreApplication::translate("main", "directory"));
  parser.addOption(format_drectory_option);

  parser.process(a);

  const QStringList args = parser.positionalArguments();
  QString cmake_format_dir = parser.value(format_drectory_option);

  if (!args.isEmpty()) {
    lookup_directory = args.at(0);
  }

  QDirIterator dir_it(lookup_directory, QDirIterator::Subdirectories);
  while (dir_it.hasNext()) {
    dir_it.next();
    if (QFileInfo(dir_it.filePath()).isFile()) {
      if (QFileInfo(dir_it.filePath()).suffix() == kNameFilter) {
        QFile cmake_file(dir_it.filePath());
        StringReorganizer::SortArgumentsInFile(cmake_file);
      }
    }
  }

  if (!cmake_format_dir.isEmpty()) {
      ScriptLauncher::LaunchCmakeFormatScript(cmake_format_dir);
  }
  qDebug()<<"Done!";
  return a.exec();
}
