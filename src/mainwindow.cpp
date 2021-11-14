#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QStandardItemModel>
#include <QUrl>

#include "clipboardurlwatcher.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    connectSignals();

    setupClipboardUrlWatcher();

    setupModelAndView();

}

void MainWindow::connectSignals()
{
    connect(ui->actionClose, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionQuit, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::onUrlCopied(const QUrl &url) {
    QList<QStandardItem*> logEntry;
    logEntry << new QStandardItem(QDateTime::currentDateTime().toString(Qt::ISODate));
    logEntry << new QStandardItem(url.toString(QUrl::FullyEncoded));
    qobject_cast<QStandardItemModel*>(ui->logView->model())->insertRow(0, logEntry);
}

void MainWindow::setupClipboardUrlWatcher()
{
    auto *clipboard = QApplication::clipboard();
    auto *clipboardWatcher = new ClipboardUrlWatcher(this);
    QClipboard::connect(clipboard, &QClipboard::changed, clipboardWatcher, &ClipboardUrlWatcher::onChanged);
    connect(clipboardWatcher, &ClipboardUrlWatcher::urlCopied, this, &MainWindow::onUrlCopied);
}
void MainWindow::setupModelAndView()
{
    auto *logItemModel = new QStandardItemModel(this);
    QStringList headers = { "Date", "URL" };
    logItemModel->setHorizontalHeaderLabels(headers);

    // insert some dummy data so that we get the date column properly sized
    QList<QStandardItem*> dummyData;
    dummyData << new QStandardItem(QDateTime::currentDateTime().toString(Qt::ISODate));
    dummyData << new QStandardItem("https://www.google.is");
    logItemModel->insertRow(0, dummyData);

    // Set up the view
    ui->logView->setModel(logItemModel);
    ui->logView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->logView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    // We don't want row numbers
    ui->logView->verticalHeader()->setVisible(false);
    ui->logView->resizeColumnToContents(0);
    ui->logView->horizontalHeader()->setSelectionMode(QAbstractItemView::NoSelection);
    ui->logView->horizontalHeader()->setStretchLastSection(true);

    // remove dummy data again now that we know how large the columns need to be
    logItemModel->removeRow(0);
}
MainWindow::~MainWindow() { delete ui; }
