#include <boost/program_options.hpp>
#include <iostream>
#include <algorithm>
#include "../utils/memoryManage_declare.h"
#include "../journal/journal.h"
#include "../log/MM_Log.h"
#include "../journal/Frame.hpp"

using namespace boost::program_options;
USING_MM_NAMESPACE
using namespace log4cplus;

using std::cout;
using std::endl;



int main(int argc, const char* argv[])
{
	/*
	LogPtr logger = optionHedge::memoryManage::Log::getLogger("logfile");
	OPTIONHEDGE_LOG_ERROR(logger, "this is the testing string");*/

	Frame* fm = new Frame(nullptr);
	return 0;
}