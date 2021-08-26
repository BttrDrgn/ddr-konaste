#pragma once
#include <discord.h>

namespace nfsu2
{
	namespace game
	{
		enum class GameFlowState : std::uint8_t
		{
			None,
			LoadingFrontend,
			UnloadingFrontend,
			InFrontend,
			LoadingRegion,
			LoadingTrack,
			Racing,
			UnloadingTrack,
			UnloadingRegion,
			ExitDemoDisc,
		};

		static const auto& GameState = *reinterpret_cast<game::GameFlowState*>(0x008654A4);

		static const auto& CallbackPhase = *reinterpret_cast<std::uint32_t*>(0x008654A0);
		static const auto& CallbackText = *reinterpret_cast<const char**>(0x0086549C);

		static const auto& WindowHeight = *reinterpret_cast<std::uint32_t*>(0x00870984);
		static const auto& WindowWidth = *reinterpret_cast<std::uint32_t*>(0x00870980);


		struct bVector4
		{
			float x, y, z, w;
		};

		struct bVector3
		{
			float x, y, z, w;
		};

		struct bVector2
		{
			float x, y;
		};

		struct FEMouseInfo
		{
			std::int16_t x, y;
			char unk[2];
			std::uint8_t button;
			//Every below is wrong
			char unk_0[5];
			std::uint32_t time_lmdown;
			std::uint32_t time_rmdown;
			char unk_2[5];
			bool is_moving;
		};

		struct Rigidbody
		{
			std::uint32_t* unk0;
			std::uint32_t* unk1;

			const char* type0;

			std::uint8_t* unkBytes[2];
			std::uint32_t* unk2;
			std::uint32_t* unk3;

			bVector3 position;

			float unk5;

			bVector4 rotation;

			bVector3 angular_force;

			bVector3 inertia_tensor;

			std::uint32_t unk6[3];

			float unk_angular_force;

			float unk_static_float;
			float unk7;

			bVector3 linear_velocity;

			float unk8;

			bVector3 angular_velocity;
		};

		struct Car
		{
			std::uint32_t* vtable0;

			std::uint32_t* unk0;
			std::uint32_t* unk1;

			std::uint32_t* vtable1;

			const char* type0;

			Rigidbody* rigid;
		};

		struct DriverInfo
		{
			char data[2368];
		};

		struct RideInfo
		{
			char data[2304];
		};

		struct LoadedRideInfo
		{
			char data[4672];
		};

		struct bList
		{
			void* next;
			void* prev;
		};

		struct bChunk
		{
			std::uint32_t id;
			std::uint32_t size;
		};

		struct UIOptionsScreen
		{
			unsigned int unk;
			unsigned int unk_1;
			char data[32];
			char data_1[212];
			bVector2 unk_2;
			char data_2[8];
			bVector2 unk_3;
			bVector2 unk_4;
			bVector2 unk_5;
			char data_3[4];
			char data_4[38];
			bool unk_6;
			char data_5[5];
			unsigned int* FEButtonWidgetThing;
			unsigned int unk_7;
		};

		struct UIPauseOptions
		{
			char data[84];
		};

		struct FEStatWidget
		{
			std::uint32_t* vtable;
			bVector2 unk;
			bVector2 unk_0;
			bVector2 unk_1;
			float unk_2;
			float unk_3;
			float unk_4;
			bool unk_5;
			bool unk_7;
			bool unk_8;
			bool unk_9;
			std::uint32_t unk_10;
			std::uint32_t unk_11;
			float unk_12;
			float unk_13;
			float unk_14;
			float unk_15;
			float unk_16;
			float unk_17;
		};

		struct FEToggleWidget : public FEStatWidget
		{
			std::uint32_t unk;
			std::uint32_t unk_0;
		};


		static auto& player = *reinterpret_cast<Car**>(0x0089CDA8);

		void init();

	}
}
