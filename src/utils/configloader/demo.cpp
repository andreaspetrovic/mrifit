
#include <stdio.h>
#include <iostream>
#include "loaders/t2fitgfconfigloader.h"
#include <loaders/datasetconfigloader.h>
#include "configs/lmconfig.h"
#include <qt4/QtCore/QResource>
#include <boost/python.hpp>
#include <qt4/QtCore/QFile>

#define MYOUT std::cout << "DEMO - Configloader: "
#define MYOUTRED(txt) MYOUT << "\033[1;31m"  << txt << "\033[0m" << std::endl
#define MYOUTYELLOW(txt) MYOUT << "\033[1;33m"  << txt << "\033[0m" << std::endl

using namespace mrifit;
namespace py = boost::python;

int main (int argc, const char* argv[])
{

    Q_INIT_RESOURCE(resources);
    // ==============================================================
    /// \todo this is just a test, remove this
    QFile f(":/xsd/basictypes.xsd");
    f.open(QIODevice::ReadOnly | QIODevice::Text);
        std::cout << "blabla: "<< std::endl;
        while (!f.atEnd()) {
            QByteArray line = f.readLine();
            std::cout << line.data();
        }
    // ==============================================================


    if (argc <= 1) {
        MYOUTRED("Not enough arguments! Aborting...") << std::endl;
        return(0);
    }


    cl::T2FitGFConfigLoader loader(argv[1]);
    cl::T2FitGFConfigLoader loader2(argv[1]);

    try
    {
        MYOUTYELLOW("Loading file " << argv[1]);
        loader.load();
    }
    catch (cl::LoaderException &l)
    {
        MYOUTRED("ERROR: " << l.what());
    }

    cl::LMConfig cfg = loader.getLMConfig();
    std::cout << "CFG: " << std::scientific << cfg.tolParam() << " " << cfg.tolGrad() << std::endl;
    std::cout << "CFG: " << std::fixed << cfg.tolParam() << " " << cfg.tolGrad() << std::endl;

   cl::DatasetConfigLoader dscl("../testdata/dataset.xml","../resources/dataset.xsd");
   dscl.load();
   std::cout << "DS: " << dscl.getDataSet().size() << std::endl;

   std::cout << "DS: " << dscl.getDataSet().at(0).size() << std::endl;

   for(int i=0; i<dscl.getDataSet().at(0).size(); i++)
   {
       std::cout << "FILE: " << i << " " << dscl.getDataSet().at(0).at(i) << std::endl;
   }

/*
 * // PYTHON TEST
   std::vector<double> v;
   v.push_back(1);
   v.push_back(2.12312312312e-12);

   Py_Initialize();

   try{
   py::object main_module = py::import("__main__");
   py::object main_namespace = main_module.attr("__dict__");
   py::exec_file("../../test.py",main_namespace);
   py::list l = py::list();
   l.append(v.at(0));
   l.append(v.at(1));
   main_namespace["passed"]= l;
   py::exec("print 'Hello world'", main_namespace);
   py::exec("bla('asdfasdfasdfasdf')", main_namespace);
   } catch (py::error_already_set const& er)
   {
       PyErr_Print();
   }
   */

}
