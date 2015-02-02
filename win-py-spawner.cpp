#include <Python.h>
#include <string>
#include <windows.h>
#include <iostream>

const char* PNAME = "pyexec-wrapper";

std::string get_exe_path()
{
    char name[2048];
    DWORD result =  GetModuleFileNameA(
        GetModuleHandle(NULL),
        name,
        sizeof(name));
    if (result == 0 ) {
        return "";
    } else {
        return std::string(name, result);
    }
}

std::string replace_suffix(std::string const& str, std::string const& current, std::string const& expected)
{
    if( str.size() < current.size() ) {
        return str;
    }
    if( str.substr(str.size()-current.size()) != current ) {
        std::cerr << PNAME << ": my name doesn't end with exe ... WTF! (" << str << ")\n";
        return str;
    }
    return str.substr(0, str.size()-current.size()) + expected;
}

int main(int argc, char** argv)
{
    PNAME = argv[0];
    Py_Initialize();
    Py_SetProgramName(argv[0]);
    PySys_SetArgvEx(argc, argv, 0);

    const std::string exe_path = get_exe_path();
    std::string py_path  = replace_suffix(exe_path, ".exe", ".pyc");
    if( access(py_path.c_str(), R_OK ) != 0 ) {
         py_path  = replace_suffix(exe_path, ".exe", ".py");
    }
    PyObject* PyFileObject = PyFile_FromString(const_cast<char*>(py_path.c_str()), "r");
    if( !PyFile_FromString ) 
    {
        std::cerr << PNAME << ": unable to open " << py_path << ": \n";
        PyErr_Print();
        Py_Finalize();
        return 2;
    }
    PyRun_SimpleFileEx(PyFile_AsFile(PyFileObject), const_cast<char*>(py_path.c_str()), 1);
    Py_Finalize();
    return 0;
}
