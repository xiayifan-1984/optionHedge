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


#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

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

	/*
	string dir = "/var/tmp";
	string jname = "testingJournal";
	int serviceIdx = 1;
	PageProviderPtr provider = PageProviderPtr(new LocalPageProvider(false));
	JournalPtr journal = Journal::create(dir, jname, serviceIdx, provider);
	JournalPtr journal1 = Journal::create(dir, jname, serviceIdx, provider);
	journal->seekTime(TIME_TO_LAST);
	journal1->seekTime(TIME_TO_LAST);
	cout << "Journal1's address is " << journal << endl;
	cout << "Journal2's address is " << journal1 << endl;

	cout << "Journal1's page address is " << journal->getShortName() << endl;
	cout << "Journal2's page address is " << journal1->getShortName() << endl;
	*/

	/*
	JournalPtr journal = Journal::create(dir, jname, serviceIdx, provider);
	journal->seekTime(TIME_TO_LAST);
	TestData *td=new TestData();
	td->id = 12;
	strcpy(td->content, "testing string");
	
	void* buffer = journal->locateFrame();
	Frame frame(buffer);
	frame.setSource(1);
	frame.setLastFlag(false);
	frame.setRequestId(1001);
	frame.setErrorData(0, 0, td, sizeof(TestData));
	frame.setExtraNano(0);
	long nano = getNanoTime();
	frame.setNano(nano);
	frame.setStatusWritten();
	journal->passFrame();*/

	string dir = "/var/tmp/testingjournal.txt";
	int fd = open(dir.c_str(),(O_RDWR | O_CREAT), (mode_t)0600);
	void* buffer = mmap(0, 128, PROT_READ , MAP_SHARED, fd, 0);
	void* buffer1 = mmap(0, 128, PROT_READ, MAP_SHARED, fd, 0);

	cout << "buffer 1 is " << buffer << endl;
	cout << "buffer 2 is " << buffer1 << endl;
	return 0;
}
