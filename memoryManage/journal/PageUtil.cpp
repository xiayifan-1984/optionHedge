#include "PageUtil.h"
#include "PageHeader.h"

#include <sys/mman.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

USING_MM_NAMESPACE

string PageUtil::GenPageFileName(const string& jname, short pageNum)
{
	return JOURNAL_PREFIX + "." + jname + "." + std::to_string(pageNum) + "." + JOURNAL_SUFFIX;
}