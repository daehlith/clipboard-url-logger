#include "clipboardurlwatcher.h"

#include <QApplication>
#include <QUrl>

Q_LOGGING_CATEGORY(clipboardWatcher, "clipboard.url.watcher")

ClipboardUrlWatcher::ClipboardUrlWatcher(QObject *parent) : QObject(parent), paused(false) { }

void ClipboardUrlWatcher::pause()
{
    paused = true;
}

void ClipboardUrlWatcher::resume()
{
    paused = false;
}

void ClipboardUrlWatcher::onChanged(QClipboard::Mode mode)
{
    if (paused) {
        return;
    }

    auto maybeUrl = QUrl::fromUserInput(QApplication::clipboard()->text(mode));
    if (maybeUrl.isValid()) {
        emit urlCopied(maybeUrl);
    }
}
