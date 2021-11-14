#pragma once

#ifndef CLIPBOARD_URL_LOGGER_CLIPBOARDURLWATCHER_H
#    define CLIPBOARD_URL_LOGGER_CLIPBOARDURLWATCHER_H

#include <QClipboard>
#include <QLoggingCategory>

class ClipboardUrlWatcher : public QObject {
    Q_OBJECT // NOLINT parameter names s and c are too short

public:
    explicit ClipboardUrlWatcher(QObject* parent = nullptr);

public slots:  // NOLINT redundant access specifier
    void onChanged(QClipboard::Mode mode);

    void pause();
    void resume();

signals:
    void urlCopied(const QUrl& url);

private:
    bool paused;
};

Q_DECLARE_LOGGING_CATEGORY(clipboardWatcher)

#endif // CLIPBOARD_URL_LOGGER_CLIPBOARDURLWATCHER_H
