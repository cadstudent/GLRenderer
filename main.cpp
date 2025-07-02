#include <iostream>
#include "include/application.hpp"

using namespace std;


int main()
{
    Application app;
    app.Init();
    app.loadvsFile("../shader/vs.glsl");
    app.loadfsFile("../shader/fs.glsl");
    //app.loadmodel("../assets/backpack/backpack.obj");
    app.loadmodel("../assets/floor/floor.obj");
    app.loadmodel("../assets/mary/Marry.obj");
    app.Run();
   
}



