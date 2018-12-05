#include <boost/program_options.hpp>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/consoleappender.h>

#include <iostream>
#include <algorithm>
#include "../utils/memoryManage_declare.h"
#include "../journal/journal.h"

using namespace boost::program_options;
USING_MM_NAMESPACE
using namespace log4cplus;

using std::cout;
using std::endl;

auto AddTest(int a, int b)
{
	return a + b;
}

int main(int argc, const char* argv[])
{
	SharedAppenderPtr _append(new FileAppender("Test.log"));
	_append->setName("file log test");

	/* step 4: Instantiate a logger object */
	Logger _logger = Logger::getInstance("test.subtestof_filelog");

	/* step 5: Attach the appender object to the logger */
	_logger.addAppender(_append);

	/* log activity */
	int i;
	for (i = 0; i < 5; ++i)
	{
		LOG4CPLUS_DEBUG(_logger, "Entering loop #" << i << "End line #");
	}
	return 0;
}