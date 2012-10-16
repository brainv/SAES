/**
 * @file CheckImageFile.cxx
 * @brief Body class check image file
 * @date 29/06/2012
 * @author Yadickson Soto
 */

#include "CheckImageFile.hxx"
#include <System/IO/Path.h>
#include <System/Runtime/ProcessLauncher.h>

using namespace Smartmatic::Graphics::Image;
using namespace Smartmatic::System::IO;
using namespace Smartmatic::System::Runtime;

CheckImageFile::CheckImageFile()
{
}

CheckImageFile::~CheckImageFile()
{
}

bool CheckImageFile::check(std::string file)
{
    bool validate = false;
    std::string extension = Path::GetFileExtension(file);
    
    if (extension == ".png" || extension == ".PNG")
    {
        std::string command = "pngcheck ";
        command += file;
        validate = (ProcessLauncher::RunProcessThroughSystem(command)) == 0;
    }
    
    return validate;
}
