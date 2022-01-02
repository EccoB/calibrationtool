#include <ui/uimain.h>

#include <QApplication>
#include <QCommandLineParser>
#include "userstrings.h"


#ifdef TESTING
    #include <testing.h>
    #include <stdio.h>
    #include <iostream>
#endif


int main(int argc, char *argv[])
{
#ifdef TESTING
    std::cout<<"Testing"<<std::endl;
    std::cout<<"Test:"<<tst::checkIntrinsics()<<std::endl;
#endif




    QApplication a(argc, argv);
    UserStrings ustr;
    UImain w(ustr);
    w.show();
    //Parsing the command line arguments, an image can be provided that will be loaded automatically
    QCommandLineParser parser;
        parser.addHelpOption();
        parser.addPositionalArgument("PathToImage", "Path to the Image for calibration");
        parser.process(QCoreApplication::arguments());
        if (!parser.positionalArguments().isEmpty() && !w.loadFile(parser.positionalArguments().at(0))) {
            return -1;
        }






    return a.exec();
}
