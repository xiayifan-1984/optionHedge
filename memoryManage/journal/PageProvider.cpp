#include "PageProvider.h"
#include "PageUtil.h"
#include "Page.h"

#include "boost/asio.hpp"
#include "boost/array.hpp"

USING_MM_NAMESPACE


LocalPageProvider::LocalPageProvider(bool isWriting, bool reviseAllowed)
{
	is_writer = isWriting;
	revise_allowed = is_writer || reviseAllowed;
}

PagePtr LocalPageProvider::getPage(const string &dir, const string &jname, int serviceIdx, short pageNum)
{
	return Page::load(dir, jname, pageNum, is_writer, false);
}

void LocalPageProvider::releasePage(void* buffer, int size, int serviceIdx)
{
	PageUtil::ReleasePageBuffer(buffer, size, false);
}