#pragma once

#ifndef CLIPBOARD_URL_LOGGER_CLIPBOARDURLLOGGER_H
#    define CLIPBOARD_URL_LOGGER_CLIPBOARDURLLOGGER_H

#include <QClipboard>
#include <QLoggingCategory>

class QPlainTextEdit;

class ClipboardUrlLogger : public QObject {
    Q_OBJECT

public:
    explicit ClipboardUrlLogger(QPlainTextEdit& editor, QObject* parent = nullptr);

public slots:
    void onChanged(QClipboard::Mode mode);

    void pause();
    void resume();

private:
    QPlainTextEdit& editor;
    bool paused;
};

Q_DECLARE_LOGGING_CATEGORY(clipboardLogger)

#endif // CLIPBOARD_URL_LOGGER_CLIPBOARDURLLOGGER_H