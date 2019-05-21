#ifndef STRING_REORGANIZER_H
#define STRING_REORGANIZER_H

#include <QString>

class QFile;

class StringReorganizer {
public:
  static void SortArgumentsInFile(QFile &source_file);
  static bool CheckArgumentsInFile(QFile &source_file);

private:
  static QString ReorganizeString(const QString &source_string);
  static QString FindSortableString(const QString &source_string);
  static QByteArray GetFileText(QFile &source_file);
};

#endif // STRING_REORGANIZER_H
