#include "clipboardurllogger.h"

#include <QApplication>
#include <QDateTime>
#include <QPlainTextEdit>

Q_LOGGING_CATEGORY(clipboardLogger, "clipboard.url.logger")

ClipboardUrlLogger::ClipboardUrlLogger(QPlainTextEdit &editor, QObject *parent) : QObject(parent), editor(editor), paused(false) { }

void ClipboardUrlLogger::pause()
{
    paused = true;
}

void ClipboardUrlLogger::resume()
{
    paused = false;
}

void ClipboardUrlLogger::onChanged(QClipboard::Mode mode)
{
    if (paused) {
        return;
    }

    auto maybeUrl = QUrl::fromUserInput(QApplication::clipboard()->text(mode));
    if (maybeUrl.isValid()) {
        editor.appendPlainText(
                QString("%1 %2").arg(QDateTime::currentDateTime().toString(Qt::ISODate), maybeUrl.toString()));
    }
}
