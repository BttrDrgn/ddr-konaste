#include <utils/file_system/file_system.hpp>
#include <utils/format/format.hpp>
#include <utils/hook/hook.hpp>
#include <utils/console/console.hpp>

namespace utils
{
	void file_system::init()
	{
		for (const auto path : { "ddr", "ddr\\logs\\",})
		{
			if (!file_system::exists(path))
			{
				file_system::create(path);
			}
		}
	}

	void file_system::make_file(const char* name, const char* contents)
	{
		std::ofstream File;
		File.open(name);
		if (strlen(contents) > 0) File << contents;
		File.close();
	}

	void file_system::append_file(const char* name, const char* contents)
	{
		if (exists(name) == true)
		{
			std::ofstream File;
			File.open(name, std::ios_base::app);
			File << contents;
			File.close();
		}
		else
		{
			return;
		}
	}

	void file_system::overwrite_file(const char* name, const char* contents)
	{
		if (file_system::exists(name) == true)
		{
			std::ofstream File;
			File.open(name);
			File << contents;
			File.close();
		}
		else
		{
			return;
		}
	}

	bool file_system::exists(const std::string& path)
	{
		return std::filesystem::exists(path);
	}

	void file_system::create(const std::string& path)
	{
		std::filesystem::create_directories(path);
	}

	std::string file_system::read_file(const std::string& file)
	{
		std::string data;
		read_file(file, &data);
		return data;
	}

	bool file_system::read_file(const std::string& file, std::string* data)
	{
		if (!data) return false;
		data->clear();

		if (file_system::exists(file))
		{
			std::ifstream stream(file, std::ios::binary);
			if (!stream.is_open()) return false;

			stream.seekg(0, std::ios::end);
			const std::streamsize size = stream.tellg();
			stream.seekg(0, std::ios::beg);

			if (size > -1)
			{
				data->resize(static_cast<uint32_t>(size));
				stream.read(const_cast<char*>(data->data()), size);
				stream.close();
				return true;
			}
		}

		return false;
	}

	int file_system::set_protocol_directory()
	{
		//Codes
		//0 = Success
		//1 = Key Already Exists
		//-1 = Error on first open
		//-2 = Error on second open

		char value[256];
		DWORD buf_size = 1024;
		RegGetValueA(HKEY_CLASSES_ROOT, "velo\\Shell\\Open\\Command\\", 0, RRF_RT_REG_SZ, 0, (PVOID)&value, &buf_size);

		if (std::strstr(value, "bootstrapper.exe") == NULL)
		{
			HKEY base;
			HKEY hkey_0;
			HKEY hkey_1;

			RegCreateKeyA(HKEY_CLASSES_ROOT, "velo\\Shell\\Open\\Command", &base);
			RegCloseKey(base);

			if (RegOpenKeyExA(HKEY_CLASSES_ROOT, "velo", 0, KEY_WRITE, &hkey_0) == ERROR_SUCCESS)
			{
				char value[] = "";
				RegSetValueExA(hkey_0, "URL protocol", 0, REG_SZ, (BYTE*)value, strlen(value));
				RegCloseKey(hkey_0);
			}
			else
			{
				return -1;
			}

			if (RegOpenKeyExA(HKEY_CLASSES_ROOT, "velo\\Shell\\Open\\Command", 0, KEY_WRITE, &hkey_1) == ERROR_SUCCESS)
			{
				std::string value = utils::format::va("\"%s\\bootstrapper.exe\" \"%s+%s\"", &std::filesystem::current_path().string()[0], "%1", &std::filesystem::current_path().string()[0]);
				RegSetValueExA(hkey_1, "", 0, REG_SZ, (BYTE*)&value[0], strlen(&value[0]));
				RegCloseKey(hkey_1);
			}
			else
			{
				return -2;
			}

			return 0;
		}
		else
		{
			return 1;
		}
		
	}

	/*
	std::string file_system::get_protocol_directory()
	{
		char value[256];
		DWORD buf_size = 1024;
		RegGetValueA(HKEY_CLASSES_ROOT, "velo\\Shell\\Open\\Command\\", 0, RRF_RT_REG_SZ, 0, (PVOID)&value, &buf_size);

		std::string temp_0 = utils::format::split(value, " ")[1];
		std::string temp_1 = utils::format::replace(utils::format::split(temp_0, "+")[1], "\"", "");

		if (!file_system::exists(utils::format::va("%s\\VELO\\GAME\\SPEED2.exe", &temp_1[0])))
		{
			MessageBoxA(nullptr, "The directory set by the protocol manager seems to have changed since the last time it was ran or has not been set yet.\nPlease go to the launcher settings and update your protocol directory!", "Velocity", 0);
			exit(0);
		}

		return temp_1;
	}
	*/
}
