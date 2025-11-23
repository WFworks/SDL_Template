#include "Application.h"
#include "SingleInstance.h"
#include <memory>
//#include <iostream>

int main(int argc, char** argv)
{
    SingleInstance instance;
    if (!instance.IsLocked()) {
        return 1;
    }
    //std::cout << "プログラムを起動しました。" << std::endl;
    
    std::unique_ptr<Application> app = std::make_unique<Application>();
    app->Execute();
    return 0;
}

