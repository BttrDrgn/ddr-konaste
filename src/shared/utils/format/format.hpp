#pragma once

namespace utils
{
	class format final
	{
		public:
			static std::string va(const char* fmt, ...);
			static std::string replace(const std::string& orig, const std::string& fnd, const std::string& repl);

			template<typename S> static auto stoi(const char* string, S default) -> S
			{
				char* end;

				const auto result = static_cast<S>(std::strtol(string, &end, 0));

				if (*string == '\0' || *end != '\0')
				{
					return default;
				}

				return result;
			}

	};
}
