#include "PageSocketHandler.h"
#include "../utils/Timer.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/mutex.hpp>

USING_MM_NAMESPACE

using namespace boost::asio;

boost::array<char, SOCKET_MESSAGE_MAX_LENGTH> _data;
boost::shared_ptr<boost::asio::local::stream_protocol::acceptor> _acceptor;
boost::shared_ptr<local::stream_protocol::socket> _socket;
boost::shared_ptr<io_service> _io;
boost::shared_ptr<PageSocketHandler> PageSocketHandler::m_ptr = boost::shared_ptr<PageSocketHandler>(nullptr);

PageSocketHandler::PageSocketHandler() :io_running(false)
{

}

PageSocketHandler* PageSocketHandler::getInstance()
{
	if (m_ptr.get() == nullptr)
	{
		m_ptr = boost::shared_ptr<PageSocketHandler>(new PageSocketHandler());
	}
	return m_ptr.get();
}

void PageSocketHandler::run(IPageSocketUtil* _util)
{
	util = _util;
	logger = util->get_logger();
	_io.reset(new io_service());
	_acceptor.reset(new local::stream_protocol::acceptor(*_io,local::stream_protocol::endpoint(PAGED_SOCKET_FILE)));
	_socket.reset(new local::stream_protocol::socket(*_io));

	_acceptor->async_accept(*_socket, boost::bind(&PageSocketHandler::handle_accept, this));
	io_running = true;
	_io->run();
}

bool PageSocketHandler::is_running()
{
	return io_running;
}

void PageSocketHandler::stop()
{
	if (_io.get() != nullptr)
	{
		_io->stop();
	}

	if (_socket.get() != nullptr)
	{
		_socket->close();
	}

	if (_acceptor.get() != nullptr)
	{
		_acceptor->close();
	}

	io_running = false;
}

void PageSocketHandler::handle_accept()
{
	_socket->read_some(buffer(_data));
	util->acquire_mutex();
	process_msg();
	util->release_mutex();
	_socket.reset(new local::stream_protocol::socket(*_io));

	_acceptor->async_accept(*_socket, boost::bind(&PageSocketHandler::handle_accept,this));
}

void PageSocketHandler::process_msg()
{
	PagedSocketRequest* req = (PagedSocketRequest*)&_data[0];
	byte req_type = req->type;
	OPTIONHEDGE_LOG_INFO(logger, "[socket] (status)" << (short)req_type << " ");

	switch (req_type)
	{
		case PAGED_SOCKET_JOURNAL_REGISTER:
		{
			int idx = util->reg_journal(req->name);
			PagedSocketRspJournal rsp = {};
			rsp.type = req_type;
			rsp.success = idx >= 0;
			rsp.comm_idx = idx;
			memcpy(&_data[0], &rsp, sizeof(rsp));
			break;
		}
		case PAGED_SOCKET_READER_REGISTER:
		case PAGED_SOCKET_WRITER_REGISTER:
		{
			string comm_file;
			int file_size;
			bool ret = util->reg_client(comm_file,file_size,req->name,req->pid,req_type==PAGED_SOCKET_WRITER_REGISTER);
			PagedSocketRspClient rsp = {};
			rsp.type = req_type;
			rsp.success = ret;
			rsp.file_size = file_size;
			memcpy(rsp.comm_file, comm_file.c_str(), comm_file.length()+1);
			memcpy(&_data[0], &rsp, sizeof(rsp));
			break;
		}
	}

	write(*_socket, buffer(_data));
}