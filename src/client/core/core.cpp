#include <core/core.hpp>
#include <utils/format/format.hpp>

utils::hook::detour get_tickets_hook;
std::int64_t get_tickets()
{
	//PRINT_INFO("0x1%0x", _ReturnAddress());
	return 5i64;
}

utils::hook::detour sub_14006ED20_hook;
std::int64_t sub_14006ED20(std::int64_t a1)
{
	//Tell the game that we are allowed to play with our fake 5 tickets
	return 2i64;
}

utils::hook::detour login_auth_hook;
void login_auth()
{
	PRINT_INFO("0x1%0x", _ReturnAddress());
}

utils::hook::detour sub_140043500_hook;
void sub_140043500(std::int64_t a1, unsigned int a2, int a3, int a4, std::int64_t a5, char* a6)
{
	PRINT_ERROR("%s (0x1%0x)", a6, _ReturnAddress());
	//sub_140043500_hook.invoke<void>(a1, a2, a3, a4, a5, a6);
}

void core::init()
{
	utils::hook::nop(0x1400337E8, 6);
	utils::hook::nop(0x1400338AF, 6);

	//Prevent streaming crash
	utils::hook::jump(0x140097E0F, 0x140097eb8);

	get_tickets_hook.create(0x14006E7F0, &get_tickets);
	sub_14006ED20_hook.create(0x14006ED20, &sub_14006ED20);
	sub_140043500_hook.create(0x140043500, &sub_140043500);
	login_auth_hook.create(0x140057490, &login_auth);

	//Make game say free play rather than ticket for smugness
	utils::hook::write_bytes(0x140336BA8, { 0x46, 0x52, 0x45, 0x45, 0x20, 0x50, 0x4C, 0x41, 0x59, 0x00, 0x00, 0x00 });
}