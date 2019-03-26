#include <boost/program_options.hpp>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include "../utils/memoryManage_declare.h"
#include "../journal/journal.h"
#include "../log/MM_Log.h"
#include "../journal/Frame.hpp"
#include "../journal/PageHeader.h"
#include "../utils/Timer.h"
#include "../journal/Page.h"
#include "../journal/PageProvider.h"
#include "../journal/JournalWriter.h"

#include "../paged/PageEngine.h"
#include "../../system/systemConfig/sys_messages.h"

#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sstream>

using namespace boost::program_options;
USING_MM_NAMESPACE
using namespace log4cplus;

using std::cout;
using std::endl;

struct TestData
{
	int id;
	char content[256];
};

int main(int argc, const char* argv[])
{
	/*
	LogPtr logger = optionHedge::memoryManage::Log::getLogger("logfile");
	OPTIONHEDGE_LOG_ERROR(logger, "this is the testing string");
	const char time_format[] = "%Y-%m-%d %H:%M:%S";
	cout << "Current time is " << parseNano(getNanoTime(), time_format) << endl;*/

	
	string dir = "/var/tmp";
	string jname = "testingJournal";
	string clientName = "testingClient1";

	std::stringstream ss;

	TestData *td = new TestData();
	

	JournalWriterPtr writer = JournalWriter::create(dir, jname, clientName);

	for (int i = 0; i < 520000; i++)
	{
		td->id = i;
		ss << "testing data num is: " << i;
		strcpy(td->content,ss.str().c_str());
		ss.clear();
		ss.str("");
		writer->write_frame(td, sizeof(TestData), 1, MSG_TYPE_SUBSCRIBE_MARKET_DATA, false, -1);
	}

	return 0;
}
