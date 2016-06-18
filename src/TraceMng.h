/*
 * TraceMng.h
 *
 */

#ifndef TRACEMNG_H_
#define TRACEMNG_H_

#include <iostream>
#include <sstream>
#include <memory>

//======== Dev Null

class NulStreambuf : public std::streambuf
{
	char                dummyBuffer[ 64 ];
protected:
	virtual int         overflow( int c )
	{
		setp( dummyBuffer, dummyBuffer + sizeof( dummyBuffer ) );
		return (c == traits_type::eof()) ? '\0' : c;
	}
};

class NulOStream : private NulStreambuf, public std::ostream
{

public:

	NulOStream() : std::ostream( this ) {}
	NulStreambuf* rdbuf() { return this; }

};

typedef NulOStream NullOut;

//======== Trace Output

class TraceOut {

public :

	TraceOut(std::ostream& os = std::cout) : m_os(os) { m_is_fatal = false ;}
	void setIsFatal(bool is_fatal) { m_is_fatal = is_fatal ; }
	void setTag(std::string tag) { m_tag = " ["+tag+"] "; }
	void insertTag() { m_os << m_tag  ; }

private :

	std::string m_tag;

public :

	std::ostream& m_os;
	bool m_is_fatal;

public :

	class Flux {
	public :
		Flux(std::ostream& os, bool &is_fatal) : f_os(os), f_is_fatal(is_fatal) {}

		//Flux() : f_os(f_os), f_is_fatal(f_is_fatal) {}

		~Flux()
		{
			f_os << std::endl;
			if ( f_is_fatal )
			{
				f_os << ">> STOP FATAL ERROR" << std::endl ;
				exit(1);
			}
		}

		std::ostream& f_os;
		bool& f_is_fatal;
	};
};

template <class T>
const std::shared_ptr<TraceOut::Flux>&
operator << (const std::shared_ptr<TraceOut::Flux>& flux, const T& t) {
	flux->f_os << t;
	return flux;
}

template<class T>
const std::shared_ptr<TraceOut::Flux>
operator << (TraceOut& trace, const T& t) {
	std::shared_ptr<TraceOut::Flux> pflux(new TraceOut::Flux(trace.m_os, trace.m_is_fatal));
	trace.insertTag();
	pflux << t;
	return pflux;
}

class TraceMng
{

private :

	NullOut  m_dev_null;

	TraceOut m_trace_null;
	TraceOut m_trace_info;
	TraceOut m_trace_debug;
	TraceOut m_trace_fatal;

public :

	TraceMng() :
		m_trace_null(m_dev_null),
		m_trace_info(std::cout),
		m_trace_debug(std::cout),
		m_trace_fatal(std::cout)
	{
		m_is_info  =  true;
		m_is_debug =  true;

		m_trace_null.setTag("DevNull");
		m_trace_info.setTag("Info ");
		m_trace_debug.setTag("Debug");
		m_trace_fatal.setTag("Fatal");
		m_trace_fatal.setIsFatal(true);
	}

public :

	void setIsInfo(bool is_info )   { m_is_info = is_info; }
	void setIsDebug(bool is_debug ) { m_is_debug = is_debug; }

private :

	bool m_is_info;
	bool m_is_debug;

public :

	TraceOut & info()  { if (m_is_info) return m_trace_info  ; else return m_trace_null;}
	TraceOut & debug() { if (m_is_debug) return m_trace_debug ; else return m_trace_null;}
	TraceOut & fatal() { return m_trace_fatal ; }
};

#endif /* TRACEMNG_H_ */
