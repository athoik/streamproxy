#ifndef _encoder_h_
#define _encoder_h_

#include "pidmap.h"
#include <string>
#include <pthread.h>

class Encoder
{
	private:

		enum
		{
			IOCTL_VUPLUS_SET_VPID			= 1,
			IOCTL_VUPLUS_SET_APID			= 2,
			IOCTL_VUPLUS_SET_PMTPID			= 3,
			IOCTL_VUPLUS_START_TRANSCODING	= 100,
			IOCTL_VUPLUS_STOP_TRANSCODING	= 200,
		};

		typedef enum
		{
			model_undef = 0,
			model_vuplus_solo2,
			model_vuplus_duo2,
			model_end
		} model_t;

		Encoder();
		Encoder(const Encoder &);

		pthread_t	start_thread;
		bool		start_thread_running;
		bool		start_thread_joined;
		bool		stopped;
		int			fd;
		int			id;
		PidMap		pids;
		model_t		model;

		static void* start_thread_function(void *);

	public:

		Encoder(const PidMap &, std::string frame_size,
				std::string bitrate, std::string profile,
				std::string level, std::string bframes)
				throw(std::string);
		~Encoder()												throw();

		std::string	getprop(std::string)				const	throw();
		void		setprop(std::string, std::string)	const	throw();

		bool		start_init()								throw();
		bool		start_finish()								throw();
		bool		stop()										throw();

		int			getfd()								const	throw();
		PidMap		getpids()							const	throw();
		std::string	model_id()							const	throw();
};

#endif
