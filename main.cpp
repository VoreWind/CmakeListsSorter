#include <QCoreApplication>

#include <QDir>
#include <QDirIterator>
#include <QFile>

#include <stringreorganizer.h>

static const QString kDirPath = "/home/jenkins/Repos/mca/ca_infrastructure";
static const QString kNameFilter = "CMakeLists.txt";

static const QString kLDebugFilepath =
    "/home/jenkins/Repos/mca/ca_infrastructure/subsystems/client_cryptography/"
    "CMakeLists.txt";

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QDirIterator dir_it(kDirPath, QDirIterator::Subdirectories);
  while (dir_it.hasNext()) {
    dir_it.next();
    if (QFileInfo(dir_it.filePath()).isFile()) {
      if (QFileInfo(dir_it.filePath()).suffix() == "txt") {
        QFile cmake_file(dir_it.filePath());
        StringReorganizer::SortArgumentsInFile(cmake_file);
      }
    }
  }

  return a.exec();
}
