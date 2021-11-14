#pragma once

#ifndef CLIPBOARD_URL_LOGGER_MAINWINDOW_H
#    define CLIPBOARD_URL_LOGGER_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow final : public QMainWindow
{
    Q_OBJECT // NOLINT

public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    MainWindow(const MainWindow&) = delete;
    MainWindow(const MainWindow&&) = delete;

    void operator=(const MainWindow&) = delete;
    void operator=(const MainWindow&&) = delete;

    ~MainWindow() final;

public slots: // NOLINT
    void onUrlCopied(const QUrl &url);

private:
    void connectSignals();
    void setupClipboardUrlWatcher();
    void setupModelAndView();

    Ui::MainWindow *ui;
};

#endif // CLIPBOARD_URL_LOGGER_MAINWINDOW_H
