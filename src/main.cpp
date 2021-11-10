#include "clipboardurllogger.h"

#include <QApplication>
#include <QMenu>
#include <QPlainTextEdit>

int main(int argc, char **argv) {
    QApplication theApp(argc, argv);

    QPlainTextEdit edit;
    edit.show();

    auto *clipboard = QApplication::clipboard();

    ClipboardUrlLogger logger(edit);
    QClipboard::connect(clipboard, &QClipboard::changed, &logger, &ClipboardUrlLogger::onChanged);

    return QApplication::exec();
}
