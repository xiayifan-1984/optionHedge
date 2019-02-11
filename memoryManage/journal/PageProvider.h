﻿#ifndef MEMORYMANAGE_PAGEPROVIDER_H
#define MEMORYMANAGE_PAGEPROVIDER_H

#include "IPageProvider.h"
MM_NAMESPACE_START

class PageProvider :public IPageProvider
{
protected:
	bool is_writer;
	bool revise_allowed;

public:
	virtual int register_journal(const string& dir, const string& jname) { return -1; }
	virtual void exit_client() {}
	virtual bool isWriter() const { return is_writer; }
};

DECLARE_PTR(PageProvider);

/**
 * LocalPageProvider,
 * provide local page, no need to connect with service.
 */
class LocalPageProvider : public PageProvider
{
public:
	/** constructor */
	LocalPageProvider(bool isWriting, bool reviseAllowed = false);
	/** override IPageProvider */
	virtual PagePtr getPage(const string &dir, const string &jname, int serviceIdx, short pageNum);
	/** override IPageProvider */
	virtual void releasePage(void* buffer, int size, int serviceIdx);
};


MM_NAMESPACE_END
#endif
