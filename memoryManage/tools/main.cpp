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

	
	string dir = "/var/tmp";
	string jname = "testingJournal";
	int serviceIdx = 1;
	long startnano = getNanoTime();
	PageProviderPtr provider = PageProviderPtr(new LocalPageProvider(true));
	PageProviderPtr readProvider = PageProviderPtr(new LocalPageProvider(false));
	JournalPtr journal = Journal::create(dir, jname, serviceIdx, provider);
	JournalPtr journalReader = Journal::create(dir, jname, serviceIdx, readProvider);
	journal->seekTime(TIME_TO_LAST);
	journalReader->seekTime(startnano);

	TestData *td=new TestData();
	td->id = 12;
	strcpy(td->content, "testing string3");
	
	void* buffer = journal->locateFrame();
	cout << "buffer address for the first time is " << buffer << endl;
	Frame frame(buffer);
	frame.setSource(1);
	frame.setLastFlag(false);
	frame.setRequestId(1001);
	frame.setErrorData(0, 0, td, sizeof(TestData));
	frame.setExtraNano(0);
	long nano = getNanoTime();
	frame.setNano(nano);
	cout << "nano time set for the first time is " << nano << endl;
	frame.setStatusWritten();
	journal->passFrame();
	
	buffer = journal->locateFrame();
	cout << "buffer address for the second time is " << buffer << endl;
	strcpy(td->content, "testing string4");
	Frame frame1(buffer);
	frame1.setSource(1);
	frame1.setLastFlag(false);
	frame1.setRequestId(1001);
	frame1.setErrorData(0, 0, td, sizeof(TestData));
	frame1.setExtraNano(0);
	nano = getNanoTime();
	frame1.setNano(nano);
	cout << "nano time set for the second time is " << nano << endl;
	frame1.setStatusWritten();
	journal->passFrame();
//	journal->loadNextPage();

	void* frameadd = journalReader->locateFrame();
	Frame rf(frameadd);

	TestData* td1 = (TestData*)rf.getData();
	cout << "content for the first frame is " << td1->content << endl;

	journalReader->passFrame();
	frameadd = journalReader->locateFrame();
	
	Frame rf1(frameadd);
	td1 = (TestData*)rf1.getData();
	cout << "content for the second frame is " << td1->content << endl;
	journalReader->passFrame();
	return 0;
}
