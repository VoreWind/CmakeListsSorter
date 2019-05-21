#include "string_reorganizer.h"

#include <QFile>
#include <QRegExp>
#include <QString>
#include <QStringList>

static const QString kLinkWithText = "LINK_WITH ";

void StringReorganizer::SortArgumentsInFile(QFile &source_file) {
  source_file.open(QIODevice::ReadOnly);
  QByteArray file_text = source_file.readAll();
  source_file.close();

  QString sortable_string = FindSortableString(file_text);

  QString sorted_string = ReorganizeString(sortable_string);

  if (!sorted_string.isEmpty()) {
    file_text.replace(sortable_string.toLatin1(), sorted_string.toLatin1());
    source_file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    source_file.write(file_text);
    source_file.close();
  }
}

QString StringReorganizer::ReorganizeString(const QString &source_string) {
  if (source_string.contains("\"")) {
    return "";
  }
  QStringList sortable_list = source_string.split("\n");
  if (sortable_list.count() == 1) {
    return "";
  }
  qint32 spaces_amount = sortable_list.at(1).count(" ");
  sortable_list = sortable_list.replaceInStrings(" ", "");
  sortable_list.sort();

  QString padding;
  padding = padding.leftJustified(spaces_amount, ' ');
  QString sorted_string = sortable_list.join("\n"+padding);
  if (sorted_string == source_string) {
    return "";
  }
  return sorted_string;
}

QString StringReorganizer::FindSortableString(const QString &source_string) {
  int link_with_position = source_string.indexOf(kLinkWithText);
  if (link_with_position == -1) {
    return "";
  }
  int closing_brace_position = source_string.indexOf(")", link_with_position);
  int sorting_list_position = link_with_position + kLinkWithText.size();
  QString sortable_string = source_string.mid(
      sorting_list_position, closing_brace_position - sorting_list_position);

  return sortable_string;
}
