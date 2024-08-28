#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include <csignal>

#include "jsontreeview.h"

struct Options {
    QString configPath;
};

Options readCmdLineArgs(const QStringList &cmdLineArgs)
{
    // Settings cmd parser
    QCommandLineParser parser;

    const QCommandLineOption pathOption(QStringList() << "p"
                                                      << "path",
                                        "Path to json file", "path", "../data/example.json");

    const QCommandLineOption helpOption(QStringList() << "h"
                                                      << "help",
                                        "Prints help text and exit");

    parser.addOption(pathOption);
    parser.addOption(helpOption);
    parser.parse(cmdLineArgs);

    if (parser.isSet(helpOption)) {
        printf("%s\n", parser.helpText().toUtf8().data());
        exit(EXIT_SUCCESS);
    }

    Options opts;
    opts.configPath = parser.value(pathOption);
    return opts;
}

void quit(int)
{
    qApp->quit();
}

int main(int argc, char *argv[])
{
    std::signal(SIGINT, quit);
    std::signal(SIGTERM, quit);
    std::signal(SIGQUIT, quit);

    QApplication app(argc, argv);
    const auto &opts = readCmdLineArgs(app.arguments());
    JsonTreeView jsonTreeView(opts.configPath);
    jsonTreeView.show();
    return app.exec();
}
