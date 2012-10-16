#include <string>
#include <sys/time.h>


class MyHelpers 
{
public:
    /**
    * Global function. Should be placed somewhere else rather than here... To be moved
    * on the next release.
    */

  static std::string getCurrentTime()  
  {
    timeval tim;
    gettimeofday(&tim, NULL);
	  const time_t lastTime = tim.tv_sec;
    struct tm * timeinfo = localtime( &lastTime );
    char buffer [96];
    strftime (buffer,96,"%d/%m/%Y %H:%M:%S,",timeinfo);
    char buffer2[96];
    sprintf(buffer2, "%.6d", (int)tim.tv_usec);
    return std::string(buffer) + std::string(buffer2);
  }

};

const std::string crappyHelp = "\nDuplicate vote finder\n\n\tUsage:\n\t\t-o <directory>\tSets the ouput directory for registering the votes. Default is \"./votelog\"\n\t\t-i <directory>\tLoad from <directory> previously processed votes\n\t\t-L \t\tStores scanned vote codes in a file along with a time stamp in <output directory>/voteCodeLog.log\n\t\t-D\t\tActivates the debug mode\n\t\t-v\t\tVerbose mode (on stderr)\n\t\t-h\t\tPrints this help\n";
