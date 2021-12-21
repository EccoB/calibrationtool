#include "uimain.h"

#include <QApplication>
#include <QCommandLineParser>
#include "userstrings.h"

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    UserStrings ustr;
    UImain w(ustr);
    w.show();
    //Parsing the command line arguments
    QCommandLineParser parser;
        parser.addHelpOption();
        parser.addPositionalArgument("PathToImage", "Path to the Image for calibration");
        parser.process(QCoreApplication::arguments());
        if (!parser.positionalArguments().isEmpty() && !w.loadFile(parser.positionalArguments().first())) {
            return -1;
        }






    return a.exec();
}
