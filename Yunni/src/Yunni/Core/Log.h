#pragma once

#include "Core.h"


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Yunni {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define YN_CORE_TRACE(...)	::Yunni::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YN_CORE_INFO(...)	::Yunni::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YN_CORE_WARN(...)	::Yunni::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YN_CORE_ERROR(...)	::Yunni::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YN_CORE_FATAL(...)	::Yunni::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define YN_TRACE(...)		::Yunni::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YN_INFO(...)		::Yunni::Log::GetClientLogger()->info(__VA_ARGS__)
#define YN_WARN(...)		::Yunni::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YN_ERROR(...)		::Yunni::Log::GetClientLogger()->error(__VA_ARGS__)
#define YN_FATAL(...)		::Yunni::Log::GetClientLogger()->fatal(__VA_ARGS__)
